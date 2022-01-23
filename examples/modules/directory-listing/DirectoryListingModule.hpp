#include <filesystem>
#include <fstream>

#include "ziapi/Module.hpp"

class DirectoryListingModule : public ziapi::IHandlerModule {
public:
    void Init(const ziapi::Config &cfg)
    {
        /// In our config, we can specify which folder our module serves.
        root_ = std::any_cast<std::string>(cfg.at("modules.directory_listing.path"));
    }

    ziapi::Version GetVersion() const noexcept { return {1, 0}; }

    ziapi::Version GetCompatibleApiVersion() const noexcept { return {1, 0}; }

    const char *GetName() const noexcept { return "DirectoryListing"; }

    const char *GetDescription() const noexcept { return "Give access to a filesystem over HTTP"; }

    virtual double GetHandlerPriority() const noexcept
    {
        /// Our module doesn't have any specific priority requirements.
        return 0.5f;
    }

    virtual bool ShouldHandle(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const
    {
        /// We only want to handle GET requests.
        return req.method == ziapi::http::method::GET;
    }

    virtual void Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
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
        res.status_code = ziapi::http::code::NOT_FOUND;
        res.reason = ziapi::http::reason::NOT_FOUND;
    }

private:
    std::string root_;
};
