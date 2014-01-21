#ifndef __RemoveBindingCommand_H
#define __RemoveBindingCommand_H

#include <kevoree-core/api/PrimitiveCommand.h>
#include <kevoree-core/api/Bootstraper.h>


class RemoveBindingCommand : public  PrimitiveCommand
{
public:
	MBinding *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;

	RemoveBindingCommand(MBinding *instance,std::string nodename,Bootstraper *bootstrapService,KevoreeModelHandlerService *mservice)
	{
		this->instance = instance;
		this->nodename = nodename;
		this->bootstrapService =bootstrapService;
		this->mservice =mservice;
	}

	void execute(boost::promise<bool> & result)
	{

	}


	void undo()
	{

	}

};

#endif /*AddInstance*/

