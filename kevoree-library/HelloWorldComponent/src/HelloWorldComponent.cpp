#include "HelloWorldComponent.h"


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
		cout <<"destructor  HelloWorldComponent powet" << endl;
}

void HelloWorldComponent::start()
{
		sleep(3);
		cout <<"HelloWorldComponent started" << endl;
		 
}
void HelloWorldComponent::stop(){
			cout <<"HelloWorldComponent stop" << endl;	
}


void HelloWorldComponent::update()
{	
		cout <<"HelloWorldComponent update" << endl;
}

