#ifndef __AbstractGroup_H
#define __AbstractGroup_H


#include <kevoree-core/model/kevoree/Group.h>

#include <string>


class AbstractGroup
{
public:
	AbstractGroup()
	{
		instance=NULL;	
	}

	void setModelElement(Group *instance)
	{
		this->instance = instance;
	}

private:
Group *instance;

};


#endif
