#ifndef __CommandMapper_H
#define __CommandMapper_H


#include <kevoree-core/api/AbstractNodeType.h>
#include <kevoree-core/api/PrimitiveCommand.h>
#include <microframework/api/trace/TraceSequence.h>
#include <microframework/api/json/JSONModelSerializer.h>

class CommandMapper 
{
public:
	 CommandMapper(AbstractNodeType *nodeType);
     PrimitiveCommand* buildPrimitiveCommand(AdaptationPrimitive *p, std::string nodeName);
private:
AbstractNodeType *nodeType; 
};

#endif /*__CommandMapper_H*/
