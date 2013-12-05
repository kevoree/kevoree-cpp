#ifndef __PrimitiveCommandExecutionHelper_H
#define __PrimitiveCommandExecutionHelper_H

#include <kevoree-core/core/KevoreeCoreBean.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include "KevoreeParDeployPhase.h"
#include <microframework/api/utils/Runnable.h>

class PrimitiveCommandExecutionHelper : public Runnable {
public:

	//fun execute(rootNode: ContainerNode, adaptionModel: AdaptationModel, nodeInstance: NodeType, afterUpdateFunc: ()->Boolean, preRollBack: ()->Boolean, postRollback: ()-> Boolean): Boolean {;
	static bool execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance);
	//    private fun executeStep(rootNode: ContainerNode, step: ParallelStep, nodeInstance: NodeType, phase: KevoreeParDeployPhase, preRollBack: ()-> Boolean): Boolean {
	static bool executeStep(ContainerNode *rootNode,ParallelStep *step,AbstractNodeType *nodeInstance,KevoreeParDeployPhase *phase);
};
#endif
