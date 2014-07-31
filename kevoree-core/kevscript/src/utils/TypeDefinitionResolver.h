#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include <microframework/api/utils/KevoreeException.h>
#include <kevoree-core/model/kevoree/TypeDefinition.h>

#ifndef TYPEDEFINITIONRESOLVER_H_
#define TYPEDEFINITIONRESOLVER_H_


class TypeDefinitionResolver {

public:
	TypeDefinitionResolver();
	static TypeDefinition* resolve(struct ast_t *ast, ContainerRoot *model);
};

#endif /*TYPEDEFINITIONRESOLVER_H_*/
