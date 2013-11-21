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

			if(	dynamic_cast<DeployUnit*>(elem) != 0)
			{
                   foundDeployUnitsToRemove->insert(elem->path());
            }
               //optimization purpose
            if( (	dynamic_cast<ContainerNode*>(elem) != 0 && elem != currentNode))
            {
                   noChildrenVisit();
                   noReferencesVisit();
            }
}


TargetNodeVisitor::TargetNodeVisitor (ContainerRoot *_targetModel,ContainerNode *_currentNode,std::set<std::string> *_foundDeployUnitsToRemove,TraceSequence  *_seq)
{
	this->currentNode = _currentNode;
	this->seq = _seq;
	this->foundDeployUnitsToRemove = _foundDeployUnitsToRemove;
	this->targetModel = _targetModel;
	
}


void TargetNodeVisitor::visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent)
{

	if(typeid(*elem) == typeid(DeployUnit))
	{

	    DeployUnit *deployunit = (DeployUnit*)elem;
	    std::set<string>::iterator srcPath;
	    srcPath = foundDeployUnitsToRemove->find(elem->path());
	    ModelAddTrace *modeladdtrace = new ModelAddTrace(elem->path(),*srcPath,"",deployunit->name);
	    seq->traces.push_back(modeladdtrace);
	    foundDeployUnitsToRemove->erase(elem->path());
	}
	   //optimization purpose
       if( (dynamic_cast<ContainerNode*>(elem) != 0  && elem != currentNode))
       {
                 noChildrenVisit();
                 noReferencesVisit();
       }
}


TargetNodeVisitor::~TargetNodeVisitor(){
		
		
}
