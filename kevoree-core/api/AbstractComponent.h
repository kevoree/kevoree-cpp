#ifndef __AbstractComponent_H
#define __AbstractComponent_H

#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/api/AbstractTypeDefinition.h>
#include <microframework/api/utils/any.h>
#include <kevoree-core/api/PortHandler.h>

class AbstractComponent: public AbstractTypeDefinition
{

public:
	virtual void receive(std::string msg){

	}
	void send(std::string id,std::string msg){

		ComponentInstance *element =	(ComponentInstance*)getModelElement();

		if(element != NULL){
			std::string  portname = ""+id;
			std::transform(portname.begin(), portname.end(), portname.begin(), ::tolower);

			if(	element->required.find(portname) != 	element->required.end()){
				//	std::cout <<" port found " << std::endl;
				Port * port = (Port*)	element->required[portname];


				for (std::map<string,MBinding*>::iterator it = port->bindings.begin();  it !=  port->bindings.end(); ++it)
				{
					MBinding *binding = (MBinding*)it->second;
					//	std::cout <<" binding "<< it->first << " " << binding->port->name << std::endl;
					if(ports.find( binding->port->name ) != ports.end())
					{
						PortHandler *handler = ports[ binding->port->name ];
						if(handler != NULL){
							handler->writeMSG(msg);
						}

					}else {
						std::cout <<" not found " << std::endl;

					}
				}




			}else
			{
				std::cout <<" port not found "<< id << std::endl;
			}

		}else {
			std::cout <<" element null " << std::endl;
		}

	}


	std::map<std::string, PortHandler*> ports;

};


#endif
