/*
 * KmfCppTest.cpp
 *
 *  Created on: 8 janv. 2014
 *      Author: jed
 */

#include "KmfCppTest.h"

#include <microframework/api/trace/DefaultTraceConverter.h>
#include <microframework/api/json/JSONModelLoader.h>
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


}
