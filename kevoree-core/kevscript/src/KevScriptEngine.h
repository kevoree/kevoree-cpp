
#include <kevoree-core/api/KevScriptService.h>

#ifndef __KevScriptEngine_H
#define __KevScriptEngine_H


class KevScriptEngine : public KevScriptService
{
public:
	KevScriptEngine();
	~KevScriptEngine();
	 void execute(std::string script,ContainerRoot *model);
	void executeFromStream(istream	&script,ContainerRoot *model);
};



#endif
