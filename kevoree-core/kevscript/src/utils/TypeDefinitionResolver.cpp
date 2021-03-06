#include <iostream>
#include <string>

#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include "maven-resolver-cpp/src/maven-resolver/api/MavenVersionComparator.h"
#include "TypeDefinitionResolver.h"

extern "C" {
#include <kevoree-core/kevscript/api/waxeyeParser.h>
}

TypeDefinition* TypeDefinitionResolver::resolve(struct ast_t *ast, ContainerRoot *model)
{
	if(ast != NULL){
		if(ast->data.tree->type != TYPE_TYPEDEF)
		{
			throw KevoreeException(string(&"Parse error, should be a type definition : "  [ast->type]));
		}

		struct vector_t *child = ast->data.tree->children;
		string typeDefName = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
		string version = "" ;
		if(child->size > 1){
			version = ast_children_as_string((struct ast_t*) vector_get(child,1)) ;

		}
		TypeDefinition *best_td = NULL ;

		std::map<string,TypeDefinition*> type_defs = model->typeDefinitions ;
		for(std::map<string,TypeDefinition*>::iterator it = type_defs.begin(); it != type_defs.end() ; ++it)
		{
			TypeDefinition * t = it->second ;
				if(!version.empty()){
					if ((it->second->name.compare(typeDefName)==0) && (version.compare(it->second->version)==0))
					{
						return it->second ;
					}
				}
				else {
					if((it->second->name.compare(typeDefName)==0)){

						if(best_td == NULL){
							best_td = it->second ;
						}else{

							if( (maven::resolver::MavenVersionComparator::max(best_td->version,it->second->version)).compare(it->second->version)  == 0){
								best_td = it->second ;
							}
						}
					}
				}

		}
		if (best_td == NULL) {
			throw KevoreeException(" TypeDefinition not found with : " +typeDefName +"\n" );
		}

		return best_td;
	}else
	{
		return NULL ;
	}
}

