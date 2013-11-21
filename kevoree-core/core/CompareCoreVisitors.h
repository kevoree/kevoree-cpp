#ifndef __CompareCoreVisitors_H
#define __CompareCoreVisitors_H

/**
 * Author: jedartois@gmail.com
 * Date: 20/11/13
 * Time: 17:39
 */
#include <string>
#include <microframework/api/KMFContainer.h>
#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/model/kevoree/DeployUnit.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoreeadaptation/AdaptationModel.h>
#include <kevoree-core/utils/HelperCompare.h>
#include <kevoree-core/core/api/Primitives.h>
#include <kevoree-core/core/PreCompare.h>

#include <set>

class CurrentNodeVisitor :public ModelVisitor
{
  public:
    CurrentNodeVisitor (ContainerNode *currentNode,std::set<std::string> *foundDeployUnitsToRemove);
    ~CurrentNodeVisitor();
    void visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent);
private:
    TraceSequence *seq;
    ContainerNode *currentNode;
    std::set<std::string> *foundDeployUnitsToRemove;
};


class TargetNodeVisitor :public ModelVisitor
{
  public:
    TargetNodeVisitor (ContainerRoot *targetModel,ContainerNode *currentNode,std::set<std::string> *foundDeployUnitsToRemove,AdaptationModel  *adaptationModel);
    ~TargetNodeVisitor();
    void visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent);
private:
	ContainerRoot *targetModel;
    ContainerNode *currentNode;
    AdaptationModel  *adaptationModel;
    std::set<std::string> *foundDeployUnitsToRemove;
};



#endif
