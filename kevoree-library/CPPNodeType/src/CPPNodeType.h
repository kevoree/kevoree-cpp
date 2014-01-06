#ifndef __CPPNODETYPE_H_
#define __CPPNODETYPE_H_

#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/AbstractNodeType.h>

#include <kevoree-core/core/adaptation/AdaptationPrimitive.h>
#include "Planner.h"
#include "CommandMapper.h"
#include <MavenResolver.h>
#include "deploy/PrimitiveCommandExecutionHelper.h"


#pragma NodeType "CPPNode"
#pragma GroupName "org.kevoree.library"
#pragma Version "1.0"
class CPPNodeType : public AbstractNodeType
{
public:
	CPPNodeType();
	virtual ~CPPNodeType();
    void start();
    void stop();
    AdaptationModel *plan(ContainerRoot *actualModel,ContainerRoot *targetModel,TraceSequence *traces);
    bool execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance);
    PrimitiveCommand* getPrimitive(AdaptationPrimitive *primitive);

Planner planner;
CommandMapper *mapper;
PrimitiveCommandExecutionHelper execPrimitive;

};

#endif /*CPPNODETYPE_H_*/
