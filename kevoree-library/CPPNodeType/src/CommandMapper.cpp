#include "CommandMapper.h"
#include "command/AddInstanceCommand.h"
#include "command/RemoveInstanceCommand.h"
#include "command/StartInstanceCommand.h"
#include "command/StopInstanceCommand.h"
#include "command/UpdateDictionaryInstanceCommand.h"
#include "Primitives.h"
#include <microframework/api/json/JSONModelSerializer.h>

CommandMapper::CommandMapper(AbstractNodeType *nodeType)
{
	this->nodeType = nodeType;	
}


PrimitiveCommand* CommandMapper::buildPrimitiveCommand(AdaptationPrimitive *p, std::string nodeName)
{
	Instance *instance = (Instance*)p->ref;
	if(p->name.compare(TO_STRING_Primitives(AddInstance)) == 0)
	{
		return new AddInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}else if(p->name.compare(TO_STRING_Primitives(StartInstance)) == 0)
	{
		return new StartInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}else if(p->name.compare(TO_STRING_Primitives(StopInstance)) == 0)
	{
		return new StopInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}else if(p->name.compare(TO_STRING_Primitives(RemoveInstance)) == 0)
	{
		return new RemoveInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}else if(p->name.compare(TO_STRING_Primitives(UpdateDictionaryInstance)) == 0)
	{
		return new UpdateDictionaryInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}
	LOGGER_WRITE(Logger::ERROR,"CommandMapper cannot manage => "+	p->name);
	return NULL;
}
