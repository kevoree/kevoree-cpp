#include <core/KevoreeCoreBean.h>



std::string KevoreeCoreBean::getNodeName(){
	return nodeName;
}


void KevoreeCoreBean::setNodeName(std::string nn)
{
	this->nodeName = nn;
}

void KevoreeCoreBean::start(){
	  if (getNodeName().compare("")==0) 
	  {
            setNodeName("node0");
      }
      // modelListeners.start(getNodeName())
      cout << "Kevoree Start event : node name = " << getNodeName() << endl;

}


void KevoreeCoreBean::stop(){
	    cout << "Kevoree Core will be stopped !" << endl;
	
}
