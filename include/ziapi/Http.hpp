#pragma once

#include <any>
#include <map>
#include <unordered_map>
#include <string>

#include "HttpConstants.hpp"

namespace ziapi::http {

/**
 *  Struct that represents an HTTP request message
 */
struct Request {
    /// For possible values of version checkout ziapi::http::version.
    int version;

    /// For possible values of method checkout ziapi::http::method.
    std::string method;

    std::string target;

    std::map<std::string, std::string> fields;

    std::string body;
};

/**
 *  Struct that represents an HTTP response message
 */
struct Response {
    /// For possible values of version checkout ziapi::http::version.
    int version;

    /// For possible values of version checkout ziapi::http::code.
    int status_code;

    /// For possible values of version checkout ziapi::http::reason.
    std::string reason;

    std::map<std::string, std::string> fields;

    std::string body;

    void Bootstrap(int status_code = CODE::OK, std::string reason = reason::OK, int version = VERSION::V1_1);
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

    virtual std::pair<Request, Context> Pop() = 0;

    [[nodiscard]] virtual std::size_t Size() const noexcept = 0;
};

/**
 *  IRequestOutputQueue is a consumer-only container for HTTP responses.
 */
class IRequestOutputQueue {
public:
    virtual ~IRequestOutputQueue() = default;

    virtual void Push(std::pair<Request, Context> &&req) = 0;

    [[nodiscard]] virtual std::size_t Size() const noexcept = 0;
};

}  // namespace ziapi::http
