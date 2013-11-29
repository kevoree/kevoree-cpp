#include <kevoree-tools/DynamicLoader/DynamicLoader.h>


DynamicLoader::DynamicLoader(Bootstraper *bootstrap)
{
	this->bootstrap = bootstrap;	
}

bool DynamicLoader::register_instance(Instance *i)
{
	TypeDefinition *type = i->typeDefinition;
	if(type == NULL)
	{
		LOGGER_WRITE(Logger::ERROR,"There is no TypeDefinition define");
		return false;
	}
	if(type->deployUnits.size() == 0)
	{
		LOGGER_WRITE(Logger::WARNING,"There is no DeployUnit to register");
		return false;	
	}
	for (std::unordered_map<string,DeployUnit*>::iterator iterator = type->deployUnits.begin(), end = type->deployUnits.end(); iterator != end; ++iterator)
	{
			 DeployUnit *du  = iterator->second;
			// todo check if for me
			map<string, void*>::const_iterator it = deploysUnits.find(du->internalGetKey());
			if (it == deploysUnits.end())
			{
				string libpath=	bootstrap->resolveDeployUnit(du);
				if(!libpath.empty())
				{
					LOGGER_WRITE(Logger::DEBUG,"install_deploy_unit "+libpath);
					void *handler = soloader_load(libpath);
					deploysUnits[du->internalGetKey()] = handler;		
					return true;	
				}else
				{
					LOGGER_WRITE(Logger::ERROR,"The DeployUnit cannot be registred beacause the Typedefintion is not found "+libpath);	
					return false;	
				}	
			}
	}
}

AbstractTypeDefinition* DynamicLoader::create_instance(Instance *i)
{
	TypeDefinition *type = i->typeDefinition;
	if(type == NULL)
	{
		LOGGER_WRITE(Logger::ERROR,"There is no TypeDefinition define");
		return false;
	}
	if(type->deployUnits.size() == 0)
	{
		LOGGER_WRITE(Logger::WARNING,"There is no DeployUnit to register");
		return false;	
	}
	
	for (std::unordered_map<string,DeployUnit*>::iterator iterator = type->deployUnits.begin(), end = type->deployUnits.end(); iterator != end; ++iterator)
	{
		DeployUnit *du  = iterator->second;
		// todo check if for me
		map<string, void*>::const_iterator it = deploysUnits.find(du->internalGetKey());
		if (it == deploysUnits.end())
		{
			return NULL;
		}
		LOGGER_WRITE(Logger::DEBUG,"newInstance of "+du->name);
		void *instance = newInstance(it->second);
		instances[i->path()] = instance;
		return(AbstractTypeDefinition*)instance;
	}	
	
	return NULL;
}

bool DynamicLoader::unload_instance(Instance *i)
{
	if(instances.find(i->path()) != instances.end())
	{
		
		AbstractTypeDefinition *inst = (AbstractTypeDefinition*)instances.find(i->path())->second;
		if(inst != NULL)
		{
					LOGGER_WRITE(Logger::DEBUG,"stop of "+i->name);
			inst->stop();
		}
		
	}

	return true;
}

void * DynamicLoader::soloader_load(std::string libpath)
{
		    void* handle = dlopen(libpath.c_str(),RTLD_GLOBAL);
			if (!handle) 
		    {
					fputs (dlerror(), stderr);
					return NULL;
		    }
		  return handle;      
}

AbstractTypeDefinition * DynamicLoader::newInstance(void *handle)
{
			AbstractTypeDefinition* (*create)();
			create =  (AbstractTypeDefinition* (*)())dlsym(handle, "create");
			AbstractTypeDefinition* c = (AbstractTypeDefinition*)create();
			return c;	
}



void  DynamicLoader::unload(std::string type)
{
	
	
}
