#include "HelloWorldComponent.h"
#include <unistd.h>

// todo generate
extern "C"{  
    AbstractComponent* create(){
    return new HelloWorldComponent();
   }                        
}
extern "C" {
	void destroy_object( HelloWorldComponent * object )
	{
	  delete object;
	}
}


HelloWorldComponent::HelloWorldComponent()
{

}
HelloWorldComponent::~HelloWorldComponent()
{
		
}

void HelloWorldComponent::start()
{

		cout <<"The HelloWorld Component START" << endl;
		 
}

void HelloWorldComponent::stop(){
			cout <<"The HelloWorld Component STOP" << endl;
}


void HelloWorldComponent::update()
{	
		cout <<"HelloWorldComponent update" << endl;
}

