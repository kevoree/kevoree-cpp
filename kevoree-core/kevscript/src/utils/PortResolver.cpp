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
extern "C" {
#include <kevoree-core/kevscript/api/Waxeye.h>
}



list<Port*>* PortResolver::resolve(struct ast_t *ast, ContainerRoot *model){
	list<Port*>* resolved = new list<Port*>() ;



	return resolved ;

}
