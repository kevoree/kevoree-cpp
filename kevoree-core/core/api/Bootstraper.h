#ifndef __Bootstraper_H
#define __Bootstraper_H
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/KevoreeModelHandlerService.h>
#include <string>

class Bootstraper{
public:
 virtual AbstractNodeType *bootstrapNodeType(ContainerRoot *model,std::string destNodeName, KevoreeModelHandlerService *mservice)=0;

};

#endif

