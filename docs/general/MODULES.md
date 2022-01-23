# Modules Documentation

The ZIAPI features 4 different types of modules:
- `INetworkModule`
- `IPreProcessorModule`
- `IHandlerModule`
- `IPostProcessorModule`

Each module is invoked at a different stage in the request lifecycle. If you remember from the [Getting started](GETTING_STARTED.md) page of the documentation, a goes through 5 different steps when received by our HTTP server. Let's see which steps correspond to which module.
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

## `IPreProcessorModule`

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

## `IPostProcessorModule`
