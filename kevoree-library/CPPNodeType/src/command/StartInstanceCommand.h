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
	
	bool execute()
	{
	   LOGGER_WRITE(Logger::DEBUG,"StartInstance ->"+instance->name+" "+instance->path());
		AbstractTypeDefinition	*ins = bootstrapService->getDynamicLoader()->create_instance(instance);
		if(ins != NULL)
		{
			ins->setBootStrapperService(bootstrapService);
			ins->setModelService(mservice);	
			ins->setModelElement(instance);
			
			ins->start(); 	
			return true;
		}
		else
		{
			LOGGER_WRITE(Logger::ERROR,"StartInstance ->"+instance->name);
			return false;
		}
	 
    }

    
	void undo()
	{
	 //        RemoveInstance(c, nodeName, modelservice, kscript, bs, nt, registry).execute()
	}
	
	void run()
	{

	}
	
private:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;	
};

#endif /*AddInstance*/

