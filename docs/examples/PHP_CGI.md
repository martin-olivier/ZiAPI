# PHP-CGI Module Tutorial

Let's implement a simple php-cgi module.

## Purpose

This module will handle incoming http requests and serve the file contained in the request's target field and will then execute any PHP code contained in it. Headers modifications are taken into account aswell.
For example purposes, the handler will be called on every HTTP request made to the server.

For example, for the following request:
```
GET /test.php HTTP/1.1
```

Our module will open `test.php` executes the PHP code and respond the modified body aswell as the modified headers.

## Tutorial

First, let's implement the `IHandlerModule` interface. We specify that the module should run everytime.

```c++
#include "ziapi/Module.hpp"

class PhpCgiModule : public ziapi::IHandlerModule {
public:
    void Init(const ziapi::Config &cfg) override {}

    [[nodiscard]] ziapi::Version GetVersion() const noexcept override { return {0, 1}; }

    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override { return {1, 0}; }

    [[nodiscard]] const char *GetName() const noexcept override { return "PHP-CGI"; }

    [[nodiscard]] const char *GetDescription() const noexcept override { return "Executes PHP"; }

    [[nodiscard]] double GetHandlerPriority() const noexcept override
    {
        /// Our module doesn't have any specific priority requirements.
        return 0.5f;
    }

    [[nodiscard]] bool ShouldHandle(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const override
    {
        /// We want to handle every requests
        return true;
    }

    void Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res) override {}
};
```

First thing we want to do is make our module configurable. 

In order to execute php, we need access to the `php-cgi` bin, so we must know it's path.
Secondly, imagine we want the routing to serve a specific directory on our computer. Let's say we want to make the `./scripts`'s directory available for the module to search files.

Well, we can add both path as variables of our config file and fetch them in the `Init()` function. We will store them as a `_root` and a `_bin_path` member variable in our class.

```c++
...

void Init(const ziapi::Config &cfg) override
{
    /// In our config, we must specify which folder our module serves.
    _root = std::any_cast<std::string>(cfg.at("root"));
    
    /// We must sepcify the `php-cgi` bin path aswell
    _bin_path = std::any_cast<std::string>(cfg.at("bin_path"));
    
    /// In case of a more concrete example, you should scope your config keys
    /// Example : cfg.at("modules.php-cgi.root")
    
}

...
```

Let's now code the `Handle()` method. We first obtain the path of the file we want to fetch to give to `php-cgi`, we're going to use `popen` in order to do so.

`ProcessOutput` is a function that will take the pipe's output (so the `php-cgi` command's output) and split the headers and body in an `std::pair`, `std::tie` can help us extract the pair in two variables. In our case we fill our body by giving it as a reference and the headers in an intermediary `headers` string.

Then, depending if there's no output, `InternalError` will send a 500 status code and an error string, otherwise we'll call `ProcessHeaders` that fills the reponse's header accordingly.

You can check the `Module.hpp` source file to see those last three functions in details.


```c++
...
    using unique_ptr_pipe_t = std::unique_ptr<FILE, decltype(&PCLOSE)>;
...
 void Handle([[gnu::unused]] http::Context &ctx, const http::Request &req, http::Response &res)
    {
        const auto filepath = std::filesystem::path(_root) / std::filesystem::path(req.target);
        const std::string command = "(" + _bin_path + " < " + filepath.string() + ") 2> /dev/null";
        unique_ptr_pipe_t command_pipe(POPEN(command.c_str(), "r"), PCLOSE);
        std::string headers;

        if (!command_pipe)
            InternalError(res);
        else
        {
            std::tie(res.body, headers) = ProcessOutput(command_pipe);
            if (res.body.empty() && headers.empty())
                InternalError(res);
            else
                ProcessHeaders(headers, res.fields);
        }
    }
...
```

You can check the full source code for this example [here](/examples/modules/php-cgi/PhpCgiModule.hpp).
