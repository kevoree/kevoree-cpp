
#include "Waxeye.h"
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
		printf("KevScript size %d octets \n",string_size);
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


int readAllmodel(){

	int res1 = readModel("./dataTest/KevScriptTest/bigScript.kevs");
	int res2 = readModel("./dataTest/KevScriptTest/empty.kevs");
	int res3 = readModel("./dataTest/KevScriptTest/fragDic.kevs");
	int res4 = readModel("./dataTest/KevScriptTest/hostedNodes.kevs");
	int res5 = readModel("./dataTest/KevScriptTest/lifecycle.kevs");
	int res6 = readModel("./dataTest/KevScriptTest/multilineAttr.kevs");
	int res7 = readModel("./dataTest/KevScriptTest/removes.kevs");
	int res8 = readModel("./dataTest/KevScriptTest/repo.kevs");
	int res9 = readModel("./dataTest/KevScriptTest/test-parser.kevs");
	int res10 = readModel("./dataTest/KevScriptTest/versions.kevs");
	int res = res1 + res2 + res3+ res4 + res5 + res6 + res7 + res8 + res9 + res10 ;

	return res ;

}

int readModel(const char *filename)
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




struct ast_t* getAst(const char *filename)
		{
	struct parser_t *parser = parser_new();
	char *data =	ReadFile(filename);
		if(data){
			struct input_t *input = input_new(data, strlen(data));
			struct ast_t *ast = parse(parser, input);
			if(ast == NULL){
				return NULL;
			}
			return ast ;
		}
		return NULL ;
		}



int test(){


	// Create our parser
	struct parser_t *parser = parser_new();

	const char *file = "./dataTest/KevScriptTest/bigScript.kevs";
	// Setup our input
	char *data = readModel(file);
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
