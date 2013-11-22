#ifndef __INodeType_H
#define __INodeType_H

#include <kevoree-core/model/kevoreeadaptation/AdaptationModel.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>
#include <microframework/api/trace/TraceSequence.h>

class AbstractNodeType
{
public:
	AbstractNodeType()
	{
		node=NULL;	
	}
	virtual void startNode(){};
	virtual void stopNode(){};
	virtual void updateNode(){};
	virtual AdaptationModel *plan(ContainerRoot *actualModel,ContainerRoot *targetModel,TraceSequence *traces){};
	virtual PrimitiveCommand getPrimitive(PrimitiveCommand primitive){};
	
	
	void setModelElement(ContainerNode *node)
	{
		this->node = node;
	}


ContainerNode *node;

};


#endif
