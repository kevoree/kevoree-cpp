/*
 * KevScriptTest.cpp
 *
 *  Created on: 12 juin 2014
 *      Author: jed
 */

#include "KevScriptTest.h"
#include <parser.h>
#include <string.h>

extern "C" {
#include "Waxeye.h"
}



CPPUNIT_TEST_SUITE_REGISTRATION( KevScriptTest );

KevScriptTest::KevScriptTest() {
	CPPUNIT_ASSERT(test() == 0);


}

KevScriptTest::~KevScriptTest() {

}

void KevScriptTest::testkev() {


}
