#ifndef __WebSocketGroup_H
#define __WebSocketGroup_H

#include <kevoree-core/core/api/AbstractGroup.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <microframework/api/json/JSONModelSerializer.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <microframework/api/json/JSONModelLoader.h>
#include <websocketpp/server.hpp>


#include <iostream>
#include <thread>


typedef websocketpp::server<websocketpp::config::asio> server;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::thread> thread_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;


#pragma GroupType "WebSocketGroup"  
#pragma GroupName "org.kevoree.library"
#pragma Version "1.0"

#pragma Dictionary "port"
#pragma Dictionary "num_threads"
class WebSocketGroup :public AbstractGroup
{
public:
	WebSocketGroup();
    void start();
	void stop();
	void update();
	
JSONModelSerializer ser;
JSONModelLoader loader;
DefaultkevoreeFactory factory;
std::vector<thread_ptr> ts;
server group;


size_t num_threads;

};

#endif /*__WebSocketGroup_H*/
