#include "CommandMapper.h"
#include "command/AddInstanceCommand.h"
#include "command/StartInstanceCommand.h"
#include "Primitives.h"

PrimitiveCommand* CommandMapper::buildPrimitiveCommand(AdaptationPrimitive *p, std::string nodeName)
{
	
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
