#ifndef __AbstractComponent_H
#define __AbstractComponent_H

#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/api/AbstractTypeDefinition.h>
#include <microframework/api/utils/any.h>
#include <kevoree-core/api/PortHandler.h>

class AbstractComponent: public AbstractTypeDefinition
{

public:
	void send(std::string id,std::string msg){


		// FIX ME
		if(ports.find(id) == ports.end())
		{
			PortHandler *handler = ports[id];



		}
	}

	//enqueue(port,message);
	// addLisntern(
	std::map<std::string, PortHandler*> ports;

};


#endif
