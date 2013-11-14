#ifndef __KevoreeCoreBean_H
#define __KevoreeCoreBean_H

#include <api/service/core/handler/KevoreeModelHandlerService.h>
#include <ContainerRoot.h>
#include <list>
#include <string>

class KevoreeCoreBean : public KevoreeModelHandlerService {
	
	public:
	std::string getNodeName();
	void setNodeName(std::string nn);
	
	void start();
	void stop();
	


public:
std::string nodeName;
time_t lastDate;
};


#endif
