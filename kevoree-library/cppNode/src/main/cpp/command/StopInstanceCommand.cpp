#include "StopInstanceCommand.h"
#include "StartInstanceCommand.h"

void StopInstanceCommand::execute(boost::promise<bool> & result)
{
	LOGGER_WRITE(Logger::DEBUG,"StopInstance ->"+instance->name);
	bool stopped = bootstrapService->getDynamicLoader()->stop_instance(instance);
	result.set_value(stopped);
}

void StopInstanceCommand::undo()
{
	boost::promise<bool>  re;
	StartInstanceCommand r(instance,nodename,bootstrapService,mservice);
	r.execute(re);
}
