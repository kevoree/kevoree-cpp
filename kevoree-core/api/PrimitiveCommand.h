#ifndef __PrimitiveCommand_H
#define __PrimitiveCommand_H
#include <boost/thread.hpp>

class PrimitiveCommand
{
public:
	virtual void execute(boost::promise<bool> & result)=0;
	virtual void undo()=0;
};


#endif
