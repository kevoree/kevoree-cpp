#ifndef __KevoreeCoreBean_H
#define __KevoreeCoreBean_H

#include <core/api/KevoreeModelHandlerService.h>
#include <core/api/Bootstraper.h>
#include <core/api/INodeType.h>
#include <core/KevoreeListeners.h>

#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/compare/ModelCompare.h>

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

	
	void start();
	void stop();
	
private:
    bool internal_update_model(ContainerRoot *proposedNewModel);
    void checkBootstrapNode(ContainerRoot *currentModel);
ContainerRoot *currentModel; 
list<ContainerRoot*> models;
std::string nodeName;
time_t lastDate;

KevoreeListeners modelListeners;

INodeType *nodeInstance;
Bootstraper *_bootstraper;
public:
DefaultkevoreeFactory factory;
JSONModelLoader loader;
ModelCompare compare;


};


#endif
