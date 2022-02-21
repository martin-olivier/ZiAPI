#pragma once

namespace ziapi::http {

namespace method {

constexpr auto kGet = "GET";
constexpr auto kPost = "POST";
constexpr auto kPut = "PUT";
constexpr auto kDelete = "DELETE";
constexpr auto kPatch = "PATCH";
constexpr auto kOptions = "OPTIONS";
constexpr auto kHead = "HEAD";

}  // namespace method

enum class Version {
    kV1 = 10,
    kV1_1 = 11,
    kV2 = 20,
    kV3 = 30,
};

namespace header {

constexpr auto kAIM = "A-IM";
constexpr auto kAccept = "Accept";
constexpr auto kAcceptCharset = "Accept-Charset";
constexpr auto kAcceptDatetime = "Accept-Datetime";
constexpr auto kAcceptEncoding = "Accept-Encoding";
constexpr auto kAcceptLanguage = "Accept-Language";
constexpr auto kAccessControlRequestMethod = "Access-Control-Request-Method";
constexpr auto kAccessControlRequestHeaders = "Access-Control-Request-Headers";
constexpr auto kAuthorization = "Authorization";
constexpr auto kCacheControl = "Cache-Control";
constexpr auto kConnection = "Connection";
constexpr auto kContentLength = "Content-Length";
constexpr auto kContentMD5 = "Content-MD5";
constexpr auto kContentType = "Content-Type";
constexpr auto kCookie = "Cookie";
constexpr auto kDate = "Date";
constexpr auto kExpect = "Expect";
constexpr auto kForwarded = "Forwarded";
constexpr auto kFrom = "From";
constexpr auto kHost = "Host";
constexpr auto kHTTP2Settings = "HTTP2-Settings";
constexpr auto kIfMatch = "If-Match";
constexpr auto kIfModifiedSince = "If-Modified-Since";
constexpr auto kIfNoneMatch = "If-None-Match";
constexpr auto kIfRange = "If-Range";
constexpr auto kIfUnmodifiedSince = "If-Unmodified-Since";
constexpr auto kMaxForwards = "Max-Forwards";
constexpr auto kOrigin = "Origin";
constexpr auto kPragma = "Pragma";
constexpr auto kPrefer = "Prefer";
constexpr auto kProxyAuthorization = "Proxy-Authorization";
constexpr auto kRange = "Range";
constexpr auto kReferer = "Referer";
constexpr auto kTE = "TE";
constexpr auto kUserAgent = "User-Agent";
constexpr auto kUpgrade = "Upgrade";
constexpr auto kVia = "Via";
constexpr auto kAcceptCH = "Accept-CH";
constexpr auto kAccessControlAllowOrigin = "Access-Control-Allow-Origin";
constexpr auto kAccessControlAllowCredentials = "Access-Control-Allow-Credentials";
constexpr auto kAccessControlExposeHeaders = "Access-Control-Expose-Headers";
constexpr auto kAccessControlMaxAge = "Access-Control-Max-Age";
constexpr auto kAccessControlAllowMethods = "Access-Control-Allow-Methods";
constexpr auto kAccessControlAllowHeaders = "Access-Control-Allow-Headers";
constexpr auto kAcceptPatch = "Accept-Patch";
constexpr auto kAcceptRanges = "Accept-Ranges";
constexpr auto kAge = "Age";
constexpr auto kAllow = "Allow";
constexpr auto kAltSvc = "Alt-Svc";
constexpr auto kContentDisposition = "Content-Disposition";
constexpr auto kContentEncoding = "Content-Encoding";
constexpr auto kContentLanguage = "Content-Language";
constexpr auto kContentLocation = "Content-Location";
constexpr auto kContentRange = "Content-Range";
constexpr auto kDeltaBase = "Delta-Base";
constexpr auto kETag = "ETag";
constexpr auto kExpires = "Expires";
constexpr auto kIM = "IM";
constexpr auto kLastModified = "Last-Modified";
constexpr auto kLink = "Link";
constexpr auto kLocation = "Location";
constexpr auto kP3P = "P3P";
constexpr auto kPreferenceApplied = "Preference-Applied";
constexpr auto kProxyAuthenticate = "Proxy-Authenticate";
constexpr auto kPublicKeyPins = "Public-Key-Pins";
constexpr auto kRetryAfter = "Retry-After";
constexpr auto kServer = "Server";
constexpr auto kSetCookie = "Set-Cookie";
constexpr auto kStrictTransportSecurity = "Strict-Transport-Security";
constexpr auto kTrailer = "Trailer";
constexpr auto kTransferEncoding = "Transfer-Encoding";
constexpr auto kTk = "Tk";
constexpr auto kVary = "Vary";
constexpr auto kWarning = "Warning";
constexpr auto kWWWAuthenticate = "WWW-Authenticate";
constexpr auto kXFrameOptions = "X-Frame-Options";
constexpr auto kKeepAlive= "Keep-Alive";

}  // namespace header

namespace reason {

constexpr auto kContinue = "Continue";
constexpr auto kSwitchingProtocols = "Switching Protocols";
constexpr auto kOK = "OK";
constexpr auto kCreated = "Created";
constexpr auto kAccepted = "Accepted";
constexpr auto kNonAuthoritativeInformation = "Non-Authoritative Information";
constexpr auto kNoContent = "No Content";
constexpr auto kResetContent = "Reset Content";
constexpr auto kPartialContent = "Partial Content";
constexpr auto kMultipleChoices = "Multiple Choices";
constexpr auto kMovedPermanently = "Moved Permanently";
constexpr auto kFound = "Found";
constexpr auto kSeeOther = "See Other";
constexpr auto kNotModified = "Not Modified";
constexpr auto kUseProxy = "Use Proxy";
constexpr auto kTemporaryRedirect = "Temporary Redirect";
constexpr auto kBadRequest = "Bad Request";
constexpr auto kUnauthorized = "Unauthorized";
constexpr auto kPaymentRequired = "Payment Required";
constexpr auto kForbidden = "Forbidden";
constexpr auto kNotFound = "Not Found";
constexpr auto kMethodNotAllowed = "Method Not Allowed";
constexpr auto kNotAcceptable = "Not Acceptable";
constexpr auto kProxyAuthenticationRequired = "Proxy Authentication Required";
constexpr auto kRequesTtimOut = "Request Time-out";
constexpr auto kConflicT = " Conflict";
constexpr auto kGone = "Gone";
constexpr auto kLengthRequired = " Length Required";
constexpr auto kPreconditionFailed = " Precondition Failed";
constexpr auto kRequestEntityTooLarge = " Request Entity Too Large";
constexpr auto kRequestURITooLarge = " Request-URI Too Large";
constexpr auto kUnsupportedMediaType = " Unsupported Media Type";
constexpr auto kRequestedRangeNotSatisfiable = " Requested range not satisfiable";
constexpr auto kExpectationFailed = " Expectation Failed";
constexpr auto kInternalServerError = "Internal Server Error";
constexpr auto kNotImplemented = "Not Implemented";
constexpr auto kBadGateway = "Bad Gateway";
constexpr auto kServiceUnavailable = "Service Unavailable";
constexpr auto kGatewayTimeout = "Gateway Time-out";
constexpr auto kHttpVersionNotSupported = "HTTP Version not supported";

}  // namespace reason

enum class Code {
    kContinue = 100,
    kSwitchingProtocols = 101,
    kOK = 200,
    kCreated = 201,
    kAccepted = 202,
    kNonAuthoritativeInformation = 203,
    kNoContent = 204,
    kResetContent = 205,
    kPartialContent = 206,
    kMultipleChoices = 300,
    kMovedPermanently = 301,
    kFound = 302,
    kSeeOther = 303,
    kNotModified = 304,
    kUseProxy = 305,
    kTemporaryRedirect = 307,
    kBadRequest = 400,
    kUnauthorized = 401,
    kPaymentRequired = 402,
    kForbidden = 403,
    kNotFound = 404,
    kMethodNotAllowed = 405,
    kNotAcceptable = 406,
    kProxyAuthenticationRequired = 407,
    kRequestTimeOut = 408,
    kConflict = 409,
    kGone = 410,
    kLengthRequired = 411,
    kPreconditionFailed = 412,
    kRequestEntityTooLarge = 413,
    kRequestURITooLarge = 414,
    kUnsupportedMediaType = 415,
    kRequestedRangeNotSatisfiable = 416,
    kExpectationFailed = 417,
    kInternalServerError = 500,
    kNotImplemented = 501,
    kBadGateway = 502,
    kServiceUnavailable = 503,
    kGatewayTime_out = 504,
    kHttpVersionNotSupported = 505,
};

}  // namespace ziapi::http
