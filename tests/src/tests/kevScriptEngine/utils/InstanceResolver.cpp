/*
 * InstanceResolver.cpp
 *
 *  Created on: 17 juil. 2014
 *      Author: Aymeric
 */
using namespace std ;
#include "InstanceResolver.h"
#include <kevoree-core/model/kevoree/ComponentInstance.h>

list<Instance>* InstanceResolver::resolve(struct ast_t *ast, ContainerRoot *model){

	list<Instance>* resolved = new list<Instance>() ;/*
	struct vector_t *child = ast->data.tree->children;
	if((ast->type == TYPE_INSTANCEPATH) && child->size < 3){
		if(child->size == 2){
			string nodeName = ast_children_as_string((struct ast_t*) vector_get(child,0));
			string childName = ast_children_as_string((struct ast_t*) vector_get(child,1));
			list<ContainerNode*>* parentsNodes = new list() ;
			std::map<string,ContainerNode*> nodeMap =	model->nodes ;
			for(std::map<string,ContainerNode*>::iterator it = nodeMap.begin(); it != nodeMap.end() ; ++it)
			{

				ContainerNode* cn = it->second ;
				if(cn->name.compare(nodeName) == 0)
				{
					parentsNodes->push_back(cn) ;
				}
				if(parentsNodes->size() == 0){
					throw string("No nodes found with: " + nodeName) ;
				}
				else{
					for (list<ContainerNode*>::iterator it = parentsNodes->begin(); it != parentsNodes->end() ; ++it){
						ContainerNode* par = it ;
						list<ComponentInstance> ci_lst = new list() ;
						for(std::map<string,ContainerNode*>::iterator it = nodeMap.begin(); it != nodeMap.end() ; ++it)
									{
								ComponentInstance ci = &it->second->components ;
								std::map<string,ContainerNode*> cn_map = &it->second->hosts ;

								for(std::map<string,ContainerNode*>::iterator it2 = cn_map.begin(); it2 != cn_map.end() ; ++it2)
											{
									ContainerNode cn = it2->second->
											}

								if(ci.name.compare(childName) == 0)
											{
										ci_lst.push_back(ci);
											}
									}
					}

				}
			}
		}
	}
*/

	return resolved ;
}

