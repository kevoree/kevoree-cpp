#ifndef __PreCompare_H
#define __PreCompare_H


#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <microframework/api/compare/ModelCompare.h>
#include <kevoree-core/api/adaptation/AdaptationModel.h>
#include <kevoree-core/api/CompareCoreVisitors.h>
#include <microframework/api/utils/any.h>
#include <list>
#include <string>
#include <set>


class PreCompare 
{
public:
	PreCompare(std::string nodename);

	TraceSequence *createTraces(ContainerRoot *currentModel,ContainerRoot *targetModel);
	void createTracesGroupsAndChannels(ContainerRoot *currentModel,ContainerRoot *targetModel,ContainerNode *currentNode,ContainerNode *targetNode,TraceSequence *traces);

private:
	void fillPort(std::map<string,Port*> ports,ContainerRoot *currentModel,TraceSequence *traces);
	ModelCompare modelCompare;
	std::string nodeName;
};



#endif
