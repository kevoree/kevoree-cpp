#ifndef __FakeConsole_H
#define __FakeConsole_H

#include <kevoree-core/api/AbstractComponent.h>
#include <boost/thread.hpp>

#pragma ComponentType "FakeConsole"
#pragma Input "Output"
#pragma Provide "showIn"

class FakeConsole :public AbstractComponent
{
	public:
	FakeConsole();
	~FakeConsole();

	 void start();
	 void stop();
	 void update();
	 boost::thread *t;
	 int started;

};

#endif /*__FakeConsole_H*/
