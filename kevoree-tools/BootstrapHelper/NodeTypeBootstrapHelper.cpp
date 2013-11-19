#include <kevoree-tools/BootstrapHelper/NodeTypeBootstrapHelper.h>
#include <dlfcn.h>
#include <iostream>


INodeType *NodeTypeBootstrapHelper::bootstrapNodeType(ContainerRoot *model,std::string destNodeName, KevoreeModelHandlerService *mservice)
{
    ContainerNode *node = model->findnodesByID(destNodeName);
    if(node !=NULL){
		    	
		TypeDefinition *type = node->typeDefinition;
		if(type != NULL)
		{
			// TODO CALL MAVEN CPP RESOLVER THEN LOAD type->name
			const char *libpath= "./libkevoree-CPPNode.so";
		    void* handle = dlopen(libpath, RTLD_LAZY | RTLD_GLOBAL);
			if (!handle) 
		    {
					fputs (dlerror(), stderr);
					return NULL;
		    }

			INodeType* (*create)();
			create =  (INodeType* (*)())dlsym(handle, "create");
			INodeType* c = (INodeType*)create();
			return c;		
		}
		else
		{
			cout << "The TypeDefinition is not define" << endl;
		}
	}
         
         
}
