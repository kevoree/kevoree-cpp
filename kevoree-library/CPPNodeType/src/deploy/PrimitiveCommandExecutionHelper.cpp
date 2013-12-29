#include "PrimitiveCommandExecutionHelper.h"
#include "DeployPhase.h"
#include "../Primitives.h"
#include <boost/thread.hpp>
#include <stdexcept>
#include <map>

bool PrimitiveCommandExecutionHelper::execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance)
{
	bool res;
	DeployPhase *phase=NULL;
	ParallelStep *orderedPrimitiveSet = adaptionModel->orderedPrimitiveSet;
	if(orderedPrimitiveSet == NULL)
	{
		LOGGER_WRITE(Logger::ERROR,"orderedPrimitiveSet is NULL");
		return false;
	}
	phase = new DeployPhase();
	res = executeStep(rootNode,orderedPrimitiveSet,nodeInstance,phase);

	if(!res)
	{
		LOGGER_WRITE(Logger::INFO,"Rollback");
		phase->rollback();	
	}
	LOGGER_WRITE(Logger::DEBUG,"Clean ParallelStep");
	cleanParallelStep(orderedPrimitiveSet);
	adaptionModel->orderedPrimitiveSet = NULL;	  
	if(phase != NULL)
	{
		delete phase;
	}
	return res;
}

bool PrimitiveCommandExecutionHelper::cleanParallelStep(ParallelStep *step)
{
	if (step == NULL)
	{
		return true;
	}
	ParallelStep *next = step->nextStep;
	delete step;
	return  cleanParallelStep(next);
}

bool PrimitiveCommandExecutionHelper::executeStep(ContainerNode *rootNode,ParallelStep *step,AbstractNodeType *nodeInstance,DeployPhase *phase){
	if (step == NULL)
	{
		return true;
	}
	try
	{
		for (std::map<string,AdaptationPrimitive*>::const_iterator it = step->adaptations.begin();  it != step->adaptations.end(); ++it)
		{
			AdaptationPrimitive *adaptation = it->second;
			PrimitiveCommand *primitive = nodeInstance->getPrimitive(adaptation);
			if(primitive != NULL)
			{
				phase->populate(primitive);
				boost::promise<bool> result;
				LOGGER_WRITE(Logger::DEBUG," START PrimitiveCommand "+adaptation->primitiveType);
				boost::thread api_caller(boost::bind(&PrimitiveCommand::execute, primitive,boost::ref(result)));

				if (!api_caller.timed_join(boost::posix_time::milliseconds(phase->getMaxTime())))
				{
					LOGGER_WRITE(Logger::ERROR,"PrimitiveCommand call timed out for "+adaptation->primitiveType+ " "+adaptation->ref->path());
					return false;
				}else
				{
					if(!result.get_future().get())
					{
						LOGGER_WRITE(Logger::ERROR,"PrimitiveCommand false for"+adaptation->primitiveType+ " "+adaptation->ref->path());
						return false;
					}
				}
				LOGGER_WRITE(Logger::DEBUG," FINISH PrimitiveCommand ");
			}
			else
			{
				LOGGER_WRITE(Logger::ERROR,"PrimitiveCommand is NULL");
				return false;
			}
		}

		return executeStep(rootNode,step->nextStep,nodeInstance,phase);
	}
	catch ( const std::exception & e )
	{
		std::cerr << e.what() << endl;
		return false;
	}
}
