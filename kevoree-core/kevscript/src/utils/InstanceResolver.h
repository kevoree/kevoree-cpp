/*
 * InstanceResolver.h
 *
 *  Created on: 17 juil. 2014
 *      Author: Aymeric
 */

#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <microframework/api/utils/KevoreeException.h>

#ifndef INSTANCERESOLVER_H_
#define INSTANCERESOLVER_H_

class InstanceResolver {
public:
	InstanceResolver();
	virtual ~InstanceResolver();
	static std::list<Instance*>* resolve(struct ast_t *ast, ContainerRoot *model);
};

#endif /* INSTANCERESOLVER_H_ */
