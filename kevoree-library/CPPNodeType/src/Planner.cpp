#include "Planner.h"
#include <map>
#include <iostream>
#include <queue>
#include <string>

// http://cpp.developpez.com/faq/cpp/?page=STL#STL_custom_sort

/*#include <iostream>
#include <queue>

using namespace std;

int main()
{
   typedef queue<int> file;
   //On crée une file d’attente:
   file ma_file;
   //On ajoute quelques éléments :
   ma_file.push(1);
   ma_file.push(2);
   ma_file.push(3);

  while (!ma_file.empty()) //tant que la file n’est pas vide
  {
  cout << ma_file.front() << endl; //on affiche l’élément de tête
   ma_file.pop();                  //puis on le supprime
   }
}*/


AdaptationPrimitive* Planner::adapt(Primitives p,KMFContainer *elem)
{
	AdaptationPrimitive *ccmd = new AdaptationPrimitive();
	ccmd->name =TO_STRING_Primitives(p);
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
	ParallelStep *step = new ParallelStep();
	step->name = "global";
	adaptationModel->addsteps(step);

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
					step->addadaptations(adapt(AddInstance, elemToAdd));
				}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
				{
					KMFContainer *elemToAdd=currentModel->findByPath(((ModelRemoveTrace*)trace)->objPath);
					step->addadaptations(adapt(StopInstance, elemToAdd));
					step->addadaptations(adapt(RemoveInstance, elemToAdd));
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
						step->addadaptations(adapt(AddInstance, elemToAdd));
					}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
					{
						KMFContainer *elemToAdd=currentModel->findByPath(((ModelRemoveTrace*)trace)->objPath);
						step->addadaptations(adapt(StopInstance, elemToAdd));
						step->addadaptations(adapt(RemoveInstance, elemToAdd));
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
						step->addadaptations(adapt(AddInstance, elemToAdd));
					}else if(dynamic_cast<ModelRemoveTrace*>(trace) != 0)
					{
						KMFContainer *elemToAdd=currentModel->findByPath(( (ModelRemoveTrace*)trace)->objPath);
						step->addadaptations(adapt(StopInstance, elemToAdd));
						step->addadaptations(adapt(RemoveInstance, elemToAdd));

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
								step->addadaptations(adapt(AddInstance, channel));
								tuple.add(elementAlreadyProcessed);
							}

						}
						step->addadaptations(adapt(AddBinding, binding));

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
										step->addadaptations(adapt(RemoveInstance, channel));
										tuple.add(elementAlreadyProcessed);
									}

								}

							}
						}
						step->addadaptations(adapt(RemoveBinding, binding));
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

							step->addadaptations(adapt(StartInstance, modelElement));
							tuple.add(elementAlreadyProcessed);
						}
					}else
					{

						TupleObjPrim tuple(modelElement,StopInstance);
						if(!tuple.equals(modelElement->path()+"StopInstance",elementAlreadyProcessed))
						{
							step->addadaptations(adapt(StopInstance, modelElement));
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
					step->addadaptations(adapt(UpdateDictionaryInstance, modelElement));
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

