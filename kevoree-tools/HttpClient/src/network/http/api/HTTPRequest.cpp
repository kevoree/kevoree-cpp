/*
 * HTTPRequest.cpp
 *
 *  Created on: 6 janv. 2014
 *      Author: edaubert
 */

#include <map>

#include <network/http/api/HTTPRequest.h>

namespace network {
namespace http {
namespace api {
void HTTPRequest::setMethod(std::string _method) {
	method = _method;
}
void HTTPRequest::setUrl(std::string _url) {
	url = _url;
}
void HTTPRequest::setHttpVersion(std::string _httpVersion) {
	httpVersion = _httpVersion;
}
void HTTPRequest::addHeader(std::string _name, std::string _value) {
	std::map<std::string, std::string>::iterator position = headers.find(_name);
	if (position == headers.end()) {
		headers[_name] = _value;
	} else {
		headers.erase(position);
		headers[_name] = _value;
	}
}

std::string const& HTTPRequest::getMethod() const {
	return method;
}
std::string const& HTTPRequest::getUrl() const {
	return url;
}
std::string const& HTTPRequest::getHttpVersion() const {
	return httpVersion;
}
std::map<std::string, std::string> const& HTTPRequest::getHeaders() const {
	return headers;
}
}
}
}
