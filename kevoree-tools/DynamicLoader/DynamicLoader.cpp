#include <kevoree-tools/DynamicLoader/DynamicLoader.h>


DynamicLoader::DynamicLoader(Bootstraper *bootstrap)
{
	this->bootstrap = bootstrap;	
}

void DynamicLoader::setModelService(KevoreeModelHandlerService *mservice){
	this->mservice = mservice;
}


bool DynamicLoader::register_instance(Instance *i)
{
	try
	{
		TypeDefinition *type = i->typeDefinition;
		if(type == NULL)
		{
			LOGGER_WRITE(Logger::ERROR,"There is no TypeDefinition define");
			return false;
		}
		
		if(type->deployUnit ==NULL)
		{
			cout << type->name << endl;
			LOGGER_WRITE(Logger::ERROR,"There is no DeployUnit define");	
			return false;
		}
		
		string libpath=	bootstrap->resolveDeployUnit(type->deployUnit);
		if(!libpath.empty())
		{
			LOGGER_WRITE(Logger::DEBUG,"install_deploy_unit "+libpath);
			void *handler = soloader_load(libpath);
			if(handler == NULL)
			{
				return false;
			}
			deploysUnits[type->deployUnit->internalGetKey()] = handler;		
			return true;	
		}else
		{
			LOGGER_WRITE(Logger::ERROR,"The DeployUnit cannot be registred beacause the Typedefintion is not found "+libpath);	
			return false;	
		}		
	}
    catch ( const std::exception & e )
    {
        std::cerr << e.what() << endl;
        return false;
    }
}

AbstractTypeDefinition* DynamicLoader::create_instance(Instance *i)
{
	try
	{
			TypeDefinition *type = i->typeDefinition;
			if(type == NULL)
			{
				LOGGER_WRITE(Logger::ERROR,"There is no TypeDefinition define");
				return NULL;
			}

			DeployUnit *du  =type->deployUnit;
			// todo check if for me
			map<string, void*>::const_iterator it = deploysUnits.find(du->internalGetKey());
			if (it == deploysUnits.end())
			{
				return NULL;
			}
			LOGGER_WRITE(Logger::DEBUG,"newInstance of "+du->name);
			void *instance = newInstance(it->second);
			if(instance == NULL){
				return NULL;
			}
			instances[i->path()] = instance;
			return(AbstractTypeDefinition*)instance;
	}
    catch ( const std::exception & e )
    {
        std::cerr << e.what() << endl;
        return NULL;
    }
}

bool DynamicLoader::unload_instance(Instance *i)
{
	TypeDefinition *type = i->typeDefinition;
	if(type == NULL)
	{
		LOGGER_WRITE(Logger::ERROR,"There is no TypeDefinition define");
		return false;
	}

	
	if(instances.find(i->path()) != instances.end())
	{
		
		AbstractTypeDefinition *inst = (AbstractTypeDefinition*)instances.find(i->path())->second;
		
		if(inst != NULL && dynamic_cast<AbstractTypeDefinition*>(inst) != 0)
		{
			LOGGER_WRITE(Logger::DEBUG,"stop of "+i->name);
			
			inst->stop();
	
					DeployUnit *du  = type->deployUnit;
					// todo check if for me
					map<string, void*>::const_iterator it = deploysUnits.find(du->internalGetKey());
					if (it == deploysUnits.end())
					{
						return false;
					}
					destroyInstance(it->second,inst);
			
							
		}else 
		{
			LOGGER_WRITE(Logger::ERROR,"instance cannt be cast");
			return false;	
		}
		
		
	}

	return true;
}

void * DynamicLoader::soloader_load(std::string libpath)
{
		    void* handle = dlopen(libpath.c_str(),RTLD_LAZY);
			if (!handle) 
		    {

					LOGGER_WRITE(Logger::ERROR,"dlopen =>"+string(dlerror()));
					return NULL;
		    }
		  return handle;      
}

void DynamicLoader::destroyInstance(void *handler,AbstractTypeDefinition *instance)
{
				LOGGER_WRITE(Logger::DEBUG,"DynamicLoader destroyInstance");
			// destructor 
			void (*destroy)(AbstractTypeDefinition*);
			destroy = (void (*)(AbstractTypeDefinition*))dlsym(handler, "destroy_object");
			destroy(instance);
			// class 
			if(dlclose(handler) != 0){
					LOGGER_WRITE(Logger::WARNING,"dlclose");
			}
}

AbstractTypeDefinition * DynamicLoader::newInstance(void *handle)
{
			LOGGER_WRITE(Logger::DEBUG,"DynamicLoader newInstance");
			AbstractTypeDefinition* (*create)();
			create =  (AbstractTypeDefinition* (*)())dlsym(handle, "create");
			AbstractTypeDefinition* c = (AbstractTypeDefinition*)create();
			return c;	
}


