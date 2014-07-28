#include <iostream>
#include <string>

#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include "maven-resolver-cpp/src/maven-resolver/api/MavenVersionComparator.h"
#include "TypeDefinitionResolver.h"

extern "C" {
#include <tests/src/tests/Waxeye.h>
}



TypeDefinition* TypeDefinitionResolver::resolve(struct ast_t *ast, ContainerRoot *model)
{
	if(ast != NULL){
		if(ast->data.tree->type != TYPE_TYPEDEF)
		{
			throw string(&"Parse error, should be a type definition : "  [ast->type]);
		}

		struct vector_t *child = ast->data.tree->children;
		string typeDefName = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;


		LOGGER_WRITE(Logger::DEBUG,string("Type Definition Name :" + typeDefName));
		string version = "" ;
		if(child->size > 1){
			version = ast_children_as_string((struct ast_t*) vector_get(child,1)) ;

		}
		TypeDefinition *best_td = NULL ;

		std::map<string,TypeDefinition*> type_defs = model->typeDefinitions ;
		for(std::map<string,TypeDefinition*>::iterator it = type_defs.begin(); it != type_defs.end() ; ++it)
		{
			cout << "test" << endl ;

			TypeDefinition * t = it->second ;

			if(t !=NULL){
				cout << "type def : " + t->name << endl ;

				if(!version.empty()){
					LOGGER_WRITE(Logger::DEBUG,string("version not emepty"));
					if ((it->first.compare(typeDefName)==0) && (version.compare(it->second->version)==0))
					{
						return it->second ;
					}
				}
				else {
					LOGGER_WRITE(Logger::DEBUG,string("else"));
					if((it->first.compare(typeDefName)==0)){
						LOGGER_WRITE(Logger::DEBUG,string("else"));
						if(best_td == NULL){
							best_td = it->second ;
						}else{

							if( (maven::resolver::MavenVersionComparator::max(best_td->version,it->second->version)).compare(it->second->version)  == 0){
								best_td = it->second ;
							}
						}
					}
				}
			}else{
				throw string("Error : null type definition");
			}
		}
		if (best_td == NULL) {
			throw string(" TypeDefinition not found with : " +typeDefName +"\n" );
		}

		return best_td;
	}else
	{
		return NULL ;
	}
}

