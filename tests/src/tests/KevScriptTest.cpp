/*
 * KevScriptTest.cpp
 *
 *  Created on: 12 juin 2014
 *      Author: jed
 */

#include "KevScriptTest.h"
#include <parser.h>


CPPUNIT_TEST_SUITE_REGISTRATION( KevScriptTest );

char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size,read_size;
   FILE *handler = fopen(filename,"r");

   if (handler)
   {
       //seek the last byte of the file
       fseek(handler,0,SEEK_END);
       //offset from the first to the last byte, or in other words, filesize
       string_size = ftell (handler);
       //go back to the start of the file
       rewind(handler);

       //allocate a string that can hold it all
       buffer = (char*) malloc (sizeof(char) * (string_size + 1) );
       //read it all in one operation
       read_size = fread(buffer,sizeof(char),string_size,handler);
       //fread doesnt set it so put a \0 in the last position
       //and buffer is now officialy a string
       buffer[string_size] = '\0';

       if (string_size != read_size) {
           //something went wrong, throw away the memory and set
           //the buffer to NULL
           free(buffer);
           buffer = NULL;
        }
    }

    return buffer;
}


void test(){


    // Create our parser
    struct parser_t *parser = parser_new();

    // Setup our input
    char *data = ReadFile("./kevoree-cpp/tests/dataTest/KevScriptTest/test-parser.kevs");
    struct input_t *input = input_new(data, strlen(data));

    // Parse our input
    struct ast_t *ast = parse(parser, input);

    // Print our ast
    display_ast(ast, type_strings);

    ast_recursive_delete(ast);
    input_delete(input);
    parser_delete(parser);


}
KevScriptTest::KevScriptTest() {


}

KevScriptTest::~KevScriptTest() {

}

void KevScriptTest::testkev() {


}
