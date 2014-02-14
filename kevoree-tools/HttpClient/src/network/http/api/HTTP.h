/*
 * HTTP.h
 *
 *  Created on: 10 déc. 2013
 *      Author: edaubert
 */

#ifndef HTTP_H_
#define HTTP_H_

namespace network {
namespace http {
namespace api {

const std::string http = "http://";
const std::string https = "https://";

const std::string HOST = "HOST";
const std::string VER_10 = "1.0";
const std::string VER_11 = "1.1";
const std::string VER = "1.1";
const std::string CRLF = "\r\n";
const std::string TAB = "\t";

const std::string GET = "GET";
const std::string HEAD = "HEAD";
const std::string POST = "POST";
const std::string PUT = "PUT";
const std::string DELETE = "DELETE";
const std::string TRACE = "TRACE";
const std::string OPTIONS = "OPTIONS";
const std::string CONNECT = "CONNECT";
const std::string PATCH = "PATCH";

// STANDARD HEADER NAMES
const std::string ACCEPT = "Accept";
const std::string ACCEPT_CHARSET ="Accept-Charset";
const std::string ACCEPT_ENCODING ="Accept-Encoding";
const std::string ACCEPT_LANGUAGE ="Accept-Language";
const std::string ACCEPT_DATETIME ="Accept-Datetime";
const std::string AUTHORIZATION ="Authorization";
const std::string CACHE_CONTROL ="Cache-Control";
const std::string CONNECTION ="Connection";
const std::string COOKIE ="Cookie";
const std::string CONTENT_LENGTH ="Content-Length";
const std::string CONTENT_MD5 ="Content-MD5";
const std::string CONTENT_TYPE ="Content-Type";
const std::string DATE ="Date";
const std::string EXPECT ="Expect";
const std::string FROM ="From";
const std::string IF_MATCH ="If-Match" ;
const std::string IF_MODIFIED_SINCE ="If-Modified-Since";
const std::string IF_NONE_MATCH ="If-None-Match";
const std::string IF_RANGE="If-Range";
const std::string IF_UNMODIFIED_SINCE ="If-Unmodified-Since";
const std::string MAX_FORWARDS ="Max-Forwards";
const std::string ORIGIN ="Origin";
const std::string PRAGMA ="Pragma";
const std::string PROXY_AUTHORIZATION ="Proxy-Authorization";
const std::string RANGE="Range";
const std::string REFERER ="Referer";
const std::string TE ="TE";
const std::string UPGRADE ="Upgrade";
const std::string USER_AGENT ="User-Agent";
const std::string VIA ="Via";
const std::string WARNING ="Warning";
const std::string ACCESS_CONTROL_ALLOW_ORIGIN = "Access-Control-Allow-Origin";
const std::string ACCEPT_RANGES = "Accept-Ranges";
const std::string AGE = "Age";
const std::string ALLOW = "Allow";
const std::string CONTENT_ENCODING = "Content-Encoding";
const std::string CONTENT_LANGUAGE = "Content-Language";
const std::string CONTENT_LOCATION = "Content-Location";
const std::string CONTENT_DISPOSITION = "Content-Disposition";
const std::string CONTENT_RANGE = "Content-Range";
const std::string ETAG = "ETag";
const std::string EXPIRES = "Expires";
const std::string LAST_MODIFIED = "Last-Modified";
const std::string LINK = "Link";
const std::string LOCATION = "Location";
const std::string P3P = "P3P";
const std::string PROXY_AUTHENTICATE = "Proxy-Authenticate";
const std::string REFRESH = "Refresh";
const std::string RETRY_AFTER = "Retry-After";
const std::string SERVER = "Server";
const std::string SET_COOKIE = "Set-Cookie";
const std::string STATUS = "Status";
const std::string STRICT_TRANSPORT_SECURITY = "Strict-Transport-Security";
const std::string TRAILER = "Trailer";
const std::string TRANSFER_ENCODING = "Transfer-Encoding";
const std::string VARY = "Vary";
const std::string WWW_AUTHENTICATE = "WWW-Authenticate";

// COMMON VALUE FOR SOME HEADERS
const std::string NO_CACHE = "no-cache";
const std::string MAX_AGE = "max-age";
const std::string CLOSE = "close";
const std::string KEEP_ALIVE = "Keep-Alive";
const std::string CHARSET = "charset";
const std::string CONTENT_RANGE_BYTES = "bytes";
const std::string CHUNKED = "Chunked";

// COMMON VALUES TO BUILD REQUEST AND/OR RESPONSE
const std::string REQEST_LINE_DELIM = " ";
const std::string HEADER_LINE_DELIM = " :";
const std::string STATUS_LINE_DELIM = " ";

// DEFAULT VALUE FOR SERVER AND/OR CLIENT
const int DEFAULT_PORT = 80;
const int DEFAULT_CHUNK_SIZE = 512 * 1024;
const int DEFAULT_TIMEOUT = 30;

}
}
}
#endif /* HTTP_H_ */
