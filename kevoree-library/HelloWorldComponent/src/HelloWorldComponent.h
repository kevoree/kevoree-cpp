#ifndef __HelloWorldComponent_H
#define __HelloWorldComponent_H

#include <kevoree-core/core/api/AbstractComponent.h>


#pragma ComponentType "HelloWorldComponent"  
class HelloWorldComponent :public AbstractComponent
{
	public:
	HelloWorldComponent();
	~HelloWorldComponent();

	 void start();
	 void stop();
	 void update();

};

#endif /*__HelloWorldComponent_H*/
