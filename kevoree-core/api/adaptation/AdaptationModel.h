#ifndef __AdaptationModel_H
#define __AdaptationModel_H

#include <vector>
#include <kevoree-core/api/adaptation/AdaptationPrimitive.h>

class AdaptationModel
{
public:
	AdaptationModel();
	~AdaptationModel();
	void add(AdaptationPrimitive *ptr);
	std::vector<AdaptationPrimitive*> adaptations;
};
#endif
