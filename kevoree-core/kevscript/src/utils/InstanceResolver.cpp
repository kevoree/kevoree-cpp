/*
 * InstanceResolver.cpp
 *
 *  Created on: 17 juil. 2014
 *      Author: Aymeric
 */
using namespace std ;
#include "InstanceResolver.h"
#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/model/kevoree/ComponentType.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
extern "C" {
#include <kevoree-core/kevscript/api/waxeyeParser.h>
}

list<Instance*>* InstanceResolver::resolve(struct ast_t *ast, ContainerRoot *model){

	list<Instance*>* resolved = new list<Instance*>() ;

    struct vector_t *child = ast->data.tree->children;
	if((ast->data.tree->type == TYPE_INSTANCEPATH) && child->size < 3){
		if(child->size == 2){
			string nodeName = ast_children_as_string((struct ast_t*) vector_get(child,0));
			string childName = ast_children_as_string((struct ast_t*) vector_get(child,1));
			list<ContainerNode*>* node_list = new list<ContainerNode*>() ;
			std::map<string,ContainerNode*> nodeMap =	model->nodes ;
			if(nodeName.compare("*"))
			{
				for(std::map<string,ContainerNode*>::iterator it = nodeMap.begin(); it != nodeMap.end() ; ++it)
					{
					node_list->push_back(it->second) ;
					}

			}else {
				ContainerNode * cn = model->findnodesByID(nodeName) ;
				if(cn != NULL)
					{
				node_list->push_back(cn);
					}
				}
			if(node_list->size()>0) {

				for(std::list<ContainerNode*>::iterator it = node_list->begin() ; it != node_list->end() ; ++it){
					ContainerNode * cn = *it ;
					std::map<string,ComponentInstance*> CIMap = cn->components ;

					for(std::map<string,ComponentInstance*>::iterator itct = CIMap.begin(); itct != CIMap.end() ; ++itct){
						ComponentInstance * ct = itct->second ;
						Instance * is = (Instance *)ct ;
						if(ct->name.compare(childName)== 0){
						resolved->push_back(is) ;
						}
					}
					std::map<string,ContainerNode*> CNH = cn->hosts ;
					for(std::map<string,ContainerNode*>::iterator itht =CNH.begin() ; itht != CNH.end() ; ++itht){
							ContainerNode * ct = itht->second ;
							Instance * is = (Instance *)ct ;
							if(ct->name.compare(childName)== 0){
							resolved->push_back(is) ;
							}
						}

					}
				}
				}
		else{
			string instanceName = ast_children_as_string((struct ast_t*) vector_get(child,0));
			list<Instance*>* instanceFound = new list<Instance *>() ;
			std::map<string,ContainerNode*> nodeMap =	model->nodes ;

			if(instanceName.compare("*") == 0)
				{

					for(std::map<string,ContainerNode*>::iterator it = nodeMap.begin(); it != nodeMap.end() ; ++it)
						{
						instanceFound->push_back((Instance *)it->second) ;
						}
					for(std::map<string,Group*>::iterator it = model->groups.begin(); it != model->groups.end() ; ++it)
						{
						instanceFound->push_back((Instance *)it->second) ;
						}
					for(std::map<string,Channel*>::iterator it = model->hubs.begin(); it != model->hubs.end() ; ++it)
						{
						instanceFound->push_back((Instance *)it->second) ;
						}
					}
			else {
				Instance * inst =  (Instance *)model->findnodesByID(instanceName) ;

				if(inst ==NULL){

					inst =(Instance *) model->findgroupsByID(instanceName);
				}
				if(inst == NULL){

					inst = (Instance *)model->findhubsByID(instanceName);
				}
				if(inst != NULL){

					resolved->push_back(inst);
					cout << "end" << endl ;
				}
				if(inst == NULL){
					throw KevoreeException("No group / channel found for "+ instanceName) ;
				}
			}
		}
	}	else if(ast->data.tree->type == TYPE_NAMELIST){
		child = ast->data.tree->children;
			if(child != NULL)
			{
			int num_child = child->size;
			for (int i = 0; i < num_child; i +=1) {
				list<Instance*>* resolved2 = InstanceResolver::resolve((struct ast_t*) vector_get(child, i), model) ;
				for(std::list<Instance *>::iterator it = resolved2->begin(); it != resolved2->end(); ++it )
				{
					Instance * inst = *it ;
					resolved->push_back(inst) ;
				}
				}
			}
		}
	return resolved ;
}

