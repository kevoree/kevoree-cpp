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
#include  <kevoree-core/model/kevoree/ContainerNode.h>
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
    TargetNodeVisitor (TraceSequence *seq,ContainerNode *targetNode);
    ~TargetNodeVisitor();
    void visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent);
private:
    TraceSequence *seq;
    ContainerNode *targetNode;
};



#endif
