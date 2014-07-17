#ifndef __FakeConsole_H
#define __FakeConsole_H

#include <kevoree-core/api/AbstractChannel.h>


#pragma ChannelType "SharedMemoryChannel"
class SharedMemoryChannel :public AbstractChannel
{
	public:
	SharedMemoryChannel();
	~SharedMemoryChannel();

	 void start();
	 void stop();
	 void update();

};

#endif /*__FakeConsole_H*/
