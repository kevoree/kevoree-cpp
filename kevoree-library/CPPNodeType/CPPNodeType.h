#ifndef __CPPNODETYPE_H_
#define __CPPNODETYPE_H_


#include <core/api/INodeType.h>

class CPPNodeType : public INodeType
{
public:
	CPPNodeType();
    void startNode();
    void stopNode();
    AdaptationModel plan(ContainerRoot *actualModel,ContainerRoot *targetModel);
    PrimitiveCommand getPrimitive(PrimitiveCommand primitive);
	virtual ~CPPNodeType();
};

#endif /*CPPNODETYPE_H_*/
