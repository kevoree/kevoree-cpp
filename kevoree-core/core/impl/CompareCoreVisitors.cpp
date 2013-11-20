#include <kevoree-core/core/CompareCoreVisitors.h>



CurrentNodeVisitor::~CurrentNodeVisitor(){
		
		
}

CurrentNodeVisitor::CurrentNodeVisitor (ContainerNode *_currentNode,std::set<std::string> *_foundDeployUnitsToRemove)
{
	this->currentNode = _currentNode;
	this->foundDeployUnitsToRemove = _foundDeployUnitsToRemove;
}


void CurrentNodeVisitor::visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent)
{
			if(typeid(elem) == typeid(DeployUnit*))
			{
                   foundDeployUnitsToRemove->insert(elem->path());
            }
               //optimization purpose
            if( (typeid(elem) == typeid(ContainerNode) && elem != currentNode))
            {
                   noChildrenVisit();
                   noReferencesVisit();
            }
}


TargetNodeVisitor::TargetNodeVisitor (TraceSequence *_seq,ContainerNode *_targetNode)
{
	this->seq = _seq;
	this->targetNode = _targetNode;
}


void TargetNodeVisitor::visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent)
{

}



TargetNodeVisitor::~TargetNodeVisitor(){
		
		
}
