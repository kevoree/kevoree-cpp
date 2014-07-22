#ifndef __core_port_H
#define __core_port_H

#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/api/AbstractChannel.h>

#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/compare/ModelCompare.h>
#include <microframework/api/trace/TraceSequence.h>
#include <microframework/api/utils/any.h>



class PortHandler {


public:
	AbstractChannel *channel;
};


#endif
