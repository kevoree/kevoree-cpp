/*
 * DebugBootstrapTest.h
 *
 *  Created on: 26 juin 2014
 *      Author: Aymeric
 */



#include "DebugBootstrapTest.h"


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

CPPUNIT_TEST_SUITE_REGISTRATION( DebugBootstrapTest );

DebugBootstrapTest::DebugBootstrapTest(){


}

DebugBootstrapTest::~DebugBootstrapTest(){


}


void DebugBootstrapTest::testBug(){

	DefaultkevoreeFactory factory;
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
//	std::cout << sequencediff2->exportToString() << std::endl;

	CPPUNIT_ASSERT(sequencediff2->traces.size()  != 0);
	CPPUNIT_ASSERT(sequencediff->traces.size()  == 0);
	CPPUNIT_ASSERT(sequenceinter->traces.size()  ==70);
	CPPUNIT_ASSERT(sequencemerge->traces.size()  ==0);



}

