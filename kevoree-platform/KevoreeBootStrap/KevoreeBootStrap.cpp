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
	LOGGER_WRITE(Logger::DEBUG," KevoreeBootStrap");
	if(started == true)
	{
		return;
	}  
	bootNodeHelper = new NodeTypeBootstrapHelper(); 
	coreBean = new KevoreeCoreBean();
	coreBean->setNodeName(this->nodeName);
	coreBean->setBootstraper(bootNodeHelper);
    coreBean->start();
   	coreBean->updateModel(bootstrapModel);	
}
