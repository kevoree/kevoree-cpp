#ifndef __UpdateDictionaryInstanceCommand_H
#define __UpdateDictionaryInstanceCommand_H

#include <kevoree-core/api/PrimitiveCommand.h>
#include <kevoree-core/api/Bootstraper.h>


class UpdateDictionaryInstanceCommand : public  PrimitiveCommand 
{
public:
	UpdateDictionaryInstanceCommand(Instance *_instance,std::string _nodename,Bootstraper *_bootstrapService,KevoreeModelHandlerService *_mservice)
	{
		this->instance = _instance;
		this->nodename = _nodename;
		this->bootstrapService =_bootstrapService;
		this->mservice =_mservice;
	}
	
	void execute(boost::promise<bool> & result)
	{
		LOGGER_WRITE(Logger::DEBUG,"UpdateDictionaryInstance ->"+instance->name+" "+instance->path());
		bool updated = bootstrapService->getDynamicLoader()->update_instance(instance);
		result.set_value(updated);
    }

	void undo()
	{
		cout << " TODO " << endl;
	}
	

private:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
};

#endif /*AddInstance*/

