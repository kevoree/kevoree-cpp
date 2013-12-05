#ifndef __AddInstance_H
#define __AddInstance_H

#include <kevoree-core/core/api/PrimitiveCommand.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include "RemoveInstanceCommand.h"

class AddInstanceCommand : public  PrimitiveCommand
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
		LOGGER_WRITE(Logger::DEBUG,"AddInstance -> "+instance->name);
		if(!bootstrapService->getDynamicLoader()->register_instance(instance))
		{
			// throw an exeception
			return false;
		}
		else 
		{
			return true;
		}
    }

    
	void undo()
	{
		RemoveInstanceCommand r(instance,nodename,bootstrapService,mservice);
		r.execute();
	}
	
};

#endif /*AddInstance*/

