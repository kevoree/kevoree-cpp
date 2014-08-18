// todo
/**
 * Author: jedartois@gmail.com
 * Date: 24/10/13
 * Time: 18:36
 */

/*
#include <microframework/api/xmi/XMIModelLoader.h>


vector<KMFContainer*>* XMIModelLoader::loadModelFromString(string str){
	std::istringstream ss( str); // convert string to istream
	return loadModelFromStream(ss);
}

vector<KMFContainer*>* XMIModelLoader::loadModelFromStream( istream &inputStream){
	if(!inputStream)
	{
		Logger::Write(Logger::ERROR,"XMIModelLoader::loadModelFromStream the file is not available ");
		return NULL;
	}
	return deserialize(inputStream);
}



vector<KMFContainer*>* XMIModelLoader::deserialize(istream &inputStream){
	vector<ResolveCommand*> *resolverCommands = new vector<ResolveCommand*>;
	vector<KMFContainer*> *roots= new  vector<KMFContainer*>;
	Lexer *lexer =new Lexer(inputStream);
	Token currentToken = lexer->nextToken();
	if(currentToken.tokenType == LEFT_BRACE)
	{
		loadObject(lexer,"",NULL,roots,resolverCommands);
		for (std::vector<ResolveCommand*>::iterator it = resolverCommands->begin() ; it != resolverCommands->end(); ++it)
		{
			ResolveCommand *cmd = *it;
			cmd->run();
			delete cmd;

		}
	} else
	{
		delete roots;
		roots = NULL;
		Logger::Write(Logger::ERROR,"XMIModelLoader::deserializeBad Format / { expected");
	}


	delete resolverCommands;
	delete lexer;
	return roots;
}
*/
