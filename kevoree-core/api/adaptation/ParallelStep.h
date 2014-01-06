#ifndef __ParallelStep_H
#define __ParallelStep_H
#include <vector>
#include <string>
#include <queue>
#include <kevoree-core/api/adaptation/AdaptationConfiguration.h>
#include <kevoree-core/api/adaptation/AdaptationPrimitive.h>

class ParallelStep : public AdaptationConfiguration{

public:

struct CompareAdaptationPrimitive : public std::binary_function<ParallelStep*, ParallelStep*, bool>
{
	bool operator()(const AdaptationPrimitive* lhs, const AdaptationPrimitive* rhs) const
	{
		return lhs->priority > rhs->priority;
	}
};

std::priority_queue<AdaptationPrimitive*,std::vector<AdaptationPrimitive*>, CompareAdaptationPrimitive > adaptations;

void addadaptations(AdaptationPrimitive *ptr);

ParallelStep();

~ParallelStep();

}; // END CLASS 
#endif
