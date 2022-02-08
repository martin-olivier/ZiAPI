#pragma once

#include <any>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>

#include "HttpConstants.hpp"

namespace ziapi::http {

struct Version {
    Version(int major, int minor) : major(major), minor(minor) {}

    inline bool operator==(const Version &other) const noexcept { return major == other.major && minor == other.minor; }

    inline bool operator!=(const Version &other) const noexcept { return !(*this == other); }

    inline bool operator>(const Version &other) const noexcept { return (*this >= other) && (*this != other); }

    inline bool operator<(const Version &other) const noexcept { return !(*this > other) && other != *this; }

    inline bool operator>=(const Version &other) const noexcept
    {
        return (major == other.major ? minor == other.minor ? true : minor > other.minor : major > other.major);
    }

    inline bool operator<=(const Version &other) const noexcept { return (*this < other) || (*this == other); }

    unsigned int major;
    unsigned int minor;
};

/**
 *  Struct that represents an HTTP request message
 */
struct Request {
    /// For possible values of version checkout ziapi::http::version.
    Version version;

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
    Version version;

    /// For possible values of version checkout ziapi::http::code.
    Code status_code;

    /// For possible values of version checkout ziapi::http::reason.
    std::string reason;

    std::map<std::string, std::string> fields;

    std::string body;

    void Bootstrap(Code status_code = Code::kOK, std::string reason = reason::kOK, Version version = Version::kV1_1)
    {
        this->status_code = status_code;
        this->reason = reason;
        this->version = version;
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
