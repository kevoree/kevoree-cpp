
#include <stdlib.h>
#include <stdio.h>
#include <parser.h>
#include <string.h>

#ifndef KEVSCRIPTTEST_C__H_
#define KEVSCRIPTTEST_C__H_


char* ReadFile(char *filename);

struct ast_t* getAst(  char *filename);

int test();

int readAllmodel();

int readModel();



#endif
