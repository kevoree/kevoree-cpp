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
	bool register_instance(Instance *i);
	AbstractTypeDefinition * create_instance(Instance *i);
	bool unload_instance(Instance *i);

private:
	void * soloader_load(std::string type);
	AbstractTypeDefinition * newInstance(void *handle);
	void destroyInstance(void *handler,AbstractTypeDefinition *instance);
	map<string, void*>	deploysUnits;
	map<string, void*>	instances;
	Bootstraper *bootstrap;
};


#endif






