#ifndef __AddBindingCommand_H
#define __AddBindingCommand_H

#include <kevoree-core/api/PrimitiveCommand.h>
#include <kevoree-core/api/Bootstraper.h>


class AddBindingCommand : public  PrimitiveCommand
{
public:
	MBinding *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;

	AddBindingCommand(MBinding *instance,std::string nodename,Bootstraper *bootstrapService,KevoreeModelHandlerService *mservice)
	{
		this->instance = instance;
		this->nodename = nodename;
		this->bootstrapService =bootstrapService;
		this->mservice =mservice;
	}

	void execute(boost::promise<bool> & result)
	{
		// TODO
	}


	void undo()
	{
		// TODO
	}

};

#endif /*AddInstance*/

