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
		
	KevoreeModelHandlerService *service = ptr->getModelService();

				if(msg->get_payload().compare("get") == 0)
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
			  }else 
			  {
				  string m = msg->get_payload();

				  ContainerRoot *model = (ContainerRoot*)  ptr->loader.loadModelFromString(m)->front();
				  // propose model
				  service->updateModel(model);
				  
			  }
    } catch (const websocketpp::lib::error_code& e) {
        std::cout << "Echo failed because: " << e
                  << "(" << e.message() << ")" << std::endl;
    }
}

WebSocketGroup::WebSocketGroup()
{
	loader.setFactory(&factory);
	num_threads=2;
	 group.set_access_channels(websocketpp::log::alevel::none);
        group.clear_access_channels(websocketpp::log::alevel::none);

        // Initialize ASIO
        group.init_asio();


        // Register our message handler
        group.set_message_handler(bind(&on_message,&group,::_1,::_2,this));

        // Listen on port 9002
        group.listen(9000);

        // Start the server accept loop
        group.start_accept();

}




void WebSocketGroup::start()
{
   if (num_threads == 1) {
            group.run();
        } else 
        {       
            for (size_t i = 0; i < num_threads; i++) {
                ts.push_back(thread_ptr(new websocketpp::lib::thread(&server::run, &group)));
            }
            
        }
}
void WebSocketGroup::stop()
{

}

void WebSocketGroup::update()
{
	

}






