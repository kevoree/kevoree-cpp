/*
 * KmfCppTest.h
 *
 *  Created on: 8 janv. 2014
 *      Author: jed
 */

#ifndef QueueTests_H
#define QueueTests_H
#include <cppunit/extensions/HelperMacros.h>


#include <iostream>
#include <boost/thread.hpp>

#include <spsc-queue.h>
#include <mpsc-queue.h>
#include <spsc-bounded-queue.h>
#include <mpmc-bounded-queue.h>



class QueueTests : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( QueueTests );
	CPPUNIT_TEST(test);

	CPPUNIT_TEST_SUITE_END();
public:

	QueueTests();
	virtual ~QueueTests();
	void test();


};
#endif /* KMFCPPTEST_H_ */
