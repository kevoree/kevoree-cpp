#ifndef __FakeConsole_H
#define __FakeConsole_H

#include <kevoree-core/api/AbstractComponent.h>
#include <boost/thread.hpp>

#pragma ComponentType "fakeconsole"
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
		 void receive(std::string msg);

};

#endif /*__FakeConsole_H*/
