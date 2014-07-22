#include "AddBindingCommand.h"

void AddBindingCommand::execute(boost::promise<bool> & result)
{
	bool r=false;

	// TODO
	MBinding *binding = (MBinding*)instance;

	if(binding->port != NULL){

		Port *port = (Port*)binding->port;
		Channel *hub = 	(Channel*)	binding->hub;
		ComponentInstance *component = (ComponentInstance*)binding->port->eContainer();
		if(component !=NULL && port !=NULL && hub !=NULL)
		{

			AbstractComponent *c =(AbstractComponent*)	 bootstrapService->getDynamicLoader()->get_instance(component);
			AbstractChannel *h =(AbstractChannel*)	 bootstrapService->getDynamicLoader()->get_instance(hub);
			if(c != NULL && h !=NULL)
			{

				if(c->ports.find(port->internalGetKey()) == c->ports.end())
				{
					PortHandler *handler = new PortHandler();
					handler->channel = h;

					Port *provided = component->findprovidedByID(port->internalGetKey());
					if(provided != NULL)
					{
						// provided  IN
					//		std::cout << " port provided" << std::endl;


						//addInternalInputPort(handler);
						//addInternalInputPort(handler);

					}else
					{

						//std::cout << " port required" << std::endl;
						for ( std::map<string,MBinding*>::iterator it = hub->bindings.begin();  it !=  hub->bindings.end(); ++it)
						{

							/* if (binding != this.modelElement) { // ignore this binding because we are already processing it
                            provided = binding.port.eContainer().findProvidedByID(binding.port.name);
                            if (provided) {
                                portInstance = this.mapper.getObject(provided.path());
                                if (!portInstance) {
                                    portInstance = new Port(provided.name, provided.path());
                                    this.mapper.addEntry(provided.path(), portInstance);
                                }
                                chanInstance.addInternalInputPort(portInstance);
                            }*/

						}

					}


					c->ports[port->internalGetKey()] = handler;

				}
				r=true;
			}




		}


	}

	result.set_value(r);

}


void AddBindingCommand::undo()
{
	// TODO
}

