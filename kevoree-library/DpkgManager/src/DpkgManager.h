#ifndef __HelloWorldComponent_H
#define __HelloWorldComponent_H

#include <kevoree-core/core/api/AbstractComponent.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>

class DpkgManager :public AbstractComponent
{
public:
DpkgManager();
~DpkgManager();

	 void start();
	 void stop();
	 void update();
		DefaultkevoreeFactory factory;
};

#endif /*__HelloWorldComponent_H*/
