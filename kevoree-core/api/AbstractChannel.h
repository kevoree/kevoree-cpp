#ifndef __AbstractGroup_H
#define __AbstractGroup_H

#include <kevoree-core/model/kevoree/MBinding.h>
#include <kevoree-core/model/kevoree/Channel.h>
#include <kevoree-core/model/kevoree/Port.h>
#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/api/AbstractTypeDefinition.h>
#include <kevoree-core/api/AbstractComponent.h>
#include <string>


class AbstractChannel  : public AbstractTypeDefinition
{

public:
	virtual void dispatch(std::string data){

	}

	std::list<Port*> getRemotePortPaths(){
		Channel *element =	(Channel*)getModelElement();
		std::list<Port*> result;
		if(element != NULL)
		{
			for ( std::map<string,MBinding*>::iterator it = element->bindings.begin();  it != element->bindings.end(); ++it)
			{
				MBinding *binding =(MBinding*) it->second;

				if (binding->port != NULL) {
					ContainerNode *node =(ContainerNode*) binding->port->eContainer()->eContainer();
					if(node->name.compare(getModelService()->getNodeName())){
						result.push_back(binding->port);
					}
				}
			}
		}
		return result;
	}
	std::list<Port*> getLocalPorts(){
		std::list<Port*> result;

		return result;

	}

	std::map<std::string, AbstractComponent*> local;


};


#endif
