#ifndef __AbstractGroup_H
#define __AbstractGroup_H


#include <kevoree-core/model/kevoree/Group.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <string>


class AbstractGroup  
{
public:
	AbstractGroup()
	{
		instance=NULL;	
	}
	
	virtual void start(){};
	virtual void stop(){};
	virtual void update(){};
	
	virtual bool push(ContainerRoot *root){};
	virtual ContainerRoot* pull(std::string nodeName){};


	
	void update_model(ContainerRoot *model)
	{
		// todo 
		
	}


	void setModelElement(Group *instance)
	{
		this->instance = instance;
	}
	
private:
Group *instance;

};


#endif
