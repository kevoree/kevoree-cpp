
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
};



#endif
