#pragma once

namespace ziapi::http {

namespace method {

constexpr auto GET = "GET";
constexpr auto POST = "POST";
constexpr auto PUT = "PUT";
constexpr auto DELETE = "DELETE";
constexpr auto PATCH = "PATCH";
constexpr auto OPTIONS = "OPTIONS";
constexpr auto HEAD = "HEAD";

}  // namespace method

namespace version {

constexpr auto V1 = 10;
constexpr auto V1_1 = 11;
constexpr auto V2 = 20;
constexpr auto V3 = 30;

}  // namespace version

namespace header {

constexpr auto CONTENT_TYPE = "Content-Type";
constexpr auto AUTHORIZATION = "Authorization";
constexpr auto HOST = "Host";

}  // namespace header

namespace reason {

constexpr auto CONTINUE = "Continue";
constexpr auto SWITCHING_PROTOCOLS = "Switching Protocols";
constexpr auto OK = "OK";
constexpr auto CREATED = "Created";
constexpr auto ACCEPTED = "Accepted";
constexpr auto NON_AUTHORITATIVE_INFORMATION = "Non-Authoritative Information";
constexpr auto NO_CONTENT = "No Content";
constexpr auto RESET_CONTENT = "Reset Content";
constexpr auto PARTIAL_CONTENT = "Partial Content";
constexpr auto MULTIPLE_CHOICES = "Multiple Choices";
constexpr auto MOVED_PERMANENTLY = "Moved Permanently";
constexpr auto FOUND = "Found";
constexpr auto SEE_OTHER = "See Other";
constexpr auto NOT_MODIFIED = "Not Modified";
constexpr auto USE_PROXY = "Use Proxy";
constexpr auto TEMPORARY_REDIRECT = "Temporary Redirect";
constexpr auto BAD_REQUEST = "Bad Request";
constexpr auto UNAUTHORIZED = "Unauthorized";
constexpr auto PAYMENT_REQUIRED = "Payment Required";
constexpr auto FORBIDDEN = "Forbidden";
constexpr auto NOT_FOUND = "Not Found";
constexpr auto METHOD_NOT_ALLOWED = "Method Not Allowed";
constexpr auto NOT_ACCEPTABLE = "Not Acceptable";
constexpr auto PROXY_AUTHENTICATION_REQUIRED = "Proxy Authentication Required";
constexpr auto REQUEST_TIMEOUT = "Request Time-out";
constexpr auto CONFLICT = " Conflict";
constexpr auto GONE = "Gone";
constexpr auto LENGTH_REQUIRED = " Length Required";
constexpr auto PRECONDITION_FAILED = " Precondition Failed";
constexpr auto REQUEST_ENTITY_TOO_LARGE = " Request Entity Too Large";
constexpr auto REQUEST_URI_TOO_LARGE = " Request-URI Too Large";
constexpr auto UNSUPPORTED_MEDIA_TYPE = " Unsupported Media Type";
constexpr auto REQUESTED_RANGE_NOT_SATISFIABLE = " Requested range not satisfiable";
constexpr auto EXPECTATION_FAILED = " Expectation Failed";
constexpr auto INTERNAL_SERVER_ERROR = "Internal Server Error";
constexpr auto NOT_IMPLEMENTED = "Not Implemented";
constexpr auto BAD_GATEWAY = "Bad Gateway";
constexpr auto SERVICE_UNAVAILABLE = "Service Unavailable";
constexpr auto GATEWAY_TIMEOUT = "Gateway Time-out";
constexpr auto HTTP_VERSION_NOT_SUPPORTED = "HTTP Version not supported";

}  // namespace reason

namespace code {

constexpr auto CONTINUE = 100;
constexpr auto SWITCHING_PROTOCOLS = 101;
constexpr auto OK = 200;
constexpr auto CREATED = 201;
constexpr auto ACCEPTED = 202;
constexpr auto NON_AUTHORITATIVE_INFORMATION = 203;
constexpr auto NO_CONTENT = 204;
constexpr auto RESET_CONTENT = 205;
constexpr auto PARTIAL_CONTENT = 206;
constexpr auto MULTIPLE_CHOICES = 300;
constexpr auto MOVED_PERMANENTLY = 301;
constexpr auto FOUND = 302;
constexpr auto SEE_OTHER = 303;
constexpr auto NOT_MODIFIED = 304;
constexpr auto USE_PROXY = 305;
constexpr auto TEMPORARY_REDIRECT = 307;
constexpr auto BAD_REQUEST = 400;
constexpr auto UNAUTHORIZED = 401;
constexpr auto PAYMENT_REQUIRED = 402;
constexpr auto FORBIDDEN = 403;
constexpr auto NOT_FOUND = 404;
constexpr auto METHOD_NOT_ALLOWED = 405;
constexpr auto NOT_ACCEPTABLE = 406;
constexpr auto PROXY_AUTHENTICATION_REQUIRED = 407;
constexpr auto REQUEST_TIME_OUT = 408;
constexpr auto CONFLICT = 409;
constexpr auto GONE = 410;
constexpr auto LENGTH_REQUIRED = 411;
constexpr auto PRECONDITION_FAILED = 412;
constexpr auto REQUEST_ENTITY_TOO_LARGE = 413;
constexpr auto REQUEST_URI_TOO_LARGE = 414;
constexpr auto UNSUPPORTED_MEDIA_TYPE = 415;
constexpr auto REQUESTED_RANGE_NOT_SATISFIABLE = 416;
constexpr auto EXPECTATION_FAILED = 417;
constexpr auto INTERNAL_SERVER_ERROR = 500;
constexpr auto NOT_IMPLEMENTED = 501;
constexpr auto BAD_GATEWAY = 502;
constexpr auto SERVICE_UNAVAILABLE = 503;
constexpr auto GATEWAY_TIME_OUT = 504;
constexpr auto HTTP_VERSION_NOT_SUPPORTED = 505;

}  // namespace code

}  // namespace ziapi::http
