#include "AddInstanceCommand.h"


void AddInstanceCommand::execute(boost::promise<bool> & result)
{
	LOGGER_WRITE(Logger::DEBUG,"AddInstance -> "+instance->name);
	if(!bootstrapService->getDynamicLoader()->register_instance(instance))
	{
		result.set_value(false);
	}
	else
	{
		AbstractTypeDefinition	*ins = bootstrapService->getDynamicLoader()->create_instance(instance);
		if(ins != NULL)
		{
			ins->setBootStrapperService(bootstrapService);
			ins->setModelService(mservice);
			ins->setPath(instance->path());
			result.set_value(true);
		}
		else
		{
			LOGGER_WRITE(Logger::ERROR,"StartInstance ->"+instance->name);
			result.set_value(false);
		}
	}
}


void AddInstanceCommand::undo()
{
	boost::promise<bool>  re;
	RemoveInstanceCommand r(instance,nodename,bootstrapService,mservice);
	r.execute(re);
}
