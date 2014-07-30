
#ifndef __KevScriptService_H
#define __KevScriptService_H


#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <string>

class KevScriptService {

public:
	virtual void execute(std::string script,ContainerRoot *model)=0;
	virtual void executeFromStream(istream	&script,ContainerRoot *model)=0;
};

#endif


