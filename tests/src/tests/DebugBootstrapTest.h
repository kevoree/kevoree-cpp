/*
 * DebugBoostrap.h
 *
 *  Created on: 26 juin 2014
 *      Author: Aymeric
 */



#ifndef DEBUGBOOTSTRAP_H_
#define DEBUGBOOTSTRAP_H_
#include <cppunit/extensions/HelperMacros.h>




class DebugBootstrapTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( DebugBootstrapTest );
	CPPUNIT_TEST(testBug);

	CPPUNIT_TEST_SUITE_END();
public:

	DebugBootstrapTest();
	virtual ~DebugBootstrapTest();
	void testBug();

};
#endif /* KMFCPPTEST_H_ */
