
#include <stdlib.h>
#include <stdio.h>
#include <parser.h>
#include <string.h>

#ifndef KEVSCRIPTTEST_C__H_
#define KEVSCRIPTTEST_C__H_
/*
 * API C for waxeye parser
 */

/**
 * script : the script
 */
struct ast_t* parseKevscript(const char *script);

/**
 * filename : the path to the file to parser
 */
struct ast_t* parseKevscriptFromFilePath(const char *filename);

/* free */
void freeKevScriptAst(struct ast_t*);

/* kind of checker*/
int checkerKevscript(const char *filename);


#endif
