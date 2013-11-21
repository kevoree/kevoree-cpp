#include "Planner.h"


AdaptationModel *Planner::compareModels(ContainerRoot *currentModel,ContainerRoot *targetModel,string nodeName,TraceSequence *traces)
{
	
	ContainerNode *currentNode = currentModel->findnodesByID(nodeName);
	ContainerNode *targetNode = targetModel->findnodesByID(nodeName);

	AdaptationModel  *adaptationModel =    factory.createAdaptationModel();
	

		for (std::list<ModelTrace*>::iterator iterator = traces->traces.begin(), end = traces->traces.end(); iterator != end; ++iterator)
        {
			ModelTrace *trace = *iterator;
			KMFContainer *modelElement = targetModel->findByPath(trace->srcPath);
		
			if(trace->refName.compare("started") ==0)
			{	
					 if((dynamic_cast<Instance*>(modelElement) != 0) && typeid(*trace) == typeid(ModelSetTrace)){
						 
						   ModelSetTrace *modelsettrace = (ModelSetTrace*) traces;
				
						   if(modelsettrace->srcPath.compare(targetNode->path()) == 0)
						   {
							          //HaraKiri case 
						   }else 
						   {
							  
							       if (modelsettrace->content.compare("true") ==0) 
							       {
											 
								   }
											 
											 
						   }
							   
					
					 }
			}
			 
		}

}
