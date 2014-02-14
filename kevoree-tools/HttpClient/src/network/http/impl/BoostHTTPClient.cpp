/*
 * BoostHTTPClient.cpp
 *
 *  Created on: 13 déc. 2013
 *      Author: edaubert
 */
#include <network/http/impl/BoostHTTPClient.h>
#include <network/http/api/HTTPResponseImpl.h>

namespace network {
namespace http {
namespace impl {

BoostHTTPClient::BoostHTTPClient() :
		network::http::api::HTTPClient() {
}

bool BoostHTTPClient::isHTTPURL(std::string const& url) {
	//std::cout << url.find_first_of(http) << std::endl;
	//std::cout << url.find_first_of(https) << std::endl;
	return url.find_first_of(network::http::api::http) == 0
			|| url.find_first_of(network::http::api::https) == 0;
}

// parsedResults is an array[3]
std::string * BoostHTTPClient::parseURL(std::string const& url,
		std::string parsedResults[]) {

	std::string newURL = url;
	if (newURL.find_first_of(network::http::api::http) == 0) {
		newURL = newURL.substr(network::http::api::http.length());
	} else if (newURL.find_first_of(network::http::api::https) == 0) {
		newURL = newURL.substr(network::http::api::https.length());
	}

	std::size_t position = newURL.find_first_of("/");
	parsedResults[0] = newURL.substr(0, position);

	if (position < newURL.length()) {
		parsedResults[2] = newURL.substr(position);
	} else {
		parsedResults[2] = "/";
	}

	parsedResults[1] = "80";

	position = parsedResults[0].find_first_of(":");
	if (position != -1) {
		parsedResults[1] = parsedResults[0].substr(position);
		parsedResults[0] = parsedResults[0].substr(0, position);
	}

	//std::cout << "Host: " << parsedResults[0] << std::endl << "Port: " << parsedResults[1] << std::endl << "Query: " << parsedResults[2] << std::endl;
	return parsedResults;
}

network::http::api::HTTPResponse * BoostHTTPClient::doGet(
		network::http::api::HTTPRequest const& request) {

	// check if the url is an http(s) one
	if (BoostHTTPClient::isHTTPURL(request.getUrl())) {
		// parse url to get host, port and uri
		// return an array of 3 string
		std::string values[3];
		parseURL(request.getUrl(), values);

		//std::cout << "Host: " << values[0] << std::endl << "Port: " << values[1] << std::endl << "Query: " << values[2] << std::endl;

		// TODO protect if there is no network

		// Get a list of endpoints corresponding to the server name.
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(values[0], "http");
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator =
				resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection.
		boost::asio::ip::tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET " << values[2] << " HTTP/1.0\r\n";
		request_stream << "Host: " << values[0] << ":" << values[1] << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// TODO use a request as param and add headers

		// Send the request.
		boost::asio::write(socket, request);

		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor.
		boost::asio::streambuf * response = new boost::asio::streambuf();
		boost::asio::read_until(socket, *response, "\r\n");

		// Check that response is OK.
		std::istream response_stream(response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
			std::cerr << "Invalid response\n";
			//return 1;
		}
		if (status_code != 200) {
			std::cerr << "Response returned with status code " << status_code
					<< std::endl;
			//return 1;
		}

		network::http::api::HTTPResponseImpl * responseResult =
				new network::http::api::HTTPResponseImpl();

		responseResult->setStatus(network::http::api::Status(status_code));

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, *response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r") {

			std::string key = header.substr(0, header.find_first_of(": "));
			std::string value = header.substr(header.find_first_of(": ") + 2);
//			std::cout << key << ":" << value << std::endl;
			responseResult->addHeader(key, value);
		}
//		std::cout << std::endl;

		// Read until EOF, reading data and storing it into response buffer
		boost::system::error_code error;
		while (boost::asio::read(socket, *response,
				boost::asio::transfer_at_least(1), error)) {
			// boost::asio::error::eof correspond to the end of the stream
			// boost::system::errc::success correspond to the end of the request (with success as a result)
			if (error != boost::asio::error::eof
					&& error != boost::system::errc::success) {
//				std::cout << std::endl << error << std::endl;
				throw boost::system::system_error(error);
			}
		}
	//	response->commit(response->size());

		std::istream * contentStream = new std::istream(response);

//		while (!contentStream->eof()) {
//			std::string s;
//			std::getline(*contentStream, s);
//			std::cout << s << std::endl;
//		}

		responseResult->setStream(contentStream);
		return responseResult;
	} else {
		return NULL;
	}
}

}
}
}
