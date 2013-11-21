#ifndef __CPPNODETYPE_H_
#define __CPPNODETYPE_H_

#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/INodeType.h>
#include <kevoree-core/model/kevoreeadaptation/DefaultkevoreeadaptationFactory.h>
#include "Planner.h"


class CPPNodeType : public INodeType
{
public:
	CPPNodeType();
	virtual ~CPPNodeType();
    void startNode();
    void stopNode();
    AdaptationModel *plan(ContainerRoot *actualModel,ContainerRoot *targetModel,TraceSequence *traces);
    PrimitiveCommand getPrimitive(PrimitiveCommand primitive);
    
Planner planner;
};

#endif /*CPPNODETYPE_H_*/
