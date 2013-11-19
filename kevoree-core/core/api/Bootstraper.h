#ifndef __Bootstraper_H
#define __Bootstraper_H
#include <kevoree-core/core/api/INodeType.h>
#include <kevoree-core/core/api/KevoreeModelHandlerService.h>
#include <string>

class Bootstraper{
public:
 virtual INodeType *bootstrapNodeType(ContainerRoot *model,std::string destNodeName, KevoreeModelHandlerService *mservice)=0;

};

#endif

