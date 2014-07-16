#include "DeployPhase.h"
#include <iostream>
#include <exception>
#include <boost/thread.hpp>
using namespace std;


DeployPhase::DeployPhase(){
	maxTimeout=100000; // 10 secondes timeout
}

DeployPhase::~DeployPhase(){
	for (std::list<PrimitiveCommand*>::const_iterator it = primitives.begin();  it != primitives.end(); ++it) 
	{
		PrimitiveCommand *cmd =*it;
		delete cmd;
	}
}

void DeployPhase::setMaxTime(long mt)
{
	maxTimeout=mt;
}

long DeployPhase::getMaxTime(){
	return maxTimeout;
}

void DeployPhase::populate(PrimitiveCommand *cmd)
{
	primitives.push_back(cmd);
}
void DeployPhase::rollback()
{
	primitives.reverse();
	for (std::list<PrimitiveCommand*>::const_iterator it = primitives.begin();  it != primitives.end(); ++it) 
	{
		PrimitiveCommand *primitive =*it;
		if(primitive)
		{
			try 
			{
				boost::thread api_caller(boost::bind(&PrimitiveCommand::undo, primitive));
				api_caller.timed_join(boost::posix_time::milliseconds(getMaxTime()));

			}
			catch (exception& e)
			{
				Logger::Write(Logger::ERROR,e.what());
			}
		}else 
		{

		}

	}
}
