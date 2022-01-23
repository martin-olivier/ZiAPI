# Implement a PostProcessor module

In this guide we will learn how to implement a PostProcessor module which is a type of module that allows us to modify an HTTP response from a current response.

## `IPostProcessorModule` interface

Let's look at the definition of the `IPostProcessorModule` interface.

```c++
class IPostProcessorModule : public IModule {
public:
    virtual void PostProcess(http::Context &ctx, http::Response &res) = 0;

    [[nodiscard]] virtual double GetPostProcessorPriority() const noexcept = 0;

    [[nodiscard]] virtual bool ShouldPostProcess(const http::Context &ctx, const http::Response &res) const = 0;
};
```

We have three methods to implement, let's go!

> :exclamation: Don't forget to implement the `IModule` methods

## Create a post-processor

Okay, let's create our own class which inherits from `IPostProcessorModule`.

```c++
#include "ziapi/Module.hpp"

class MyPostProcessor : public ziapi::IPostProcessorModule {
public:
    void PostProcess(http::Context &ctx, http::Response &res) override;

    [[nodiscard]] double GetPostProcessorPriority() const noexcept override;

    [[nodiscard]] bool ShouldPostProcess(const http::Context &ctx, const http::Response &res) const override;
};
```

Then, let's implement the `GetPostProcessorPriority()`. Our module doesn't have specific priority requirements so we'll put it at `0.5f`.

```c++
[[nodiscard]] double MyPostProcessor::GetPostProcessorPriority() const noexcept
{
    return 0.5f;
}
```

Then, let's implement the `ShouldPostProcess()`. This method is invoked to know if our post-processor should be called for a specific request. We can return `true` if we want all requests to go through this post-processor but let's just say our post-processor only handles `status code` inferior to 400 for the sake of the example.

```c++
[[nodiscard]] bool ShouldPostProcess(const http::Context &ctx, const http::Response &res) const
{
    return res.status_code < 400;
}
```

Great! Now our post-processor will be called on all GET requests! Now let's add the `PostProcess()`.

```c++
void MyPostProcessor::PostProcess(http::Context &ctx, http::Response &res)
{
    res.status_code = 200;
    res.body = "Hello guys!";
}
```

And that's it! You now have a module which displays `"Hello guys!"` in your browser upon all `GET` requests.
