#pragma once

#include <map>
#include <string>

namespace ziapi::http {

struct Request {
    int version;
    std::string method;
    std::string target;
    std::map<std::string, std::string> fields;
    std::string body;
};

struct Response {
    int version;
    int status_code;
    std::string reason;
    std::map<std::string, std::string> fields;
    std::string body;
};

class IResponseInputQueue {
public:
    virtual Response Pop() = 0;

    virtual std::size_t Size() = 0;

    /// Wait for content to be available to be popped from the queue.
    virtual void Wait() = 0;
};

class IRequestOutputQueue {
public:
    virtual void Push(Request &&req) = 0;

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
