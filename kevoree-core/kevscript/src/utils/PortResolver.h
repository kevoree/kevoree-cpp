/*
 * PortResolver.h
 *
 *  Created on: 30 juil. 2014
 *      Author: Aymeric
 */

#ifndef PORTRESOLVER_H_
#define PORTRESOLVER_H_
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/Port.h>
class PortResolver {
public:
	PortResolver();
	virtual ~PortResolver();
	static std::list<Port*>* resolve(struct ast_t *ast, ContainerRoot *model);
};

#endif /* PORTRESOLVER_H_ */
