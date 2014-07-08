
#ifndef __KevScriptService_H
#define __KevScriptService_H


#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <string>

class KevScriptService {

public:
	virtual void execute(std::string nodeName,ContainerRoot *model)=0;
	virtual void executeFromStream(istream	&inputstream,ContainerRoot *model)=0;
};

#endif


