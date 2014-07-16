#ifndef __AddInstance_H
#define __AddInstance_H

#include <kevoree-core/api/PrimitiveCommand.h>
#include <kevoree-core/api/Bootstraper.h>
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

	void execute(boost::promise<bool> & result);

	void undo();
};

#endif /*AddInstance*/

