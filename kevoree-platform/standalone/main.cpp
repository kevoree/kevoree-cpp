	
	#include <kevoree-platform/KevoreeBootStrap/KevoreeBootStrap.h>
	#include <microframework/api/trace/DefaultTraceConverter.h>
	#include <microframework/api/json/JSONModelLoader.h>
	#include <microframework/api/json/JSONModelSerializer.h>
	#include <microframework/api/compare/ModelCompare.h>
	#include <kevoree-core/model/kevoreeadaptation/kevoreeadaptation.h>
	#include <kevoree-core/model/kevoree/ContainerRoot.h>
	#include <kevoree-core/model/kevoree/Instance.h>
	#include <iostream>
	#include <fstream>
	#include <stdio.h>
	#include <sys/time.h>
	#include <microframework/api/KMFContainer.h>
	#include <microframework/api/utils/Logger.h>
	#include <sys/time.h>
#include <sys/resource.h>


#include <kevoree-tools/DynamicLoader/DynamicLoader.h>
	
	int main(int argc,char **argv)
	{
		DefaultkevoreeFactory factory;
		JSONModelLoader loader;	 
	

		
		int exit=0;
		clock_t start = clock();
		LOGGER_START(Logger::DEBUG, "kevoree.log");
		KevoreeBootStrap *kb = new KevoreeBootStrap(); 	
		kb->setNodeName("node0");	

		loader.setFactory(&factory);
			
		ContainerRoot *model = factory.createContainerRoot();
			
		ContainerNode *node0 = factory.createContainerNode();
		node0->name = "node0";
		node0->started= true;
			
			
			DeployUnit *d =factory.createDeployUnit();
			d->name = "CPPNodeType";
			d->groupName = "org.kevoree.library";
			d->version = "1.0";
			d->type ="elf32-i386";
			
			TypeDefinition *nodetype = factory.createNodeType();
			nodetype->name = "CPPNode";
			nodetype->abstract= false;
			nodetype->adddeployUnit(d);
			
					
			DeployUnit *dg =factory.createDeployUnit();
			dg->name = "kevoree-group-websocket";
			dg->groupName = "org.kevoree.library";
			dg->version = "1.0";
			dg->type ="elf32-i386";
			
			TypeDefinition *grouptype = factory.createGroupType();
			grouptype->abstract= false;
			grouptype->name ="WebSocketGroup";
			
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

			
			Group *group = factory.createGroup();
			group->name ="group0";
			group->started = true;
			group->addtypeDefinition(grouptype);
			
			Dictionary *dico =factory.createDictionary();
			DictionaryValue *valport = factory.createDictionaryValue();
			valport->name ="port";
			valport->value ="9000";
			
			
			dico->addvalues(valport);
			group->adddictionary(dico);
			
			TypeDefinition *comtype  = factory.createComponentType();
			comtype->name = "comp";
			
			DeployUnit *dc =factory.createDeployUnit();
			dc->name = "HelloWorldComponent";
			dc->groupName = "org.kevoree.library";
			dc->version = "1.0";
			dc->type ="elf32-i386";
			
			comtype->adddeployUnit(dc);
			
			
			ComponentInstance *c2 = factory.createComponentInstance();
			c2->name ="HelloWorldComponent0";


			node0->addtypeDefinition(nodetype);

			node0->addcomponents(c2);

			model->addtypeDefinitions(grouptype);
			model->addtypeDefinitions(nodetype);
			model->addtypeDefinitions(comtype);
			model->adddeployUnits(d);
			model->adddeployUnits(dg);
			model->adddeployUnits(dc);
			
			c2->addtypeDefinition(comtype);
			model->addnodes(node0);
			
			model->addgroups(group);
			group->addsubNodes(node0);
			node0->addgroups(group);


			kb->setBootstrapModel(model); // boostrapmodel
			 int who = RUSAGE_SELF; 
			 struct rusage usage; 
			 getrusage(who,&usage);
			 cout << usage.ru_maxrss << endl;
			kb->start();



	    clock_t finish = clock();	
		std::cin >> exit; 
	}
		
	

		
	

	
	

	
