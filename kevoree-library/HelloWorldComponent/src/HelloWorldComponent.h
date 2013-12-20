#ifndef __HelloWorldComponent_H
#define __HelloWorldComponent_H

#include <kevoree-core/core/api/AbstractComponent.h>


#pragma ComponentType "HelloWorldComponent"
#pragma GroupName "org.kevoree.library"
#pragma Version "1.0"
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
