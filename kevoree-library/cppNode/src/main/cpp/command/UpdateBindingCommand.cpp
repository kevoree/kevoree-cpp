#include "UpdateBindingCommand.h"


void UpdateBindingCommand::execute(boost::promise<bool> & result)
{
	LOGGER_WRITE(Logger::DEBUG,"TODO UpdateBindingCommand ->"+instance->name);
	result.set_value(true);

}

void UpdateBindingCommand::undo()
{

}
