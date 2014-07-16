#ifndef __StopInstanceCommand_H
#define __StopInstanceCommand_H

#include <kevoree-core/api/PrimitiveCommand.h>
#include <kevoree-core/api/Bootstraper.h>


class StopInstanceCommand : public  PrimitiveCommand 
{
public:
	StopInstanceCommand(Instance *_instance,std::string _nodename,Bootstraper *_bootstrapService,KevoreeModelHandlerService *_mservice)
	{
		this->instance = _instance;
		this->nodename = _nodename;
		this->bootstrapService =_bootstrapService;
		this->mservice =_mservice;
	}
	
	void execute(boost::promise<bool> & result);
	void undo();
	
private:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
};

#endif /*AddInstance*/

