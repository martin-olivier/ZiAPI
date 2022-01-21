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
    // Handler invoked as the response-generation step for the request. For a
    // single HTTP request, only one handler will be invoked. If multiple
    // handler modules try to handle the same request through the ShouldHandle
    // method, only one handler will be invoked.
    virtual void Handle(http::Request &req, http::Response &res) = 0;

    // Whether this module's Handle method should be called on the request.
    [[nodiscard]] virtual bool ShouldHandle(const http::Request &req) = 0;
};

// Post processor modules are invoked after the generation of the response
// by the handler module. They can be used for logging, cors, compression,
// etc.
class IPostProcessorModule : public IModule {
    // Value between zero and one which states the module's priority of
    // execution in the pipeline. Higher values are prioritized.
    [[nodiscard]] virtual double GetPostProcessorPriority() const noexcept = 0;

    // Handler invoked during the post-processing pipeline after the handler.
    virtual void PostProcess(http::Response &res) = 0;

    // Whether this module's PostProcess should be called on the response.
    [[nodiscard]] virtual bool ShouldPostProcess(const http::Response &res) = 0;
};

// Pre processor modules are invoked before the generation of the response by
// the handler module. They can be used for url rewriting, authentication,
// logging, etc.
class IPreProcessorModule : public IModule {
    // Value between zero and one which states the module's priority of
    // execution in the pipeline. Higher values are prioritized.
    [[nodiscard]] virtual double GetPreProcessorPriority() const noexcept = 0;

    // Handler invoked during the pre-processing pipeline before the handler.
    virtual void PreProcess(http::Request &req) = 0;

    // Whether this module's PreProcess method should be called on the request.
    [[nodiscard]] virtual bool ShouldPreProcess(const http::Request &req) = 0;
};

class IPostReceiveModule : public IModule {
};

class IreModule : public IModule {
};

class IParsingModule : public IModule {
};

}  // namespace ziapi
