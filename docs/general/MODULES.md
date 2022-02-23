# Modules Documentation

The ZIAPI features 4 different types of modules:
- `INetworkModule`
- `IPreProcessorModule`
- `IHandlerModule`
- `IPostProcessorModule`

Each module is invoked at a different stage in the request lifecycle. If you remember from the [Getting started](GETTING_STARTED.md) page of the documentation, a request goes through 5 different steps when received by our HTTP server. Let's see which steps correspond to which module.
- **1. Receive** step is handled by `INetworkModule`.
- **2. Pre-process** step is handled by `IPreProcessorModule`.
- **3. Handle** step is handled by `IHandlerModule`.
- **4. Post-process** step is handled by `IPostProcessorModule`.
- **5. Send** step is handled by `INetworkModule`.

We'll see each of these modules types detail, but first, let's look at the `IModule` interface.

## The `IModule` interface

Each **ZIAPI** module type inherits from `IModule`. It features very basic methods to make it easier to manage modules.

```c++
virtual void Init(const Config &cfg) = 0;

[[nodiscard]] virtual Version GetVersion() const noexcept = 0;

[[nodiscard]] virtual Version GetCompatibleApiVersion() const noexcept = 0;

[[nodiscard]] virtual const char *GetName() const noexcept = 0;

[[nodiscard]] virtual const char *GetDescription() const noexcept = 0;
```

There's not much to say about this interface. Every module must implement it so we can have access to its version, name, description...

## `INetworkModule`

The `Run()` method starts the module, providing it with an output queue in which it shall push incoming requests and an input queue from which it should receive incoming responses and send them over the network. So basically, inside the run method, you should create your sockets, spin up your http parser and wait for incoming requests! This method is intended to run forever!

```c++
virtual void Run(http::IRequestOutputQueue &requests, http::IResponseInputQueue &responses);
```

The `Terminate()` method will be invoked upon reloading or termination of the server, it notifies the module that it needs to stops running altogether and release every resource it has created. So this is the time where you should **close** all your sockets and return the flow of control to the caller of your `Run` method.

```c++
virtual void Terminate() = 0;
```

## `IPreProcessorModule`

The `PreProcess()` is the method invoked on a request before the handler is called. You can use pre-processor to modify the request's data (add / remove headers, etc...)

```c++
virtual void PreProcess(http::Context &ctx, http::Request &req) = 0;
```

The `GetPreProcessorPriority()` method returns the priority of the module between zero and one. Pre-processors with a higher priority are executed first!

```c++
[[nodiscard]] virtual double GetPreProcessorPriority() const noexcept = 0;
```

The `ShouldPreProcess()` method returns `true` if this module's PreProcess method should be called on the request. For example you can choose that your module will only pre-process requests with a `Content-Type: application/json` header.

```c++
[[nodiscard]] virtual bool ShouldPreProcess(const http::Context &ctx, const http::Request &req) const = 0;
```

## `IPostProcesserModule`

The `PostProcess()` is the method invoked on a response after the handler is called. You can use post-processors to modify the response after it is generated (serializing the body, logging the response, etc...).

```c++
virtual void PostProcess(http::Context &ctx, http::Response &res) = 0;
```

The `GetPostProcessorPriority()` method returns the priority of the module between zero and one. Post-processors with a higher priority are executed first!

```c++
[[nodiscard]] virtual double GetPostProcessorPriority() const noexcept = 0;
```

The `ShouldPostProcess()` method returns `true` if this module's PostProcess should be called on the response. For example you can choose that your module will only post-process responses with a status code over `399` to log them to the console!

```c++
[[nodiscard]] virtual bool ShouldPostProcess(const http::Context &ctx, const http::Request &req, const http::Response &res) const = 0;
```

## `IHandlerModule`

The `Handle()` method is invoked on a request in order to generate a response. It's like any typical web framework you can find: you get access to the incoming request and you're in charge of generating a response!

```c++
virtual void Handle(http::Context &ctx, const http::Request &req, http::Response &res) = 0;
```

The `GetHandlerPriority()` sets the module's priority of execution. If you have two handlers in your API which both want to handle a particular request, only the handler with the highest priority will be called.

```c++
[[nodiscard]] virtual double GetHandlerPriority() const noexcept = 0;
```

The `ShouldHandle()` is used to determin if your module **wants** to handle a specific request. For example, you may have a module which only handles `GET` requests, or requests with a specific header, etc...

```c++
[[nodiscard]] virtual bool ShouldHandle(const http::Context &ctx, const http::Request &req) const = 0;
```
