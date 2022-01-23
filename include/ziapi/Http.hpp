#pragma once

#include <any>
#include <map>
#include <string>

namespace ziapi::http {

/**
 *  Struct that represents an HTTP request message
 */
struct Request {
    int version;
    std::string method;
    std::string target;
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

namespace method {

constexpr auto GET = "GET";
constexpr auto POST = "POST";
constexpr auto PUT = "PUT";
constexpr auto DELETE = "DELETE";
constexpr auto PATCH = "PATCH";
constexpr auto OPTIONS = "OPTIONS";
constexpr auto HEAD = "HEAD";

}  // namespace method

}  // namespace ziapi::http
