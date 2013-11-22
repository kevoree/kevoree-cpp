#include "Planner.h"



AdaptationPrimitive* Planner::adapt(Primitives p,KMFContainer *elem,ContainerRoot *model)
{
	//cout << TO_STRING_Primitives(p) << endl;
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

	//cout << traces->exportToString() << endl;
//	std::set<TupleObjPrim>::iterator srcPath;

	AdaptationModel  *adaptationModel =    factory.createAdaptationModel();
	

		for (std::list<ModelTrace*>::iterator iterator = traces->traces.begin(), end = traces->traces.end(); iterator != end; ++iterator)
        {
			ModelTrace *trace = *iterator;
			KMFContainer *modelElement = targetModel->findByPath(trace->srcPath);
			
			if(trace->refName.compare("components") ==0)
			{
					   if(trace->srcPath.compare(targetNode->path()) == 0)
					   {
						   	ModelAddTrace *modeladdtrace = (ModelAddTrace*) trace;
						    KMFContainer *elemToAdd=targetModel->findByPath(modeladdtrace->srcPath);
						    
						   	if(dynamic_cast<ModelAddTrace*>(trace) != 0)
							{
								adaptationModel->addadaptations(adapt(AddInstance, elemToAdd, targetModel));
							}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
							{
								adaptationModel->addadaptations(adapt(RemoveInstance, elemToAdd, targetModel));	
							}
						   
					   }
					   
			}else if(trace->refName.compare("hosts") ==0)
			{
				
					   if(trace->srcPath.compare(targetNode->path()) == 0)
					   {
							 if(trace->srcPath.compare(targetNode->path()) == 0)
						   {
								ModelAddTrace *modeladdtrace = (ModelAddTrace*) trace;
								KMFContainer *elemToAdd=targetModel->findByPath(modeladdtrace->srcPath);
								
								if(dynamic_cast<ModelAddTrace*>(trace) != 0)
								{
									adaptationModel->addadaptations(adapt(AddInstance, elemToAdd, targetModel));
								}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
								{
									adaptationModel->addadaptations(adapt(RemoveInstance, elemToAdd, targetModel));	
								}
							   
						   }
						   
					   }
			
			}else if(trace->refName.compare("groups") ==0)
			{
				
					   if(trace->srcPath.compare(targetNode->path()) == 0)
					   {
							 if(trace->srcPath.compare(targetNode->path()) == 0)
						   {
								ModelAddTrace *modeladdtrace = (ModelAddTrace*) trace;
								KMFContainer *elemToAdd=targetModel->findByPath(modeladdtrace->srcPath);
								
								if(dynamic_cast<ModelAddTrace*>(trace) != 0)
								{
									adaptationModel->addadaptations(adapt(AddInstance, elemToAdd, targetModel));
								}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
								{
									adaptationModel->addadaptations(adapt(RemoveInstance, elemToAdd, targetModel));	
								}
							   
						   }
						   
					   }
			
			}else if(trace->refName.compare("bindings") ==0)
			{
				        //TODO here process potential AddBinding
					   if(trace->srcPath.compare(targetNode->path()) == 0)
					   {
							 if(trace->srcPath.compare(targetNode->path()) == 0)
						   {
								ModelAddTrace *modeladdtrace = (ModelAddTrace*) trace;
								MBinding *binding=(MBinding*)targetModel->findByPath(modeladdtrace->srcPath);
								Channel *channel=NULL;
								if(binding != NULL)
								{
									channel = binding->hub;
								}
								if(dynamic_cast<ModelAddTrace*>(trace) != 0)
								{
															
									if(channel != NULL){ // todo check registry && !registry.containsKey(channel.path())){
									
										TupleObjPrim tuple(channel,AddInstance);
										if(!tuple.equals(modelElement->path(),elementAlreadyProcessed))
										{
													adaptationModel->addadaptations(adapt(AddInstance, channel, targetModel));
													tuple.add(elementAlreadyProcessed);
										}
											
									}
									adaptationModel->addadaptations(adapt(AddBinding, binding, targetModel));
									
								}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
								{
									MBinding *previousBinding=(MBinding*)currentModel->findByPath(modeladdtrace->srcPath);
									Channel *oldChannel=previousBinding->hub;
									//check if not no current usage of this channel
									bool stillUsed = (channel != NULL);
								    if(channel != NULL)
								    {
												for (std::unordered_map<string,MBinding*>::iterator iterator = channel->bindings.begin(), end = channel->bindings.end(); iterator != end; ++iterator)
												{
													
													   MBinding *loopBinding = iterator->second;
													   if(loopBinding->port->eContainer() == targetNode)
													   {
														stillUsed = true;
													   }
													   
													   if(!stillUsed ) //TODO && !registry.containsKey(oldChannel!!)
													   {
															TupleObjPrim tuple(channel,RemoveInstance);
															if(!tuple.equals(modelElement->path(),elementAlreadyProcessed))
															{
																		adaptationModel->addadaptations(adapt(RemoveInstance, channel, targetModel));
																		tuple.add(elementAlreadyProcessed);
															}		 
																	 
													    }
													
												}		 
									}
									adaptationModel->addadaptations(adapt(RemoveBinding, binding, targetModel));
								}
							   
						   }
						   
					   }
					   
			}else if(trace->refName.compare("typeDefinition") ==0){
					if(dynamic_cast<Instance*>(modelElement) != 0)
					{
							cout << "           //TODO continuous design" << endl;	
					}
					
				
			
			}else if(trace->refName.compare("started") ==0)
			{	
					 if((dynamic_cast<Instance*>(modelElement) != 0) && (dynamic_cast<ModelSetTrace*>(trace) != 0)){
						 
						   ModelSetTrace *modelsettrace = (ModelSetTrace*) trace;
				
						   if(modelsettrace->srcPath.compare(targetNode->path()) == 0)
						   {
							          //TODO CLEAN REMOVE IN CORE 
							        //  cout << "HaraKiri case " << modelsettrace->toString() << endl;
						   }else 
						   {
							       if (modelsettrace->content.compare("true") ==0) 
							       {
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
