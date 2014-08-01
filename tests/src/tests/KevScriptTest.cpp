/*
 * KevScriptTest.cpp
 *
 *  Created on: 12 juin 2014
 *      Author: jed
 */

#include "KevScriptTest.h"
#include <kevoree-core/kevscript/api/KevScriptEngine.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <iostream>

extern "C" {
#include <kevoree-core/kevscript/api/waxeyeParser.h>
}


CPPUNIT_TEST_SUITE_REGISTRATION( KevScriptTest );

KevScriptTest::KevScriptTest() {
	CPPUNIT_ASSERT(1);


}


KevScriptTest::~KevScriptTest() {

}

void KevScriptTest::testkevAllModel() {

	int res1 = checkerKevscript("./dataTest/KevScriptTest/bigScript.kevs");
	int res2 = checkerKevscript("./dataTest/KevScriptTest/empty.kevs");
	int res3 = checkerKevscript("./dataTest/KevScriptTest/fragDic.kevs");
	int res4 = checkerKevscript("./dataTest/KevScriptTest/hostedNodes.kevs");
	int res5 = checkerKevscript("./dataTest/KevScriptTest/lifecycle.kevs");
	int res6 = checkerKevscript("./dataTest/KevScriptTest/multilineAttr.kevs");
	int res7 = checkerKevscript("./dataTest/KevScriptTest/removes.kevs");
	int res8 = checkerKevscript("./dataTest/KevScriptTest/repo.kevs");
	int res9 = checkerKevscript("./dataTest/KevScriptTest/test-parser.kevs");
	int res10 = checkerKevscript("./dataTest/KevScriptTest/versions.kevs");
	int res = res1 + res2 + res3+ res4 + res5 + res6 + res7 + res8 + res9 + res10 ;
	CPPUNIT_ASSERT(res == 0);
}

void KevScriptTest::TestAddRepo() {
	DefaultkevoreeFactory factory;
	ContainerRoot   *model=NULL;
	ifstream f;
	f.open ("./dataTest/KevScriptTest/repo.kevs");

	try
	{
		model = factory.createContainerRoot();
		CPPUNIT_ASSERT(model !=NULL);
		KevScriptEngine kse;
		if(f){
			kse.executeFromStream(f,model);
		}
	}
	catch(std::exception const& e)
	{
		LOGGER_WRITE(Logger::ERROR," "+string(e.what()));
	}



	CPPUNIT_ASSERT(model->repositories.size() == 1);
	delete model;
}

void KevScriptTest::TestRemove() {
	DefaultkevoreeFactory factory;
	ContainerRoot   *model=NULL;
	ifstream f;
	f.open ("./dataTest/KevScriptTest/kevscriptKevCPP.kevs");

	try
	{
		model = factory.createContainerRoot();
		CPPUNIT_ASSERT(model !=NULL);

		KevScriptEngine kse;
		if(f){
			kse.executeFromStream(f,model);
		}
	}
	catch(std::exception const& e)
	{
		LOGGER_WRITE(Logger::ERROR," "+string(e.what()));
	}


	// TODO AYMERIC
	CPPUNIT_ASSERT(1);
	delete model;
}

void KevScriptTest::theUltimeTest(){
	DefaultkevoreeFactory factory;
	JSONModelLoader loader;
	KevScriptEngine kse;
	ContainerRoot   *model=NULL;
	ifstream f;
	f.open ("./dataTest/KevScriptTest/kevscriptKevCPP.kevs");

	loader.setFactory(&factory);
	ifstream json_file;
	json_file.open ("./dataTest/KevScriptTest/model_to_check.json");
	if(!json_file){
		cout << "no json_file trace" << endl;
	}

	ContainerRoot *model_to_compare = (ContainerRoot*)loader.loadModelFromStream(json_file)->front();
	CPPUNIT_ASSERT(model_to_compare !=NULL);
	try
	{
		model = factory.createContainerRoot();
		CPPUNIT_ASSERT(model !=NULL);

		if(f){
			kse.executeFromStream(f,model);

			ModelCompare *compare= new ModelCompare();

				// FIX ME
				TraceSequence *sequencediff = compare->diff(model,model_to_compare);

				CPPUNIT_ASSERT(sequencediff->traces.size()  == 0);
				delete compare;
				delete sequencediff;
		}
	}
	catch(std::exception const& e)
	{
		LOGGER_WRITE(Logger::ERROR," "+string(e.what()));
	}


	// TODO AYMERIC
	CPPUNIT_ASSERT(1);
	delete model;
}
