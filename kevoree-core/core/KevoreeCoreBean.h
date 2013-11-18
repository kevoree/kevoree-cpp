#ifndef __KevoreeCoreBean_H
#define __KevoreeCoreBean_H

#include <core/api/KevoreeModelHandlerService.h>
#include <core/api/Bootstraper.h>
#include <core/KevoreeListeners.h>

#include <model/kevoree/ContainerRoot.h>
#include <model/kevoree/DefaultkevoreeFactory.h>

#include <list>
#include <string>

class KevoreeCoreBean : public  KevoreeModelHandlerService {
	
	public:
	KevoreeCoreBean();
	std::string getNodeName();
	void setNodeName(std::string nn);
	ContainerRoot *getLastModel();
	void updateModel(ContainerRoot *model);
	std::list<ContainerRoot> getPreviousModels();
	bool checkModel(ContainerRoot *targetModel);
	void setBootstraper(Bootstraper *b);
	NodeType *nodeInstance;
	
	void start();
	void stop();
	
private:
    bool internal_update_model(ContainerRoot *proposedNewModel);

public:
std::string nodeName;
time_t lastDate;
DefaultkevoreeFactory factory;
KevoreeListeners modelListeners;
ContainerRoot *model;  // Root Model


};


#endif
