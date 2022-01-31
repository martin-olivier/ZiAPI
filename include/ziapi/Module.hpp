#pragma once

#include <functional>
#include <ostream>

#include "Config.hpp"
#include "Http.hpp"
#include "Version.hpp"

namespace ziapi {

class IModule {
public:
    virtual ~IModule() = default;

    virtual void Init(const config::Node &cfg) = 0;

    [[nodiscard]] virtual Version GetVersion() const noexcept = 0;

    [[nodiscard]] virtual Version GetCompatibleApiVersion() const noexcept = 0;

    [[nodiscard]] virtual const char *GetName() const noexcept = 0;

    [[nodiscard]] virtual const char *GetDescription() const noexcept = 0;
};

/**
 *  Handler modules handle HTTP requests and are responsible for generating
 *  the contents of the response such as a directory listing module, a web
 *  server module, etc...
 */
class IHandlerModule : public IModule {
public:
    virtual ~IHandlerModule() = default;

    /**
     *  Handler invoked as the response-generation step for the request. For a
     *  single HTTP request, only one handler will be invoked. If multiple
     *  handler modules try to handle the same request through the ShouldHandle
     *  method, only one handler with the highest priority will be invoked
     */
    virtual void Handle(http::Context &ctx, const http::Request &req, http::Response &res) = 0;

    /**
     *  Value between zero and one which states the module's priority. Higher
     *  values are prioritized
     */
    [[nodiscard]] virtual double GetHandlerPriority() const noexcept = 0;

    /**
     *  Whether this module's Handle method should be called on the request
     */
    [[nodiscard]] virtual bool ShouldHandle(const http::Context &ctx, const http::Request &req) const = 0;
};

/**
 *  Post processor modules are invoked after the generation of the response
 *  by the handler module. They can be used for logging, cors, compression, etc...
 */
class IPostProcessorModule : public IModule {
public:
    virtual ~IPostProcessorModule() = default;
    /**
     *  Handler invoked during the post-processing pipeline after the handler.
     */
    virtual void PostProcess(http::Context &ctx, http::Response &res) = 0;

    /**
     *  Value between zero and one which states the module's priority of
     *  execution in the pipeline. Higher values are prioritized
     */
    [[nodiscard]] virtual double GetPostProcessorPriority() const noexcept = 0;

    /**
     *  Whether this module's PostProcess should be called on the response
     */
    [[nodiscard]] virtual bool ShouldPostProcess(const http::Context &ctx, const http::Response &res) const = 0;
};

/**
 *  Pre processor modules are invoked before the generation of the response by
 *  the handler module. They can be used for url rewriting, authentication, logging, etc...
 */
class IPreProcessorModule : public IModule {
public:
    virtual ~IPreProcessorModule() = default;
    /**
     *  Handler invoked during the pre-processing pipeline before the handler
     */
    virtual void PreProcess(http::Context &ctx, http::Request &req) = 0;

    /**
     *  Value between zero and one which states the module's priority of
     *  execution in the pipeline. Higher values are prioritized
     */
    [[nodiscard]] virtual double GetPreProcessorPriority() const noexcept = 0;

    /**
     *  Whether this module's PreProcess method should be called on the request
     */
    [[nodiscard]] virtual bool ShouldPreProcess(const http::Context &ctx, const http::Request &req) const = 0;
};

class INetworkModule : public IModule {
public:
    virtual ~INetworkModule() = default;
    /**
     *  Run starts the module providing it with an output queue in which it
     *  shall push incoming requests and an input queue from which it should
     *  receive incoming responses and send them over the network
     */
    virtual void Run(http::IRequestOutputQueue &requests, http::IResponseInputQueue &responses) = 0;

    /**
     *  Terminate will be invoked upon reloading or termination of the server,
     *  it notifies the module that it needs to stops running altogether and
     *  release every resource it has created
     */
    virtual void Terminate() = 0;
};

}  // namespace ziapi
