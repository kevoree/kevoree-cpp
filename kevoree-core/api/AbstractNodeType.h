#ifndef __INodeType_H
#define __INodeType_H

#include <kevoree-core/api/adaptation/AdaptationModel.h>
#include <kevoree-core/api/adaptation/AdaptationPrimitive.h>
#include <kevoree-core/api/PrimitiveCommand.h>
#include <kevoree-core/api/AbstractTypeDefinition.h>

#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
#include <microframework/api/trace/TraceSequence.h>


#include <string>

class AbstractNodeType: public AbstractTypeDefinition
{
public:

	virtual AdaptationModel *plan(ContainerRoot *actualModel,ContainerRoot *targetModel,TraceSequence *traces){};
	virtual bool execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance){};
	virtual PrimitiveCommand* getPrimitive(AdaptationPrimitive *primitive){};
	
	virtual std::string getNodeName()
	{
		return nodename;
	}
	
	virtual void setnodeName(std::string nodeName){
		this->nodename = nodeName;
	}
private:
std::string nodename;

};


#endif
