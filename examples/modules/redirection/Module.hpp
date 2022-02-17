#pragma once

#include <any>
#include <iostream>
#include <string>

#include "ziapi/Module.hpp"

class RedirectionModule : public ziapi::IHandlerModule {
public:
    void Init(const ziapi::config::Node &cfg) override
    {
        /// We'll load from the configuration where to redirect to!
        redirection_route_ = cfg["modules"]["redirection"]["route"];
    }

    void Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res) override
    {
        /// Now we just say that the resource was moved permenatly and we indicate the new
        /// location with the redirection route.
        res.headers[ziapi::http::header::kLocation] = redirection_route_;
        res.status_code = ziapi::http::Code::kMovedPermanently;
    }

    [[nodiscard]] bool ShouldHandle(const ziapi::http::Request &req)
    {
        /// We wish to handle all requests.
        return true;
    }

    [[nodiscard]] double GetHandlerPriority() const noexcept
    {
        /// Our handler is really important!
        return 0.9f;
    }

    [[nodiscard]] ziapi::Version GetVersion() const noexcept { return {3, 0, 0}; }

    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept { return {3, 0, 0}; }

    [[nodiscard]] const char *GetName() const noexcept { return "Redirection Module"; }

    [[nodiscard]] const char *GetDescription() const noexcept { return "Redirects the request to another location."; }

private:
    std::string redirection_route_;
};
