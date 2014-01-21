#include <kevoree-core/api/PreCompare.h>
#include <map>

PreCompare::PreCompare(std::string _nodeName){
	this->nodeName = _nodeName;
}

void PreCompare::fillPort(std::map<string,Port*> ports,ContainerRoot *currentModel,TraceSequence *traces){
	TraceSequence *seq;
	for ( std::map<string,Port*>::const_iterator it = ports.begin();  it != ports.end(); ++it)
	{
		Port *port = it->second;
		for ( std::map<string,MBinding*>::const_iterator it_port = port->bindings.begin();  it_port != port->bindings.end(); ++it_port)
		{
			MBinding *port = it_port->second;
			if(port->hub != NULL)
			{
				Channel *previousChannel =(Channel*)currentModel->findByPath(port->hub->path());
				if(previousChannel != NULL)
				{
					seq =modelCompare.diff(previousChannel,port->hub);
					traces->append(seq);
					seq->traces.clear();
					delete seq;
				} else {
					traces->populate(port->hub->toTraces(true, true));
				}
			}
		}
	}

}
void PreCompare::createTracesGroupsAndChannels(ContainerRoot *currentModel,ContainerRoot *targetModel,ContainerNode *currentNode,ContainerNode *targetNode,TraceSequence *traces)
{
	TraceSequence *seq;

	// HOSTS
	for ( std::map<string,ContainerNode*>::const_iterator it = targetNode->hosts.begin();  it != targetNode->hosts.end(); ++it)
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

	// GROUPS
	for ( std::map<string,Group*>::const_iterator it = targetNode->groups.begin();  it != targetNode->groups.end(); ++it)
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

	// CHANNELS
	for ( std::map<string,ComponentInstance*>::const_iterator it = targetNode->components.begin();  it != targetNode->components.end(); ++it)
	{
		ComponentInstance *n = it->second;
		fillPort(n->provided,currentModel,traces);
		fillPort(n->required,currentModel,traces);
	}

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

