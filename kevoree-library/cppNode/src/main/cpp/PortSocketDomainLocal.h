#ifndef __PortSocketDomainLocal_H
#define __PortSocketDomainLocal_H


#include <kevoree-core/api/PortHandler.h>
#include <kevoree-core/api/AbstractChannel.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/select.h>




class PortSocketDomainLocal : public PortHandler
{
public:
	PortSocketDomainLocal();
	PortSocketDomainLocal(std::string name,AbstractChannel *h);
	virtual ~PortSocketDomainLocal();

	void writeMSG(std::string msg);

	std::string name;
	AbstractChannel *channel;
};

#endif
