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
		TypeDefinition *type = (TypeDefinition*)instance->typeDefinition;
		LOGGER_WRITE(Logger::DEBUG,"UpdateDictionaryInstance ->"+instance->name+" "+instance->path());

		result.set_value(true);
    }

	void undo()
	{
		
	}
	

private:
	Instance *instance;
	std::string nodename;
	Bootstraper *bootstrapService;
	KevoreeModelHandlerService *mservice;
};

#endif /*AddInstance*/

