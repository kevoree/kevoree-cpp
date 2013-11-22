#include <kevoree-framework/deploy/PrimitiveCommandExecutionHelper.h>
#include <kevoree-framework/deploy/KevoreeParDeployPhase.h>


bool PrimitiveCommandExecutionHelper::execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance)
{
	ParallelStep *orderedPrimitiveSet = adaptionModel->orderedPrimitiveSet;
	if(orderedPrimitiveSet == NULL){
		return false;
	}
	 KevoreeParDeployPhase *phase = new KevoreeParDeployPhase();
	 
	 bool res = executeStep(rootNode,orderedPrimitiveSet,nodeInstance,phase);
	 if(res){
		 
		 
	 }

	
	delete phase;
}



bool PrimitiveCommandExecutionHelper::executeStep(ContainerNode *rootNode,ParallelStep *step,AbstractNodeType *nodeInstance,KevoreeParDeployPhase *phase){
	     if (step == NULL)
	     {
            return true;
         }
         
        for (std::unordered_map<string,AdaptationPrimitive*>::const_iterator it = step->adaptations.begin();  it != step->adaptations.end(); ++it) 
		{
			AdaptationPrimitive *adaptation = it->second;
			
			LOGGER_WRITE(Logger::INFO,"Populate primitive =>"+adaptation->primitiveType);
			
		//	nodeInstance.getPrimitive(adaptation);
			
			
	    }

}
