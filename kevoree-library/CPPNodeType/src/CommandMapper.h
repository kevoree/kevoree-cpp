#ifndef __CommandMapper_H
#define __CommandMapper_H

#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>





class CommandMapper 
{
public:
	 CommandMapper(AbstractNodeType *nodeType);
     PrimitiveCommand* buildPrimitiveCommand(AdaptationPrimitive *p, std::string nodeName);
private:
AbstractNodeType *nodeType; 
};

#endif /*__CommandMapper_H*/
