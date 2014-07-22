#ifndef __AddBindingCommand_H
#define __AddBindingCommand_H

#include <kevoree-core/api/PrimitiveCommand.h>
#include <kevoree-core/api/Bootstraper.h>
#include <kevoree-core/model/kevoree/MBinding.h>
#include <kevoree-core/model/kevoree/Port.h>
#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/api/AbstractChannel.h>

class AddBindingCommand : public  PrimitiveCommand
{
public:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;

	AddBindingCommand(Instance *instance,std::string nodename,Bootstraper *bootstrapService,KevoreeModelHandlerService *mservice)
	{
		this->instance = instance;
		this->nodename = nodename;
		this->bootstrapService =bootstrapService;
		this->mservice =mservice;
	}

	void execute(boost::promise<bool> & result);

	void undo();

};

#endif /*AddInstance*/

