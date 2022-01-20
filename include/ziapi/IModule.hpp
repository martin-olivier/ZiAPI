#pragma once

#include <ostream>

#include "Http.hpp"
#include "IConfig.hpp"
#include "Version.hpp"

namespace ziapi {

class IModule {
public:
    virtual ~IModule() = default;

    virtual void Init(const IConfig &cfg) = 0;

    [[nodiscard]] virtual Version GetVersion() const noexcept = 0;

    [[nodiscard]] virtual Version GetCompatibleApiVersion() const noexcept = 0;

    [[nodiscard]] virtual char *GetName() const noexcept = 0;

    [[nodiscard]] virtual char *GetDescription() const noexcept = 0;
};

// Handler modules handle HTTP requests and are responsible for generating
// the contents of the response such as a directory listing module, a web
// server module, etc...
class IHandlerModule : public IModule {
public:
    virtual void GetHandlerPriority() = 0;

    virtual void Handle(http::Request &req, http::Response &res) = 0;
};

// Post processor modules are invoked after the generation of the body of the
// response by the handler modules. They can be used for logging, cors, etc.
class IPostProcessorModule : public IModule {
    virtual void GetPostProcessorPriority() = 0;

    virtual void PostProcess(http::Request &req) = 0;
};

// Pre
class IPreProcessorModule : public IModule {
    virtual void GetPreProcessorPriority() = 0;

    virtual void PreProcess(http::Response &res) = 0;
};

class IReaderModule : public IModule {
};

class IWriterModule : public IModule {
};

}  // namespace ziapi
