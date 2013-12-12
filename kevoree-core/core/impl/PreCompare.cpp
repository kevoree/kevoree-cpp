#include <kevoree-core/core/PreCompare.h>



PreCompare::PreCompare(std::string _nodeName){
	this->nodeName = _nodeName;
}
void PreCompare::createTracesGroupsAndChannels(ContainerRoot *currentModel,ContainerRoot *targetModel,ContainerNode *currentNode,ContainerNode *targetNode,TraceSequence *traces)
{
	TraceSequence *seq;
	 for ( std::unordered_map<string,ContainerNode*>::const_iterator it = targetNode->hosts.begin();  it != targetNode->hosts.end(); ++it) 
	 {
			ContainerNode *n = it->second;
			ContainerNode *previousNode =(ContainerNode*)currentModel->findByPath(n->path());
			
		   if(previousNode != NULL)
		   {
                   seq =modelCompare.diff(previousNode, n);
                   traces->append(seq);
                   seq->traces.clear();
				   delete seq; 
           } else 
           {
                   traces->populate(n->toTraces(true, true));
          }  
	}
	
	for ( std::unordered_map<string,Group*>::const_iterator it = targetNode->groups.begin();  it != targetNode->groups.end(); ++it) 
	 {
			Group *n = it->second;
			Group *previousGroup =(Group*)currentModel->findByPath(n->path());
			
		   if(previousGroup != NULL)
		   {
				seq =modelCompare.diff(previousGroup, n);
                traces->append(seq);
                seq->traces.clear();
				delete seq; 
           } else {
                   traces->populate(n->toTraces(true, true));
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
TraceSequence *PreCompare::createTraces(ContainerRoot *currentModel,ContainerRoot *targetModel)
{
	//cout << "BEGIN -- PreCompare createTraces" << " " << nodeName <<  endl;
	ContainerNode *currentNode = (ContainerNode*)currentModel->findnodesByID(nodeName);
	ContainerNode *targetNode = (ContainerNode*)targetModel->findnodesByID(nodeName);
	TraceSequence *sequence=NULL;
    std::set<std::string> foundDeployUnitsToRemove;
    
    clock_t start = clock();   
	if (currentNode != NULL && targetNode != NULL)
	{
		  LOGGER_WRITE(Logger::INFO,"PreCompare Updating");
		/*  no bootstrapNode
		 *
		 */
           sequence = modelCompare.diff(currentNode, targetNode);
           if(sequence == NULL){
			     LOGGER_WRITE(Logger::INFO,"PreCompare diff cannot be done");
			   return NULL;
		   }
		  createTracesGroupsAndChannels(currentModel,targetModel,currentNode,targetNode,sequence);
       } 
       else 
       {
		   /* bootstrap Node
		    * 
		    */
		    //cout << "bootstrap Node" << endl;
		   LOGGER_WRITE(Logger::INFO,"PreCompare BootStraping");
           if(targetNode != NULL)
           {
               sequence = modelCompare.inter(targetNode, targetNode);
                if(sequence == NULL)
                {
				   LOGGER_WRITE(Logger::ERROR,"PreCompare BootStraping model intersection");
				   return NULL;
				}
               // TODO FIX ME CLEAN remvoe "SET" src current node to avoid harakiri traces 
               
           	  createTracesGroupsAndChannels(currentModel,targetModel,currentNode,targetNode,sequence);
           }else if(currentNode != NULL) 
           {
			   /*
			    *  unbootstrap Node
			    */
			  LOGGER_WRITE(Logger::INFO,"PreCompare UnBootStrap");
			  sequence = modelCompare.inter(currentNode, currentNode);
			  if(sequence == NULL)
                {
				  LOGGER_WRITE(Logger::ERROR,"PreCompare UnBootStrap model intersection");
				   return NULL;
				}
               // TODO FIX ME CLEAN remvoe "SET" src current node to avoid harakiri traces 
            	  createTracesGroupsAndChannels(currentModel,targetModel,currentNode,targetNode,sequence);  
		   }
			      
       }


    /*
     * 
     * Looking for the deploy units in the current model  
     */ 
      if(currentNode !=NULL)
      {
		 CurrentNodeVisitor *currentnodevisit = new CurrentNodeVisitor(currentNode,&foundDeployUnitsToRemove);	  
		 currentNode->visit(currentnodevisit,true,true,true);
		 delete currentnodevisit;
	  }

       
      if(targetNode !=NULL) 
      {
		   TargetNodeVisitor *targetNodevisitor = new TargetNodeVisitor(targetModel,currentNode,&foundDeployUnitsToRemove,sequence);
		   targetNode->visit(targetNodevisitor,true,true,true);
		   delete targetNodevisitor;
      }
	
		for (std::set<std::string>::iterator iterator = foundDeployUnitsToRemove.begin(), end = foundDeployUnitsToRemove.end(); iterator != end; ++iterator)
        {
			ModelRemoveTrace *removetrace = new ModelRemoveTrace("","deployUnits",*iterator);
			sequence->traces.push_back(removetrace);
		}  


      return sequence; 
}

