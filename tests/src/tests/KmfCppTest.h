/*
 * KmfCppTest.h
 *
 *  Created on: 8 janv. 2014
 *      Author: jed
 */

#ifndef KMFCPPTEST_H_
#define KMFCPPTEST_H_
#include <cppunit/extensions/HelperMacros.h>



class KmfCppTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( KmfCppTest );
	CPPUNIT_TEST(testKmfFactory);
	CPPUNIT_TEST( testKmfTraces );
	CPPUNIT_TEST( testKmfLoader );
	CPPUNIT_TEST( testKmfSerializer );
	CPPUNIT_TEST( testKmfCompare );

	CPPUNIT_TEST_SUITE_END();
public:

	KmfCppTest();
	virtual ~KmfCppTest();
	void testKmfFactory();
	void testKmfLoader();
	void testKmfTraces();
	void testKmfSerializer();
	void testKmfCompare();
};

#endif /* KMFCPPTEST_H_ */
