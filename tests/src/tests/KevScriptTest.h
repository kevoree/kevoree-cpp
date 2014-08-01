/*
 * KevScriptTest.h
 *
 *  Created on: 12 juin 2014
 *      Author: jed
 */

#ifndef KEVSCRIPTTEST_H_
#define KEVSCRIPTTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <microframework/api/trace/DefaultTraceConverter.h>
#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/json/JSONModelSerializer.h>


#include <microframework/api/compare/ModelCompare.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>

class KevScriptTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( KevScriptTest );
	CPPUNIT_TEST(testkevAllModel);
	CPPUNIT_TEST(TestAddRepo);
	CPPUNIT_TEST(TestRemove);
	CPPUNIT_TEST(theUltimeTest);
	CPPUNIT_TEST_SUITE_END();

public:
	KevScriptTest();
	virtual ~KevScriptTest();
	void testkevAllModel();
	void TestAddRepo();
	void TestRemove();

	void theUltimeTest();
};

#endif /* KEVSCRIPTTEST_H_ */
