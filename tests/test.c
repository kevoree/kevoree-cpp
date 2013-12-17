#include <stdio.h>






#pragma KEVOREE ComponentType "HelloWorldComponent"
class HelloWorldComponent 
{
public:
HelloWorldComponent();
~HelloWorldComponent();

	 void start();
	 void stop();
	 void update();
	 #pragma KEVOREE Dictionary
	 int port;
};


int main(void)
{
	
	
	
}
