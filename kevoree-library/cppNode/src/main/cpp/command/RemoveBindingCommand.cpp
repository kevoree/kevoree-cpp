#include "RemoveBindingCommand.h"





void RemoveBindingCommand::execute(boost::promise<bool> & result)
{
	std::cout << "TODO remove binding" << std::endl;
	bool r=false;
	MBinding *binding = (MBinding*)instance;

	if(instance != NULL && binding->port != NULL){

		Port *port = (Port*)binding->port;
		Channel *hub = 	(Channel*)	binding->hub;
		ComponentInstance *component = (ComponentInstance*)binding->port->eContainer();

		if(component !=NULL && port !=NULL && hub !=NULL)
		{
			AbstractComponent *c =(AbstractComponent*)	 bootstrapService->getDynamicLoader()->get_instance(component);
			if(c != NULL)
			{
				PortHandler *handler = c->ports[port->internalGetKey()];
				if(handler != NULL){
					c->ports.erase(port->internalGetKey());
					delete handler;
					r =true;
				}

			}
		}

	}


	result.set_value(r);
}


void RemoveBindingCommand::undo(){


}
