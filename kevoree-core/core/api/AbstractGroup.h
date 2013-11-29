#ifndef __AbstractGroup_H
#define __AbstractGroup_H


#include <kevoree-core/model/kevoree/Group.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/core/api/AbstractTypeDefinition.h>
#include <string>


class AbstractGroup  : public AbstractTypeDefinition
{
public:
	AbstractGroup()
	{
		instance=NULL;	
	}
	
	virtual bool push(ContainerRoot *root){};
	virtual ContainerRoot* pull(std::string nodeName){};
	
	
	void setModelElement(Group *instance)
	{
		this->instance = instance;
	}
	
private:
Group *instance;
KevoreeModelHandlerService *service;

};


#endif
