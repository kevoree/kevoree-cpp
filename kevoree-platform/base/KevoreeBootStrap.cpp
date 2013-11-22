#include <kevoree-platform/base/KevoreeBootStrap.h>
#include <kevoree-tools/BootstrapHelper/NodeTypeBootstrapHelper.h>


KevoreeBootStrap::KevoreeBootStrap(){
	started= false;
	
}
// todo add destructor bootstraper
void KevoreeBootStrap::setBootstrapModel(ContainerRoot *bmodel)
{
	  bootstrapModel = bmodel;
}


KevoreeCoreBean* KevoreeBootStrap::getCore()
{
	return coreBean;  
}

void KevoreeBootStrap::setNodeName(std::string nodeName){
this->nodeName = nodeName;		
}

void KevoreeBootStrap::start()
{
	if(started == true){
		return;
	}  
	NodeTypeBootstrapHelper *bootstraper = new NodeTypeBootstrapHelper(); 
	coreBean = new KevoreeCoreBean();
	coreBean->setNodeName(this->nodeName);
	coreBean->setBootstraper(bootstraper);
    	coreBean->start();
   	coreBean->updateModel(bootstrapModel);
}
