/*
 *  shatest.cpp
 *
 *  Copyright (C) 1998, 2009
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *****************************************************************************
 *  $Id: shatest.cpp 12 2009-06-22 19:34:25Z paulej $
 *****************************************************************************
 *
 *  Description:
 *      This file will exercise the SHA1 class and perform the three
 *      tests documented in FIPS PUB 180-1.
 *
 *  Portability Issues:
 *      None.
 *
 */

#include <iostream>
#include "sha1.h"

using namespace std;

/*
 *  Define patterns for testing
 */
#define TESTA   "abc"
#define TESTB   "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"

/*
 *  Function prototype
 */
void DisplayMessageDigest(unsigned *message_digest);

/*  
 *  main
 *
 *  Description:
 *      This is the entry point for the program
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */


/*  
 *  DisplayMessageDigest
 *
 *  Description:
 *      Display Message Digest array
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
void DisplayMessageDigest(unsigned *message_digest)
{
    ios::fmtflags   flags;

    cout << '\t';

    flags = cout.setf(ios::hex|ios::uppercase,ios::basefield);
    cout.setf(ios::uppercase);

    for(int i = 0; i < 5 ; i++)
    {
        cout << message_digest[i] << ' ';
    }

    cout << endl;

    cout.setf(flags);
}
