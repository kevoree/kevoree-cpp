#include <kevoree-tools/BootstrapHelper/NodeTypeBootstrapHelper.h>


NodeTypeBootstrapHelper::NodeTypeBootstrapHelper()
{
	dynamicLoader = new DynamicLoader(this);
}

NodeTypeBootstrapHelper::~NodeTypeBootstrapHelper()
{
	delete	dynamicLoader;

}

std::string NodeTypeBootstrapHelper::resolveDeployUnit(DeployUnit *deployunit)
{
	std::list<std::string> urls;
	return resolver.resolve(deployunit->groupName,deployunit->name,deployunit->version,"zip",urls);	
		
}



IDynamicLoader* NodeTypeBootstrapHelper::getDynamicLoader()
{
	 return dynamicLoader;
}
	 
AbstractNodeType *NodeTypeBootstrapHelper::bootstrapNodeType(ContainerRoot *model,std::string destNodeName, KevoreeModelHandlerService *mservice)
{
    ContainerNode *node = model->findnodesByID(destNodeName);
    if(node !=NULL)
    {
		    	
		TypeDefinition *type = node->typeDefinition;

		if(type != NULL)
		{
	
			LOGGER_WRITE(Logger::DEBUG,"Bootstraping NodeType => "+type->name);
			dynamicLoader->register_instance(node);
			dynamicLoader->setModelService(mservice);
			AbstractTypeDefinition *instance =dynamicLoader->create_instance(node);
			if(instance){
				instance->setBootStrapperService(this);
				instance->setModelService(mservice);
				return (AbstractNodeType*)instance;
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			cout << "The TypeDefinition is not define" << endl;
			return NULL;
		}
	}
         
         
}
