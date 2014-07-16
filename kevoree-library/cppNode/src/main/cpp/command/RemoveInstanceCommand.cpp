#include "RemoveInstanceCommand.h"

#include "AddInstanceCommand.h"


void RemoveInstanceCommand::execute(boost::promise<bool> & result)
{
	LOGGER_WRITE(Logger::DEBUG,"RemoveInstance ->"+instance->name+" path="+instance->path());
	result.set_value(bootstrapService->getDynamicLoader()->destroy_instance(instance));
}


void RemoveInstanceCommand::undo(){
	boost::promise<bool>  re;
	AddInstanceCommand r(instance,nodename,bootstrapService,mservice);
	r.execute(re);
}
