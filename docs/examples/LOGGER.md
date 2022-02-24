# Logger Module Tutorial

Let's implement a simple logger module.

## Purpose

This module will log every requests that goes through our API and their state.

For example, for the following request:
```
GET /users/notfound HTTP/1.1
```

Our module will log the status code, the time the request took, the reason and the target, so we could have an output like:
```
 [X] 404: Not found exception (GET /users/notfound HTTP/1.1, 4.02s)
```

## Tutorial

This module is going to be a little special. It's going to have **two types**, it's going to be a post-processor **and** a pre-processor. We'll use diamond heritage for this!

Let's implement the `IPreProcessorModule` and the `IPostProcessorModule` interfaces.
We want it to log every request, so we'll return `true` in `ShouldPreProcess` and `ShouldPostProcess`.
We set the pre-processing priority to 0 so it is the first module called.
We set the post-processing priority to 1 so it is also the last module called.
```cpp

class LoggerModule : virtual public ziapi::IPreProcessorModule, public ziapi::IPostProcessorModule {
public:
    void Init(const ziapi::config::Node &cfg) {}

    [[nodiscard]] ziapi::Version GetVersion() const noexcept override { return {1, 0}; }

    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override { return {1, 0}; }

    [[nodiscard]] const char *GetName() const noexcept override { return "LoggerModule"; }

    [[nodiscard]] const char *GetDescription() const noexcept override
    {
        return "Log all responses from HTTP requests";
    }

    [[nodiscard]] double GetPostProcessorPriority() const noexcept override { return 1; }

    [[nodiscard]] bool ShouldPostProcess(const ziapi::http::Context &ctx, const ziapi::http::Request &req, const ziapi::http::Response &res) const override
    {
        return true;
    }

    [[nodiscard]] double GetPreProcessorPriority() const noexcept override { return 0; }

    [[nodiscard]] bool ShouldPreProcess(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const override
    {
        return true;
    }

    // ...
}
```
Then, first thing we want is to store the timestamp when the request is received so we can time it. We'll store that timestamp in the request context to fetch it later.

```cpp
...

void PreProcess(ziapi::http::Context &ctx, ziapi::http::Request &req) override
{
    ctx["timestamp"] = std::time(nullptr);
    ctx["target"] = req.target;
    ctx["method"] = req.method;
}

...
```
And now in the post-process we can just simply access our variables and use them :smile:
```cpp
...

void PostProcess(ziapi::http::Context &ctx, ziapi::http::Response &res) override
{
    std::stringstream ss;

    // Example: ` [X] 404: Not found (GET /test, 2.02s)`
    ss << std::to_string(res.status_code) << ": " << res.reason << " (" << std::any_cast<std::string>(ctx["method"])
        << " " << std::any_cast<std::string>(ctx["target"]) << ", " << std::setprecision(2)
        << difftime(std::time(nullptr), std::any_cast<time_t>(ctx["timestamp"])) << "s)";
    if (res.status_code < 300) {
        ziapi::Logger::Info(ss.str());
    } else if (res.status_code < 400) {
        ziapi::Logger::Warning(ss.str());
    } else {
        ziapi::Logger::Error(ss.str());
    }
}

...
```
You can check the full source code for this example [here](/examples/modules/logger/LoggerModule.hpp).
