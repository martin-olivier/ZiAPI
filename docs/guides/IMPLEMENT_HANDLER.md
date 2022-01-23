# Implement a Handler module

In this guide we will learn how to implement a Handler module which is a type of module that allows us to generate an HTTP response from a request.

## `IHandlerModule` interface

Let's look at the definition of the `IHandlerModule` interface.

```c++
class IHandlerModule : public IModule {
public:
    virtual void Handle(http::Request &req, http::Response &res) = 0;

    [[nodiscard]] virtual double GetHandlerPriority() const noexcept = 0;

    [[nodiscard]] virtual bool ShouldHandle(const http::Context &ctx, const http::Request &req) const = 0;
};
```

We have three methods to implement, let's go!

> :exclamation: Don't forget to implement the `IModule` methods

## Create a handler

Okay, let's create our own class which inherits from `IHandlerModule`.

```c++
#include "ziapi/Module.hpp"

class MyHandler : public ziapi::IHandlerModule {
public:
    void Handle(http::Context &ctx, const http::Request &req, http::Response &res) override;

    [[nodiscard]] double GetHandlerPriority() const noexcept override;

    [[nodiscard]] bool ShouldHandle(const http::Context &ctx, const http::Request &req) const override;
};
```

Then, let's implement the `GetHandlerPriority()`. Our module doesn't have specific priority requirements so we'll put it at `0.5f`.

```c++
[[nodiscard]] double MyHandler::GetHandlerPriority() const noexcept
{
    return 0.5f;
}
```

Then, let's implement the `ShouldHandle()`. This method is invoked to know if our handler should be called for a specific request. We can return `true` if we want all requests to go through this handler but let's just say our handler only handles `GET` request for the sake of the example.

```c++
[[nodiscard]] bool MyHandler::ShouldHandle(const http::Context &ctx, const http::Request &req) const
{
    return req.method == http::method::GET;
}
```

Great! Now our handler will be called on all GET requests! Now let's add the `Handle()`.

```c++
void MyHandler::Handle(http::Context &ctx, const http::Request &req, http::Response &res)
{
    res.status_code = 200;
    res.body = "Hello guys!";
}
```

And that's it! You now have a module which displays `"Hello guys!"` in your browser upon all `GET` requests.
