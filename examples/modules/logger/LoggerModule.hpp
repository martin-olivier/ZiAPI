#include <iomanip>
#include <sstream>

#include "ziapi/Logger.hpp"
#include "ziapi/Module.hpp"

class LoggerModule : virtual public ziapi::IPreProcessorModule, public ziapi::IPostProcessorModule {
public:
    void Init(const ziapi::config::Node &config) {}

    [[nodiscard]] ziapi::Version GetVersion() const noexcept override { return {3, 1, 0}; }

    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override { return {3, 1, 0}; }

    [[nodiscard]] const char *GetName() const noexcept override { return "LoggerModule"; }

    [[nodiscard]] const char *GetDescription() const noexcept override
    {
        return "Log all responses from HTTP requests";
    }

    [[nodiscard]] double GetPostProcessorPriority() const noexcept override { return 1; }

    [[nodiscard]] bool ShouldPostProcess(const ziapi::http::Context &ctx,
                                         const ziapi::http::Response &res) const override
    {
        return true;
    }

    [[nodiscard]] double GetPreProcessorPriority() const noexcept override { return 0; }

    [[nodiscard]] bool ShouldPreProcess(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const override
    {
        return true;
    }

    void PostProcess(ziapi::http::Context &ctx, ziapi::http::Response &res) override
    {
        std::stringstream ss;

        // Exemple: ` [X] 404: Not found (GET /test, 2s)`
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

    void PreProcess(ziapi::http::Context &ctx, ziapi::http::Request &req) override
    {
        ctx["timestamp"] = std::time(nullptr);
        ctx["target"] = req.target;
        ctx["method"] = req.method;
    }
};
