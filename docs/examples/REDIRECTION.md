# Redirection Module Tutorial

Let's implement a simple redirection module.

## Purpose

This module will handle incoming http requests and send back a redirection response.
For example we might want to redirect all requests to `google.com`.

So for the following incoming request:
```
GET /google HTTP/1.1
```

We'll then get the following response:
```
HTTP/1.1 301 Moved Permanently
Location: www.google.com
``` 

## Tutorial

First, let's implement the `IHandlerModule` interface base.

```c++
#include "ziapi/Module.hpp"

class PhpCgiModule : public ziapi::IHandlerModule {
public:
    void Init(const ziapi::config::Node &cfg) override {}

    [[nodiscard]] Version GetVersion() const noexcept { return {0, 1}; }

    [[nodiscard]] Version GetCompatibleApiVersion() const noexcept { return {0, 1}; }

    [[nodiscard]] const char *GetName() const noexcept { return "Redirection Module"; }

    [[nodiscard]] const char *GetDescription() const noexcept { return "Redirects the request to another location."; }

    [[nodiscard]] double GetHandlerPriority() const noexcept { 
        // Directions should be treated in priority
        return 0.9; 
    }

    void Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res) override {}
};
```

Let's give our module a configuration.
Let's load from the config the route to which we will redirect requests. We'll store the value in a member variable of our module called `redirection_route_`.

```c++
...

void Init(const Config &cfg)
{
    /// We'll load from the configuration where to redirect to!
    redirection_route_ = cfg.AsDict()["modules"]->AsDict()["redirection"]->AsDict()["route"]->AsString();
}

...
```

We want to redirect all requests so we just return `true` in our `ShouldHandle()`.

```cpp
...

[[nodiscard]] bool ShouldHandle(const http::Context &, const http::Request &req) const
{
    return true;
}

...
```

Let's now implement the `Handle()` method. We simply redirect each request to the `redirection_route_` by changing the `Location` header on the response. We also set the appropriate status code.

```c++
...

void Handle(http::Context &, const http::Request &, http::Response &res)
{
    res.fields[ziapi::http::header::kLocation] = redirection_route_;
    res.status_code = ziapi::http::code::kMovedPermanently;
}

...
```

You can check the full source code for this example [here](/examples/modules/redirection/Module.hpp).
