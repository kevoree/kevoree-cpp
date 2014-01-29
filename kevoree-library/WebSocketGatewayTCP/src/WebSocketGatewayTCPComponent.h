/*
 * WebSocketGatewayTCPComponent.h
 *
 *  Created on: 29 janv. 2014
 *      Author: jed
 */

#ifndef WEBSOCKETGATEWAYTCPCOMPONENT_H_
#define WEBSOCKETGATEWAYTCPCOMPONENT_H_

#include <kevoree-core/api/AbstractComponent.h>

#include <boost/thread.hpp>
#include <websocketpp/websocketpp.hpp>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <sstream>
#include <iomanip>

class WebSocketGatewayTCPComponent :public AbstractComponent
{
public:
	WebSocketGatewayTCPComponent();
	virtual ~WebSocketGatewayTCPComponent();
	 void start();
	 void stop();
	 void update();
	 boost::thread t;
	 websocketpp::server *server;
};

#endif /* WEBSOCKETGATEWAYTCPCOMPONENT_H_ */
