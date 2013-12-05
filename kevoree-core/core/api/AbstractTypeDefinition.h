#ifndef __AbstractTypeDefinition_H
#define __AbstractTypeDefinition_H

#include <kevoree-core/core/api/KevoreeModelHandlerService.h>

class Bootstraper;


class AbstractTypeDefinition  
{
public:

	virtual void start(){};
	virtual void stop(){};
	virtual void update(){};
	
	void setModelService(KevoreeModelHandlerService *handler)
	{
		this->service = handler;
	}
	
	KevoreeModelHandlerService *getModelService()
	{
		return service;	
	}
	void setBootStrapperService(Bootstraper *bootstrapService)
	{
		this->bootstrapService =bootstrapService;
	}
	Bootstraper *getBootStrapperService()
	{
		return bootstrapService;
	}

	void setModelElement(KMFContainer *elem)
	{
		this->elem = elem;
	}
	KMFContainer* getModelElement()
	{
		return elem;
	};
	
private:
KevoreeModelHandlerService *service;
Bootstraper *bootstrapService;
KMFContainer *elem;
};


#endif






