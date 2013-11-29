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


void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg,WebSocketGroup *ptr)
{
    try 
    {
		int command = (char)msg->get_payload().at(0);
	KevoreeModelHandlerService *service = ptr->getModelService();

         if(command==PULL_JSON)
              {
		

				
					
						KMFContainer *model = service->getLastModel();
						if(model != NULL)
						{
								std::string result =ptr->ser.serialize(model);
								s->send(hdl, result, msg->get_opcode());	
						}
						else
						{
							cout << "MODEL IS NULL" << endl;
						}
			  }else if(command==PUSH)
			  {
				  string m = msg->get_payload();
				  m.erase(0,1); // remove magic number
				  ContainerRoot *model = (ContainerRoot*)  ptr->loader.loadModelFromString(m)->front();
				  // propose model
				  service->updateModel(model);
				  
			  }else 
			  {
					  cout << msg->get_payload() << endl;    
			  }
    } catch (const websocketpp::lib::error_code& e) {
        std::cout << "Echo failed because: " << e
                  << "(" << e.message() << ")" << std::endl;
    }
}

WebSocketGroup::WebSocketGroup()
{
	loader.setFactory(&factory);
}


ContainerRoot* WebSocketGroup::pull(std::string nodeName)
{
		
		
}


void WebSocketGroup::start()
{
	   // Create a server endpoint
		server echo_server;

        try {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::none);
        echo_server.clear_access_channels(websocketpp::log::alevel::none);

        // Initialize ASIO
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&on_message,&echo_server,::_1,::_2,this));

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
void WebSocketGroup::stop()
{

}

void WebSocketGroup::update()
{
	

}






