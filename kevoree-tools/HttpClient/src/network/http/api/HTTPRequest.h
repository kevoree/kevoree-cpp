/*
 * Request.h
 *
 *  Created on: 10 déc. 2013
 *      Author: edaubert
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include <string>
#include <vector>

namespace network {
namespace http {
namespace api {
class HTTPRequest {
private:
	std::string method;
	std::string url;
	std::string httpVersion;
	std::map<std::string, std::string> headers;
public:
	void setMethod(std::string method);
	void setUrl(std::string url);
	void setHttpVersion(std::string httpVersion);
	void addHeader(std::string name, std::string value);

	std::string const& getMethod() const;
	std::string const& getUrl() const;
	std::string  const& getHttpVersion() const;
	std::map<std::string, std::string> const& getHeaders() const;
};

}
}
}
#endif /* REQUEST_H_ */
