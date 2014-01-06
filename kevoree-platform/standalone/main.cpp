	
	#include <kevoree-platform/KevoreeBootStrap/KevoreeBootStrap.h>
	#include <microframework/api/trace/DefaultTraceConverter.h>
	#include <microframework/api/json/JSONModelLoader.h>
	#include <microframework/api/json/JSONModelSerializer.h>
	#include <microframework/api/compare/ModelCompare.h>
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
	#include <signal.h>
	#include <stdlib.h>
	#include <stdio.h>

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
		LOGGER_START(Logger::DEBUG, "kevoree.log");
		/*
		for(int i=0;i<100000;i++){
		 void* handle = dlopen("/home/jed/KEVOREE_PROJECT/kevoree-cpp/build/libwebsocketgroup.so",RTLD_NOW);
		
			AbstractTypeDefinition* (*create)();
			create =  (AbstractTypeDefinition* (*)())dlsym(handle, "create");
			if(!create){
				LOGGER_WRITE(Logger::DEBUG,"cannot find symbol newInstance");	
			}
			AbstractTypeDefinition* c = (AbstractTypeDefinition*)create();
			c->dico["port"] = "9000";
			//c->start();
			
			boost::thread api_caller(boost::bind(&AbstractTypeDefinition::start, c));
			api_caller.timed_join(boost::posix_time::milliseconds(10000000));
		
		
			boost::thread api_caller_stop(boost::bind(&AbstractTypeDefinition::stop, c));
			api_caller_stop.timed_join(boost::posix_time::milliseconds(10000000));
		
		
		
			void (*destroy)(AbstractTypeDefinition*);
			destroy = (void (*)(AbstractTypeDefinition*))dlsym(handle, "destroy_object");
			destroy(c);
		}
			
		return 0;*/
		DefaultkevoreeFactory factory;
		JSONModelLoader loader;	 
		
		signal (SIGINT,my_handler);
		int exit=0;
		clock_t start = clock();
	
		kb = new KevoreeBootStrap(); 	
		kb->setNodeName("node0");	

		loader.setFactory(&factory);
			
		model = factory.createContainerRoot();
			

			
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
			
			
		
			TypeDefinition *comdpkg  = factory.createComponentType();
			comdpkg->name ="DpkgManager";
			comdpkg->abstract = false;
			
			DeployUnit *dc2 =factory.createDeployUnit();
			dc2->name = "DpkgManager";
			dc2->groupName = "org.kevoree.library";
			dc2->version = "1.0";
			dc2->type ="elf32-i386";
			comdpkg->adddeployUnit(dc2);
			
			
			
			TypeDefinition *comtype  = factory.createComponentType();
			comtype->name = "comp";
			comtype->abstract = false;
			
			DeployUnit *dc =factory.createDeployUnit();
			dc->name = "HelloWorldComponent";
			dc->groupName = "org.kevoree.library";
			dc->version = "1.0";
			dc->type ="elf32-i386";
			
			comtype->adddeployUnit(dc);
			
			
			ComponentInstance *c2 = factory.createComponentInstance();
			c2->name ="HelloWorldComponent0";
			c2->started = true;

			node0->addtypeDefinition(nodetype);

	
			


			model->addtypeDefinitions(grouptype);
			model->addtypeDefinitions(nodetype);
			model->addtypeDefinitions(comtype);
			model->addtypeDefinitions(comdpkg);
			
			model->adddeployUnits(d);
			model->adddeployUnits(dg);
			model->adddeployUnits(dc);
			model->adddeployUnits(dc2);
			
			c2->addtypeDefinition(comtype);
			model->addnodes(node0);
			
			model->addgroups(group);
			group->addsubNodes(node0);
			node0->addgroups(group);


			kb->setBootstrapModel(model); // boostrapmodel
			kb->start();



	    clock_t finish = clock();	
		std::cin >> exit; 
	}
		
	

		
	

	
	

	
