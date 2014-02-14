/*
 * HTTPResponseImpl.cpp
 *
 *  Created on: 20 déc. 2013
 *      Author: edaubert
 */
#include <network/http/api/HTTPResponseImpl.h>
#include <sstream>
namespace network {
namespace http {
namespace api {

HTTPResponseImpl::HTTPResponseImpl() {
	status = internal_server_error;
	stream = NULL;
}

HTTPResponseImpl::~HTTPResponseImpl() {
	if(stream != NULL)
	{
		delete stream;
	}
}

void HTTPResponseImpl::addHeader(std::string _name, std::string _value) {
	std::map<std::string, std::string>::iterator position = headers.find(_name);
	if (position == headers.end()) {
		headers[_name] = _value;
	} else {
		headers.erase(position);
		headers[_name] = _value;
	}
}
void HTTPResponseImpl::removeHeader(std::string _name) {
	std::map<std::string, std::string>::iterator position = headers.find(_name);
	if (position != headers.end()) {
		headers.erase(position);
	}
}
void HTTPResponseImpl::setStatus(Status _status) {
	status = _status;
}

void HTTPResponseImpl::setStream(std::istream * _stream) {
	stream = _stream;
}

Status HTTPResponseImpl::getStatus() {
	return status;
}
std::map<std::string, std::string> HTTPResponseImpl::getHeaders() {
	return headers;
}
std::string HTTPResponseImpl::getHeader(std::string _name) {
	std::map<std::string, std::string>::iterator position = headers.find(_name);
	if (position != headers.end()) {
		return headers[_name];
	} else {
		return NULL;
	}
}

std::string HTTPResponseImpl::getContentAsString() {
	std::ostringstream out;
	out << stream->rdbuf();
	return out.str();
}
//short int * HTTPResponseImpl::getContent() {
//}
//long HTTPResponseImpl::getContentLength() {
//}
std::istream& HTTPResponseImpl::getStream() {
	return *stream;
}
}
}
}

