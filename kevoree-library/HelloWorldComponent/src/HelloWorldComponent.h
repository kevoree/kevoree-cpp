#ifndef __HelloWorldComponent_H
#define __HelloWorldComponent_H

#include <kevoree-core/core/api/AbstractComponent.h>

#define ADD_PORT(name) 

ADD_PORT("input");

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
