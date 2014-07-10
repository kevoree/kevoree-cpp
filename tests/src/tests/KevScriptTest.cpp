/*
 * KevScriptTest.cpp
 *
 *  Created on: 12 juin 2014
 *      Author: jed
 */

#include "KevScriptTest.h"
#include "KevScriptEngine.h"
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


void KevScriptTest::TestGetAst() {
	struct ast_t *ast =	getAst("./dataTest/KevScriptTest/bigScript.kevs") ;
	DefaultkevoreeFactory factory;
	ContainerRoot   *model = factory.createContainerRoot();
	//interpret(ast,model);
	//display_ast(ast, type_strings);

	CPPUNIT_ASSERT(1);

}
