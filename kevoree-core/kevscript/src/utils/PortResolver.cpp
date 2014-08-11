/*
 * PortResolver.cpp
 *
 *  Created on: 30 juil. 2014
 *      Author: Aymeric
 */
 using namespace std ;

#include "PortResolver.h"

#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/model/kevoree/ComponentType.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
#include <kevoree-core/model/kevoree/PortTypeRef.h>
extern "C" {
#include <kevoree-core/kevscript/api/waxeyeParser.h>
}



list<Port*>* PortResolver::resolve(struct ast_t *ast, ContainerRoot *model){
	list<Port*>* resolved = new list<Port*>() ;
	  display_ast(ast, type_strings);

    struct vector_t *child = ast->data.tree->children;
	if((ast->data.tree->type == TYPE_INSTANCEPATH) && child->size == 3){

		string nodeName = string(ast_children_as_string((struct ast_t*) vector_get(child,0)));
		string componentname = string(ast_children_as_string((struct ast_t*) vector_get(child,1)));
		string portName = string(ast_children_as_string((struct ast_t*) vector_get(child,2)));

		list<ContainerNode*>* node_list = new list<ContainerNode*>() ;
		std::map<string,ContainerNode*> nodeMap =	model->nodes ;

		if(nodeName.compare("*") == 0)
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
		if(node_list->empty()){
			throw KevoreeException("No nodes resolved from : " + componentname) ;
		}


		for(std::list<ContainerNode*>::iterator it = node_list->begin() ; it != node_list->end() ; ++it){
				ContainerNode* cn = *it ;
				list<ComponentInstance*>* cil = new list<ComponentInstance*>();
				std::map<string,ComponentInstance*> CIMap = cn->components ;

				if(componentname.compare("*") == 0){
					for(std::map<string,ComponentInstance*>::iterator itct = CIMap.begin(); itct != CIMap.end() ; ++itct){
						ComponentInstance * ct = itct->second ;
						cil->push_back(ct) ;
					}
				}else
				{
					cout <<"add" << endl;
					cout << cn->components.size() << endl ;
					ComponentInstance * ct = cn->findcomponentsByID(componentname) ;
					cil->push_back(	ct);
					cout <<ct->name << endl;
				}
				cout << cil->size() << endl ;

				for(std::list<ComponentInstance *>::iterator itci = cil->begin() ; itci != cil->end(); ++cil){
					ComponentInstance* currCi = *itci ;
					cout << "ee" << endl ;
					cout << currCi << endl ;

					for(std::map<string,Port*>::iterator itprov = currCi->provided.begin() ;  itprov != currCi->provided.end() ; ++itprov)
					{
						cout << "ee3" << endl ;
						Port* p = itprov->second ;
						cout << "ee4" << endl ;
						if(p->portTypeRef->name.compare(portName) == 0){
							resolved->push_back(p) ;
						}
					}
					for(std::map<string,Port*>::iterator itreq = currCi->required.begin() ;  itreq != currCi->required.end() ; ++itreq)
					{
						cout << "ee5" << endl ;
						Port* p = itreq->second ;
						cout << "ee6" << endl ;
						if(p->portTypeRef->name.compare(portName) == 0)
						{
							resolved->push_back(p) ;
						}
					}
					}
		}


	}else{
		throw KevoreeException("Bad name to resolve ports" );
	}   if (resolved->empty()) {
        throw KevoreeException("no port resolved" );
    }
	return resolved ;

}
