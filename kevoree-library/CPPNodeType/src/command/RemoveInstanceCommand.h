#ifndef _RemoveInstanceCommand_H
#define _RemoveInstanceCommand_H

#include <kevoree-core/api/PrimitiveCommand.h>
#include <kevoree-core/api/Bootstraper.h>
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
	
	void execute(boost::promise<bool> & result)
	{
		LOGGER_WRITE(Logger::DEBUG,"RemoveInstance ->"+instance->name+" path="+instance->path());
		result.set_value(bootstrapService->getDynamicLoader()->destroy_instance(instance));
    }

    
	void undo()
	{
	//	AddInstanceCommand *a(instance,nodename,bootstrapService,mservice);
	cout << "TODO" << endl;

	}
	

	
public:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
	
};

#endif /*AddInstance*/

