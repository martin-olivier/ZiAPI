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

static const char *GET = "GET";
static const char *POST = "POST";
static const char *PUT = "PUT";
static const char *DELETE = "DELETE";
static const char *PATCH = "PATCH";
static const char *OPTIONS = "OPTIONS";
static const char *HEAD = "HEAD";

}  // namespace method

}  // namespace ziapi::http
