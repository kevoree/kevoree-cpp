#ifndef __LoaderTypeDefinition_H
#define __LoaderTypeDefinition_H

#include <kevoree-core/core/api/KevoreeModelHandlerService.h>
#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include <kevoree-core/model/kevoree/DeployUnit.h>
#include <kevoree-core/core/api/AbstractTypeDefinition.h>
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/AbstractComponent.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include <kevoree-core/core/api/IDynamicLoader.h>


#include <map>
#include <string>
#include <dlfcn.h>

class DynamicLoader : public IDynamicLoader
{
public:
	DynamicLoader(Bootstraper *bootstrap);
	void register_DeployUnit(DeployUnit *du);
	void * create_DeployUnitById(std::string id);
	
	void * soloader_load(std::string type);
	void  unload(std::string type);
	AbstractTypeDefinition * newInstance(void *handle);

	
private:
map<string, void*>	deploysUnits;
Bootstraper *bootstrap;
};


#endif






