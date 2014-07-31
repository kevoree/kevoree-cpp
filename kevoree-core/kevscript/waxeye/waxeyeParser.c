#include <kevoree-core/kevscript/api/waxeyeParser.h>
#include "stdio.h"

char* ReadFile(const char *filename)
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
		//printf("KevScript size %d octets \n",string_size);
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
	}else {

		return NULL;
	}

	return buffer;
}


int checkerKevscript(const char *filename)
{

	// Create our parser
	struct parser_t *parser = parser_new();

	// Setup our input
	char *data =	ReadFile(filename);
	if(data){
		struct input_t *input = input_new(data, strlen(data));

		// Parse our input
		struct ast_t *ast = parse(parser, input);
		if(ast == NULL){
			return -1;
		}

		// Print our ast
		//display_ast(ast, type_strings);


		// delete
		ast_recursive_delete(ast);
		input_delete(input);
		parser_delete(parser);

	}else {
		printf("KevScript file not found \n");
		return -1;
	}
	return 0;
}




struct ast_t* parseKevscriptFromFilePath(const char *filename)
{
	struct ast_t *ast=NULL;
	char *data =	ReadFile(filename);
	ast = parseKevscript(data);
	free(data);
	return ast;
}


struct ast_t* parseKevscript(const char *script){
	struct ast_t *ast=NULL;
	struct input_t *input=NULL;
	struct parser_t *parser = parser_new();
	if(script){
		input = input_new(script, strlen(script));
		if(input !=NULL){
			ast = parse(parser, input);
			input_delete(input);
		}
	}

	parser_delete(parser);
	return ast ;
}

void freeKevScriptAst(struct ast_t *ast){
	if(ast !=NULL){
		// TODO AYMERIC FIX ME
		//ast_recursive_delete(ast);
	}
}

