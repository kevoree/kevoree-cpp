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


	if(!(ast->type == TYPE_TYPEDEF))
	{
		throw string("Parse error, should be a type definition : " + ast->type);
	}
	 struct vector_t *chil = ast->data.tree->children;
	 string typeDefName = ast_children_as_string((struct ast_t*) vector_get(chil,0)) ;
	 string version = NULL ;
	 if(ast->data.tree->end > 0){
		 struct vector_t *chil = ast->data.tree->children;
		 version = ast_children_as_string((struct ast_t*) vector_get(chil,1)) ;
		 LOGGER_WRITE(Logger::DEBUG,version);
	 }


	TypeDefinition *best_td = NULL ;
	std::map<string,TypeDefinition*> type_defs = model->typeDefinitions ;
	for(std::map<string,TypeDefinition*>::iterator it = type_defs.begin(); it != type_defs.end() ; ++it)
	{
		if(version.empty()){
			if ((it->first.compare(typeDefName)==0) && (version.compare(it->second->version)==0))
					{
				return it->second ;
					}
			else {
				if((it->first.compare(typeDefName)==0)){
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
	}
	  if (best_td == NULL) {
	            throw string("TypeDefinition not found with : " +typeDefName );
	        }

	        return best_td;
}

