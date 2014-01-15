#ifndef __AbstractTypeDefinition_H
#define __AbstractTypeDefinition_H

#include <kevoree-core/api/KevoreeModelHandlerService.h>
#include <map>

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
			return service->getLastModel()->findByPath(path);
		}else 
		{
			return NULL;	
		}

	};
	virtual void updateParam(string key,string value){
		params[key] =value;
	}
	std::map<std::string, string> params;
private:
	KevoreeModelHandlerService *service;
	Bootstraper *bootstrapService;
	std::string path;
};


#endif






