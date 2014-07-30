
#include <kevoree-core/api/KevScriptService.h>
#include <kevoree-core/model/kevoree/Instance.h>
#ifndef __KevScriptEngine_H
#define __KevScriptEngine_H


class KevScriptEngine : public KevScriptService
{
public:
	KevScriptEngine();
	~KevScriptEngine();
	void execute(std::string script,ContainerRoot *model);
	void executeFromStream(istream	&script,ContainerRoot *model);
// FIX ME AYMERIC
//private:
	void interpret(struct ast_t *ast, ContainerRoot *model);
	bool applyAdd(TypeDefinition *td, struct ast_t *ast, ContainerRoot *model) ;
	void applyMove(Instance *leftH, Instance *rightH, ContainerRoot *model) ;
	void applyAttach(Instance *leftH, Instance *rightH, ContainerRoot *model, bool reverse) ;

};



#endif
