#ifndef __PrimitiveCommandExecutionHelper_H
#define __PrimitiveCommandExecutionHelper_H

#include <kevoree-core/core/KevoreeCoreBean.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include "DeployPhase.h"
#include <string>
class PrimitiveCommandExecutionHelper{
public:
	 bool execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance);
	 bool executeStep(ContainerNode *rootNode,ParallelStep *step,AbstractNodeType *nodeInstance,DeployPhase *phase);
	 bool cleanParallelStep(ParallelStep *step);
};
#endif
