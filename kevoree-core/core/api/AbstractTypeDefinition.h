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

	void setPath(std::string path)
	{
		this->path = path;
	}
	
	KMFContainer* getModelElement()
	{
		if(service != NULL && service->getLastModel() != NULL )
		{
			LOGGER_WRITE(Logger::DEBUG,"getModelElement -> "+path);
			return service->getLastModel()->findByPath(path);
		}else 
		{
			LOGGER_WRITE(Logger::ERROR,"getModelElement ->"+path);
			return NULL;	
		}

	};
	
private:
KevoreeModelHandlerService *service;
Bootstraper *bootstrapService;
std::string path;
};


#endif






