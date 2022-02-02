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

enum class VERSION {
    V1 = 10,
    V1_1 = 11,
    V2 = 20,
    V3 = 30,
};

namespace header {

constexpr auto A_IM = "A-IM";
constexpr auto ACCEPT = "Accept";
constexpr auto ACCEPT_CHARSET = "Accept-Charset";
constexpr auto ACCEPT_DATETIME = "Accept-Datetime";
constexpr auto ACCEPT_ENCODING = "Accept-Encoding";
constexpr auto ACCEPT_LANGUAGE = "Accept-Language";
constexpr auto ACCESS_CONTROL_REQUEST_METHOD = "Access-Control-Request-Method";
constexpr auto ACCESS_CONTROL_REQUEST_HEADERS = "Access-Control-Request-Headers";
constexpr auto AUTHORIZATION = "Authorization";
constexpr auto CACHE_CONTROL = "Cache-Control";
constexpr auto CONNECTION = "Connection";
constexpr auto CONTENT_LENGTH = "Content-Length";
constexpr auto CONTENT_MD5 = "Content-MD5";
constexpr auto CONTENT_TYPE = "Content-Type";
constexpr auto COOKIE = "Cookie";
constexpr auto DATE = "Date";
constexpr auto EXPECT = "Expect";
constexpr auto FORWARDED = "Forwarded";
constexpr auto FROM = "From";
constexpr auto HOST = "Host";
constexpr auto HTTP2_SETTINGS = "HTTP2-Settings";
constexpr auto IF_MATCH = "If-Match";
constexpr auto IF_MODIFIED_SINCE = "If-Modified-Since";
constexpr auto IF_NONE_MATCH = "If-None-Match";
constexpr auto IF_RANGE = "If-Range";
constexpr auto IF_UNMODIFIED_SINCE = "If-Unmodified-Since";
constexpr auto MAX_FORWARDS = "Max-Forwards";
constexpr auto ORIGIN = "Origin";
constexpr auto PRAGMA = "Pragma";
constexpr auto PREFER = "Prefer";
constexpr auto PROXY_AUTHORIZATION = "Proxy-Authorization";
constexpr auto RANGE = "Range";
constexpr auto REFERER = "Referer";
constexpr auto TE = "TE";
constexpr auto USER_AGENT = "User-Agent";
constexpr auto UPGRADE = "Upgrade";
constexpr auto VIA = "Via";
constexpr auto ACCEPT_CH = "Accept-CH";
constexpr auto ACCESS_CONTROL_ALLOW_ORIGIN = "Access-Control-Allow-Origin";
constexpr auto ACCESS_CONTROL_ALLOW_CREDENTIALS = "Access-Control-Allow-Credentials";
constexpr auto ACCESS_CONTROL_EXPOSE_HEADERS = "Access-Control-Expose-Headers";
constexpr auto ACCESS_CONTROL_MAX_AGE = "Access-Control-Max-Age";
constexpr auto ACCESS_CONTROL_ALLOW_METHODS = "Access-Control-Allow-Methods";
constexpr auto ACCESS_CONTROL_ALLOW_HEADERS = "Access-Control-Allow-Headers";
constexpr auto ACCEPT_PATCH = "Accept-Patch";
constexpr auto ACCEPT_RANGES = "Accept-Ranges";
constexpr auto AGE = "Age";
constexpr auto ALLOW = "Allow";
constexpr auto ALT_SVC = "Alt-Svc";
constexpr auto CONTENT_DISPOSITION = "Content-Disposition";
constexpr auto CONTENT_ENCODING = "Content-Encoding";
constexpr auto CONTENT_LANGUAGE = "Content-Language";
constexpr auto CONTENT_LOCATION = "Content-Location";
constexpr auto CONTENT_RANGE = "Content-Range";
constexpr auto DELTA_BASE = "Delta-Base";
constexpr auto ETAG = "ETag";
constexpr auto EXPIRES = "Expires";
constexpr auto IM = "IM";
constexpr auto LAST_MODIFIED = "Last-Modified";
constexpr auto LINK = "Link";
constexpr auto LOCATION = "Location";
constexpr auto P3P = "P3P";
constexpr auto PREFERENCE_APPLIED = "Preference-Applied";
constexpr auto PROXY_AUTHENTICATE = "Proxy-Authenticate";
constexpr auto PUBLIC_KEY_PINS = "Public-Key-Pins";
constexpr auto RETRY_AFTER = "Retry-After";
constexpr auto SERVER = "Server";
constexpr auto SET_COOKIE = "Set-Cookie";
constexpr auto STRICT_TRANSPORT_SECURITY = "Strict-Transport-Security";
constexpr auto TRAILER = "Trailer";
constexpr auto TRANSFER_ENCODING = "Transfer-Encoding";
constexpr auto TK = "Tk";
constexpr auto VARY = "Vary";
constexpr auto WARNING = "Warning";
constexpr auto WWW_AUTHENTICATE = "WWW-Authenticate";
constexpr auto X_FRAME_OPTIONS = "X-Frame-Options";

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

enum class CODE {
    CONTINUE = 100,
    SWITCHING_PROTOCOLS = 101,
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NON_AUTHORITATIVE_INFORMATION = 203,
    NO_CONTENT = 204,
    RESET_CONTENT = 205,
    PARTIAL_CONTENT = 206,
    MULTIPLE_CHOICES = 300,
    MOVED_PERMANENTLY = 301,
    FOUND = 302,
    SEE_OTHER = 303,
    NOT_MODIFIED = 304,
    USE_PROXY = 305,
    TEMPORARY_REDIRECT = 307,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    PAYMENT_REQUIRED = 402,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    METHOD_NOT_ALLOWED = 405,
    NOT_ACCEPTABLE = 406,
    PROXY_AUTHENTICATION_REQUIRED = 407,
    REQUEST_TIME_OUT = 408,
    CONFLICT = 409,
    GONE = 410,
    LENGTH_REQUIRED = 411,
    PRECONDITION_FAILED = 412,
    REQUEST_ENTITY_TOO_LARGE = 413,
    REQUEST_URI_TOO_LARGE = 414,
    UNSUPPORTED_MEDIA_TYPE = 415,
    REQUESTED_RANGE_NOT_SATISFIABLE = 416,
    EXPECTATION_FAILED = 417,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503,
    GATEWAY_TIME_OUT = 504,
    HTTP_VERSION_NOT_SUPPORTED = 505,
};

}  // namespace ziapi::http
