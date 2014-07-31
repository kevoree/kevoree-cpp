#include <iostream>
#include <string>
#include <kevoree-core/api/KevScriptService.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <microframework/api/utils/KevoreeException.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <kevoree-core/model/kevoree/Channel.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/kevscript/src/utils/InstanceResolver.h>



#ifndef __KevScriptEngine_H
#define __KevScriptEngine_H


class KevScriptEngine : public KevScriptService
{
public:
	KevScriptEngine();
	~KevScriptEngine();
	void execute(std::string &script,ContainerRoot *model);
	void executeFromStream(istream	&script,ContainerRoot *model);

private:
	void interpret(struct ast_t *ast, ContainerRoot *model);
	bool applyAdd(TypeDefinition *td, struct ast_t *ast, ContainerRoot *model) ;
	void applyMove(Instance *leftH, Instance *rightH, ContainerRoot *model) ;
	void applyAttach(Instance *leftH, Instance *rightH, ContainerRoot *model, bool reverse) ;
};



#endif
