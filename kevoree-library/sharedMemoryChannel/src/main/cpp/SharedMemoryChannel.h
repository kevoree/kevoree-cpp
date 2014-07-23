#ifndef __FakeConsole_H
#define __FakeConsole_H

#include <kevoree-core/api/AbstractChannel.h>


#pragma ChannelType "sharedMemoryChannel"
class SharedMemoryChannel :public AbstractChannel
{
	public:
	SharedMemoryChannel();
	~SharedMemoryChannel();

	 void start();
	 void stop();
	 void update();
     void dispatch(std::string data);



};

#endif /*__FakeConsole_H*/
