#ifndef __KevoreeCoreBean_H
#define __KevoreeCoreBean_H

#include <kevoree-core/core/api/KevoreeModelHandlerService.h>
#include <kevoree-core/core/api/Bootstraper.h>
#include <kevoree-core/core/api/INodeType.h>
#include <kevoree-core/core/KevoreeListeners.h>

#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/compare/ModelCompare.h>

#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>

#include <list>
#include <string>
#include <set>
#include <microframework/api/trace/TraceSequence.h>

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
	TraceSequence *createTraces(ContainerRoot *curent,ContainerRoot *target);
	void createTracesGroupsAndChannels(ContainerRoot *currentModel,ContainerRoot *targetModel,ContainerNode *currentNode,ContainerNode *targetNode,TraceSequence *traces);
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
	ModelCompare modelCompare;
};


#endif
