#include "WebSocketGroup.h"



// todo generate
extern "C"{  
    AbstractGroup* create(){
    return new WebSocketGroup();
   }                        
}
extern "C" void destroy_object( WebSocketGroup* object )
{
  delete object;
}


void WebSocketGroup::on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg){
	    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;

    try 
    {
        s->send(hdl, msg->get_payload(), msg->get_opcode());
    } catch (const websocketpp::lib::error_code& e) {
        std::cout << "Echo failed because: " << e
                  << "(" << e.message() << ")" << std::endl;
    }
}

WebSocketGroup::WebSocketGroup()
{
	cout <<"WebSocketGroup loaded" << endl;
	
	   // Create a server endpoint
		server echo_server;

        try {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize ASIO
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&WebSocketGroup::on_message,&echo_server,::_1,::_2));

        // Listen on port 9002
        echo_server.listen(8000);

        // Start the server accept loop
        echo_server.start_accept();

            // Start the ASIO io_service run loop
        echo_server.run();
    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
    } catch (websocketpp::lib::error_code e) {
        std::cout << e.message() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }

}


ContainerRoot* WebSocketGroup::pull(std::string nodeName)
{
		
		
}


void WebSocketGroup::start()
{

	
}
void WebSocketGroup::stop()
{

}

void WebSocketGroup::update()
{
	

}






