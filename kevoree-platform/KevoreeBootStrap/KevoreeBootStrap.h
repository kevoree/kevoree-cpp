#ifndef __KevoreeBootStrap_H
#define __KevoreeBootStrap_H

#include <kevoree-core/api/KevoreeCoreBean.h>
#include <kevoree-tools/BootstrapHelper/NodeTypeBootstrapHelper.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>

class KevoreeBootStrap {
public:
	KevoreeBootStrap();
	~KevoreeBootStrap();
    KevoreeCoreBean* getCore();
    void setNodeName(std::string nodeName);
    void setBootstrapModel(ContainerRoot *bmodel);
	void start();
	
private:
  std::string nodeName;
  ContainerRoot *bootstrapModel;
  NodeTypeBootstrapHelper *bootNodeHelper;
  KevoreeCoreBean *coreBean;
  bool started; //false
  DefaultkevoreeFactory factory;
};


#endif
