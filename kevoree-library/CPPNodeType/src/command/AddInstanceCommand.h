#ifndef __AddInstance_H
#define __AddInstance_H

#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/AbstractComponent.h>
#include <kevoree-core/core/api/AbstractGroup.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>

#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/model/kevoree/Group.h>
#include <kevoree-core/model/kevoree/DeployUnit.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include <dlfcn.h>
#include <iostream> // remove later
#include <microframework/api/utils/Runnable.h>

class AddInstanceCommand : public  PrimitiveCommand,public Runnable
{
	public:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
	
	AddInstanceCommand(Instance *instance,std::string nodename,Bootstraper *bootstrapService,KevoreeModelHandlerService *mservice)
	{
		this->instance = instance;
		this->nodename = nodename;
		this->bootstrapService =bootstrapService;
		this->mservice =mservice;
	}
	
	bool execute()
	{
		start();
    };
    void wait(){
		join();
	}
    
	void undo()
	{
	 //        RemoveInstance(c, nodeName, modelservice, kscript, bs, nt, registry).execute()
	};
	
	void run()
	{
		LOGGER_WRITE(Logger::DEBUG,"AddInstance -> "+instance->name);
		if(!bootstrapService->getDynamicLoader()->register_instance(instance))
		{
			// throw an exeception
		}
		
	}
};

#endif /*AddInstance*/

