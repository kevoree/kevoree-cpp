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




using namespace std;

void ThreadFunction(HelloWorldComponent *ptr)
{
	int counter = 0;

	network::http::api::HTTPRequest request;
	request.addHeader("User-Agent", "Kevoree");

	std::string url = "http://127.0.0.1/arduino/digital/";
	url += ptr->params["pin"];
	url += "/";

	if(ptr->params["enable"].compare("true") == 0)
	{
		url += "1";
	}else {
		url += "0";
	}
	request.setUrl(url);
	try
	{
		BoostHTTPClient * client = new BoostHTTPClient();
		network::http::api::HTTPResponse * response = client->doGet(request);
		std::cout << response->getContentAsString() << std::endl;
		delete response;
		//delete client;
	}
	catch(boost::thread_interrupted&)
	{
		cout << "Thread is stopped" << endl;
		return;
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


	boost::thread t(&ThreadFunction,this);


}

void HelloWorldComponent::stop(){
	cout <<"The HelloWorld Component STOP" << endl;
}


void HelloWorldComponent::update()
{	
	boost::thread t(&ThreadFunction,this);
}


