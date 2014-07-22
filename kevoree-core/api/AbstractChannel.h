#ifndef __AbstractGroup_H
#define __AbstractGroup_H


#include <kevoree-core/model/kevoree/Channel.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/api/AbstractTypeDefinition.h>
#include <string>


class AbstractChannel  : public AbstractTypeDefinition
{
 //  FIFO IN

public:
	void write(std::string data){

		std::cout << "Channel "<< data << std::endl;
	}
	// FIFO OUT
};


#endif
