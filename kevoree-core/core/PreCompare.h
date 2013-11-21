#ifndef __PreCompare_H
#define __PreCompare_H


#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <microframework/api/compare/ModelCompare.h>
#include <kevoree-core/model/kevoreeadaptation/AdaptationModel.h>
#include <kevoree-core/model/kevoreeadaptation/DefaultkevoreeadaptationFactory.h>
#include <kevoree-core/core/CompareCoreVisitors.h>
#include <microframework/api/utils/any.h>
#include <list>
#include <string>
#include <set>
#include <kevoree-core/core/api/Primitives.h>

class PreCompare 
{
	PreCompare(std::string nodename);
	
public:
static AdaptationPrimitive* adapt(Primitives p,KMFContainer *elem,ContainerRoot *model);
TraceSequence *createTraces(ContainerRoot *currentModel,ContainerRoot *targetModel,AdaptationModel  *adaptationModel);
void createTracesGroupsAndChannels(ContainerRoot *currentModel,ContainerRoot *targetModel,ContainerNode *currentNode,ContainerNode *targetNode,TraceSequence *traces);	
static DefaultkevoreeadaptationFactory factoryAdaptation;
ModelCompare modelCompare;
std::string nodeName;
};



#endif
