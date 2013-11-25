#ifndef __AbstractComponent_H
#define __AbstractComponent_H


#include <kevoree-core/model/kevoree/ComponentInstance.h>

#include <string>

class AbstractComponent
{
public:
	AbstractComponent()
	{
		instance=NULL;	
	}
	virtual void start(){};
	virtual void stop(){};
	virtual void update(){};


	void setModelElement(ComponentInstance *instance)
	{
		this->instance = instance;
	}

private:
ComponentInstance *instance;

};


#endif
