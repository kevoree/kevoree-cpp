#include "PrimitiveCommandExecutionHelper.h"
#include "KevoreeParDeployPhase.h"
#include "../Primitives.h"

bool PrimitiveCommandExecutionHelper::execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance)
{
	
	ParallelStep *orderedPrimitiveSet = adaptionModel->orderedPrimitiveSet;
	if(orderedPrimitiveSet == NULL)
	{
		LOGGER_WRITE(Logger::WARNING,"orderedPrimitiveSet is NULL");
		return false;
	}
	 KevoreeParDeployPhase *phase = new KevoreeParDeployPhase();

	 bool res = executeStep(rootNode,orderedPrimitiveSet,nodeInstance,phase);
	 if(res)
	 {
		 
		 
	 }

	
	delete phase;
	return true;
}



bool PrimitiveCommandExecutionHelper::executeStep(ContainerNode *rootNode,ParallelStep *step,AbstractNodeType *nodeInstance,KevoreeParDeployPhase *phase){
	     if (step == NULL)
	     {
            return true;
         }
		
        for (std::unordered_map<string,AdaptationPrimitive*>::const_iterator it = step->adaptations.begin();  it != step->adaptations.end(); ++it) 
		{
			AdaptationPrimitive *adaptation = it->second;
			PrimitiveCommand *primitive = nodeInstance->getPrimitive(adaptation);
			if(primitive != NULL)
			{
				primitive->execute();
				if(adaptation->primitiveType.compare(TO_STRING_Primitives(AddInstance)) == 0)
				{
						primitive->wait();			
				}	
			}
			else
			{
					LOGGER_WRITE(Logger::ERROR,"PrimitiveCommand is NULL");
				
			}
			
	
	    }
	    // TODO end of this step primitive->wait(); for AddInstance 
	    executeStep(rootNode,step->nextStep,nodeInstance,phase);
}
