#include <kevoree-platform/base/KevoreeBootStrap.h>
#include <kevoree-tools/BootstrapHelper/NodeTypeBootstrapHelper.h>


KevoreeBootStrap::KevoreeBootStrap(){
	started= false;
	
}
void KevoreeBootStrap::setBootstrapModel(ContainerRoot *bmodel)
{
	  bootstrapModel = bmodel;
}


KevoreeCoreBean* KevoreeBootStrap::getCore()
{
	return coreBean;  
}


void KevoreeBootStrap::start()
{
	if(started == true){
		return;
	}  
	NodeTypeBootstrapHelper *bootstraper = new NodeTypeBootstrapHelper(); 
	coreBean = new KevoreeCoreBean();
	coreBean->setBootstraper(bootstraper);
    coreBean->start();
   	coreBean->updateModel(bootstrapModel);
}
