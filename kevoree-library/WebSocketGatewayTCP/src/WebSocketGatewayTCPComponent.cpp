/*
 * WebSocketGatewayTCPComponent.cpp
 *
 *  Created on: 29 janv. 2014
 *      Author: jed
 */

#include "WebSocketGatewayTCPComponent.h"


/*
 * Copyright (c) 2012, Stephan Wypler. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WSS Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL STEPHAN WYPLER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */



#define VERSION "VERSION 0.2"

// The Connection created on construction a new TCP connection.
// It forwards incoming TCP traffic to the websocket.
// Its send() method sends stuff (from the websocket) to the TCP endpoint

	class Connection : public boost::enable_shared_from_this<Connection>{
public:
	Connection(websocketpp::server::handler::connection_ptr con, boost::asio::io_service &io_service) :
		websocket_connection(con), socket(io_service), readBuffer(8192){
#ifdef DEBUG
		std::cout << "Constructor of Connection" << std::endl;
#endif
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(Connection::hostname, Connection::port);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		boost::asio::ip::tcp::resolver::iterator end;
		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if (error) {
#ifdef DEBUG
			std::cerr << "connection error" << std::endl;
#endif
			websocket_connection->close(websocketpp::close::status::NORMAL, "cant establish tcp connection");
		}
#ifdef DEBUG
		std::cout << "Created new Connection at " << this << std::endl;
#endif
	}

	~Connection(){
#ifdef DEBUG
		std::cout << "Begin of Destructor at " << this << std::endl;
#endif
		websocket_connection->close(websocketpp::close::status::NORMAL, "closing connection");
#ifdef DEBUG
		std::cout << "End of Destructor" << std::endl;
#endif
	}

	void receive(const boost::system::error_code& error, size_t bytes_transferred) {
		if (!error && websocket_connection->get_state() == websocketpp::session::state::OPEN) {
			std::string message(readBuffer.data(), bytes_transferred);
#ifdef DEBUG
			std::cout << "received TCP segment from broker " << bytes_transferred << " bytes: ";
			unsigned int i = 0;
			for(std::vector<char>::iterator it = readBuffer.begin(); it != readBuffer.end() && i <= message.size(); it++, i++){
				std::cout << std::setw(2) << std::setfill('0') << std::hex << (short)*it << " ";
			}
			std::cout << std::dec << std::endl;
		    std::cout << "plaintext: " << message << std::endl;
#endif
			websocket_connection->send(message, websocketpp::frame::opcode::BINARY);
			socket.async_receive(
					boost::asio::buffer(readBuffer),
					boost::bind(&Connection::receive, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
		else {
#ifdef DEBUG
			std::cout << "I'm done (stopping async_receive)" << std::endl;
#endif
			if(error != boost::asio::error::operation_aborted)
				websocket_connection->close(websocketpp::close::status::NORMAL, "failed to receive data from broker");
		}
	}

	void send(const std::string &message) {
#ifdef DEBUG
		std::cout << "sent TCP segment to broker " << message.size() << " bytes: " ;
		unsigned int i = 0;
		for(std::string::const_iterator it = message.begin(); it != message.end() && i <= message.size(); it++, i++)
			std::cout << std::setw(2) << std::setfill('0') << std::hex << (short)*it << " ";
		std::cout << std::dec << std::endl;
		std::cout << "plaintext: " << message << std::endl;
#endif
		try{
			socket.write_some(boost::asio::buffer(message.c_str(), message.size()));
		}catch(boost::system::system_error &e){
#ifdef DEBUG
			std::cerr << "Write Error in TCP connection to broker: " << e.what() << std::endl;
#endif
			websocket_connection->close(websocketpp::close::status::NORMAL, "cant close tcp connection");
		}
	}

	void start() {
#ifdef DEBUG
		std::cout << "begin of start(). Connection at " << this << std::endl;
#endif
		socket.async_receive(
				boost::asio::buffer(readBuffer),
				boost::bind(&Connection::receive, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
#ifdef DEBUG
		std::cout << "started async TCP receive" << std::endl;
#endif
	}

	void stop() {
#ifdef DEBUG
		std::cout << "begin of stop(). Connection at " << this << std::endl;
#endif
		socket.cancel();
		socket.close();
#ifdef DEBUG
		std::cout << "stopped async TCP receive" << std::endl;
#endif
	}

	static std::string hostname;
	static std::string port;

private:
	websocketpp::server::handler::connection_ptr websocket_connection;
	boost::asio::ip::tcp::socket socket;
	std::vector<char> readBuffer;
};

std::string Connection::hostname;
std::string Connection::port;

// The WebSocket++ handler
class ServerHandler: public websocketpp::server::handler {
public:
	void on_open(connection_ptr con) {
		if (connections.find(con) == connections.end()) {
#ifdef DEBUG
			std::cout << "new connection, create new handler to process this message" << std::endl;
#endif
			connections[con] = boost::shared_ptr<Connection>(new Connection(con, con->get_io_service()));
			connections[con]->start();
		}
#ifdef DEBUG
		else
			std::cerr << "did I just reuse a connection pointer???" << std::endl;
#endif
	}

	void on_message(connection_ptr con, message_ptr msg) {
		if (connections.find(con) != connections.end()){
#ifdef DEBUG
            std::cout << "received from websocket: " << msg->get_payload() << std::endl;
#endif
			connections[con]->send(msg->get_payload());
		}
#ifdef DEBUG
		else
			std::cerr << "error receiving websocket message" << std::endl;
#endif
	}

	void on_close(connection_ptr con) {
		std::map<connection_ptr, boost::shared_ptr<Connection> >::iterator it = connections.find(con);
		if (it != connections.end()) {
			connections[con]->stop();
			connections[con].reset();
			connections.erase(it);
#ifdef DEBUG
			std::cout << "closing connection, delete corresponding handler. handlers left:" << connections.size() << std::endl;
#endif
		}
#ifdef DEBUG
		else
			std::cerr << "can't remove connection on close" << std::endl;
#endif
	}

	void on_fail(connection_ptr con) {
		std::map<connection_ptr, boost::shared_ptr<Connection> >::iterator it = connections.find(con);
		if (it != connections.end()) {
			connections[con]->stop();
			connections[con].reset();
			connections.erase(it);
#ifdef DEBUG
			std::cout << "something failed. deleted handler. number of handlers left:" << connections.size() << std::endl;
#endif
		}
#ifdef DEBUG
		else
			std::cerr << "there is nothing to clean up after something failed in the connection handler." << std::endl;
#endif
	}
private:
	std::map<connection_ptr, boost::shared_ptr<Connection> > connections;
};


// todo generate
extern "C"{
AbstractComponent* create(){
	return new WebSocketGatewayTCPComponent();
}
}
extern "C" {
void destroy_object( WebSocketGatewayTCPComponent * object )
{
	delete object;
}
}





WebSocketGatewayTCPComponent::WebSocketGatewayTCPComponent() {
	// TODO Auto-generated constructor stub

}

WebSocketGatewayTCPComponent::~WebSocketGatewayTCPComponent() {
	// TODO Auto-generated destructor stub
}



void ThreadFunction(WebSocketGatewayTCPComponent *ptr)
{
	try {

			unsigned short websocketPort = atoi(ptr->params["port_gw"].c_str());
			Connection::hostname = ptr->params["HOST_MQTT"];
			Connection::port = ptr->params["port_MQTT"];

			websocketpp::server::handler::ptr serverHandler = websocketpp::server::handler::ptr(new ServerHandler());
			websocketpp::server websocketServer(serverHandler);
			ptr->server = &websocketServer;


			//boost::asio::signal_set signals(websocketServer.get_io_service(), SIGINT, SIGTERM);
			//signals.async_wait(boost::bind(&websocketpp::server::stop, boost::ref(websocketServer), true,  websocketpp::close::status::NORMAL, "websocket server quit"));

			websocketServer.alog().unset_level(websocketpp::log::alevel::ALL);
			websocketServer.elog().unset_level(websocketpp::log::elevel::ALL);
			/*
			if (variables_map.find("verbose") != variables_map.end()) {
				websocketServer.elog().set_level(websocketpp::log::elevel::RERROR);
				websocketServer.elog().set_level(websocketpp::log::elevel::FATAL);
			}
			*/
			websocketServer.listen(boost::asio::ip::tcp::v4(), websocketPort, 1);
			websocketServer.stop_listen(true);


		} catch(boost::system::system_error &e){
			std::cerr << "System Error: " << e.what() << std::endl;

		} catch (std::exception& e) {
			std::cerr << "Exception: " << e.what() << std::endl;

		}
}
void WebSocketGatewayTCPComponent::start(){

 t = boost::thread(&ThreadFunction,this);

}
void WebSocketGatewayTCPComponent::stop(){
	server->stop(true);
	t.interrupt();
}
void WebSocketGatewayTCPComponent::update(){

}
