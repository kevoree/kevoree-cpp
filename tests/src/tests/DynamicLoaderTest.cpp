/*
 * DynamicLoaderTest.cpp
 *
 *  Created on: 17 févr. 2014
 *      Author: jed
 */

#include "DynamicLoaderTest.h"

DynamicLoaderTest::DynamicLoaderTest() {
	// TODO Auto-generated constructor stub

}

DynamicLoaderTest::~DynamicLoaderTest() {
	// TODO Auto-generated destructor stub
}


/*
	for(int i=0;i<100000;i++){
	 void* handle = dlopen("/home/jed/KEVOREE_PROJECT/kevoree-cpp/build/libwebsocketgroup.so",RTLD_NOW);

		AbstractTypeDefinition* (*create)();
		create =  (AbstractTypeDefinition* (*)())dlsym(handle, "create");
		if(!create){
			LOGGER_WRITE(Logger::DEBUG,"cannot find symbol newInstance");
		}
		AbstractTypeDefinition* c = (AbstractTypeDefinition*)create();
		c->dico["port"] = "9000";
		//c->start();

		boost::thread api_caller(boost::bind(&AbstractTypeDefinition::start, c));
		api_caller.timed_join(boost::posix_time::milliseconds(10000000));


		boost::thread api_caller_stop(boost::bind(&AbstractTypeDefinition::stop, c));
		api_caller_stop.timed_join(boost::posix_time::milliseconds(10000000));



		void (*destroy)(AbstractTypeDefinition*);
		destroy = (void (*)(AbstractTypeDefinition*))dlsym(handle, "destroy_object");
		destroy(c);
	}

	return 0;
	*/
