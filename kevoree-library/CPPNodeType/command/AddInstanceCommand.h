#ifndef __AddInstance_H
#define __AddInstance_H

#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/AbstractComponent.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>

#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/model/kevoree/DeployUnit.h>
#include <dlfcn.h>
#include <iostream>

class AddInstanceCommand : public  PrimitiveCommand
{
	public:
	AddInstanceCommand(Instance *instance,std::string nodename)
	{
		
		if(dynamic_cast<ComponentInstance*>(instance) != 0)
		{
				ComponentInstance *c = (ComponentInstance*)instance;
				TypeDefinition *type = (TypeDefinition*)c->typeDefinition;
				
				LOGGER_WRITE(Logger::DEBUG,"AddInstance ComponentInstance name "+instance->name+" TypeDefinition "+type->name);
				
				for (std::unordered_map<string,DeployUnit*>::iterator iterator = type->deployUnits.begin(), end = type->deployUnits.end(); iterator != end; ++iterator)
				{
					DeployUnit *deployunit= iterator->second;

					LOGGER_WRITE(Logger::DEBUG,"DeployUnit "+deployunit->name+" "+deployunit->groupName+" "+deployunit->version+" "+deployunit->url);
				}
				
		   // todo class loader 
		   
			const char *libpath= "kevoree-library/HelloWorldComponent/libhelloworld_component.so";
		    void* handle = dlopen(libpath, RTLD_LAZY | RTLD_GLOBAL);
			if (!handle) 
		    {
					fputs (dlerror(), stderr);
				
		    }
		    
		    		AbstractComponent* (*create)();
			create =  (AbstractComponent* (*)())dlsym(handle, "create");
			AbstractComponent* c2 = (AbstractComponent*)create();

			
		
			
		}
	

	}
	
	bool execute()
	{
	 
    };
    
	void undo()
	{
	 //        RemoveInstance(c, nodeName, modelservice, kscript, bs, nt, registry).execute()
	};
};

#endif /*AddInstance*/

