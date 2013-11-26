#include "CommandMapper.h"
#include "command/AddInstanceCommand.h"
#include "command/StartInstanceCommand.h"
#include "Primitives.h"

PrimitiveCommand* CommandMapper::buildPrimitiveCommand(AdaptationPrimitive *p, std::string nodeName)
{
	/*
	std::string primitiveType;
std::string targetNodeName;
std::string ref;
std::string generated_KMF_ID;*/
	//LOGGER_WRITE(Logger::DEBUG,"CommandMapper::buildPrimitiveCommand id="+p->generated_KMF_ID+" primitiveType="+p->primitiveType+" ref="+p->ref);
			
	if(p->primitiveType.compare(TO_STRING_Primitives(AddInstance)) == 0)
	{
		Instance *instance = (Instance*)targetModel->findByPath(p->ref);
		return new AddInstanceCommand(instance,nodeName);
	}else if(p->primitiveType.compare(TO_STRING_Primitives(StartInstance)) == 0)
	{
		Instance *instance = (Instance*)targetModel->findByPath(p->ref);
		return new StartInstanceCommand(instance,nodeName);
	}
	

}
//FIX ME
void CommandMapper::internal_update(ContainerRoot *_actualModel,ContainerRoot *_targetModel){
	 actualModel=_actualModel;
     targetModel=_targetModel;
 }
