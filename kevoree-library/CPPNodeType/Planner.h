#ifndef __Planner_H
#define __Planner_H

#include <kevoree-core/model/kevoreeadaptation/kevoreeadaptation.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/model/kevoreeadaptation/AdaptationModel.h>
#include <kevoree-core/model/kevoreeadaptation/DefaultkevoreeadaptationFactory.h>	
#include <kevoree-core/model/kevoree/Instance.h>

class Planner 
{
	public:
	AdaptationModel* compareModels(ContainerRoot *actualModel,ContainerRoot *targetModel,string nodeName,TraceSequence *traces);
	
	DefaultkevoreeadaptationFactory factory;	
};






#endif
