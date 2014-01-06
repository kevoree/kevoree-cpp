#ifndef __AdaptationModel_H
#define __AdaptationModel_H

#include <vector>
#include <queue>
#include <kevoree-core/api/adaptation/ParallelStep.h>
#include <kevoree-core/api/adaptation/AdaptationPrimitive.h>

class AdaptationModel
{

public:

	struct CompareAdaptationParallelStep : public std::binary_function<ParallelStep*, ParallelStep*, bool>
	{
		bool operator()(const ParallelStep* lhs, const ParallelStep* rhs) const
		{
			return lhs->priority > rhs->priority;
		}
	};

	std::priority_queue<ParallelStep*,std::vector<ParallelStep*>, CompareAdaptationParallelStep > steps;


	void addsteps(ParallelStep *ptr);
	int size();

	AdaptationModel();

	~AdaptationModel();

}; // END CLASS 
#endif
