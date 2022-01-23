# Directory Listing Module Tutorial

Let's implement a simple redirection module.

## Purpose

This module will handle incoming http requests and send back a redirection response.
It will allow us to redirect certain routes to other websites or other routes.

For example if we want to redirect our `/google` route to google.com and fetch it like so: 
```
GET /google HTTP/1.1
```

We'll then get this response:
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
    void Init(const ziapi::Config &cfg) override {}

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
We first need to know which routes are going to be redirected to which route or website.
For this example sake, we're going to make every page affected by redirection, redirect with the same status code.
Well, we can add both the status code and the different redircetions as variables of our config file and fetch them in the `Init()` function. We will store them as a `_redirections` and a `_status_code` member variable in our class.

```c++
    /// Our target route as key and the redirection as value
    using routeRedirectionMap = std::map<std::string, std::string>;

    enum RedirectCode : ushort {
        kMultipleChoice = 300,
        kMovedPermanently,
        kFound,
        kSeeOther,
        kNotModified,
        kUseProxy,
        kSwitchProxy,
        kTemporaryRedirect,
        kPermanentRedirect,
    };
...
    void Init(const Config &cfg)
    {
        if (cfg.find("redirections") != cfg.end())
            _redirections = std::any_cast<routeRedirectionMap>(cfg.at("redirections"));
        if (cfg.find("redirect_code") != cfg.end())
            _status_code = std::any_cast<RedirectCode>(cfg.at("redirect_code"));
    }
...
```

Now let's get to the `ShouldHandle()` function, we need this to know if we need to redirect or not !
It's pretty simple, we just need check if the target appears in the config.

```cpp
    [[nodiscard]] bool ShouldHandle([[gnu::unused]] const http::Context &ctx, const http::Request &req) const
    {
        return _redirections.find(req.target) != _redirections.end();
    }
```

Let's now code the `Handle()` method.

It's actually very simple, we just need to change or add our Location header and change the status in the response.

```c++
...    
    void Handle([[gnu::unused]] http::Context &ctx, [[gnu::unused]] const http::Request &req, http::Response &res)
    {
        res.fields["Location"] = _redirections[req.target];
        res.status_code = _status_code;
    }
...
```

You can check the full source code for this example [here](/examples/modules/redirection/Module.hpp).
