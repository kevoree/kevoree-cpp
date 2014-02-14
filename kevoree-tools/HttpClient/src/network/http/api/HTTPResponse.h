/*
 * Response.h
 *
 *  Created on: 10 déc. 2013
 *      Author: edaubert
 */

#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <map>
#include <string>
#include <iostream>

#include "Status.h"

namespace network {
namespace http {
namespace api {
class HTTPResponse {

public:
//	HTTPResponse();
//	~HTTPResponse();
	virtual Status getStatus() = 0;
	virtual std::map<std::string, std::string> getHeaders() = 0;
	virtual std::string getHeader(std::string _name) = 0;
	virtual std::string getContentAsString() = 0;
//	virtual short int * getContent() = 0;
//	virtual long getContentLength() = 0;
	virtual std::istream& getStream() = 0;
};

}
}
}
#endif /* RESPONSE_H_ */
