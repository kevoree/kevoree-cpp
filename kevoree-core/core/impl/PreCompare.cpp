#include <kevoree-core/core/PreCompare.h>


AdaptationPrimitive* PreCompare::adapt(Primitives p,KMFContainer *elem,ContainerRoot *model)
{
	AdaptationPrimitive *ccmd = factoryAdaptation.createAdaptationPrimitive();
	//ccmd->primitiveType = model->findadaptationPrimitiveTypesByID(TO_STRING_Primitives(p));
	ccmd->primitiveType =TO_STRING_Primitives(p); // TODO remove TO_STRING USE INT
    ccmd->ref = elem->path();
    return ccmd;
}
PreCompare::PreCompare(std::string _nodeName){
	this->nodeName = _nodeName;
}
void PreCompare::createTracesGroupsAndChannels(ContainerRoot *currentModel,ContainerRoot *targetModel,ContainerNode *currentNode,ContainerNode *targetNode,TraceSequence *traces)
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
TraceSequence *PreCompare::createTraces(ContainerRoot *currentModel,ContainerRoot *targetModel,AdaptationModel  *adaptationModel)
{
	ContainerNode *currentNode = (ContainerNode*)currentModel->findnodesByID(nodeName);
	ContainerNode *targetNode = (ContainerNode*)targetModel->findnodesByID(nodeName);
	TraceSequence *traces=NULL;
	//AdaptationModel  *adaptationModel =    factory->createAdaptationModel();


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
       
       TargetNodeVisitor *targetNodevisitor = new TargetNodeVisitor(targetModel,currentNode,foundDeployUnitsToRemove,adaptationModel);
       targetNode->visit(targetNodevisitor,true,true,true);
       

}

