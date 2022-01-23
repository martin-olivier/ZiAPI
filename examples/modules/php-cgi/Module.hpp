#pragma once

#include <any>
#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>

#include "ziapi/Module.hpp"

using namespace ziapi;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define POPEN _popen
#define PCLOSE _pclose
#define FGETS _fgets
#else
#define POPEN popen
#define PCLOSE pclose
#define FGETS fgets
#endif

class PhpCgiModule : public IHandlerModule
{
private:
    static const inline std::string kHeaderBodySeparator = "\r\n\r\n";
    static constexpr uint16_t kBufferSize = 1024;

public:
    void Init(const Config &cfg)
    {
        if (cfg.find("bin_path") != cfg.end())
            _bin_path = std::any_cast<std::string>(cfg.at("bin_path"));
        if (cfg.find("root") != cfg.end())
            _root = std::any_cast<std::string>(cfg.at("root"));
    }

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

    bool ShouldHandle([[gnu::unused]] const http::Context &ctx, [[gnu::unused]] const http::Request &req) const
    {
        return true;
    }

    [[nodiscard]] Version GetVersion() const noexcept { return {0, 1}; }

    [[nodiscard]] Version GetCompatibleApiVersion() const noexcept { return {1, 0}; }

    [[nodiscard]] const char *GetName() const noexcept { return "PHP CGI"; }

    [[nodiscard]] const char *GetDescription() const noexcept { return "Executes PHP."; }

    [[nodiscard]] double GetHandlerPriority() const noexcept { return 0.5f; }

private:
    using unique_ptr_pipe_t = std::unique_ptr<FILE, decltype(&PCLOSE)>;

    void InternalError(http::Response &res)
    {
        res.status_code = 500;
        res.body = "Internal server error";
    }

    void ProcessHeaders(std::string &headers, std::map<std::string, std::string> &headerMap)
    {
        std::istringstream headers_stream(headers);
        std::string full_header;

        while (std::getline(headers_stream, full_header))
        {
            const auto delimiter = full_header.find(':');
            const auto header_name = full_header.substr(0, delimiter);
            auto header_value = full_header.substr(delimiter + 2);

            if (header_value.back() == '\r')
                header_value.pop_back();

            headerMap[header_name] = header_value;
        }
    }
    std::pair<std::string, std::string> ProcessOutput(unique_ptr_pipe_t &pipe)
    {
        std::array<char, kBufferSize> buffer;
        std::string result;
        std::string headers;
        std::string body;

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            result += buffer.data();
        if (!result.empty())
        {
            body = result.substr(result.find(kHeaderBodySeparator) + kHeaderBodySeparator.length());
            headers = result.substr(0, result.find(kHeaderBodySeparator));
        }
        return std::make_pair(body, headers);
    }

    static inline std::string _bin_path{};
    static inline std::string _root{};
};