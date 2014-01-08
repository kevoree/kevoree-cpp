#include "Planner.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <string>

AdaptationPrimitive* Planner::adapt(Primitives p,KMFContainer *elem)
{
	AdaptationPrimitive *ccmd = new AdaptationPrimitive();
	ccmd->primitiveType =p;
	ccmd->priority = Priority_Primitives(p);
	ccmd->ref = elem;
	return ccmd;
}


AdaptationModel *Planner::compareModels(ContainerRoot *currentModel,ContainerRoot *targetModel,string nodeName,TraceSequence *traces)
{

	ContainerNode *currentNode = currentModel->findnodesByID(nodeName);
	ContainerNode *targetNode = targetModel->findnodesByID(nodeName);

	std::map<string,std::list<TupleObjPrim> > elementAlreadyProcessed;

	//LOGGER_WRITE(Logger::DEBUG,"Planner::compareModels TRACES =>\n"+traces->exportToString());

	AdaptationModel  *adaptationModel =   new AdaptationModel();


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
					adaptationModel->add(adapt(AddInstance, elemToAdd));
				}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
				{
					KMFContainer *elemToAdd=currentModel->findByPath(((ModelRemoveTrace*)trace)->objPath);
					adaptationModel->add(adapt(StopInstance, elemToAdd));
					adaptationModel->add(adapt(RemoveInstance, elemToAdd));
				}

			}

		}else if(trace->refName.compare("hosts") ==0)
		{


			if(trace->srcPath.compare(targetNode->path()) == 0)
			{
				if(dynamic_cast<ModelAddTrace*>(trace) != 0)
				{
					KMFContainer *elemToAdd=targetModel->findByPath(((ModelAddTrace*)trace)->previousPath);
					adaptationModel->add(adapt(AddInstance, elemToAdd));
				}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
				{
					KMFContainer *elemToAdd=currentModel->findByPath(((ModelRemoveTrace*)trace)->objPath);
					adaptationModel->add(adapt(StopInstance, elemToAdd));
					adaptationModel->add(adapt(RemoveInstance, elemToAdd));
				}

			}

		}else if(trace->refName.compare("groups") ==0)
		{

			if(trace->srcPath.compare(targetNode->path()) == 0)
			{
				if(dynamic_cast<ModelAddTrace*>(trace) != 0)
				{
					KMFContainer *elemToAdd=targetModel->findByPath(( (ModelAddTrace*)trace)->previousPath);
					adaptationModel->add(adapt(AddInstance, elemToAdd));
				}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
				{
					KMFContainer *elemToAdd=currentModel->findByPath(( (ModelRemoveTrace*)trace)->objPath);
					adaptationModel->add(adapt(StopInstance, elemToAdd));
					adaptationModel->add(adapt(RemoveInstance, elemToAdd));

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
								adaptationModel->add(adapt(AddInstance, channel));
								tuple.add(elementAlreadyProcessed);
							}

						}
						adaptationModel->add(adapt(AddBinding, binding));

					}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
					{
						MBinding *previousBinding=(MBinding*)currentModel->findByPath(modeladdtrace->srcPath);
						Channel *oldChannel=previousBinding->hub;
						//check if not no current usage of this channel
						bool stillUsed = (channel != NULL);
						if(channel != NULL)
						{
							for (std::map<string,MBinding*>::iterator iterator = channel->bindings.begin(), end = channel->bindings.end(); iterator != end; ++iterator)
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
										adaptationModel->add(adapt(RemoveInstance, channel));
										tuple.add(elementAlreadyProcessed);
									}

								}

							}
						}
						adaptationModel->add(adapt(RemoveBinding, binding));
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

							adaptationModel->add(adapt(StartInstance, modelElement));
							tuple.add(elementAlreadyProcessed);
						}
					}else
					{

						TupleObjPrim tuple(modelElement,StopInstance);
						if(!tuple.equals(modelElement->path()+"StopInstance",elementAlreadyProcessed))
						{
							adaptationModel->add(adapt(StopInstance, modelElement));
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
					adaptationModel->add(adapt(UpdateDictionaryInstance, modelElement));
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


AdaptationModel* Planner::schedule(AdaptationModel *adaptionModel,std::string nodeName)
{

	struct {
		bool operator()(const AdaptationPrimitive* lhs, const AdaptationPrimitive* rhs)
		{
			return lhs->priority < rhs->priority;
		}
	} customLess;
	std::sort( adaptionModel->adaptations.begin(), adaptionModel->adaptations.end(), customLess );
	/*
	for (std::vector<AdaptationPrimitive*>::iterator it=adaptionModel->adaptations.begin(); it!=adaptionModel->adaptations.end(); ++it){
		AdaptationPrimitive *adaptation = *it;
		KMFContainerImpl *c = (KMFContainerImpl*)adaptation->ref;
		cout << " " << adaptation->primitiveType<< " "<< c->metaClassName() << " key "<< c->internalGetKey() << "  path " << adaptation->ref->path() << endl;
	}*/


	return adaptionModel;
}
