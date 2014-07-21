
#include "SharedMemoryChannel.h"
// todo generate
extern "C"{
AbstractChannel* create(){
		return new SharedMemoryChannel();
	}
}
extern "C" {
	void destroy_object( SharedMemoryChannel * object )
	{
		delete object;
	}
}




SharedMemoryChannel::SharedMemoryChannel()
{

}
SharedMemoryChannel::~SharedMemoryChannel()
{


}

void SharedMemoryChannel::start()
{

std::cout << " CHANNEL IS STARTING" << std::endl;
}

void SharedMemoryChannel::stop(){
	std::cout << " CHANNEL IS STOPING" << std::endl;
}


void SharedMemoryChannel::update()
{
	std::cout << " CHANNEL IS UPDATING" << std::endl;
}
