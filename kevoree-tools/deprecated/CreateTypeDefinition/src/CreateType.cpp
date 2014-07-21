
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


#include <iostream>
#include <cstdlib>

using namespace std;

ContainerRoot *model=NULL;


int main(int argc,char **argv)
{
	Logger::Start(Logger::DEBUG, "kevoree.log");

	DefaultkevoreeFactory factory;
	JSONModelLoader loader;
	JSONModelSerializer serializer;

	model = factory.createContainerRoot();

	char Name[32];
	char GroupName[128];
	char Version[64];
	cout << "Name :";
	cin >> Name;


	cout << "GroupName :";
	cin >> GroupName;


	cout << "Version :";
	cin >> Version;

	unsigned short int t;


	cout << " --> 0 - Create a Library" << endl;
	cout << " --> 1 - Create a NodeType" << endl;
	cout << " --> 2 - Create a GroupType" << endl;
	cout << "TypeDefiniton :";
	cout << "";

	cin >> t;

	DeployUnit *du =factory.createDeployUnit();
	du->name = Name;
	du->groupName = GroupName;
	du->version = Version;
	du->type ="so";

	TypeDefinition *type;

	switch(t){

	case 0:
		type  = factory.createComponentType();
		type->name = Name;
		type->abstract = false;
		break;


	case 1:


		type = factory.createNodeType();
		type->name = Name;
		type->abstract= false;


		break;

	case 2:
		type = factory.createGroupType();
		type->name = Name;
		type->abstract= false;

		break;
	}
	/* TODO
	cout << "DictionaryType :";
	cout << "";
*/


	type->adddeployUnit(du);
	model->addtypeDefinitions(type);


	model->adddeployUnits(du);


	//	std::cout << serializer.serialize(type) << std::endl;

	ofstream fichier("lib.json");

	fichier << serializer.serialize(model);

	fichier.close();                     //fermeture du flux



}










