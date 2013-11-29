#ifndef __StopInstanceCommand_H
#define __StopInstanceCommand_H

#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>

#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/model/kevoree/DeployUnit.h>
#include <microframework/api/utils/Runnable.h>

class StopInstanceCommand : public  PrimitiveCommand,public Runnable
{
public:
	StopInstanceCommand(Instance *_instance,std::string _nodename,Bootstraper *_bootstrapService,KevoreeModelHandlerService *_mservice)
	{
		this->instance = _instance;
		this->nodename = _nodename;
		this->bootstrapService =_bootstrapService;
		this->mservice =_mservice;
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
		TypeDefinition *type = (TypeDefinition*)instance->typeDefinition;
		LOGGER_WRITE(Logger::DEBUG,"StopInstance ->"+instance->name);

	}
private:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
};

#endif /*AddInstance*/

