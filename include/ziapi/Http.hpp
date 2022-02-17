#pragma once

#include <any>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>

#include "HttpConstants.hpp"

namespace ziapi::http {

/**
 *  Struct that represents an HTTP request message
 */
struct Request {
    /// For possible values of version checkout ziapi::http::Version.
    Version version;

    /// The request target contains the route and the query parameters.
    /// The route is simply the path of the request, like `/users/profile`.
    /// The query parameters are the parameters of the request, like `?username=toto&age=18`.
    std::string target;

    /// For possible values of method checkout ziapi::http::method.
    std::string method;

    std::map<std::string, std::string> headers;

    std::string body;
};

/**
 *  Struct that represents an HTTP response message
 */
struct Response {
    /// For possible values of version checkout ziapi::http::Version.
    Version version;

    /// For possible values of version checkout ziapi::http::code.
    Code status_code;

    /// For possible values of version checkout ziapi::http::reason.
    std::string reason;

    std::map<std::string, std::string> headers;

    std::string body;

    void Bootstrap(Code status_code_ = Code::kOK, std::string reason_ = reason::kOK, Version version_ = Version::kV1_1)
    {
        status_code = status_code_;
        reason = reason_;
        version = version_;
    }
};

/**
 *  Context stores the context associated with an HTTP request. It acts like
 *  a key value store to allow inter-module communication
 */
using Context = std::unordered_map<std::string, std::any>;

/**
 *  IResponseInputQueue is a consumer-only container for HTTP responses.
 */
class IResponseInputQueue {
public:
    virtual ~IResponseInputQueue() = default;

    [[nodiscard]] virtual std::optional<std::pair<Response, Context>> Pop() = 0;

    [[nodiscard]] virtual std::size_t Size() const noexcept = 0;
};

/**
 *  IRequestOutputQueue is a consumer-only container for HTTP requests.
 */
class IRequestOutputQueue {
public:
    virtual ~IRequestOutputQueue() = default;

    virtual void Push(std::pair<Request, Context> &&req) = 0;

    [[nodiscard]] virtual std::size_t Size() const noexcept = 0;
};

}  // namespace ziapi::http
