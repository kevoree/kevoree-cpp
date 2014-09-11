#include <kevoree-core/api/KevoreeCoreBean.h>
#include <stdexcept>
#include <sys/time.h>
#include <sys/resource.h>
#include <kevoree-core/kevscript/api/KevScriptEngine.h>
#include <microframework/api/utils/ModelCloner.h>


KevoreeCoreBean::KevoreeCoreBean(){
	currentModel=NULL;
	nodeInstance=NULL;
	preCompare=NULL;
	kevScriptEngine = new KevScriptEngine();
	pthread_mutex_init(&lock_core, 0);	
}
KevoreeCoreBean::~KevoreeCoreBean()
{
	if(preCompare != NULL){
		delete preCompare; 
	}	
	pthread_mutex_destroy(&lock_core);
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



void KevoreeCoreBean::checkBootstrapNode(ContainerRoot *proposedNewModel)
{
	if (nodeInstance == NULL) 
	{
		ContainerNode *foundNode = proposedNewModel->findnodesByID(getNodeName());
		if(foundNode != NULL)
		{
			nodeInstance = _bootstraper->bootstrapNodeType(getNodeName(), this);
			if(nodeInstance != NULL)
			{
				LOGGER_WRITE(Logger::DEBUG,"Starting Node =>"+getNodeName());
				nodeInstance->setPath(foundNode->path());
				nodeInstance->setnodeName(getNodeName());
				nodeInstance->setBootStrapperService(_bootstraper);
				nodeInstance->setModelService(this);
				nodeInstance->start();
				LOGGER_WRITE(Logger::DEBUG,"Done Bootstrap node  =>"+getNodeName());
			} else
			{
				LOGGER_WRITE(Logger::ERROR,"The installation of the Typedefintion of the NodeType has fail, the runtime cannot start !");
				exit(0);
			}
		}else 
		{
			LOGGER_WRITE(Logger::ERROR,"The instance o fNodeName  "+getNodeName()+" is not found in the bootstrap model !");
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
	bool deployResult=false;
	try
	{
		pthread_mutex_lock(&lock_core);
		clock_t start = clock();
		if (proposedNewModel->findnodesByID(getNodeName()) == NULL) {
			LOGGER_WRITE(Logger::WARNING, "Asking for update with a NULL model or node name (" + getNodeName() +") was not found in target model !");
			return false;
		}

		if(checkModel(proposedNewModel))
		{

		}
		// set proposedNewModel
		_bootstraper->setproposedNewModel(proposedNewModel);

		//  if the platforme is starting we need to load the nodeType
		checkBootstrapNode(proposedNewModel);

		ContainerRoot *currentModel = getLastModel(); 


		LOGGER_WRITE(Logger::DEBUG,"Before listeners PreCheck !");

		//modelListeners.preUpdate(currentModel, readOnlyNewModel);

		TraceSequence *traces = preCompare->createTraces(currentModel,proposedNewModel);

		//	 LOGGER_WRITE(Logger::DEBUG,traces->exportToString());

		AdaptationModel *adaptationModel = nodeInstance->plan(currentModel, proposedNewModel,traces);
		LOGGER_WRITE(Logger::INFO,("Adaptation model size "+Utils::IntegerUtilstoString(adaptationModel->adaptations.size())));


		ContainerNode *rootNode = currentModel->findnodesByID(getNodeName());

		deployResult = nodeInstance->execute(rootNode,adaptationModel,nodeInstance);
		clock_t finish = clock();

		LOGGER_WRITE(Logger::INFO,"Adaptation time delta (ms) = "+    Utils::IntegerUtilstoString(Utils::mstimer(start,finish)));

		// destructors 
		delete adaptationModel;
		delete traces;

		if(deployResult)
		{
			switchToNewModel(proposedNewModel);
			LOGGER_WRITE(Logger::INFO,"Update sucessfully completed.");
		}
		else
		{
			delete proposedNewModel;
			LOGGER_WRITE(Logger::ERROR,"Update failed, sorry about that");
		}

		pthread_mutex_unlock(&lock_core);
	}
	catch ( const std::exception & e )
	{
		pthread_mutex_unlock(&lock_core);
		std::cerr << e.what() << endl;
	}
	return deployResult;
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

	ContainerRoot *currentmodel = getLastModel();
	ModelCloner *cloner= new ModelCloner(&factory);
	ContainerRoot *stopModel = cloner->clone(currentmodel,true,true) ;

	ContainerNode *currentNode = stopModel->findnodesByID(getNodeName());
	if(currentNode == NULL){

//todo throw exception
	}
	currentNode->started = false;

	// stop hosts
	for ( std::map<string,ContainerNode*>::iterator it = currentNode->hosts.begin();  it !=  currentNode->hosts.end(); ++it)
	{
		ContainerNode *n = it->second;
		n->started = false;

	}
	for ( std::map<string,Group*>::iterator it = stopModel->groups.begin();  it !=  stopModel->groups.end(); ++it)
	{
		Group *g = it->second;
		g->started = false;

	}

	for ( std::map<string,Channel*>::iterator it = stopModel->hubs.begin();  it !=  stopModel->hubs.end(); ++it)
	{
		Channel *c = it->second;
		c->started = false;

	}

	for ( std::map<string,ComponentInstance*>::iterator it = currentNode->components.begin();  it !=  currentNode->components.end(); ++it)
	{
		ComponentInstance *co = it->second;
		co->started = false;

	}
	LOGGER_WRITE(Logger::INFO,"Update to StopModel");
	updateModel(stopModel);

}

bool KevoreeCoreBean::checkModel(ContainerRoot *targetModel){
	LOGGER_WRITE(Logger::INFO,"Model Checker");


	return true;
}
