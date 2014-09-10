/*
 * KmfCppTest.cpp
 *
 *  Created on: 8 janv. 2014
 *      Author: jed
 */

#include "KmfCppTest.h"

#include <microframework/api/trace/DefaultTraceConverter.h>
#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/json/JSONModelSerializer.h>


#include <microframework/api/compare/ModelCompare.h>
#include <microframework/api/utils/ModelCloner.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/time.h>
#include <string>
#include <microframework/api/trace/TraceSequence.h>

CPPUNIT_TEST_SUITE_REGISTRATION( KmfCppTest );

KmfCppTest::KmfCppTest(){


}

KmfCppTest::~KmfCppTest(){


}
void KmfCppTest::testKmfFactory(){
	DefaultkevoreeFactory factory;
	KMFContainer *c = factory.create("org.kevoree.ContainerRoot");
	CPPUNIT_ASSERT(c != NULL);
	c = factory.create("org.kevoree.ContainerNode");
	CPPUNIT_ASSERT(c != NULL);



}
void KmfCppTest::testKmfTraces(){
	ModelTrace *model_trace = new ModelAddTrace("","nodes","nodes[server-node]","org.kevoree.ContainerNode");
	// todo

}
void KmfCppTest::testKmfLoader()
{
	DefaultkevoreeFactory factory;
	JSONModelLoader loader;

	loader.setFactory(&factory);
	ifstream myfile;
	myfile.open ("dataTest/kmf/model1.json");
	if(!myfile){
		cout << "no file trace" << endl;
	}

	ContainerRoot *model = (ContainerRoot*)loader.loadModelFromStream(myfile)->front();

	CPPUNIT_ASSERT(model != NULL);
	CPPUNIT_ASSERT(model->nodes.size() ==1);
	CPPUNIT_ASSERT(model->groups.size() ==2);


	CPPUNIT_ASSERT(	model->findByPath("nodes[node0]") != NULL);
	ContainerNode *node = (ContainerNode*)model->findByPath("nodes[node0]");

	CPPUNIT_ASSERT(	node->name.compare("node0")  == 0);

	delete model;
}


void KmfCppTest::testKmfSerializer(){

	DeployUnit *d =new DeployUnit();
	d->name = "CPPNodeType";
	d->groupName = "org.kevoree.library";
	d->version = "1.0";
	d->type ="elf32-i386";

	DeployUnit *d2 =new DeployUnit();
	d2->name = "CPPNodeType";
	d2->groupName = "org.kevoree.library";
	d2->version = "1.0";
	d2->type ="elf32-i386";

	JSONModelSerializer ser;
	CPPUNIT_ASSERT( ser.serialize(d).compare(ser.serialize(d2)) == 0);




}
void KmfCppTest::testKmfCompare(){


	DefaultkevoreeFactory factory;
	JSONModelLoader loader;
	ContainerRoot   *model = factory.createContainerRoot();
	ContainerRoot   *model2 = factory.createContainerRoot();

	CPPUNIT_ASSERT(model != NULL);
	CPPUNIT_ASSERT(model2 != NULL);

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
	grouptype->name ="w";
	grouptype->version = "1";

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
	group->name ="g0";
	group->started = true;
	group->addtypeDefinition(grouptype);

	FragmentDictionary *dico =factory.createFragmentDictionary();

	dico->name ="node0";
	DictionaryValue *valport = factory.createDictionaryValue();
	valport->name ="port";
	valport->value ="9000";

	dico->addvalues(valport);

	group->addfragmentDictionary(dico);

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

	model->adddeployUnits(d);
	model->adddeployUnits(dg);
	model->adddeployUnits(dc);

	c2->addtypeDefinition(comtype);
	model->addnodes(node0);

	model->addgroups(group);
	group->addsubNodes(node0);
	node0->addgroups(group);

	ModelCompare *compare= new ModelCompare();
	TraceSequence *sequencediff = compare->diff(model,model);
	TraceSequence *sequenceinter = compare->inter(model,model);
	TraceSequence *sequencemerge = compare->merge(model,model);

	TraceSequence *sequencediff2 = compare->diff(model2,model);
	//std::cout << sequencediff2->exportToString() << std::endl;

	CPPUNIT_ASSERT(sequencediff2->traces.size()  != 0);
	CPPUNIT_ASSERT(sequencediff->traces.size()  == 0);
	CPPUNIT_ASSERT(sequenceinter->traces.size()  ==70);
	CPPUNIT_ASSERT(sequencemerge->traces.size()  ==0);


	loader.setFactory(&factory);
	ifstream myfile;
	myfile.open ("dataTest/kmf/model_channel_fakeconsole.json");
	if(!myfile){
		cout << "no file trace" << endl;
	}

	ContainerRoot *model3 = (ContainerRoot*)loader.loadModelFromStream(myfile)->front();
	TraceSequence *sequencediff3 = compare->diff(model2,model3);


	CPPUNIT_ASSERT(sequencediff2->traces.size()  == 70);
	//std::cout << sequencediff2->traces.size() << std::endl;

	delete model3;
	delete model;
	delete sequencediff;
	delete sequenceinter;
	delete sequencemerge;
	delete sequencediff2;
	delete sequencediff3;

}

void KmfCppTest::testKmfCompare2(){

	DefaultkevoreeFactory factory;
	JSONModelLoader loader;
	ContainerRoot   *model_src;
	ContainerRoot   *model_target;
	loader.setFactory(&factory);

	ifstream src;
	src.open ("dataTest/kmf/model_src.json");
	if(!src){
		cout << "no file trace" << endl;
	}

	ifstream target;
	target.open ("dataTest/kmf/model_target.json");
	if(!target){
		cout << "no file trace" << endl;
	}

	model_src = (ContainerRoot*)loader.loadModelFromStream(src)->front();
	model_target = (ContainerRoot*)loader.loadModelFromStream(target)->front();
	CPPUNIT_ASSERT(model_src  !=NULL);
	CPPUNIT_ASSERT(model_target != NULL);
	ModelCompare *compare= new ModelCompare();

	// FIX ME
	TraceSequence *sequencediff = compare->diff(model_src,model_target);

	CPPUNIT_ASSERT(sequencediff->traces.size()  == 13);

	delete sequencediff;
	delete model_src;
	delete model_target;
}
/* REMOVE ONE BINDING */
void KmfCppTest::testKmfCompareBinding(){
	DefaultkevoreeFactory factory;
		JSONModelLoader loader;
		ContainerRoot   *model_src;
		ContainerRoot   *model_target;
		loader.setFactory(&factory);

		ifstream src;
		src.open ("dataTest/kmf/bindings.json");
		if(!src){
			cout << "no file trace" << endl;
		}

		ifstream target;
		target.open ("dataTest/kmf/bindings2.json");
		if(!target){
			cout << "no file trace" << endl;
		}

		model_src = (ContainerRoot*)loader.loadModelFromStream(src)->front();
		model_target = (ContainerRoot*)loader.loadModelFromStream(target)->front();
		CPPUNIT_ASSERT(model_src  !=NULL);
		CPPUNIT_ASSERT(model_target != NULL);
		ModelCompare *compare= new ModelCompare();

		// FIX ME
		TraceSequence *sequencediff = compare->diff(model_src,model_target);
	//	std::cout << sequencediff->exportToString() << std::endl;
		//CPPUNIT_ASSERT(sequencediff->traces.size()  == 7);

		delete sequencediff;
		delete model_src;
		delete model_target;
}

void KmfCppTest::testKmfCompare3(){
	DefaultkevoreeFactory factory;
		JSONModelLoader loader;
		ContainerRoot   *model_src;
		ContainerRoot   *model_target;
		loader.setFactory(&factory);

		ifstream src;
		src.open ("dataTest/kmf/bindings.json");
		if(!src){
			cout << "no file trace" << endl;
		}

		ifstream target;
		target.open ("dataTest/kmf/model_node_empty.json");
		if(!target){
			cout << "no file trace" << endl;
		}

		model_src = (ContainerRoot*)loader.loadModelFromStream(src)->front();
		model_target = (ContainerRoot*)loader.loadModelFromStream(target)->front();
		CPPUNIT_ASSERT(model_src  !=NULL);
		CPPUNIT_ASSERT(model_target != NULL);
		ModelCompare *compare= new ModelCompare();

		// FIX ME
		TraceSequence *sequencediff = compare->diff(model_src,model_target);
	//	std::cout << sequencediff->exportToString() << std::endl;
		//std::cout <<sequencediff->traces.size() << std::endl;

		CPPUNIT_ASSERT(sequencediff->traces.size()  == 63);

		delete sequencediff;
		delete model_src;
		delete model_target;

}

void KmfCppTest::testKmfCloner(){
//	Logger::Start(Logger::DEBUG_MICROFRAMEWORK, "log");
	DefaultkevoreeFactory factory;
		JSONModelLoader loader;
		JSONModelSerializer serial ;
		ContainerRoot   *model_src;
		ContainerRoot   *model_target;
		loader.setFactory(&factory);

		ifstream src;
		src.open ("dataTest/kmf/bindings.json");
		if(!src){
			cout << "no file trace" << endl;
		}

		ifstream target;
		target.open ("dataTest/kmf/model_node_empty.json");
		if(!target){
			cout << "no file trace" << endl;
		}


		model_src = (ContainerRoot*)loader.loadModelFromStream(src)->front();
	//	model_target = (ContainerRoot*)loader.loadModelFromStream(target)->front();
		CPPUNIT_ASSERT(model_src  !=NULL);
		CPPUNIT_ASSERT(model_target != NULL);
/*
		ModelCompare *compare= new ModelCompare();
		TraceSequence *sequencediff = compare->diff(model_src,model_target);
		std::cout << sequencediff->exportToString() << std::endl;
		cout << "-----------------" << endl ;
*/
		ModelCloner *cloner= new ModelCloner(&factory);
		model_target = cloner->clone(model_src,true,true) ;
		//model_src->toTraces(true, true) ;
		ModelCompare *compare= new ModelCompare();
		TraceSequence *sequencediff = compare->diff(model_src,model_target);
		std::cout << sequencediff->exportToString() << std::endl;
	//	cout <<serial.serialize(model_src) <<endl;
		cout <<"------------------------------" <<endl;
		cout <<serial.serialize(model_target) <<endl;



		CPPUNIT_ASSERT(sequencediff->traces.size()  == 0);




		delete sequencediff;
		delete model_src;
		delete model_target;

}


