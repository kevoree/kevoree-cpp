#ifndef _RemoveInstanceCommand_H
#define _RemoveInstanceCommand_H

#include <kevoree-core/api/PrimitiveCommand.h>
#include <kevoree-core/api/Bootstraper.h>




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
	void execute(boost::promise<bool> & result);
	void undo();

public:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;

};

#endif /*AddInstance*/

