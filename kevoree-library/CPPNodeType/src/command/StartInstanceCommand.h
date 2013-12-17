#ifndef __StartInstanceCommand_H
#define __StartInstanceCommand_H

#include <kevoree-core/core/api/PrimitiveCommand.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include "StopInstanceCommand.h"


class StartInstanceCommand : public  PrimitiveCommand
{
public:
	StartInstanceCommand(Instance *instance,std::string nodename,Bootstraper *bootstrapService,KevoreeModelHandlerService *mservice)
	{
		
		this->instance = instance;
		this->nodename = nodename;
		this->bootstrapService =bootstrapService;
		this->mservice =mservice;
	}
	
	void execute()
	{
		LOGGER_WRITE(Logger::DEBUG,"StartInstance ->"+instance->name+" "+instance->path());
		result= bootstrapService->getDynamicLoader()->start_instance(instance);
    }

    
	void undo()
	{
	   StopInstanceCommand(instance, nodename, bootstrapService, mservice).execute();	
	}
	
	
private:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;	
};

#endif /*AddInstance*/

