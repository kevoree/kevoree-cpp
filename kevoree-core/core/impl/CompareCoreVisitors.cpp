#include <kevoree-core/core/CompareCoreVisitors.h>



CurrentNodeVisitor::~CurrentNodeVisitor(){
		
		
}

CurrentNodeVisitor::CurrentNodeVisitor (ContainerNode *_currentNode,std::set<std::string> *_foundDeployUnitsToRemove)
{
	cout << "BEGIN -- CurrentNodeVisitor::CurrentNodeVisitor" << endl;
	this->currentNode = _currentNode;
	this->foundDeployUnitsToRemove = _foundDeployUnitsToRemove;
	cout << "END -- CurrentNodeVisitor::CurrentNodeVisitor" << endl;
}


void CurrentNodeVisitor::visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent)
{
	//cout << "BEGIN -- CurrentNodeVisitor" << endl;
			if(	dynamic_cast<DeployUnit*>(elem) != 0)
			{
			//	cout << "Insert" << elem->path() << endl;
                   foundDeployUnitsToRemove->insert(elem->path());
            }
               //optimization purpose
            if( (	dynamic_cast<ContainerNode*>(elem) != 0 && elem != currentNode))
            {
                   noChildrenVisit();
                   noReferencesVisit();
            }
            
   // cout << "END -- CurrentNodeVisitor" << endl;
}


TargetNodeVisitor::TargetNodeVisitor (ContainerRoot *_targetModel,ContainerNode *_currentNode,std::set<std::string> *_foundDeployUnitsToRemove,TraceSequence  *_seq)
{
	
	//cout << "BEGIN -- TargetNodeVisitor::CurrentNodeVisitor" << endl;
	this->currentNode = _currentNode;
	this->seq = _seq;
	this->foundDeployUnitsToRemove = _foundDeployUnitsToRemove;
	this->targetModel = _targetModel;
	//cout << "BEGIN -- TargetNodeVisitor::CurrentNodeVisitor" << endl;
}


void TargetNodeVisitor::visit (KMFContainer * elem, string refNameInParent,KMFContainer * parent)
{
	//cout << "BEGIN -- TargetNodeVisitor" << endl;
	if(	dynamic_cast<DeployUnit*>(elem) != 0)
	{
	    DeployUnit *deployunit = (DeployUnit*)elem;
	    std::set<string>::iterator srcPath;

	    srcPath = foundDeployUnitsToRemove->find(elem->path());
	    if(srcPath != foundDeployUnitsToRemove->end())
	    {
		    ModelAddTrace *modeladdtrace = new ModelAddTrace(elem->path(),*srcPath,"",deployunit->name);
			seq->traces.push_back(modeladdtrace);
		}else 
		{
			   foundDeployUnitsToRemove->erase(elem->path());
		}


	}
	   //optimization purpose
       if( (dynamic_cast<ContainerNode*>(elem) != 0  && elem != currentNode))
       {
                 noChildrenVisit();
                 noReferencesVisit();
       }
       //	cout << "END -- TargetNodeVisitor" << endl;
}


TargetNodeVisitor::~TargetNodeVisitor(){
		
		
}
