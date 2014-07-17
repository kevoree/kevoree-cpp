
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


}

void SharedMemoryChannel::stop(){

}


void SharedMemoryChannel::update()
{

}
