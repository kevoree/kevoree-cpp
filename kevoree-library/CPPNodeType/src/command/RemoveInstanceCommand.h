#ifndef _RemoveInstanceCommand_H
#define _RemoveInstanceCommand_H

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

class RemoveInstanceCommand : public  PrimitiveCommand,public Runnable
{
public:
	RemoveInstanceCommand(Instance *_instance,std::string _nodename,Bootstraper *_bootstrapService,KevoreeModelHandlerService *_mservice)
	{
		this->instance = _instance;
		this->nodename = _nodename;
		this->bootstrapService =_bootstrapService;
		this->mservice =_mservice;
	}
	
	bool execute()
	{
		// FIX ME 
		LOGGER_WRITE(Logger::DEBUG,"RemoveInstance ->"+instance->name+" path="+instance->path());
		bootstrapService->getDynamicLoader()->unload_instance(instance);
    }
    void wait()
    {
		join();
	}
    
	void undo()
	{

	}
	
	void run()
	{
		// CANNOT RUN HERE WTF ??? get a  segmentation (core dumped)
		// CONTEXT MEMORY ?? dlopen ?? 
	}
	
public:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
	
};

#endif /*AddInstance*/

