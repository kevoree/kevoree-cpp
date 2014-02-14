/*
 * BoostHTTPClient.cpp
 *
 *  Created on: 13 déc. 2013
 *      Author: edaubert
 */
#ifndef BOOSTHTTPCLIENT_INCLUDED
#define BOOSTHTTPCLIENT_INCLUDED

#include <boost/asio.hpp>

#include <network/http/api/HTTPClient.h>

namespace network {
namespace http {
namespace impl {

class BoostHTTPClient: public network::http::api::HTTPClient {
private:
	boost::asio::io_service io_service;

public:
	BoostHTTPClient();
	~BoostHTTPClient();
	bool isHTTPURL(std::string const& url);
	network::http::api::HTTPResponse * doGet(network::http::api::HTTPRequest const& request);

private:
	std::string * parseURL(std::string const& url, std::string parsedResults[]);
};
}
}
}

#endif // BOOSTHTTPCLIENT_INCLUDED
