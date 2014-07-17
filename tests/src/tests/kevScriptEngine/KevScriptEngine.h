
#include <kevoree-core/api/KevScriptService.h>

#ifndef __KevScriptEngine_H
#define __KevScriptEngine_H


class KevScriptEngine : public KevScriptService
{
public:
	KevScriptEngine();
	~KevScriptEngine();
	void execute(std::string nodeName,ContainerRoot *model);
	void executeFromStream(istream	&inputstream,ContainerRoot *model);
	void interpret(struct ast_t *ast, ContainerRoot *model);
	bool applyAdd(TypeDefinition *td, struct ast_t *ast, ContainerRoot *model) ;
	void applyMove(Instance *leftH, Instance *rightH, ContainerRoot *model) ;
	void applyAttach(Instance *leftH, Instance *rightH, ContainerRoot *model, bool reverse) ;

};



#endif
