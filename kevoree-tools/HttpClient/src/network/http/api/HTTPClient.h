/*
 * HTTPClient.h
 *
 *  Created on: 10 déc. 2013
 *      Author: edaubert
 */

#ifndef HTTPCLIENT_H_
#define HTTPCLIENT_H_

#include <string>
#include <network/http/api/HTTP.h>
#include <network/http/api/HTTPRequest.h>
#include <network/http/api/HTTPResponse.h>

namespace network {
namespace http {
namespace api {
class HTTPClient {

public:
//	virtual ~HTTPClient() = 0;
	virtual bool isHTTPURL(std::string const& url) = 0;
	virtual network::http::api::HTTPResponse * doGet(network::http::api::HTTPRequest const& request) = 0;
//	void doPOST(std::string url, std::string content);
//	void doPUT(std::string url);
};

}
}
}
#endif /* HTTPCLIENT_H_ */
