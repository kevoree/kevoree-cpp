/*
 * InstanceResolver.h
 *
 *  Created on: 17 juil. 2014
 *      Author: Aymeric
 */

#ifndef INSTANCERESOLVER_H_
#define INSTANCERESOLVER_H_
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/Instance.h>

class InstanceResolver {
public:
	InstanceResolver();
	virtual ~InstanceResolver();
	static std::list<Instance>* resolve(struct ast_t *ast, ContainerRoot *model);
};

#endif /* INSTANCERESOLVER_H_ */
