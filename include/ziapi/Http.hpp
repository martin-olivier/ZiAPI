#pragma once

#include <any>
#include <map>
#include <string>

namespace ziapi::http {

/// Response represents an HTTP request message.
struct Request {
    int version;
    std::string method;
    std::string target;
    std::map<std::string, std::string> fields;
    std::string body;
};

/// Response represents an HTTP response message.
struct Response {
    int version;
    int status_code;
    std::string reason;
    std::map<std::string, std::string> fields;
    std::string body;
};

/// IContext stores the context associated with an HTTP request. It acts like
/// a key value store to allow inter-module communication.
class IContext {
public:
    virtual void Set(const std::string &key, std::any value) = 0;

    virtual std::any Get(const std::string &key) = 0;
};

/// IResponseInputQueue is a consumer-only container for HTTP responses.
class IResponseInputQueue {
public:
    virtual std::pair<Request, IContext> Pop() = 0;

    virtual std::size_t Size() = 0;

    /// Wait for content to be available to be popped from the queue.
    virtual void Wait() = 0;
};

/// IResponseInputQueue is a producer-only container for HTTP requests.
class IRequestOutputQueue {
public:
    virtual void Push(std::pair<Request, IContext> &&req) = 0;

    virtual std::size_t Size() = 0;
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
