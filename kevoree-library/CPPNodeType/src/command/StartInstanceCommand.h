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
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
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
		
		TypeDefinition *type = (TypeDefinition*)instance->typeDefinition;
		
		LOGGER_WRITE(Logger::DEBUG,"StartInstance"+instance->name);
		
		if(dynamic_cast<ComponentInstance*>(instance) != 0)
		{
				ComponentInstance *c = (ComponentInstance*)instance;
								
				for (std::unordered_map<string,DeployUnit*>::iterator iterator = type->deployUnits.begin(), end = type->deployUnits.end(); iterator != end; ++iterator)
				{
					DeployUnit *du= iterator->second;
					bootstrapService->getDynamicLoader()->create_DeployUnitById(du->internalGetKey());
				}
			
		
			
		}else if(dynamic_cast<Group*>(instance) != 0){
			
			Group *group = (Group*)instance;
			
				for (std::unordered_map<string,DeployUnit*>::iterator iterator = type->deployUnits.begin(), end = type->deployUnits.end(); iterator != end; ++iterator)
				{
					DeployUnit *du= iterator->second;
					AbstractGroup *instance = (AbstractGroup*)bootstrapService->getDynamicLoader()->create_DeployUnitById(du->internalGetKey());
					instance->setBootStrapperService(bootstrapService);
					instance->setModelService(mservice);
					
					//instance->start(); TODO TOMORRW in THREad
				}		
				
		}
		
		
	};
};

#endif /*AddInstance*/

