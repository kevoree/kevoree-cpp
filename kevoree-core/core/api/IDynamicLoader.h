#ifndef __DynamicLoader_H
#define __DynamicLoader_H

#include <kevoree-core/core/api/KevoreeModelHandlerService.h>
#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include <kevoree-core/model/kevoree/DeployUnit.h>
#include <kevoree-core/core/api/AbstractTypeDefinition.h>
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/AbstractComponent.h>
#include <kevoree-core/core/api/Bootstraper.h>



class IDynamicLoader  
{
public:
	virtual void register_DeployUnit(DeployUnit *du){};
	virtual void * create_DeployUnitById(std::string id){};
};


#endif






