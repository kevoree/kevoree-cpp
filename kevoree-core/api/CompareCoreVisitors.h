#ifndef __CompareCoreVisitors_H
#define __CompareCoreVisitors_H

/**
 * Author: jedartois@gmail.com
 * Date: 20/11/13
 * Time: 17:39
 */


#include <kevoree-core/api/adaptation/AdaptationModel.h>
#include <kevoree-core/api/PreCompare.h>


#include <kevoree-core/model/kevoree/DeployUnit.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <microframework/api/KMFContainer.h>
#include <microframework/api/trace/TraceSequence.h>

#include <set>
#include <string>
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
    TargetNodeVisitor (ContainerRoot *targetModel,ContainerNode *currentNode,std::set<std::string> *foundDeployUnitsToRemove,TraceSequence  *seq);
    ~TargetNodeVisitor();
    void visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent);
    
private:
	ContainerRoot *targetModel;
    ContainerNode *currentNode;
    TraceSequence *seq;
    std::set<std::string> *foundDeployUnitsToRemove;
};



#endif
