#include "KevoreeParDeployPhase.h"
#include <iostream>
#include <exception>
#include <boost/thread.hpp>
using namespace std;


KevoreeParDeployPhase::KevoreeParDeployPhase(){
	maxTimeout=10000;
}

KevoreeParDeployPhase::~KevoreeParDeployPhase(){
	for (std::list<PrimitiveCommand*>::const_iterator it = primitives.begin();  it != primitives.end(); ++it) 
	{
		PrimitiveCommand *cmd =*it;
		delete cmd;
	}
}

void KevoreeParDeployPhase::setMaxTime(long mt)
{
		maxTimeout=mt;
}
long KevoreeParDeployPhase::getMaxTime(){
	return maxTimeout;
}

void KevoreeParDeployPhase::populate(PrimitiveCommand *cmd)
{
	primitives.push_back(cmd);
}
void KevoreeParDeployPhase::rollback()
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
			cout << e.what() << '\n';
		  }
		}else 
		{
			
		}
	
	}
}
