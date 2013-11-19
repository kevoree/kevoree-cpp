#ifndef __INodeType_H
#define __INodeType_H

#include <model/kevoree.adaptation/AdaptationModel.h>
#include <model/kevoree/ContainerRoot.h>
#include <core/api/PrimitiveCommand.h>

class INodeType
{
public:
	virtual void startNode(){};
	virtual void stopNode(){};
	virtual void updateNode(){};
	virtual AdaptationModel plan(ContainerRoot *actualModel,ContainerRoot *targetModel){};
	virtual PrimitiveCommand getPrimitive(PrimitiveCommand primitive){};

};


#endif
