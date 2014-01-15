#ifndef __DynamicLoader_H
#define __DynamicLoader_H

#include <kevoree-core/api/KevoreeModelHandlerService.h>
#include <kevoree-core/api/AbstractTypeDefinition.h>
#include <kevoree-core/api/AbstractNodeType.h>
#include <kevoree-core/api/AbstractComponent.h>
#include <kevoree-core/api/Bootstraper.h>

#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include <kevoree-core/model/kevoree/DeployUnit.h>

class IDynamicLoader  
{
public:
	virtual bool register_instance(Instance *i)=0;
	virtual AbstractTypeDefinition * create_instance(Instance *i)=0;	
	virtual bool destroy_instance(Instance *i)=0;
	virtual bool start_instance(Instance *i)=0;
	virtual bool stop_instance(Instance *i)=0;
	virtual bool update_instance(Instance *i)=0;
};


#endif






