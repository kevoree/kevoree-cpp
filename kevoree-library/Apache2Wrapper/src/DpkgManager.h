#ifndef __Apache2Wrapper_H
#define __Apache2Wrapper_H

#include <kevoree-core/core/api/AbstractComponent.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>

class Apache2Wrapper :public AbstractComponent
{
public:
Apache2Wrapper();
~Apache2Wrapper();

	 void start();
	 void stop();
	 void update();
		DefaultkevoreeFactory factory;
};

#endif /*__HelloWorldComponent_H*/
