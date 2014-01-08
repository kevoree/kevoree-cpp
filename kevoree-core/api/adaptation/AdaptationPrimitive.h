#ifndef __AdaptationPrimitive_H
#define __AdaptationPrimitive_H

#include <microframework/api/KMFContainer.h>
#include <string>
class AdaptationPrimitive  {
public:
	AdaptationPrimitive();
	~AdaptationPrimitive();
	int priority;
	int primitiveType;
	std::string targetNodeName;
	KMFContainer * ref;
}; // END CLASS 
#endif
