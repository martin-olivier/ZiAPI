#pragma once

#include <ostream>

#include "Http.hpp"

namespace ziapi {

class IModule {
public:
    struct Version {
        int major;
        int minor;
    };

    enum class Type {
        REQUEST_HANDLER,
        PRESENTATION_HANDLER,
    };

    virtual void Init() = 0;

    virtual Version GetVersion() = 0;

    virtual Type GetType() = 0;

    virtual std::string GetDescription() = 0;

    virtual void Dispose() = 0;
};

class IHandlerModule : public IModule {
public:
    virtual int GetPriority() = 0;

    virtual void HandleRequest(HttpRequest &req, HttpResponse &res) = 0;
};

class IPresentationModule : public IModule {
    virtual void HandleInbound(std::istream &in, HttpRequest &req) = 0;

    virtual void HandleOutbound(std::ostream &out, HttpResponse &res) = 0;
};

}  // namespace ziapi
