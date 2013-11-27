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
	
			LOGGER_WRITE(Logger::DEBUG,"NodeTypeBootstrapHelper "+type->name);
	
			for (std::unordered_map<string,DeployUnit*>::iterator iterator = type->deployUnits.begin(), end = type->deployUnits.end(); iterator != end; ++iterator)
			{
						DeployUnit *deployunit= iterator->second;
						dynamicLoader->register_DeployUnit(deployunit);
						AbstractNodeType *instance = (AbstractNodeType*)dynamicLoader->create_DeployUnitById(deployunit->internalGetKey());
						instance->setBootStrapperService(this);
						instance->setModelService(mservice);
		
						return instance;
			}
			
			

		}
		else
		{
			cout << "The TypeDefinition is not define" << endl;
			return NULL;
		}
	}
         
         
}
