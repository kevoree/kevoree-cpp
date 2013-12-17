#ifndef __HelloWorldComponent_H
#define __HelloWorldComponent_H

#include <kevoree-core/core/api/AbstractComponent.h>



class HelloWorldComponent :public AbstractComponent
{
public:
HelloWorldComponent();
~HelloWorldComponent();

	 void start();
	 void stop();
	 void update();
	 #pragma kevoree dictonnary
	 int port;
};

#endif /*__HelloWorldComponent_H*/
