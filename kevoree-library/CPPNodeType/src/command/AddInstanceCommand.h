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

	void execute(boost::promise<bool> & result)
	{
		LOGGER_WRITE(Logger::DEBUG,"AddInstance -> "+instance->name);
		if(!bootstrapService->getDynamicLoader()->register_instance(instance))
		{
			result.set_value(false);
		}
		else 
		{
			AbstractTypeDefinition	*ins = bootstrapService->getDynamicLoader()->create_instance(instance);
			if(ins != NULL)
			{
				ins->setBootStrapperService(bootstrapService);
				ins->setModelService(mservice);	
				ins->setPath(instance->path());
				result.set_value(true);
			}
			else
			{
				LOGGER_WRITE(Logger::ERROR,"StartInstance ->"+instance->name);
				result.set_value(false);
			}
		}
	}


	void undo()
	{
		boost::promise<bool>  re;
		RemoveInstanceCommand r(instance,nodename,bootstrapService,mservice);
		r.execute(re);
	}

};

#endif /*AddInstance*/

