#ifndef __HelloWorldComponent_H
#define __HelloWorldComponent_H

#include <kevoree-core/api/AbstractComponent.h>


#pragma ComponentType "HelloWorldComponent"
#pragma Dictionary "demo"

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
