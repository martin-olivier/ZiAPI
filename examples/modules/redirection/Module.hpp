#pragma once

#include <any>
#include <iostream>

#include "ziapi/Module.hpp"

using namespace ziapi;

class RedirectionModule : public IHandlerModule {
public:
    enum RedirectCode : ushort {
        kMultipleChoice = 300,
        kMovedPermanently,
        kFound,
        kSeeOther,
        kNotModified,
        kUseProxy,
        kSwitchProxy,
        kTemporaryRedirect,
        kPermanentRedirect,
    };

    using routeRedirectionMap = std::map<std::string, std::string>;

    void Init(const Config &cfg)
    {
        if (cfg.find("redirections") != cfg.end())
            _redirections = std::any_cast<routeRedirectionMap>(cfg.at("redirections"));
        if (cfg.find("redirect_code") != cfg.end())
            _status_code = std::any_cast<RedirectCode>(cfg.at("redirect_code"));
    }

    void Handle(http::Request &req, http::Response &res)
    {
        res.fields["Location"] = _redirections[req.target];
        res.status_code = _status_code;
    }

    [[nodiscard]] bool ShouldHandle(const http::Request &req)
    {
        return _redirections.find(req.target) != _redirections.end();
    }

    [[nodiscard]] Version GetVersion() const noexcept { return {0, 1}; }

    [[nodiscard]] Version GetCompatibleApiVersion() const noexcept { return {0, 1}; }

    [[nodiscard]] const char *GetName() const noexcept { return "Redirection Module"; }

    [[nodiscard]] const char *GetDescription() const noexcept { return "Redirects the request to another location."; }

    [[nodiscard]] double GetHandlerPriority() const noexcept { return 0.9; }

private:
    static inline std::map<std::string, std::string> _redirections{};
    static inline RedirectCode _status_code = kMultipleChoice;
};