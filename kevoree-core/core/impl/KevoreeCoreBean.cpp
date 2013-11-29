#include <kevoree-core/core/KevoreeCoreBean.h>
#include <stdexcept>

KevoreeCoreBean::~KevoreeCoreBean()
{
	if(preCompare != NULL){
		delete preCompare; 
	}	
}
KevoreeCoreBean::KevoreeCoreBean(){
	currentModel=NULL;
	nodeInstance=NULL;
	preCompare=NULL;
	
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
						LOGGER_WRITE(Logger::DEBUG,"Starting the Node =>"+getNodeName());
						nodeInstance->setModelElement(foundNode);
						nodeInstance->setBootStrapperService(_bootstraper);
						nodeInstance->setModelService(this);	
                        nodeInstance->start();
                    } else 
                    {
							LOGGER_WRITE(Logger::ERROR,"The installation of the Typedefintion of the NodeType has fail, the runtime cannot start !");
							exit(0);
					}
		}else 
		{
					LOGGER_WRITE(Logger::ERROR," Node instance name {} not found in bootstrap model !");
		 }
     } 
}

void KevoreeCoreBean::switchToNewModel(ContainerRoot *update)
{
		delete currentModel;
		currentModel = update;
	 //Changes the current model by the new model	
}

bool KevoreeCoreBean::internal_update_model(ContainerRoot *proposedNewModel)
{
	try
    {
		clock_t start = clock();
		if (proposedNewModel->findnodesByID(getNodeName()) == NULL) {
			LOGGER_WRITE(Logger::WARNING, "Asking for update with a NULL model or node name (" + getNodeName() +") was not found in target model !");
			return false;
		}
		if(checkModel(proposedNewModel)){
			
		}
		
		checkBootstrapNode(proposedNewModel);
		
		ContainerRoot *currentModel = getLastModel(); 


		LOGGER_WRITE(Logger::DEBUG,"Before listeners PreCheck !");
		
	  //modelListeners.preUpdate(currentModel, readOnlyNewModel);
		
		TraceSequence *traces = preCompare->createTraces(currentModel,proposedNewModel);
		if(traces ==NULL){
				LOGGER_WRITE(Logger::ERROR,"createTraces");
		}
	   // LOGGER_WRITE(Logger::INFO,traces->exportToString());

		AdaptationModel *adaptationModel = nodeInstance->plan(currentModel, proposedNewModel,traces);
		LOGGER_WRITE(Logger::INFO,("Adaptation model size "+Utils::IntegerUtilstoString(adaptationModel->adaptations.size())));
		
		ContainerNode *rootNode = currentModel->findnodesByID(getNodeName());

		bool deployResult = nodeInstance->execute(rootNode,adaptationModel,nodeInstance);
		clock_t finish = clock();
		LOGGER_WRITE(Logger::INFO,"Adaptation time delta (ms) = "+    Utils::IntegerUtilstoString(Utils::mstimer(start,finish)));

		if(deployResult)
		{
		switchToNewModel(proposedNewModel);		
		 LOGGER_WRITE(Logger::INFO,"Update sucessfully completed.");	
		}
		else
		{
			 delete proposedNewModel;
			 LOGGER_WRITE(Logger::ERROR,"Update failed");
		}
			
    }
    catch ( const std::exception & e )
    {
        std::cerr << e.what() << endl;
    }
		
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
		    LOGGER_WRITE(Logger::WARNING,"None NodeName, default node0");
            setNodeName("node0");
      }
      modelListeners.start(getNodeName());
      LOGGER_WRITE(Logger::INFO,"Kevoree Start event : node name = "+getNodeName());
      currentModel = factory.createContainerRoot();
      preCompare = new PreCompare(getNodeName());
}


void KevoreeCoreBean::stop()
{
	    LOGGER_WRITE(Logger::INFO,"Kevoree Core will be stopped ! "+getNodeName());
        modelListeners.stop();
	
}

bool KevoreeCoreBean::checkModel(ContainerRoot *targetModel){
	// todo
	return true;
}
