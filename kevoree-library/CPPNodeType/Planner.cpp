#include "Planner.h"



AdaptationPrimitive* Planner::adapt(Primitives p,KMFContainer *elem,ContainerRoot *model)
{
	cout << TO_STRING_Primitives(p) << endl;
        AdaptationPrimitive *ccmd = factory.createAdaptationPrimitive();
        //ccmd->primitiveType = model->findadaptationPrimitiveTypesByID(TO_STRING_Primitives(p));
        ccmd->primitiveType =TO_STRING_Primitives(p); // TODO remove TO_STRING USE INT
    ccmd->ref = elem->path();
    return ccmd;
}


AdaptationModel *Planner::compareModels(ContainerRoot *currentModel,ContainerRoot *targetModel,string nodeName,TraceSequence *traces)
{
	
	ContainerNode *currentNode = currentModel->findnodesByID(nodeName);
	ContainerNode *targetNode = targetModel->findnodesByID(nodeName);
	
	std::unordered_map<string,std::list<TupleObjPrim>> elementAlreadyProcessed; 


	cout << traces->exportToString() << endl;
//	std::set<TupleObjPrim>::iterator srcPath;

	AdaptationModel  *adaptationModel =    factory.createAdaptationModel();
	

		for (std::list<ModelTrace*>::iterator iterator = traces->traces.begin(), end = traces->traces.end(); iterator != end; ++iterator)
        {
			ModelTrace *trace = *iterator;
			KMFContainer *modelElement = targetModel->findByPath(trace->srcPath);
		
			if(trace->refName.compare("started") ==0)
			{	
					 if((dynamic_cast<Instance*>(modelElement) != 0) && (dynamic_cast<ModelSetTrace*>(trace) != 0)){
						 
						   ModelSetTrace *modelsettrace = (ModelSetTrace*) trace;
				
						   if(modelsettrace->srcPath.compare(targetNode->path()) == 0)
						   {
							          //TODO CLEAN REMOVE IN CORE 
							        //  cout << "HaraKiri case " << modelsettrace->toString() << endl;
						   }else 
						   {
							   
							   cout << modelsettrace->content << endl;
							   
							       if (modelsettrace->content.compare("true") ==0) 
							       {
											bool found=false;
											TupleObjPrim tuple(modelElement,StartInstance);
											
											if(!tuple.equals(modelElement->path(),elementAlreadyProcessed))
											{
												   adaptationModel->addadaptations(adapt(StartInstance, modelElement, targetModel));
												   tuple.add(elementAlreadyProcessed);
											}
								   }else 
								   {
											TupleObjPrim tuple(modelElement,StopInstance);
											if(!tuple.equals(modelElement->path(),elementAlreadyProcessed))
											{
												   adaptationModel->addadaptations(adapt(StopInstance, modelElement, targetModel));
												   tuple.add(elementAlreadyProcessed);
											}
								   }
											 
											 
						   }
							   
					
					 }
			}else if(trace->refName.compare("value") ==0){
				
				if(dynamic_cast<Dictionary*>(modelElement) != 0)
				{
					TupleObjPrim tuple(modelElement,UpdateDictionaryInstance);
					if(!tuple.equals(modelElement->path(),elementAlreadyProcessed))
					{
					     adaptationModel->addadaptations(adapt(UpdateDictionaryInstance, modelElement, targetModel));
					     tuple.add(elementAlreadyProcessed);
				    }	 
				}
				
			}
			 
		}
		
		return adaptationModel;
}
