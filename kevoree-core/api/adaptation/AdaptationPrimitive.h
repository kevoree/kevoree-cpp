#ifndef __AdaptationPrimitive_H
#define __AdaptationPrimitive_H
#include <list>
#include <string>
#include <map>
#include <kevoree-core/api/adaptation/AdaptationConfiguration.h>
#include <microframework/api/KMFContainer.h>

class AdaptationPrimitive : public AdaptationConfiguration {
public:
std::string targetNodeName;
KMFContainer * ref;
AdaptationPrimitive();

~AdaptationPrimitive();

}; // END CLASS 
#endif
