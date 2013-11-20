#include <kevoree-core/core/KevoreeCoreBean.h>
#include <kevoree-core/core/CompareCoreVisitors.h>


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

void KevoreeCoreBean::createTracesGroupsAndChannels(ContainerRoot *currentModel,ContainerRoot *targetModel,ContainerNode *currentNode,ContainerNode *targetNode,TraceSequence *traces)
{
	 for ( std::unordered_map<string,ContainerNode*>::const_iterator it = targetNode->hosts.begin();  it != targetNode->hosts.end(); ++it) 
	 {
			ContainerNode *n = it->second;
			ContainerNode *previousNode =(ContainerNode*)currentModel->findByPath(n->path());
			
		   if(previousNode != NULL)
		   {
                   traces->append(modelCompare.diff(previousNode, n));
           } else {
                  // traces!!.populate(n.toTraces(true, true))
          }
        
	}
	
	
	/*for(n in targetNode!!.hosts){
               val previousNode = currentModel.findByPath(n.path()!!)
               if(previousNode != null){
                   traces!!.append(modelCompare.diff(previousNode, n))
               } else {
                   traces!!.populate(n.toTraces(true, true))
               }
           }
           for(g in targetNode.groups){
               val previousGroup = currentModel.findByPath(g.path()!!)
               if(previousGroup != null){
                   traces!!.append(modelCompare.diff(previousGroup, g))
               } else {
                   traces!!.populate(g.toTraces(true, true))
               }
           }
           //This process can really slow down
           for(comp in targetNode.components){
               fun fillPort(ports: List<Port>) {
                   for(port in ports){
                       for(b in port.bindings){
                           if(b.hub != null){
                               val previousChannel = currentModel.findByPath(b.hub!!.path()!!)
                               if(previousChannel != null){
                                   traces!!.append(modelCompare.diff(previousChannel, b.hub!!))
                               } else {
                                   traces!!.populate(b.hub!!.toTraces(true, true))
                               }
                           }
                       }
                   }
               }
               fillPort(comp.provided)
               fillPort(comp.required)
           }*/
}
TraceSequence *KevoreeCoreBean::createTraces(ContainerRoot *currentModel,ContainerRoot *targetModel)
{
	ContainerNode *currentNode = (ContainerNode*)currentModel->findnodesByID(getNodeName());
	ContainerNode *targetNode = (ContainerNode*)targetModel->findnodesByID(getNodeName());
	TraceSequence *traces=NULL;

	if (currentNode != NULL && targetNode != NULL)
	{
		/*  no bootstrapNode
		 *
		 */
           traces = modelCompare.diff(currentNode, targetNode);
	//	  createTracesGroupsAndChannels(currentModel,targetModel,currentNode,targetNode,traces);
       } else 
       {
		   /* bootstrap Node
		    * 
		    */
           if(targetNode != NULL){
               traces = modelCompare.inter(targetNode, targetNode);
           //	  createTracesGroupsAndChannels(currentModel,targetModel,currentNode,targetNode,traces);
           }else if(currentNode != NULL) 
           {
			   /*
			    *  unbootstrap Node
			    */
			  traces = modelCompare.inter(currentNode, currentNode);
            //	  createTracesGroupsAndChannels(currentModel,targetModel,currentNode,targetNode,traces);  
		   }
			      
       }
       std::set<std::string> *foundDeployUnitsToRemove = new std::set<std::string>;
       CurrentNodeVisitor *currentnodevisit = new CurrentNodeVisitor(currentNode,foundDeployUnitsToRemove);
       currentNode->visit(currentnodevisit,true,true,true);
       delete currentnodevisit;
	
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

std::list<ContainerRoot> KevoreeCoreBean::getPreviousModels(){
	
	
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
