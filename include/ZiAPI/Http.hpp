#pragma once

#include <string>
#include <map>

namespace ziapi {

struct HttpRequest {
    int version;
    std::string method;
    std::string target;
    std::map<std::string, std::string> fields;
    std::string body;
};

struct HttpResponse {
    int version;
    int status_code;
    std::string reason;
    std::map<std::string, std::string> fields;
    std::string body;
};

}  // namespace ziapi
