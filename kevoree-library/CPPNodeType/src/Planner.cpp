#include "Planner.h"
#include <unordered_map>


AdaptationPrimitive* Planner::adapt(Primitives p,KMFContainer *elem)
{
	AdaptationPrimitive *ccmd = factory.createAdaptationPrimitive();
	ccmd->primitiveType =TO_STRING_Primitives(p);
	ccmd->ref = elem;
	return ccmd;
}


AdaptationModel *Planner::compareModels(ContainerRoot *currentModel,ContainerRoot *targetModel,string nodeName,TraceSequence *traces)
{

	ContainerNode *currentNode = currentModel->findnodesByID(nodeName);
	ContainerNode *targetNode = targetModel->findnodesByID(nodeName);

	std::unordered_map<string,std::list<TupleObjPrim> > elementAlreadyProcessed; 

	//LOGGER_WRITE(Logger::DEBUG,"Planner::compareModels TRACES =>\n"+traces->exportToString());

	AdaptationModel  *adaptationModel =    factory.createAdaptationModel();


	for (std::list<ModelTrace*>::iterator iterator = traces->traces.begin(), end = traces->traces.end(); iterator != end; ++iterator)
	{
		ModelTrace *trace = *iterator;
		KMFContainer *modelElement = targetModel->findByPath(trace->srcPath);

		if(trace->refName.compare("components") ==0)
		{
			if(trace->srcPath.compare(targetNode->path()) == 0)
			{

				if(dynamic_cast<ModelAddTrace*>(trace) != 0)
				{
					KMFContainer *elemToAdd=targetModel->findByPath(((ModelAddTrace*)trace)->previousPath);
					adaptationModel->addadaptations(adapt(AddInstance, elemToAdd));
				}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
				{
					KMFContainer *elemToAdd=currentModel->findByPath(((ModelRemoveTrace*)trace)->objPath);
					adaptationModel->addadaptations(adapt(RemoveInstance, elemToAdd));
				}

			}

		}else if(trace->refName.compare("hosts") ==0)
		{

			if(trace->srcPath.compare(targetNode->path()) == 0)
			{
				if(trace->srcPath.compare(targetNode->path()) == 0)
				{
					if(dynamic_cast<ModelAddTrace*>(trace) != 0)
					{
						KMFContainer *elemToAdd=targetModel->findByPath(((ModelAddTrace*)trace)->previousPath);
						adaptationModel->addadaptations(adapt(AddInstance, elemToAdd));
					}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
					{
						KMFContainer *elemToAdd=currentModel->findByPath(((ModelRemoveTrace*)trace)->objPath);
						adaptationModel->addadaptations(adapt(RemoveInstance, elemToAdd));
					}

				}

			}

		}else if(trace->refName.compare("groups") ==0)
		{

			if(trace->srcPath.compare(targetNode->path()) == 0)
			{
				if(trace->srcPath.compare(targetNode->path()) == 0)
				{
					if(dynamic_cast<ModelAddTrace*>(trace) != 0)
					{
						KMFContainer *elemToAdd=targetModel->findByPath(( (ModelAddTrace*)trace)->previousPath);
						adaptationModel->addadaptations(adapt(AddInstance, elemToAdd));
					}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
					{
						KMFContainer *elemToAdd=currentModel->findByPath(( (ModelRemoveTrace*)trace)->objPath);
						adaptationModel->addadaptations(adapt(RemoveInstance, elemToAdd));
						adaptationModel->addadaptations(adapt(StopInstance, elemToAdd));
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
								adaptationModel->addadaptations(adapt(AddInstance, channel));
								tuple.add(elementAlreadyProcessed);
							}

						}
						adaptationModel->addadaptations(adapt(AddBinding, binding));

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
										adaptationModel->addadaptations(adapt(RemoveInstance, channel));
										tuple.add(elementAlreadyProcessed);
									}

															   }

							}
						}
						adaptationModel->addadaptations(adapt(RemoveBinding, binding));
					}

				}

			}

		}else if(trace->refName.compare("typeDefinition") ==0)
		{
			if(dynamic_cast<Instance*>(modelElement) != 0)
			{





			}



		}else if(trace->refName.compare("started") ==0)
		{
			if((dynamic_cast<Instance*>(modelElement) != 0) && (dynamic_cast<ModelSetTrace*>(trace) != 0)){



				ModelSetTrace *modelsettrace = (ModelSetTrace*) trace;

				if(modelsettrace->srcPath.compare(targetNode->path()) == 0)
				{
					//TODO CLEAN REMOVE IN CORE
					//   cout << "HaraKiri case " << modelsettrace->toString() << endl;
				}else
				{
					if (modelsettrace->content.compare("true") ==0)
					{

						TupleObjPrim tuple(modelElement,StartInstance);
						if(!tuple.equals(modelElement->path()+"StartInstance",elementAlreadyProcessed))
						{

							adaptationModel->addadaptations(adapt(StartInstance, modelElement));
							tuple.add(elementAlreadyProcessed);
						}
					}else
					{

						TupleObjPrim tuple(modelElement,StopInstance);
						if(!tuple.equals(modelElement->path()+"StopInstance",elementAlreadyProcessed))
						{
							adaptationModel->addadaptations(adapt(StopInstance, modelElement));
							tuple.add(elementAlreadyProcessed);
						}
					}


				}


			}
		}else if(trace->refName.compare("value") ==0){


			if(dynamic_cast<DictionaryValue*>(modelElement) != 0)
			{
				TupleObjPrim tuple(modelElement,UpdateDictionaryInstance);
				if(!tuple.equals(modelElement->path(),elementAlreadyProcessed))
				{
					adaptationModel->addadaptations(adapt(UpdateDictionaryInstance, modelElement));
					tuple.add(elementAlreadyProcessed);
				}
			}else {
				// TODO CHECK cout << modelElement->path() << endl;

			}

		}

	}
	elementAlreadyProcessed.clear();
	return adaptationModel;
}

/*
 * 	UpdateDeployUnit,
    AddDeployUnit,
    RemoveDeployUnit,
    UpdateInstance,
    UpdateBinding,
    UpdateDictionaryInstance,
    AddInstance,
    RemoveInstance,
    AddBinding,
    RemoveBinding,
    StartInstance,
    StopInstance*/
AdaptationModel* Planner::schedule(AdaptationModel *adaptationmodel,std::string nodeName)
{
	ParallelStep *step_StopInstance=factory.createParallelStep();
	ParallelStep *step_RemoveBinding=factory.createParallelStep();
	ParallelStep *step_RemoveInstance=factory.createParallelStep();
	ParallelStep *step_RemoveDeployUnit=factory.createParallelStep();
	ParallelStep *step_UpdateDeployUnit=factory.createParallelStep();
	ParallelStep *step_UpdateBinding=factory.createParallelStep();
	ParallelStep *step_AddDeployUnit=factory.createParallelStep();
	ParallelStep *step_AddInstance=factory.createParallelStep();
	ParallelStep *step_AddBinding=factory.createParallelStep();
	ParallelStep *step_UpdateDictionaryInstance=factory.createParallelStep();
	ParallelStep *step_StartInstance=factory.createParallelStep();

	// schedule
	adaptationmodel->orderedPrimitiveSet = step_StopInstance;
	step_StopInstance->nextStep=step_RemoveBinding;
	step_RemoveBinding->nextStep=step_RemoveInstance;
	step_RemoveInstance->nextStep=step_RemoveDeployUnit;
	step_RemoveDeployUnit->nextStep=step_UpdateDeployUnit;
	step_UpdateDeployUnit->nextStep=step_UpdateBinding;
	step_UpdateBinding->nextStep=step_AddDeployUnit;
	step_AddDeployUnit->nextStep=step_AddInstance;
	step_AddInstance->nextStep=step_AddBinding;
	step_AddBinding->nextStep=step_UpdateDictionaryInstance;
	step_UpdateDictionaryInstance->nextStep=step_StartInstance;
	step_StartInstance->nextStep=NULL;
	// TODO delete in memory 

	//STOP INSTANCEs
	// REMOVE BINDINGS
	// REMOVE INSTANCEs
	// REMOVE DEPLOYUNITS
	// UPDATE DEPLOYUNITS
	// ADD DEPLOYUNITS
	// ADD INSTANCES
	// ADD BINDINGs
	// UPDATE DICTIONARYs
	// START INSTANCEs

	for (std::unordered_map<string,AdaptationPrimitive*>::iterator it = adaptationmodel->adaptations.begin();  it != adaptationmodel->adaptations.end(); ++it)
	{
		AdaptationPrimitive *adaptation = it->second;

		if(adaptation->primitiveType.compare(TO_STRING_Primitives(AddDeployUnit))==0)
		{
			step_AddDeployUnit->addadaptations(adaptationmodel->findadaptationsByID(adaptation->internalGetKey()));
		}else 	if(adaptation->primitiveType.compare(TO_STRING_Primitives(AddInstance))==0)
		{
			step_AddInstance->addadaptations(adaptationmodel->findadaptationsByID(it->first));
		}else if(adaptation->primitiveType.compare(TO_STRING_Primitives(StartInstance))==0)
		{
			step_StartInstance->addadaptations(adaptationmodel->findadaptationsByID(it->first));
		}else if(adaptation->primitiveType.compare(TO_STRING_Primitives(StopInstance))==0)
		{
			step_StopInstance->addadaptations(adaptationmodel->findadaptationsByID(it->first));
		}else if(adaptation->primitiveType.compare(TO_STRING_Primitives(RemoveInstance))==0)
		{
			step_StopInstance->addadaptations(adaptationmodel->findadaptationsByID(it->first));
		}else if(adaptation->primitiveType.compare(TO_STRING_Primitives(UpdateDictionaryInstance))==0){

			step_UpdateDictionaryInstance->addadaptations(adaptationmodel->findadaptationsByID(it->first));
		}else
		{

			LOGGER_WRITE(Logger::ERROR,"Scheduler TODO manage => "+	adaptation->primitiveType);

		}
	}



	//STOP INSTANCEs
	// REMOVE BINDINGS
	// REMOVE INSTANCEs
	// REMOVE DEPLOYUNITS
	// UPDATE DEPLOYUNITS
	// ADD DEPLOYUNITS
	// ADD INSTANCES
	// ADD BINDINGs
	// UPDATE DICTIONARYs
	// START INSTANCEs





	return adaptationmodel;
}
