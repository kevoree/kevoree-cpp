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
#include <kevoree-core/kevscript/api/Waxeye.h>
}


CPPUNIT_TEST_SUITE_REGISTRATION( KevScriptTest );

KevScriptTest::KevScriptTest() {
	CPPUNIT_ASSERT(1);


}


KevScriptTest::~KevScriptTest() {

}

void KevScriptTest::testkevAllModel() {
	CPPUNIT_ASSERT(readAllmodel() == 0);

}

void KevScriptTest::TestAddRepo() {

	struct ast_t *ast =	getAst("./dataTest/KevScriptTest/repo.kevs") ;
	DefaultkevoreeFactory factory;
	ContainerRoot   *model = factory.createContainerRoot();
	KevScriptEngine *kse = new KevScriptEngine() ;
	try
	{
		kse->interpret(ast,model);
	}
	catch (string e)
	{
		LOGGER_WRITE(Logger::ERROR,e);
	}

	CPPUNIT_ASSERT(model->repositories.size() == 1);
	delete model;
	delete kse;

}

void KevScriptTest::TestRemove() {

	struct ast_t *ast =	getAst("./dataTest/KevScriptTest/kevscriptKevCPP.kevs") ;
	DefaultkevoreeFactory factory;
	ContainerRoot   *model = factory.createContainerRoot();
	KevScriptEngine *kse = new KevScriptEngine() ;

	try
	{
		kse->interpret(ast,model);
	}
	catch (string e)
	{
		LOGGER_WRITE(Logger::ERROR,e);
	}


	CPPUNIT_ASSERT(1);
	delete model;
	delete kse;

}






