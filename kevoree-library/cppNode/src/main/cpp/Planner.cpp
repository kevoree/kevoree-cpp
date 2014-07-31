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

	std::map<string,std::tuple<KMFContainer*,Primitives> > elementAlreadyProcessed;


	LOGGER_WRITE(Logger::DEBUG,"Planner::compareModels TRACES =>\n"+traces->exportToString());

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
			//std::cout << trace->srcPath << " "<< targetNode->path() <<trace->srcPath.compare(targetNode->path()) <<  std::endl;
			if(dynamic_cast<Channel*>(targetNode->findByPath(trace->srcPath)) == 0)
			{



				if(dynamic_cast<ModelAddTrace*>(trace) != 0)
				{
					ModelAddTrace *modeladdtrace = (ModelAddTrace*) trace;
					MBinding *binding=(MBinding*)targetModel->findByPath(modeladdtrace->previousPath);
					Channel *channel=NULL;
					if(binding != NULL)
					{
						channel = binding->hub;
					}
					if(binding != NULL)
					{

						if(elementAlreadyProcessed.find(binding->path()+"/AddBinding") == elementAlreadyProcessed.end()){
							adaptationModel->add(adapt(AddBinding, binding));
							auto tuple = std::make_tuple (binding,AddBinding);
							elementAlreadyProcessed[binding->path()+"/AddBinding"] = tuple;
						}

					}

					if(channel != NULL){
						Channel *exist_channel=(Channel*)currentModel->findByPath(channel->path());
						if(elementAlreadyProcessed.find(channel->path()+"/AddInstance") == elementAlreadyProcessed.end()){
							if((exist_channel !=NULL && exist_channel->bindings.size() == 0) || exist_channel ==NULL){
								adaptationModel->add(adapt(AddInstance, channel));
								auto tuple = std::make_tuple (channel,AddInstance);
								elementAlreadyProcessed[channel->path()+"/AddInstance"] = tuple;
							}
						}
					}else
					{
						LOGGER_WRITE(Logger::ERROR,"Channel not found");
					}

				}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
				{
					ModelRemoveTrace *removetrace = (ModelRemoveTrace*)trace;
				//	LOGGER_WRITE(Logger::DEBUG,"ModelRemoveTrace "+removetrace->toString());
					Channel *channel;
					Channel *oldChannel;
					/* the previous binding */
					MBinding *previousbinding=(MBinding*)currentModel->findByPath(removetrace->objPath);

					if(previousbinding !=NULL)
					{
						// the channel exist in the target model ?
						channel=(Channel*)targetModel->findByPath(previousbinding->hub->path());
						// old channel
						oldChannel = previousbinding->hub;
					}else
					{
						LOGGER_WRITE(Logger::ERROR,"Try to remove a binding but didn't find it !!");
					}


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
								break;
							}
						}


					}else {
						LOGGER_WRITE(Logger::DEBUG,"Channel is null");
					}
					if(!stillUsed )
					{
						if(elementAlreadyProcessed.find(oldChannel->path()+"/RemoveInstance") == elementAlreadyProcessed.end()){
							adaptationModel->add(adapt(StopInstance, oldChannel));
							adaptationModel->add(adapt(RemoveInstance, oldChannel));
							auto tuple = std::make_tuple (oldChannel,RemoveInstance);
							elementAlreadyProcessed[oldChannel->path()+"/RemoveInstance"] = tuple;

						}else {
						//	LOGGER_WRITE(Logger::DEBUG,"RemoveInstance channel already stopped "+oldChannel->path()+"/RemoveInstance");
						}
					}
					if(previousbinding != NULL)
					{

						if(elementAlreadyProcessed.find(previousbinding->path()+"/RemoveBinding") == elementAlreadyProcessed.end()){
							adaptationModel->add(adapt(RemoveBinding, previousbinding));
							auto tuple = std::make_tuple (previousbinding,RemoveBinding);
							elementAlreadyProcessed[previousbinding->path()+"/RemoveBinding"] = tuple;
						}else
						{
							//LOGGER_WRITE(Logger::WARNING,"RemoveBinding "+previousbinding->path());
						}
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

						if(elementAlreadyProcessed.find(modelElement->path()+"/StartInstance") == elementAlreadyProcessed.end()){
							adaptationModel->add(adapt(StartInstance, modelElement));
							auto tuple = std::make_tuple (modelElement,RemoveInstance);
							elementAlreadyProcessed[modelElement->path()+"/StartInstance"] = tuple;

						}else {
							LOGGER_WRITE(Logger::DEBUG,"StartInstance already in queue "+modelElement->path());
						}

					}else
					{

						if(elementAlreadyProcessed.find(modelElement->path()+"/StopInstance") == elementAlreadyProcessed.end()){
							adaptationModel->add(adapt(StopInstance, modelElement));
							auto tuple = std::make_tuple (modelElement,StopInstance);
							elementAlreadyProcessed[modelElement->path()+"/StopInstance"] = tuple;

						}else {
							LOGGER_WRITE(Logger::DEBUG,"StopInstance already in queue"+modelElement->path());
						}

					}


				}


			}
		}else if(trace->refName.compare("value") ==0){


			if(dynamic_cast<DictionaryValue*>(modelElement) != 0)
			{

				if(elementAlreadyProcessed.find(modelElement->path()+"/UpdateDictionaryInstance") == elementAlreadyProcessed.end()){
					adaptationModel->add(adapt(UpdateDictionaryInstance,  modelElement->eContainer()->eContainer()));
					auto tuple = std::make_tuple (modelElement,StopInstance);
					elementAlreadyProcessed[modelElement->path()+"/UpdateDictionaryInstance"] = tuple;

				}else {
					LOGGER_WRITE(Logger::WARNING,"RemoveInstance channel already stopped");
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
