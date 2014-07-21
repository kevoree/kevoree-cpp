#ifndef __Planner_H
#define __Planner_H


#include <kevoree-core/api/adaptation/AdaptationModel.h>
#include <kevoree-core/api/adaptation/AdaptationPrimitive.h>
#include <kevoree-core/model/kevoree/kevoree.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/Channel.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
#include <microframework/api/trace/TraceSequence.h>
#include <set>
#include <map>
#include "Primitives.h"
#include <tuple>

class Planner 
{
	public:
	AdaptationModel* compareModels(ContainerRoot *actualModel,ContainerRoot *targetModel,string nodeName,TraceSequence *traces);
	AdaptationModel* schedule(AdaptationModel *adaptationModel,std::string nodeName);
	private:
	AdaptationPrimitive* adapt(Primitives p,KMFContainer *elem);
};

#endif
