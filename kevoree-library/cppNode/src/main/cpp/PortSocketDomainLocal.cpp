#include "PortSocketDomainLocal.h"


PortSocketDomainLocal::PortSocketDomainLocal(std::string name,AbstractChannel *channel){

this->channel = channel;

}
PortSocketDomainLocal::~PortSocketDomainLocal()
{

}

void PortSocketDomainLocal::writeMSG(std::string msg){
	// TODO
	if(channel !=NULL){
		channel->dispatch(msg);
	}else {

		LOGGER_WRITE(Logger::ERROR,"PortSocketDomainLocal channel is null");
	}
}

