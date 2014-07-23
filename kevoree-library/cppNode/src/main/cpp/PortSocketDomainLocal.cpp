#include "PortSocketDomainLocal.h"


PortSocketDomainLocal::PortSocketDomainLocal(std::string name,AbstractChannel *channel){

this->channel = channel;

}
PortSocketDomainLocal::~PortSocketDomainLocal()
{

}

void PortSocketDomainLocal::writeMSG(std::string msg){
	// TODO
	channel->dispatch(msg);
}

