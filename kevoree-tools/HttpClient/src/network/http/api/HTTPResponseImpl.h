/*
 * HTTPResponseImpl.h
 *
 *  Created on: 20 déc. 2013
 *      Author: edaubert
 */

#ifndef HTTPRESPONSEIMPL_H_
#define HTTPRESPONSEIMPL_H_

#include <network/http/api/HTTPResponse.h>

namespace network {
namespace http {
namespace api {
class HTTPResponseImpl : public network::http::api::HTTPResponse {
private:
	Status status;
	/// The headers to be included in the reply.
	std::map<std::string, std::string> headers;
	/// The content to be sent in the reply.
	std::istream * stream;

public:
	HTTPResponseImpl();
	~HTTPResponseImpl();

	Status getStatus();
	std::map<std::string, std::string> getHeaders();
	std::string getHeader(std::string _name);
	std::string getContentAsString();
//	short int * getContent();
//	long getContentLength();
	std::istream& getStream();

	void addHeader(std::string _name, std::string _value);
	void removeHeader(std::string _name);
	void setStatus(Status _status);
	void setStream(std::istream * _stream);

};
}
}
}

#endif /* HTTPRESPONSEIMPL_H_ */
