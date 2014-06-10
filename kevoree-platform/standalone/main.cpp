
#include <kevoree-platform/KevoreeBootStrap/KevoreeBootStrap.h>
#include <microframework/api/trace/DefaultTraceConverter.h>
#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/json/JSONModelSerializer.h>
#include <microframework/api/compare/ModelCompare.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <microframework/api/KMFContainer.h>
#include <microframework/api/utils/Logger.h>

#include <kevoree-tools/DynamicLoader/DynamicLoader.h>

ContainerRoot *model=NULL;
KevoreeBootStrap *kb=NULL;

void my_handler(int s)
{

	if(kb !=NULL){
		//kb->stop();	
		delete kb;
	}
	if(model != NULL)
		delete model;

	exit(1);
}



int main(int argc,char **argv)
{
	Logger::Start(Logger::DEBUG, "kevoree.log");

	DefaultkevoreeFactory factory;
	JSONModelLoader loader;

	signal (SIGINT,my_handler);
	int exit=0;
	clock_t start = clock();

	kb = new KevoreeBootStrap();

	// FIX ME PARAM
	kb->setNodeName("node0");
	kb->setBasePath("/tmp/.m2"); // FIX ME $HOME/.m2




	loader.setFactory(&factory);

	model = factory.createContainerRoot();



	DeployUnit *d =factory.createDeployUnit();
	d->name = "CPPNodeType";
	d->groupName = "org.kevoree.library";
	d->version = "1.0.0-SNAPSHOT";
	d->type ="so";


	TypeDefinition *nodetype = factory.createNodeType();
	nodetype->name = "CPPNode";
	nodetype->abstract= false;
	nodetype->adddeployUnit(d);


	DeployUnit *dg =factory.createDeployUnit();
	dg->name = "kevoree-group-websocket";
	dg->groupName = "org.kevoree.library";
	dg->version = "1.0.0-SNAPSHOT";
	dg->type ="so";

	TypeDefinition *grouptype = factory.createGroupType();
	grouptype->abstract= false;
	grouptype->name ="WebSocketGroup";
	grouptype->version = "1.0";

	DictionaryType *typegroup= factory.createDictionaryType();
	DictionaryAttribute *attport = factory.createDictionaryAttribute();
	attport->optional = false;
	attport->datatype = "int";
	attport->fragmentDependant = true;
	attport->name ="port";
	attport->defaultValue = "9000";
	typegroup->addattributes(attport);

	grouptype->adddictionaryType(typegroup);

	grouptype->adddeployUnit(dg);



	ContainerNode *node0 = factory.createContainerNode();
	node0->name = "node0";
	node0->started= true;
	node0->started = true;


	Group *group = factory.createGroup();
	group->name ="group0";
	group->started = true;
	group->addtypeDefinition(grouptype);

	FragmentDictionary *dico =factory.createFragmentDictionary();

	dico->name ="node0";
	DictionaryValue *valport = factory.createDictionaryValue();
	valport->name ="port";
	valport->value ="9000";

	dico->addvalues(valport);


	group->addfragmentDictionary(dico);




	DeployUnit *dc =factory.createDeployUnit();
	dc->name = "HelloWorldComponent";
	dc->groupName = "org.kevoree.library";
	dc->version = "1.0.0-SNAPSHOT";
	dc->type ="so";




	node0->addtypeDefinition(nodetype);


	/* Temperature */
	TypeDefinition *helloworldtype  = factory.createComponentType();
	helloworldtype->name = "HelloWorldComponent10101";
	helloworldtype->abstract = false;





	DeployUnit *dcano =factory.createDeployUnit();
	dcano->name = "TemperatureComponent";
	dcano->groupName = "org.kevoree.library";
	dcano->version = "1.0.0-SNAPSHOT";
	dcano->type ="so";


	helloworldtype->adddeployUnit(dcano);

	model->addtypeDefinitions(helloworldtype);
	model->addtypeDefinitions(grouptype);
	model->addtypeDefinitions(nodetype);


	model->adddeployUnits(d);
	model->adddeployUnits(dg);
	model->adddeployUnits(dc);
	model->adddeployUnits(dcano);


	model->addnodes(node0);

	model->addgroups(group);
	group->addsubNodes(node0);
	node0->addgroups(group);




	Repository *repo = factory.createRepository();
	repo->url = "http://maven.reacloud.com/repository/reacloud";

	model->addrepositories(repo);

	kb->setBootstrapModel(model); // boostrapmodel
	kb->start();



	clock_t finish = clock();
	std::cin >> exit;
}










