/*
 *  shacmp.cpp
 *
 *  Copyright (C) 1998, 2009
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *****************************************************************************
 *  $Id: shacmp.cpp 12 2009-06-22 19:34:25Z paulej $
 *****************************************************************************
 *
 *  Description:
 *      This utility will compare two files by producing a message digest
 *      for each file using the Secure Hashing Algorithm and comparing
 *      the message digests.  This function will return 0 if they
 *      compare or 1 if they do not or if there is an error.
 *      Errors result in a return code higher than 1.
 *
 *  Portability Issues:
 *      none.
 *
 */

#include <stdio.h>
#include <string.h>
#include "sha1.h"

/*
 *  Return codes
 */
#define SHA1_COMPARE        0
#define SHA1_NO_COMPARE     1
#define SHA1_USAGE_ERROR    2
#define SHA1_FILE_ERROR     3

/*
 *  Function prototype
 */
void usage();

/*  
 *  main
 *
 *  Description:
 *      This is the entry point for the program
 *
 *  Parameters:
 *      argc: [in]
 *          This is the count of arguments in the argv array
 *      argv: [in]
 *          This is an array of filenames for which to compute message digests
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */

/*  
 *  usage
 *
 *  Description:
 *      This function will display program usage information to the user.
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

