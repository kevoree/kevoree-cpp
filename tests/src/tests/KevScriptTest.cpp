/*
 * KevScriptTest.cpp
 *
 *  Created on: 12 juin 2014
 *      Author: jed
 */

#include "KevScriptTest.h"
#include "kevScriptEngine/KevScriptEngine.h"
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <iostream>

extern "C" {
#include "Waxeye.h"
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
	const string log_file ="kevoree.log";
	Logger::Start(Logger::DEBUG, log_file);
	struct ast_t *ast =	getAst("./dataTest/KevScriptTest/repo.kevs") ;
	DefaultkevoreeFactory factory;
	ContainerRoot   *model = factory.createContainerRoot();
	KevScriptEngine *kse = new KevScriptEngine() ;
	kse->interpret(ast,model);

	CPPUNIT_ASSERT(model->repositories.size() == 1);
	delete model;
	delete kse;

	//parser_delete(ast);

}
