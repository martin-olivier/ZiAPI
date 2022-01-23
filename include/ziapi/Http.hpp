#pragma once

#include <any>
#include <map>
#include <string>

#include "Constants.hpp"

namespace ziapi::http {

/**
 *  Struct that represents an HTTP request message
 */
struct Request {
    /// Versions are described using an integer as per the boost implemetation
    /// of HTTP.
    /// 1.0 => 10
    /// 1.1 => 11
    /// 2.0 => 20
    /// 3.0 => 20
    int version;

    /// The HTTP request's method (GET, PUT, PATCH, OPTIONS, DELETE, HEAD)
    std::string method;

    /// The requests' headers fields.
    std::string target;

    /// The requests' headers.
    std::map<std::string, std::string> fields;

    std::string body;
};

/**
 *  Struct that represents an HTTP response message
 */
struct Response {
    int version;
    int status_code;
    std::string reason;
    std::map<std::string, std::string> fields;
    std::string body;
};

/**
 *  Context stores the context associated with an HTTP request. It acts like
 *  a key value store to allow inter-module communication
 */
using Context = std::map<std::string, std::any>;

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
