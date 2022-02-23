#include "ziapi/Module.hpp"

class CompressorModule : public ziapi::IPostProcessorModule {
public:
    void Init(const ziapi::config::Node &) override
    {
        // Don't need anything to configure in this implementation
    }

    [[nodiscard]] ziapi::Version GetVersion() const noexcept override { return ziapi::Version{3, 1, 0}; }

    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override { return ziapi::Version{3, 1, 0}; }

    [[nodiscard]] const char *GetName() const noexcept override { return "CompressorModule"; }

    [[nodiscard]] const char *GetDescription() const noexcept override
    {
        return "Compress the response body before sending it back to the network";
    }

    void PostProcess(ziapi::http::Context &, ziapi::http::Response &res) override { res.body = CompressBody(res.body); }

    [[nodiscard]] double GetPostProcessorPriority() const noexcept override
    {
        // Compressor needs to be ran last, just before sending data back
        return 1.0f;
    }

    [[nodiscard]] bool ShouldPostProcess(const ziapi::http::Context &, const ziapi::http::Request &,
                                         const ziapi::http::Response &) const override
    {
        // Compressor will always be used as it's always useful
        return true;
    }

private:
    std::string CompressBody(const std::string &body)
    {
        // Algorithm of the hell
        return body.substr(0, body.length() / 2);
    }
};
