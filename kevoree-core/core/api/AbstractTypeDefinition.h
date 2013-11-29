#ifndef __AbstractTypeDefinition_H
#define __AbstractTypeDefinition_H

#include <kevoree-core/core/api/KevoreeModelHandlerService.h>

class Bootstraper;


class AbstractTypeDefinition  
{
public:
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
	virtual void start(){};
	virtual void stop(){};
	virtual void update(){};
	
private:
KevoreeModelHandlerService *service;
Bootstraper *bootstrapService;
};


#endif






