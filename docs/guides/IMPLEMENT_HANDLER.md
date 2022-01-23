# Implement a Handler module

In this guide we will learn how to implement a Handler module which is a type of module that allows us to generate an HTTP response from a request.

## `IHandlerModule` interface

Let's look at the definition of the `IHandlerModule` interface (simplified).

```c++
class IHandlerModule : public IModule {
public:
    void Handle(http::Request &req, http::Response &res) = 0;

    double GetHandlerPriority() const = 0;

    bool ShouldHandle(const http::Request &req) = 0;
};
```

We have three methods to implement, let's go!

## Create a handler

Okay, let's create our own class which inherits from `IHandlerModule`.

```c++
#include "ziapi/Module.hpp"

class MyHandler : public ziapi::IHandlerModule {
public:
    [[nodiscard]] double GetHandlerPriority() const noexcept override;

    [[nodiscard]] bool ShouldHandle(const http::Context &ctx, const ziapi::http::Request &req);

    void Handle(http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res);
}
```

Then, let's implement the `GetHandlerPriority()`. Our module doesn't have specific priority requirements so we'll put it at `0.5f`.

```c++
double MyHandler::GetHandlerPriority() const noexcept
{
    return 0.5f;
}
```

Then, let's implement the `ShouldHandle()`. This method is invoked to know if our handler should be called for a specific request. We can return `true` if we want all requests to go through this handler but let's just say our handler only handles `GET` request for the sake of the example.

```c++
bool MyHandler::ShouldHandle(const http::Context &ctx, const ziapi::http::Request &req)
{
    return req.method == ziapi::http::method::GET;
}
```

Great! Now our handler will be called on all GET requests! Now let's add the `Handle()`.

```c++
void MyHandler::Handle(http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
    res.status_code = 200;
    res.body = "Hello guys!";
}
```

And that's it! You now have a module which displays `"Hello guys!"` in your browser upon all `GET` requests.
