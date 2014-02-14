#include <network/http/impl/BoostHTTPClient.h>
#include <network/http/api/HTTPRequest.h>


/*using namespace network::http::impl;
int main(int argc, char **argv) {

	BoostHTTPClient * client = new BoostHTTPClient();
	network::http::api::HTTPRequest request;
	request.addHeader("User-Agent", "Kevoree");
	request.setUrl("http://192.168.1.115/arduino/analog/0");
	network::http::api::HTTPResponse * response = client->doGet(request);
				std::cout << response->getContentAsString() << std::endl;

}
*/
