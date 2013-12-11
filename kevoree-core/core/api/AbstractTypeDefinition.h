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
	
	virtual void setModelService(KevoreeModelHandlerService *handler)
	{
		this->service = handler;
	}
	
	virtual KevoreeModelHandlerService *getModelService()
	{
		return service;	
	}
	virtual void setBootStrapperService(Bootstraper *bootstrapService)
	{
		this->bootstrapService =bootstrapService;
	}
	virtual Bootstraper *getBootStrapperService()
	{
		return bootstrapService;
	}

	virtual void setPath(std::string path)
	{
		this->path = path;
	}
	
	virtual KMFContainer* getModelElement()
	{
		if(service != NULL && service->getLastModel() != NULL )
		{
			//LOGGER_WRITE(Logger::DEBUG,"getModelElement -> "+path);
			return service->getLastModel()->findByPath(path);
		}else 
		{
			//LOGGER_WRITE(Logger::ERROR,"getModelElement ->"+path);
			return NULL;	
		}

	};
	
private:
KevoreeModelHandlerService *service;
Bootstraper *bootstrapService;
std::string path;
};


#endif






