#include <base/KevoreeBootStrap.h>


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


void KevoreeBootStrap::start(){
	if(started != true){
		return;
	}  
	coreBean = new KevoreeCoreBean();
	
	//coreBean->setBootstraper(bootstrapModel);
	coreBean->start();
	  
}
