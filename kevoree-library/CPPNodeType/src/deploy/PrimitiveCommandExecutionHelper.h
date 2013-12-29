#ifndef __PrimitiveCommandExecutionHelper_H
#define __PrimitiveCommandExecutionHelper_H

#include <kevoree-core/core/KevoreeCoreBean.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include "DeployPhase.h"

class PrimitiveCommandExecutionHelper{
public:

	//fun execute(rootNode: ContainerNode, adaptionModel: AdaptationModel, nodeInstance: NodeType, afterUpdateFunc: ()->Boolean, preRollBack: ()->Boolean, postRollback: ()-> Boolean): Boolean {;
	 bool execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance);
	//    private fun executeStep(rootNode: ContainerNode, step: ParallelStep, nodeInstance: NodeType, phase: KevoreeParDeployPhase, preRollBack: ()-> Boolean): Boolean {
	 bool executeStep(ContainerNode *rootNode,ParallelStep *step,AbstractNodeType *nodeInstance,DeployPhase *phase);
	 bool cleanParallelStep(ParallelStep *step);
};
#endif
