#include <kevoree-tools/BootstrapHelper/NodeTypeBootstrapHelper.h>
#include <dlfcn.h>
#include <iostream>


AbstractNodeType *NodeTypeBootstrapHelper::bootstrapNodeType(ContainerRoot *model,std::string destNodeName, KevoreeModelHandlerService *mservice)
{
    ContainerNode *node = model->findnodesByID(destNodeName);
    if(node !=NULL)
    {
		    	
		TypeDefinition *type = node->typeDefinition;
		if(type != NULL)
		{
			LOGGER_WRITE(Logger::DEBUG,"NodeTypeBootstrapHelper "+node->name);
			// TODO CALL MAVEN CPP RESOLVER THEN LOAD type->name
			const char *libpath= "build/libkevoree-CPPNode.so";
		    void* handle = dlopen(libpath, RTLD_LAZY | RTLD_GLOBAL);
			if (!handle) 
		    {
					fputs (dlerror(), stderr);
					return NULL;
		    }

			AbstractNodeType* (*create)();
			create =  (AbstractNodeType* (*)())dlsym(handle, "create");
			AbstractNodeType* c = (AbstractNodeType*)create();
			return c;		
		}
		else
		{
			cout << "The TypeDefinition is not define" << endl;
		}
	}
         
         
}
