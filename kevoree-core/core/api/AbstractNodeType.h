#ifndef __INodeType_H
#define __INodeType_H

#include <kevoree-core/model/kevoreeadaptation/AdaptationModel.h>
#include <kevoree-core/model/kevoreeadaptation/AdaptationPrimitive.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>
#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/AbstractTypeDefinition.h>
#include <string>

class AbstractNodeType: public AbstractTypeDefinition
{
public:
	AbstractNodeType()
	{
		node=NULL;	
	}
	virtual AdaptationModel *plan(ContainerRoot *actualModel,ContainerRoot *targetModel,TraceSequence *traces){};
	virtual bool execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance){};
	virtual PrimitiveCommand* getPrimitive(AdaptationPrimitive *primitive){};
	
	
	void setModelElement(ContainerNode *node)
	{
		this->node = node;
	}

	std::string getNodeName()
	{
		if(node != NULL)
		{
			return node->name;
		}else 
		{
			return "";
		}
	}

ContainerNode *node;

};


#endif
