#ifndef __Bootstraper_H
#define __Bootstraper_H
#include <kevoree-core/api/AbstractNodeType.h>
#include <kevoree-core/api/KevoreeModelHandlerService.h>
#include <kevoree-core/api/IDynamicLoader.h>

class Bootstraper
{
public:
 virtual AbstractNodeType *bootstrapNodeType(ContainerRoot *model,std::string destNodeName, KevoreeModelHandlerService *mservice)=0;
 virtual std::string resolveDeployUnit(DeployUnit *du)=0;
 virtual IDynamicLoader* getDynamicLoader()=0;
};

#endif

