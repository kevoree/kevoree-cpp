#include "KevScriptEngine.h"
#include <iostream>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include "utils/TypeDefinitionResolver.h"

extern "C" {
#include <tests/src/tests/Waxeye.h>
}


KevScriptEngine::KevScriptEngine()
{

}

KevScriptEngine::~KevScriptEngine()
{

}


void KevScriptEngine::execute(std::string nodeName,ContainerRoot *model){

}
void KevScriptEngine::executeFromStream(istream	&inputstream,ContainerRoot *model){


}


void KevScriptEngine::interpret(struct ast_t *ast, ContainerRoot *model){
	struct ast_tree_t *tree = ast->data.tree;
    struct vector_t *chil ;
    size_t num_chil ;
    size_t i;
    TypeDefinition *td  ;
    DefaultkevoreeFactory factory;
    Repository *rep ;

    switch (tree->type) {

    case TYPE_KEVSCRIPT:

    	chil = ast->data.tree->children;
    	if(chil != NULL)
    	{
    	num_chil = chil->size;
    	for (i = 0; i < num_chil; i +=1) {
    		interpret((struct ast_t*) vector_get(chil, i), model);
    		}
    	}
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_KEVSCRIPT");

    	break ;
    case TYPE_STATEMENT:
       	chil = ast->data.tree->children;
        	if(chil != NULL)
        	{
        	num_chil = chil->size;
        	for (i = 0; i < num_chil; i +=1) {
        		interpret((struct ast_t*) vector_get(chil, i), model);
        		}
        	}
        	LOGGER_WRITE(Logger::DEBUG,"TYPE_STATEMENT");
        	break ;
    case TYPE_ADDREPO:
    	chil = ast->data.tree->children;
      	rep = factory.createRepository();
      	rep->url = ast_children_as_string((struct ast_t*) vector_get(chil,0)) ;
      	model->addrepositories(rep);
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADDREPO");
    	break ;

    case TYPE_ADD:
			td = TypeDefinitionResolver::resolve((struct ast_t*) vector_get(chil, 0),model) ;

    	if(td == NULL)
    	{
    		throw string("TypeDefinition not found : " + string(ast_children_as_string((struct ast_t*) vector_get(chil,1))))	;
    	}else
    	{
    		struct ast_t *instance_name =  (struct ast_t*)  vector_get(chil, 1) ;
    		if(instance_name->type == TYPE_NAMELIST)
    		{
    			struct vector_t *chil_inst =instance_name->data.tree->children;
    			size_t num_inst = chil_inst->size;

				for (i = 0; i < num_inst; i +=1) {
					LOGGER_WRITE(Logger::DEBUG,"Todo : ApplyAdd");
									}
    		}
    	}
       	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADD");
    	break ;
    case TYPE_INCLUDE:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_INCLUDE");
    	break ;

    case TYPE_REMOVE:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_REMOVE");
    	break ;
    case TYPE_MOVE:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_MOVE");
    	break ;
    case TYPE_ATTACH:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_ATTACH");
    	break ;
    case TYPE_DETACH:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_DETACH");
    	break ;


    case TYPE_NETWORK:
     	LOGGER_WRITE(Logger::DEBUG,"TYPE_NETWORK");
    	break ;
    case TYPE_INCLUDE:
       	LOGGER_WRITE(Logger::DEBUG,"TYPE_INCLUDE");
    	break ;
    case TYPE_ADDBINDING:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADDBINDING");
    	break ;
    case TYPE_DELBINDING:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_DELBINDING");
    	break ;
    default:
    	LOGGER_WRITE(Logger::DEBUG,"default");
    	break ;
    }

   delete tree ;


	}

/*
case TYPE_START:
	LOGGER_WRITE(Logger::DEBUG,"TYPE_START");

case TYPE_PAUSE:
  	LOGGER_WRITE(Logger::DEBUG,"TYPE_PAUSE");

case TYPE_STOP:
   	LOGGER_WRITE(Logger::DEBUG,"TYPE_STOP");
 */
