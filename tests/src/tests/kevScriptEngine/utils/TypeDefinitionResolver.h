

#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include "maven-resolver-cpp/src/maven-resolver/api/MavenResolver.h"

#ifndef TYPEDEFINITIONRESOLVER_H_
#define TYPEDEFINITIONRESOLVER_H_


class TypeDefinitionResolver {

public:
	TypeDefinitionResolver();
	static TypeDefinition* resolve(struct ast_t *ast, ContainerRoot *model);
};

#endif /*TYPEDEFINITIONRESOLVER_H_*/
