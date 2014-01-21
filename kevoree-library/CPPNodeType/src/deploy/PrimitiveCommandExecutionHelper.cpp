#include "PrimitiveCommandExecutionHelper.h"
#include "DeployPhase.h"
#include "../Primitives.h"
#include <boost/thread.hpp>
#include <stdexcept>
#include <map>
#include <iostream>

/*
 *
 * decouper pour permettre la réutilisation
 */
bool PrimitiveCommandExecutionHelper::execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance)
{
	bool res=true;
	DeployPhase *phase=NULL;
	phase = new DeployPhase();
	for (std::vector<AdaptationPrimitive*>::iterator it=adaptionModel->adaptations.begin(); it!=adaptionModel->adaptations.end(); ++it){

		AdaptationPrimitive *adaptation = *it;
		PrimitiveCommand *primitive = nodeInstance->getPrimitive(adaptation);
		if(primitive != NULL)
		{
			phase->populate(primitive);
			boost::promise<bool> result;
			boost::thread api_caller(boost::bind(&PrimitiveCommand::execute, primitive,boost::ref(result)));
			if (!api_caller.timed_join(boost::posix_time::milliseconds(phase->getMaxTime())))
			{
				res= false;
				break;

			}else
			{

				if(!result.get_future().get())
				{
					res= false;
					break;
				}
			}
		}
		else
		{
			Logger::Write(Logger::ERROR,"PrimitiveCommand is NULL");
			res= false;
			break;
		}
	}

	if(res ==false)
	{
		Logger::Write(Logger::INFO,"Rollback to the previous point in time.");
		phase->rollback();
	}

	Logger::Write(Logger::DEBUG,"Cleaning adaptation Primitives");
	for (std::vector<AdaptationPrimitive*>::iterator it=adaptionModel->adaptations.begin(); it!=adaptionModel->adaptations.end(); ++it){
		delete *it;
	}


	if(phase != NULL)
	{
		delete phase;
	}
	return res;
}
