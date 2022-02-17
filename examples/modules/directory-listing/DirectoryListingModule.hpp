#include <filesystem>
#include <fstream>

#include "ziapi/Config.hpp"
#include "ziapi/Module.hpp"

class DirectoryListingModule : public ziapi::IHandlerModule {
public:
    void Init(const ziapi::config::Node &cfg) override
    {
        /// In our config, we can specify which folder our module serves.
        /// We fetch the "modules.directoryListing.root" variable from the config
        /// as a string.
        root_ = cfg["modules"]["directoryListing"]["root"].AsString();
    }

    [[nodiscard]] ziapi::Version GetVersion() const noexcept override { return {3, 1, 0}; }

    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override { return {3, 1, 0}; }

    [[nodiscard]] const char *GetName() const noexcept override { return "DirectoryListing"; }

    [[nodiscard]] const char *GetDescription() const noexcept override
    {
        return "Give access to a filesystem over HTTP";
    }

    [[nodiscard]] double GetHandlerPriority() const noexcept override
    {
        /// Our module doesn't have any specific priority requirements.
        return 0.5f;
    }

    [[nodiscard]] bool ShouldHandle(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const override
    {
        /// We only want to handle GET requests.
        return req.method == ziapi::http::method::kGet;
    }

    void Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res) override
    {
        /// Here we concat the root path from our config (e.g /var/www/) with the target from our request (e.g.
        /// index.html) to get the full path of our file.
        auto filepath = std::filesystem::path(root_) / std::filesystem::path(req.target);
        std::error_code ec;

        /// If the file is a directory let's provide a list of all the files as a response.
        if (std::filesystem::is_directory(filepath, ec)) {
            std::ostringstream ss;
            for (const auto &entry : std::filesystem::directory_iterator(filepath)) {
                ss << entry.path().string() << "\n";
            }
            return;
        } else {
            /// If the file is not a directory, we assume it's a regular file and we just send its contents with the
            /// response.
            std::ifstream file_stream(filepath.filename());
            std::ostringstream ss;
            ss << file_stream.rdbuf();
            res.body = ss.str();
            return;
        }
        res.status_code = ziapi::http::Code::kNotFound;
        res.reason = ziapi::http::reason::kNotFound;
    }

private:
    std::string root_;
};
