#ifndef __PortSocketDomainLocal_H
#define __PortSocketDomainLocal_H


#include <kevoree-core/api/PortHandler.h>



class PortSocketDomainLocal : public PortHandler
{
public:
	PortSocketDomainLocal();
	PortSocketDomainLocal(std::string name);
	virtual ~PortSocketDomainLocal();

};

#endif
