#ifndef __FakeConsole_H
#define __FakeConsole_H

#include <kevoree-core/api/AbstractComponent.h>


#pragma ComponentType "FakeConsole"
#pragma Input   "fuck"
#pragma Provides "fuck"
class FakeConsole :public AbstractComponent
{
	public:
	FakeConsole();
	~FakeConsole();

	 void start();
	 void stop();
	 void update();

};

#endif /*__FakeConsole_H*/
