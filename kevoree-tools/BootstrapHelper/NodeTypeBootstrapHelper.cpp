#include <kevoree-tools/BootstrapHelper/NodeTypeBootstrapHelper.h>


NodeTypeBootstrapHelper::NodeTypeBootstrapHelper(std::string mvn_maven_base_path)
{
	dynamicLoader = new DynamicLoader(this);
	resolver.setBasePath(mvn_maven_base_path);
}

NodeTypeBootstrapHelper::~NodeTypeBootstrapHelper()
{
	delete	dynamicLoader;

}

std::string NodeTypeBootstrapHelper::resolveDeployUnit(DeployUnit *deployunit)
{
	std::list<std::string> urls;
	ContainerRoot * model = proposedNewModel;
	if(model == NULL)
	{
		LOGGER_WRITE(Logger::ERROR,"The model is null");
		return "";
	}

	for ( std::map<string,Repository*>::const_iterator it = (model->repositories).begin();  it != (model->repositories).end(); ++it)
	{
		Repository *repo = it->second;
		if(repo != NULL)
		{
			urls.push_back(repo->url);
		}
	}

	return resolver.resolve(deployunit->groupName,deployunit->name,deployunit->version,deployunit->type,urls);
}



IDynamicLoader* NodeTypeBootstrapHelper::getDynamicLoader()
{
	return dynamicLoader;
}
void NodeTypeBootstrapHelper::setproposedNewModel(ContainerRoot *model){
	this->proposedNewModel = model;
}
AbstractNodeType *NodeTypeBootstrapHelper::bootstrapNodeType(std::string destNodeName, KevoreeModelHandlerService *mservice)
{
	if(proposedNewModel == NULL)
	{
		LOGGER_WRITE(Logger::ERROR,"The proposed model is not defined !");
		return NULL;
	}

	ContainerNode *node = proposedNewModel->findnodesByID(destNodeName);
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
				LOGGER_WRITE(Logger::ERROR,"The create instance fail");
				return NULL;
			}
		}
		else
		{
			LOGGER_WRITE(Logger::ERROR,"The TypeDefinition is not define ! TODO ADD IN MODEL CHECKER");
			return NULL;
		}
	}


}
