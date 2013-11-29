#ifndef __HelloWorldComponent_H
#define __HelloWorldComponent_H

#include <kevoree-core/core/api/AbstractGroup.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <microframework/api/json/JSONModelSerializer.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <microframework/api/json/JSONModelLoader.h>
#include <websocketpp/server.hpp>


#include <iostream>


enum 
{
	PULL        = 0,
	PUSH        = 1,
	REGISTER    = 3,
	PULL_JSON   = 42
} REQUESTS;

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;


class WebSocketGroup :public AbstractGroup
{
public:
	WebSocketGroup();
    void start();
	void stop();
	void update();
	ContainerRoot* pull(std::string nodeName);
	
JSONModelSerializer ser;
JSONModelLoader loader;
DefaultkevoreeFactory factory;

};

#endif /*__HelloWorldComponent_H*/
