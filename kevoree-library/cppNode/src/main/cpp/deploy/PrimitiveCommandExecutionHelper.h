#ifndef __PrimitiveCommandExecutionHelper_H
#define __PrimitiveCommandExecutionHelper_H

#include <kevoree-core/api/KevoreeCoreBean.h>
#include <kevoree-core/api/Bootstraper.h>
#include "DeployPhase.h"
#include <string>
class PrimitiveCommandExecutionHelper{
public:
	bool execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance);
};
#endif
