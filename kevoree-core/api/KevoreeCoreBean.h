#ifndef __KevoreeCoreBean_H
#define __KevoreeCoreBean_H

#include <kevoree-core/api/KevoreeModelHandlerService.h>
#include <kevoree-core/api/Bootstraper.h>
#include <kevoree-core/api/AbstractNodeType.h>
#include <kevoree-core/api/KevoreeListeners.h>
#include  <kevoree-core/api/adaptation/AdaptationModel.h>
#include <kevoree-core/api/PreCompare.h>

#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/compare/ModelCompare.h>
#include <microframework/api/trace/TraceSequence.h>
#include <microframework/api/utils/Logger.h>
#include <pthread.h>
#include <list>
#include <string>
#include <set>


class KevoreeCoreBean : public  KevoreeModelHandlerService {
public:
	KevoreeCoreBean();
	~KevoreeCoreBean();
	std::string getNodeName();
	void setNodeName(std::string nn);
	ContainerRoot *getLastModel();
	void updateModel(ContainerRoot *model);
	std::list<ContainerRoot*> getPreviousModels();
	bool checkModel(ContainerRoot *targetModel);
	void setBootstraper(Bootstraper *b);
	void start();
	void stop();

private:
	bool internal_update_model(ContainerRoot *proposedNewModel);
	void checkBootstrapNode(ContainerRoot *currentModel);
	void switchToNewModel(ContainerRoot *update);
	ContainerRoot *currentModel; 
	list<ContainerRoot*> models;
	std::string nodeName;
	time_t lastDate;
	KevoreeListeners modelListeners;
	AbstractNodeType *nodeInstance;
	Bootstraper *_bootstraper;
	pthread_mutex_t lock_core;
public:
	DefaultkevoreeFactory factory;
	JSONModelLoader loader;
	ModelCompare modelCompare;
	PreCompare *preCompare; // TODO DE
};


#endif
