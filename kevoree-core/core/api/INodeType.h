#ifndef __INodeType_H
#define __INodeType_H

#include <kevoree-core/model/kevoreeadaptation/AdaptationModel.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>

class INodeType
{
public:
	virtual void startNode(){};
	virtual void stopNode(){};
	virtual void updateNode(){};
	virtual AdaptationModel *plan(ContainerRoot *actualModel,ContainerRoot *targetModel){};
	virtual PrimitiveCommand getPrimitive(PrimitiveCommand primitive){};

};


#endif
