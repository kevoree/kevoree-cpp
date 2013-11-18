#ifndef __KevoreeBootStrap_H
#define __KevoreeBootStrap_H
#include <core/KevoreeCoreBean.h>
#include <model/kevoree/DefaultkevoreeFactory.h>

class KevoreeBootStrap {
public:
	KevoreeBootStrap();
    KevoreeCoreBean* getCore();
    void setBootstrapModel(ContainerRoot *bmodel);
    void start(); 
	void stop();
	
private:
  ContainerRoot *bootstrapModel;
  KevoreeCoreBean *coreBean;
  bool started; //false
  DefaultkevoreeFactory factory;
};


#endif
