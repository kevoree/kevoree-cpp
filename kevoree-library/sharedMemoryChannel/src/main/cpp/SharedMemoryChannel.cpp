
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

void SharedMemoryChannel::dispatch(std::string data)
{
// FIX ME POC
	Channel *element =	(Channel*)getModelElement();
	for ( std::map<string,MBinding*>::iterator it = element->bindings.begin();  it !=  element->bindings.end(); ++it)
	{
		MBinding *binding = it->second;
		Port *p = binding->port;
		ComponentInstance *component = (ComponentInstance*)binding->port->eContainer();
		Port *provided = component->findprovidedByID(p->internalGetKey());
		if(provided != NULL)
		{
			//std::cout << component->name+"/"+provided->name << std::endl;
			std::string path =component->name+"/"+provided->name;
			if(local.find(path) != local.end())
			{
				local[path]->receive(data);

			}else {
				std::cout << "not found "<<path << std::endl;
			}


		}


	}

}
