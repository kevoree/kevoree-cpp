	
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


	
	int main(int argc,char **argv)
	{
		int exit=0;
		clock_t start = clock();
		LOGGER_START(Logger::DEBUG, "kevoree.log");
		KevoreeBootStrap *kb = new KevoreeBootStrap(); 	
		kb->setNodeName("node0");	
		DefaultkevoreeFactory factory;
		JSONModelLoader loader;
		loader.setFactory(&factory);
			
		ContainerRoot *model = factory.createContainerRoot();
			
		ContainerNode *node0 = factory.createContainerNode();
		node0->name = "node0";
		node0->started= true;
			
			
			DeployUnit *d =factory.createDeployUnit();
			d->name = "CPPNodeType";
			d->groupName = "org.kevoree.library";
			d->version = "1.0";
			
			TypeDefinition *nodetype = factory.createNodeType();
			nodetype->name = "CPPNode";
			nodetype->adddeployUnits(d);
			
					
			DeployUnit *dg =factory.createDeployUnit();
			dg->name = "kevoree-group-websocket";
			dg->groupName = "org.kevoree.library";
			dg->version = "1.0";
			
			TypeDefinition *grouptype = factory.createGroupType();
			grouptype->name ="WebSocketGroup";
			grouptype->adddeployUnits(dg);

			
			Group *group = factory.createGroup();
			group->name ="group0";
			group->started = true;
			group->addtypeDefinition(grouptype);
		

			
			TypeDefinition *comtype  = factory.createComponentType();
			
			DeployUnit *dc =factory.createDeployUnit();
			dc->name = "HelloWorldComponent";
			dc->groupName = "org.kevoree.library";
			dc->version = "1.0";
			comtype->adddeployUnits(dc);
			
			ComponentInstance *c2 = factory.createComponentInstance();
			c2->name ="HelloWorldComponent0";
			c2->addtypeDefinition(comtype);

			node0->addtypeDefinition(nodetype);
			node0->addgroups(group);
			node0->addcomponents(c2);

			model->addtypeDefinitions(grouptype);
			model->addtypeDefinitions(nodetype);
			model->addtypeDefinitions(comtype);
			model->addnodes(node0);
			model->addgroups(group);


			kb->setBootstrapModel(model); // boostrapmodel
			kb->start();

		kb->join();
	    clock_t finish = clock();	
		std::cin >> exit; 
	}
		
	

		
	

	
	

	
