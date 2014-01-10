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
	myfile.open ("model1.json");
	if(!myfile){
		cout << "no file trace" << endl;
	}
	CPPUNIT_ASSERT(myfile != NULL);
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
	ContainerRoot   *model = factory.createContainerRoot();
	CPPUNIT_ASSERT(model != NULL);

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

	CPPUNIT_ASSERT(sequencediff->traces.size()  == 0);
	CPPUNIT_ASSERT(sequenceinter->traces.size()  ==70);
	CPPUNIT_ASSERT(sequencemerge->traces.size()  ==0);

}

