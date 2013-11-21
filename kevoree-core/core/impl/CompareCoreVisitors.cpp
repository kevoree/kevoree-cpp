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
			if(typeid(*elem) == typeid(DeployUnit))
			{
                   foundDeployUnitsToRemove->insert(elem->path());
            }
               //optimization purpose
            if( (typeid(*elem) == typeid(ContainerNode) && elem != currentNode))
            {
                   noChildrenVisit();
                   noReferencesVisit();
            }
}


TargetNodeVisitor::TargetNodeVisitor (ContainerRoot *_targetModel,ContainerNode *_currentNode,std::set<std::string> *_foundDeployUnitsToRemove,AdaptationModel  *_adaptationModel)
{
	this->currentNode = _currentNode;
	this->adaptationModel = _adaptationModel;
	this->foundDeployUnitsToRemove = _foundDeployUnitsToRemove;
	this->targetModel = _targetModel;
}


void TargetNodeVisitor::visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent)
{

	if(typeid(*elem) == typeid(DeployUnit))
	{
		PreCompare::adapt(AddDeployUnit,elem,targetModel);
	    adaptationModel->addadaptations(PreCompare::adapt(AddDeployUnit, elem, targetModel));
	    
	    foundDeployUnitsToRemove->erase(elem->path());
	}
	   //optimization purpose
       if( (typeid(*elem) == typeid(ContainerNode) && elem != currentNode))
       {
                 noChildrenVisit();
                 noReferencesVisit();
       }
}


TargetNodeVisitor::~TargetNodeVisitor(){
		
		
}
