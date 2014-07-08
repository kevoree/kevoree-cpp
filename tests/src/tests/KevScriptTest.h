/*
 * KevScriptTest.h
 *
 *  Created on: 12 juin 2014
 *      Author: jed
 */

#ifndef KEVSCRIPTTEST_H_
#define KEVSCRIPTTEST_H_

#include <cppunit/extensions/HelperMacros.h>

class KevScriptTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( KevScriptTest );
	CPPUNIT_TEST(testkevAllModel);
	CPPUNIT_TEST_SUITE_END();

public:
	KevScriptTest();
	virtual ~KevScriptTest();
	void testkevAllModel();
};

#endif /* KEVSCRIPTTEST_H_ */
