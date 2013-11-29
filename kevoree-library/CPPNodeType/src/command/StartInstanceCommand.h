#ifndef __StartInstanceCommand_H
#define __StartInstanceCommand_H

#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>

#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/model/kevoree/DeployUnit.h>
#include <microframework/api/utils/Runnable.h>

class StartInstanceCommand : public  PrimitiveCommand,public Runnable
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
			start();
	 
    }
    void wait(){
		join();
	}
    
	void undo()
	{
	 //        RemoveInstance(c, nodeName, modelservice, kscript, bs, nt, registry).execute()
	}
	
	void run()
	{
	   LOGGER_WRITE(Logger::DEBUG,"StartInstance ->"+instance->name+" "+instance->path());
		AbstractTypeDefinition	*ins = bootstrapService->getDynamicLoader()->create_instance(instance);
		if(ins != NULL)
		{
			ins->setBootStrapperService(bootstrapService);
			ins->setModelService(mservice);	
			ins->start(); 	
		}
		else
		{
			// TODO THROW EXCEPTION
			LOGGER_WRITE(Logger::ERROR,"StartInstance ->"+instance->name);
		}
	}
	
private:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;	
};

#endif /*AddInstance*/

