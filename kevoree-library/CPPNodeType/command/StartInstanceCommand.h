#ifndef __StartInstanceCommand_H
#define __StartInstanceCommand_H

#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/core/api/AbstractNodeType.h>
#include <kevoree-core/core/api/PrimitiveCommand.h>

#include <kevoree-core/model/kevoree/TypeDefinition.h>
#include <kevoree-core/model/kevoree/ComponentInstance.h>
#include <kevoree-core/model/kevoree/DeployUnit.h>

class StartInstanceCommand : public  PrimitiveCommand
{
	public:
	StartInstanceCommand(Instance *instance,std::string nodename)
	{
		
		if(dynamic_cast<ComponentInstance*>(instance) != 0)
		{
				ComponentInstance *c = (ComponentInstance*)instance;
				
				LOGGER_WRITE(Logger::DEBUG,"StartInstance ComponentInstance name "+instance->name);
				

		}
	

	}
	
	bool execute()
	{
	 
    };
    
	void undo()
	{
	 //        RemoveInstance(c, nodeName, modelservice, kscript, bs, nt, registry).execute()
	};
};

#endif /*AddInstance*/

