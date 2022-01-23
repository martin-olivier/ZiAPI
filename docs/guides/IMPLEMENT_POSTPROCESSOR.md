# Implement a PostProcessor module

In this guide we will learn how to implement a PostProcessor module which is a type of module that allows us to modify an HTTP response from a current response.

## `IPostProcessorModule` interface

Let's look at the definition of the `IPostProcessorModule` interface (simplified).

```c++
class IPostProcessorModule : public IModule {
public:
    void PostProcess(http::Context &ctx, http::Response &res);

    double GetPostProcessorPriority() const;

    bool ShouldPostProcess(const http::Context &ctx, const http::Response &res) const;
};
```

We have three methods to implement, let's go!

## Create a post-processor

Okay, let's create our own class which inherits from `IPostProcessorModule`.

```c++
#include "ziapi/Module.hpp"

class MyPostProcessor : public ziapi::IPostProcessorModule {
public:
    [[nodiscard]] double GetPostProcessorPriority() const noexcept override;

    [[nodiscard]] bool ShouldHandle(const http::Context &ctx, const ziapi::http::Request &req);

    void Handle(http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res);
}
```

Then, let's implement the `GetPostProcessorPriority()`. Our module doesn't have specific priority requirements so we'll put it at `0.5f`.

```c++
double MyPostProcessor::GetPostProcessorPriority() const noexcept
{
    return 0.5f;
}
```

Then, let's implement the `ShouldHandle()`. This method is invoked to know if our post-processor should be called for a specific request. We can return `true` if we want all requests to go through this post-processor but let's just say our post-processor only handles `GET` request for the sake of the example.

```c++
bool MyPostProcessor::ShouldHandle(const http::Context &ctx, const ziapi::http::Request &req)
{
    return req.method == ziapi::http::method::GET;
}
```

Great! Now our post-processor will be called on all GET requests! Now let's add the `Handle()`.

```c++
void MyPostProcessor::Handle(http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
    res.status_code = 200;
    res.body = "Hello guys!";
}
```

And that's it! You now have a module which displays `"Hello guys!"` in your browser upon all `GET` requests.
