#include <core/KevoreeCoreBean.h>


KevoreeCoreBean::KevoreeCoreBean(){
	model=NULL;
	
}
std::string KevoreeCoreBean::getNodeName(){
	return nodeName;
}



ContainerRoot *KevoreeCoreBean::getLastModel(){
	return model;
}
void KevoreeCoreBean::updateModel(ContainerRoot *_model){
	internal_update_model(_model);
}

bool KevoreeCoreBean::internal_update_model(ContainerRoot *proposedNewModel){
	
    if (proposedNewModel->findnodesByID(getNodeName()) == NULL) {
        cout << "Asking for update with a NULL model or node name (" << getNodeName()<< ") was not found in target model !" << endl;
        return false;
    }
    // TODO  checker proposedNewModel
    
    ContainerRoot *currentModel = getLastModel(); 
    cout << "Before listeners PreCheck !" << endl;
   // val preCheckResult = modelListeners.preUpdate(currentModel, readOnlyNewModel)
    
    
    
	
	
}

std::list<ContainerRoot> KevoreeCoreBean::getPreviousModels(){
	
	
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
      model = factory.createContainerRoot();

}


void KevoreeCoreBean::stop(){
	    cout << "Kevoree Core will be stopped !" << endl;
        modelListeners.stop();
	
}

bool KevoreeCoreBean::checkModel(ContainerRoot *targetModel){
	
	
}
