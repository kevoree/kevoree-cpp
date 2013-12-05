#ifndef _RemoveInstanceCommand_H
#define _RemoveInstanceCommand_H

#include <kevoree-core/core/api/PrimitiveCommand.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include "AddInstanceCommand.h"



class RemoveInstanceCommand : public  PrimitiveCommand
{
public:
	RemoveInstanceCommand(Instance *instance,std::string nodename,Bootstraper *bootstrapService,KevoreeModelHandlerService *mservice)
	{
		this->instance = instance;
		this->nodename = nodename;
		this->bootstrapService =bootstrapService;
		this->mservice =mservice;
	}
	
	bool execute()
	{
		LOGGER_WRITE(Logger::DEBUG,"RemoveInstance ->"+instance->name+" path="+instance->path());
		return bootstrapService->getDynamicLoader()->unload_instance(instance);
    }

    
	void undo()
	{
	//	AddInstanceCommand *a(instance,nodename,bootstrapService,mservice);

	}
	

	
public:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
	
};

#endif /*AddInstance*/

