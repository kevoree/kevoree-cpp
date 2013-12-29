#include "WebSocketGroup.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>


// todo generate
extern "C"{  
AbstractGroup* create()
{
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

		if(msg->get_payload().compare("get") == 0 | msg->get_payload().compare("pull") == 0)
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
			if (boost::starts_with(m, "push")){
				m.erase(0,5); // push/

			}
			vector<KMFContainer*> *roots =ptr->loader.loadModelFromString(m);

			if(roots)
			{
				ContainerRoot *model = (ContainerRoot*) roots->front();
				delete roots;
				// propose model
				service->updateModel(model);
			}else
			{
				LOGGER_WRITE(Logger::WARNING,"The Group cannot deserialized the model");
			}


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

}




void WebSocketGroup::start()
{
	LOGGER_WRITE(Logger::DEBUG,"The Group is listenning on port "+this->dico["port"]);

	group.set_access_channels(websocketpp::log::alevel::none);
	group.clear_access_channels(websocketpp::log::alevel::none);

	// Initialize ASIO
	group.init_asio();


	// Register our message handler
	group.set_message_handler(bind(&on_message,&group,::_1,::_2,this));

	int port = atoi(this->dico["port"].c_str());

	// Listen on port 9002
	group.listen(port);

	// Start the server accept loop
	group.start_accept();
	if (num_threads == 1)
	{
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
	LOGGER_WRITE(Logger::DEBUG,"stop group");
	group.stop();

	if(num_threads != 1)
	{
		for (size_t i = 0; i < num_threads; i++)
		{
			ts[i]->interrupt();

		if(!ts[i]->timed_join(boost::posix_time::milliseconds(1000))){

			LOGGER_WRITE(Logger::WARNING,"timed_join group");
		}

		}
	}
}

void WebSocketGroup::update()
{


}






