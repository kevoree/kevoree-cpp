#ifndef __AbstractComponent_H
#define __AbstractComponent_H


#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/core/api/AbstractTypeDefinition.h>
#include <string>

class AbstractComponent: public AbstractTypeDefinition
{
public:
	AbstractComponent()
	{
		instance=NULL;	
	}

	void setModelElement(ComponentInstance *instance)
	{
		this->instance = instance;
	}

private:
ComponentInstance *instance;

};


#endif
