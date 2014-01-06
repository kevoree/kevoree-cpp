#include <kevoree-core/api/adaptation/ParallelStep.h>

ParallelStep::ParallelStep(){


}

ParallelStep::~ParallelStep(){


}

void ParallelStep::addadaptations(AdaptationPrimitive *ptr)
{
	if(ptr != NULL)
	{
		adaptations.push(ptr);
	}else
	{
		Logger::Write(Logger::ERROR,"ParallelStep cannot add adaptation null");
	}
}
