#include <kevoree-tools/DynamicLoader/DynamicLoader.h>


DynamicLoader::DynamicLoader(Bootstraper *bootstrap)
{
	this->bootstrap = bootstrap;	
}


void DynamicLoader::register_DeployUnit(DeployUnit *du)
{
	map<string, void*>::const_iterator it = deploysUnits.find(du->internalGetKey());
	if (it == deploysUnits.end())
	{
		string libpath=	bootstrap->resolveDeployUnit(du);
		if(!libpath.empty())
		{
			LOGGER_WRITE(Logger::DEBUG,"install_deploy_unit "+libpath);
			void *handler = soloader_load(libpath);
			deploysUnits[du->internalGetKey()] = handler;			
		}else
		{
			LOGGER_WRITE(Logger::ERROR,"The DeployUnit cannot be registred beacause the Typedefintion is not found "+libpath);				
		}	
	}

}

void  * DynamicLoader::create_DeployUnitById(std::string id){
	map<string, void*>::const_iterator it = deploysUnits.find(id);
	if (it == deploysUnits.end())
	{
		return NULL;
	}
		LOGGER_WRITE(Logger::DEBUG,"newInstance of "+id);
	return newInstance(it->second);
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
