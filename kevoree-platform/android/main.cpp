
#include <kevoree-platform/KevoreeBootStrap/KevoreeBootStrap.h>
#include <microframework/api/trace/DefaultTraceConverter.h>
#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/json/JSONModelSerializer.h>
#include <microframework/api/compare/ModelCompare.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <microframework/api/KMFContainer.h>
#include <kevoree-logger/api/Logger.h>

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
	//kb->setBasePath("/tmp/.m2");
	kb->setBasePath("/mnt/sdcard/reacloud/");



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
	attport->defaultValue = "9001";
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
	valport->value ="9001";

	dico->addvalues(valport);


	group->addfragmentDictionary(dico);





	TypeDefinition *comtype  = factory.createComponentType();
	comtype->name = "Light";
	comtype->abstract = false;

	PortTypeRef *reglight = new PortTypeRef();
	reglight->name ="port";
	reglight->optional = true;

	((ComponentType*)comtype)->addrequired(reglight);

	DictionaryType *typegroup2= factory.createDictionaryType();
	DictionaryAttribute *attport2 = factory.createDictionaryAttribute();
	attport2->optional = false;
	attport2->datatype = "Boolean";
	attport2->fragmentDependant = false;
	attport2->name ="enable";
	attport2->defaultValue = "true";
	typegroup2->addattributes(attport2);




	DictionaryAttribute *attport3 = factory.createDictionaryAttribute();
	attport3->optional = false;
	attport3->datatype = "int";
	attport3->fragmentDependant = false;
	attport3->name ="pin";
	attport3->defaultValue = "7";

	typegroup2->addattributes(attport3);
	comtype->adddictionaryType(typegroup2);


	DeployUnit *dc =factory.createDeployUnit();
	dc->name = "LightComponent";
	dc->groupName = "org.kevoree.library";
	dc->version = "1.0.0-SNAPSHOT";
	dc->type ="so";

	comtype->adddeployUnit(dc);





	node0->addtypeDefinition(nodetype);


	/* Temperature */
	TypeDefinition *anenotype  = factory.createComponentType();
	anenotype->name = "Temperature";
	anenotype->abstract = false;

	PortTypeRef *reg = new PortTypeRef();
	reg->name ="port";
	reg->optional = true;

	((ComponentType*)anenotype)->addrequired(reg);




	DictionaryType *typeanomo= factory.createDictionaryType();
	anenotype->adddictionaryType(typeanomo);

	DictionaryAttribute *attportanom = factory.createDictionaryAttribute();
	attportanom->optional = false;
	attportanom->datatype = "int";
	attportanom->fragmentDependant = false;
	attportanom->name ="pin";
	attportanom->defaultValue = "7";
	typeanomo->addattributes(attportanom);

	DeployUnit *dcano =factory.createDeployUnit();
	dcano->name = "TemperatureComponent";
	dcano->groupName = "org.kevoree.library";
	dcano->version = "1.0.0-SNAPSHOT";
	dcano->type ="so";

	/* GW  */

	TypeDefinition *gwMQTTtype  = factory.createComponentType();
	gwMQTTtype->name = "WebSocketGatewayMQTT";
	gwMQTTtype->abstract = false;


	DeployUnit *dcMQTTgw =factory.createDeployUnit();
	dcMQTTgw->name = "WebSocketGatewayMQTT";
	dcMQTTgw->groupName = "org.kevoree.library";
	dcMQTTgw->version = "1.0.0-SNAPSHOT";
	dcMQTTgw->type ="so";


	DictionaryType *typegwMQTT= factory.createDictionaryType();
	DictionaryAttribute *attportGW = factory.createDictionaryAttribute();
	attportGW->optional = false;
	attportGW->datatype = "int";
	attportGW->fragmentDependant = false;
	attportGW->name ="port_gw";
	attportGW->defaultValue = "18883";
	typegwMQTT->addattributes(attportGW);
	gwMQTTtype->adddictionaryType(typegwMQTT);


	DictionaryAttribute *attportGW2 = factory.createDictionaryAttribute();
	attportGW2->optional = false;
	attportGW2->datatype = "int";
	attportGW2->fragmentDependant = false;
	attportGW2->name ="port_MQTT";
	attportGW2->defaultValue = "1883";
	typegwMQTT->addattributes(attportGW2);




	DictionaryAttribute *attportGW3 = factory.createDictionaryAttribute();
	attportGW3->optional = false;
	attportGW3->datatype = "int";
	attportGW3->fragmentDependant = false;
	attportGW3->name ="HOST_MQTT";
	attportGW3->defaultValue = "localhost";
	typegwMQTT->addattributes(attportGW3);

	gwMQTTtype->adddictionaryType(typegwMQTT);


	gwMQTTtype->adddeployUnit(dcMQTTgw);


	model->addtypeDefinitions(anenotype);
	model->addtypeDefinitions(grouptype);
	model->addtypeDefinitions(nodetype);
	model->addtypeDefinitions(comtype);
	model->addtypeDefinitions(gwMQTTtype);

	model->adddeployUnits(d);
	model->adddeployUnits(dg);
	model->adddeployUnits(dc);
	model->adddeployUnits(dcano);
	model->adddeployUnits(dcMQTTgw);

	model->addnodes(node0);

	model->addgroups(group);
	group->addsubNodes(node0);
	node0->addgroups(group);


	kb->setBootstrapModel(model); // boostrapmodel
	kb->start();



	clock_t finish = clock();
	std::cin >> exit;
}










