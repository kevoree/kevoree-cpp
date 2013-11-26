#ifndef __NodeTypeBootstrapHelper_H
#define __NodeTypeBootstrapHelper_H


#include <KevoreeBootStrap/KevoreeBootStrap.h>

class NodeTypeBootstrapHelper : public Bootstraper {
	
  AbstractNodeType *bootstrapNodeType(ContainerRoot *model,std::string destNodeName, KevoreeModelHandlerService *mservice);
	

	    
};
#endif
