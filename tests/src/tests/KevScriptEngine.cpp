#include "KevScriptEngine.h"
#include <iostream>


extern "C" {
#include "Waxeye.h"
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


void interpret(struct ast_t *ast, ContainerRoot *model){

	struct ast_tree_t *tree = ast->data.tree;
    switch (tree->type) {
        case TYPE_STATEMENT:
         std::cout << "statement" <<std::endl ;

        default:
            std::cout << "default" <<std::endl ;

    }
}

