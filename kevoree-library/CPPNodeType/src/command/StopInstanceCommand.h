#ifndef __StopInstanceCommand_H
#define __StopInstanceCommand_H

#include <kevoree-core/core/api/PrimitiveCommand.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include "StartInstanceCommand.h"

class StopInstanceCommand : public  PrimitiveCommand 
{
public:
	StopInstanceCommand(Instance *_instance,std::string _nodename,Bootstraper *_bootstrapService,KevoreeModelHandlerService *_mservice)
	{
		this->instance = _instance;
		this->nodename = _nodename;
		this->bootstrapService =_bootstrapService;
		this->mservice =_mservice;
	}
	
	void execute()
	{
		TypeDefinition *type = (TypeDefinition*)instance->typeDefinition;
		LOGGER_WRITE(Logger::DEBUG,"StopInstance ->"+instance->name);
		result= bootstrapService->getDynamicLoader()->stop_instance(instance);
    }

	void undo()
	{
		//	StartInstanceCommand(instance, nodename, bootstrapService, mservice).execute();
		// TODO BREAK A<->B
	}
	
private:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
};

#endif /*AddInstance*/

