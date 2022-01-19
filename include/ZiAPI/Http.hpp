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
