#ifndef __NodeTypeBootstrapHelper_H
#define __NodeTypeBootstrapHelper_H


#include <base/KevoreeBootStrap.h>

class NodeTypeBootstrapHelper : public Bootstraper {
	
  INodeType *bootstrapNodeType(ContainerRoot *model,std::string destNodeName, KevoreeModelHandlerService *mservice);
	

	    
};
#endif