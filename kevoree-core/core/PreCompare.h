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
//todo rename PreTraceGenerator
class PreCompare 
{
	public:
	PreCompare(std::string nodename);

TraceSequence *createTraces(ContainerRoot *currentModel,ContainerRoot *targetModel);
void createTracesGroupsAndChannels(ContainerRoot *currentModel,ContainerRoot *targetModel,ContainerNode *currentNode,ContainerNode *targetNode,TraceSequence *traces);	

ModelCompare modelCompare;
std::string nodeName;
};



#endif
