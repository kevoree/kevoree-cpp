#include "PrimitiveCommandExecutionHelper.h"
#include "DeployPhase.h"
#include "../Primitives.h"
#include <boost/thread.hpp>
#include <stdexcept>
#include <map>
#include <iostream>
#include <queue>

bool PrimitiveCommandExecutionHelper::execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance)
{
	bool res=true;
	DeployPhase *phase=NULL;

	phase = new DeployPhase();

	while ( !adaptionModel->steps.empty()  && res ==true)
	{
		ParallelStep *step = adaptionModel->steps.top();
		res = executeStep(rootNode,step,nodeInstance,phase);
		adaptionModel->steps.pop();
	}

	if(!res)
	{
		LOGGER_WRITE(Logger::INFO,"Rollback");
		phase->rollback();	
	}

	if(phase != NULL)
	{
		delete phase;
	}
	return res;
}


bool PrimitiveCommandExecutionHelper::executeStep(ContainerNode *rootNode,ParallelStep *step,AbstractNodeType *nodeInstance,DeployPhase *phase){
	if (step->adaptations.size() == 0)
	{
		return true;
	}

	while ( !step->adaptations.empty() )
	{

		AdaptationPrimitive *adaptation = step->adaptations.top();
		PrimitiveCommand *primitive = nodeInstance->getPrimitive(adaptation);
		if(primitive != NULL)
		{
			phase->populate(primitive);
			boost::promise<bool> result;

			boost::thread api_caller(boost::bind(&PrimitiveCommand::execute, primitive,boost::ref(result)));

			if (!api_caller.timed_join(boost::posix_time::milliseconds(phase->getMaxTime())))
			{
				LOGGER_WRITE(Logger::ERROR,"PrimitiveCommand call timed out for "+adaptation->name+ " "+adaptation->ref->path());
				return false;
			}else
			{
				if(!result.get_future().get())
				{
					LOGGER_WRITE(Logger::ERROR,"PrimitiveCommand false for"+adaptation->name+ " "+adaptation->ref->path());
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
		step->adaptations.pop();

	}
	return true;
}
