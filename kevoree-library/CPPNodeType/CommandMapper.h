#ifndef __CommandMapper_H
#define __CommandMapper_H

#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>





class CommandMapper 
{
public:

     PrimitiveCommand* buildPrimitiveCommand(AdaptationPrimitive *p, std::string nodeName);
     void internal_update(ContainerRoot *actualModel,ContainerRoot *targetModel);//FIX ME UGLY
     
     ContainerRoot *actualModel;
     ContainerRoot *targetModel;
};

#endif /*__CommandMapper_H*/
