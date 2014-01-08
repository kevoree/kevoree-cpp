#include "CommandMapper.h"
#include "command/AddInstanceCommand.h"
#include "command/RemoveInstanceCommand.h"
#include "command/StartInstanceCommand.h"
#include "command/StopInstanceCommand.h"
#include "command/UpdateDictionaryInstanceCommand.h"
#include "Primitives.h"


CommandMapper::CommandMapper(AbstractNodeType *nodeType)
{
	this->nodeType = nodeType;	
}


PrimitiveCommand* CommandMapper::buildPrimitiveCommand(AdaptationPrimitive *p, std::string nodeName)
{
	Instance *instance = (Instance*)p->ref;
	if(p->primitiveType ==AddInstance)
	{
		return new AddInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}else if(p->primitiveType == StartInstance)
	{
		return new StartInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}else if(p->primitiveType == StopInstance)
	{
		return new StopInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}else if(p->primitiveType == RemoveInstance)
	{
		return new RemoveInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}else if(p->primitiveType == UpdateDictionaryInstance)
	{
		return new UpdateDictionaryInstanceCommand(instance,nodeName,nodeType->getBootStrapperService(),nodeType->getModelService());
	}
	Logger::Write(Logger::ERROR,"CommandMapper cannot manage");
	return NULL;
}
