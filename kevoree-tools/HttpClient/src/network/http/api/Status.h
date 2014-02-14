/*
 * Status.h
 *
 *  Created on: 10 déc. 2013
 *      Author: edaubert
 */

#ifndef STATUS_H_
#define STATUS_H_

namespace network {
namespace http {
namespace api {

enum Status {
	ok = 200,
	created = 201,
	accepted = 202,
	no_content = 204,
	multiple_choices = 300,
	moved_permanently = 301,
	moved_temporarily = 302,
	not_modified = 304,
	bad_request = 400,
	unauthorized = 401,
	forbidden = 403,
	not_found = 404,
	internal_server_error = 500,
	not_implemented = 501,
	bad_gateway = 502,
	service_unavailable = 503
};
}
}
}

#endif /* STATUS_H_ */
