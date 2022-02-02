# Implement a PreProcessor module

In this guide we will learn how to implement a PreProcessor module which is a type of module that allows us to modify an HTTP request before it is handled.

## `IPreProcessorModule` interface

Let's look at the definition of the `IPreProcessorModule` interface.

```c++
class IPreProcessorModule : public IModule {
public:
    virtual void PreProcess(http::Context &ctx, http::Request &req) = 0;

    [[nodiscard]] virtual double GetPreProcessorPriority() const noexcept = 0;

    [[nodiscard]] virtual bool ShouldPreProcess(const http::Context &ctx, const http::Request &req) const = 0;
};
```

We have three methods to implement, let's go!

> :exclamation: Don't forget to implement the `IModule` methods

## Create a pre-processor

Okay, let's create our own class which inherits from `IPreProcessorModule`.

```c++
#include "ziapi/Module.hpp"

class MyPreProcessor : public ziapi::IPreProcessorModule {
public:
    void PreProcess(http::Context &ctx, http::Request &req) override;

    [[nodiscard]] double GetPreProcessorPriority() const noexcept override;

    [[nodiscard]] bool ShouldPreProcess(const http::Context &ctx, const http::Request &req) const override;
};
```

Then, let's implement the `GetPreProcessorPriority()`. Our module doesn't have specific priority requirements so we'll put it at `0.5f`.

```c++
[[nodiscard]] double MyPreProcessor::GetPreProcessorPriority() const noexcept
{
    return 0.5f;
}
```

Then, let's implement the `ShouldPreProcess()`. This method is invoked to know if our pre-processor should be called for a specific request. We can return `true` if we want all requests to go through this pre-processor but let's just say our pre-processor only handles `GET` request for the sake of the example.

```c++
[[nodiscard]] bool ShouldPreProcess(const http::Context &ctx, const http::Request &req) const
{
    return req.method == http::method::kGet;
}
```

Great! Now our pre-processor will be called on all GET requests! Now let's add the `PreProcess()`.

```c++
void MyPreProcessor::PreProcess(http::Context &ctx, http::Request &req)
{
    req.method = http::method::kPost;
}
```

And that's it! You now have a module which transforms all `GET` requests to `POST` requests in order to completely break your API ^^.
