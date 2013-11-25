#include "HelloWorldComponent.h"


// todo generate
extern "C"{  
    AbstractComponent* create(){
    return new HelloWorldComponent();
   }                        
}
extern "C" void destroy_object( AbstractComponent* object )
{
  delete object;
}



HelloWorldComponent::HelloWorldComponent()
{
	cout <<"HelloWorldComponent loaded" << endl;
}

void HelloWorldComponent::start()
{
		 
}
void HelloWorldComponent::stop(){
	
	
}


void HelloWorldComponent::update(){
	
	
}

