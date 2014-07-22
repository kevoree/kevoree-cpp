#ifndef __PortSocketDomainLocal_H
#define __PortSocketDomainLocal_H


#include <kevoree-core/api/PortHandler.h>

#include <iostream>
#include <string>
#include <cctype>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>





class PortSocketDomainLocal : public PortHandler
{
public:
	PortSocketDomainLocal();
	PortSocketDomainLocal(std::string name);
	virtual ~PortSocketDomainLocal();

};

#endif
