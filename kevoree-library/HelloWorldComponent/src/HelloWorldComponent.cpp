#include "HelloWorldComponent.h"

#include <network/http/impl/BoostHTTPClient.h>
#include <network/http/api/HTTPRequest.h>
#include <boost/thread.hpp>

using namespace network::http::impl;

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

	cout <<"The HelloWorld component is starting"  << endl;
}

void HelloWorldComponent::stop(){
	cout <<"The HelloWorld component is stopping" << endl;
}


void HelloWorldComponent::update()
{	
	cout <<"The HelloWorld component is updating" << endl;
}


