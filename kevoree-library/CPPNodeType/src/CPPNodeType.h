#ifndef __CPPNODETYPE_H_
#define __CPPNODETYPE_H_


#include <kevoree-core/api/AbstractNodeType.h>
#include <kevoree-core/api/adaptation/AdaptationPrimitive.h>
#include <microframework/api/trace/TraceSequence.h>
#include "Planner.h"
#include "CommandMapper.h"
#include <maven-resolver/api/MavenResolver.h>
#include "deploy/PrimitiveCommandExecutionHelper.h"


#pragma NodeType "CPPNode"
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
