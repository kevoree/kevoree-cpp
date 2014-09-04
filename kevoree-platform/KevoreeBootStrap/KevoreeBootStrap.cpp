#include "KevoreeBootStrap.h"

KevoreeBootStrap::KevoreeBootStrap(){
	started= false;
	bootNodeHelper=NULL;
	coreBean=NULL;

}

KevoreeBootStrap::~KevoreeBootStrap(){
	if(coreBean)
	{
		delete coreBean;
	}
		
	if(bootNodeHelper)
	{
		delete bootNodeHelper;
	}
}

void KevoreeBootStrap::setBootstrapModel(ContainerRoot *bmodel)
{
	  bootstrapModel = bmodel;
}

void KevoreeBootStrap::setBasePath(std::string path)
{
	this->maven_base_path = path;
}

KevoreeCoreBean* KevoreeBootStrap::getCore()
{
	return coreBean;  
}

void KevoreeBootStrap::setNodeName(std::string nodeName)
{
	this->nodeName = nodeName;		
}

void KevoreeBootStrap::start()
{
	LOGGER_WRITE(Logger::DEBUG,"KevoreeBootStrap NodeType");
	if(started == true)
	{
		return;
	}  
	bootNodeHelper = new NodeTypeBootstrapHelper(maven_base_path);
	coreBean = new KevoreeCoreBean();
	coreBean->setNodeName(this->nodeName);
	coreBean->setBootstraper(bootNodeHelper);
    coreBean->start();
   	coreBean->updateModel(bootstrapModel);	
}

void KevoreeBootStrap::stop()
{
	if(started == true)
	{
		return;
	}
    coreBean->stop();

}
