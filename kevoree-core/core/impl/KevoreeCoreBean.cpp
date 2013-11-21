#include <kevoree-core/core/KevoreeCoreBean.h>



KevoreeCoreBean::KevoreeCoreBean(){
	currentModel=NULL;
	nodeInstance=NULL;
	
}
std::string KevoreeCoreBean::getNodeName(){
	return nodeName;
}

ContainerRoot *KevoreeCoreBean::getLastModel(){
	return currentModel;
}
void KevoreeCoreBean::updateModel(ContainerRoot *_model){
	internal_update_model(_model);
}



void KevoreeCoreBean::checkBootstrapNode(ContainerRoot *currentModel)
{
	if (nodeInstance == NULL) 
	{
         ContainerNode *foundNode = currentModel->findnodesByID(getNodeName());
                if(foundNode != NULL)
                {
                   nodeInstance = _bootstraper->bootstrapNodeType(currentModel, getNodeName(), this);
                    
                    if(nodeInstance != NULL)
                    {
                        nodeInstance->startNode();
                     
                    } else 
                    {
                      cout << "ERROR TypeDef installation fail !" << endl;
                    }
                } else {
                       cout << "ERROR Node instance name {} not found in bootstrap model !" << getNodeName() << endl;
                }
    }
		
}


bool KevoreeCoreBean::internal_update_model(ContainerRoot *proposedNewModel){
	
    if (proposedNewModel->findnodesByID(getNodeName()) == NULL) {
        cout << "Asking for update with a NULL model or node name (" << getNodeName()<< ") was not found in target model !" << endl;
        return false;
    }
    // TODO CALL MODEL CHECKER ON proposedNewModel
    
    checkBootstrapNode(proposedNewModel);
    
    ContainerRoot *currentModel = getLastModel(); 
    cout << "Before listeners PreCheck !" << endl;
    
  //modelListeners.preUpdate(currentModel, readOnlyNewModel);
    

    AdaptationModel *adaptationModel = nodeInstance->plan(currentModel, proposedNewModel);
	cout << "Adaptation model size {}" << adaptationModel->adaptations.size() << endl;
    
	ContainerNode *rootNode = currentModel->findnodesByID(getNodeName());
	
	
}

std::list<ContainerRoot*> KevoreeCoreBean::getPreviousModels(){
	return models;	
}

void KevoreeCoreBean::setBootstraper(Bootstraper *b)
{
	_bootstraper = b;
}


void KevoreeCoreBean::setNodeName(std::string nn)
{
	this->nodeName = nn;
}

void KevoreeCoreBean::start(){
	  if (getNodeName().compare("")==0) 
	  {
            setNodeName("node0");
      }
      modelListeners.start(getNodeName());
      cout << "Kevoree Start event : node name = " << getNodeName() << endl;
      currentModel = factory.createContainerRoot();

}


void KevoreeCoreBean::stop(){
	    cout << "Kevoree Core will be stopped !" << endl;
        modelListeners.stop();
	
}

bool KevoreeCoreBean::checkModel(ContainerRoot *targetModel){
	
	
}
