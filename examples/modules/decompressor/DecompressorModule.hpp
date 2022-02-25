#include "ziapi/Module.hpp"

class DecompressorModule : public ziapi::IPreProcessorModule {
public:
    ~DecompressorModule() = default;

    void Init(const ziapi::config::Node &) override
    {
        // Don't need anything to configure in this implementation
    }

    [[nodiscard]] ziapi::Version GetVersion() const noexcept override { return ziapi::Version{4, 0, 0}; }

    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override { return ziapi::Version{4, 0, 0}; }

    [[nodiscard]] const char *GetName() const noexcept override { return "DecompressorModule"; }

    [[nodiscard]] const char *GetDescription() const noexcept override
    {
        return "Decompress the response body before sending it to the module pipeline";
    }

    void PreProcess(ziapi::http::Context &, ziapi::http::Request &req) override { req.body = DecompressBody(req.body); }

    [[nodiscard]] double GetPreProcessorPriority() const noexcept override
    {
        // Decompressor needs to be ran first, before any pre-processor.
        return 0.0f;
    }

    [[nodiscard]] bool ShouldPreProcess(const ziapi::http::Context &, const ziapi::http::Request &req) const override
    {
        // Only use if compressed header is set
        return req.headers.at("compressed") == std::string("true");
    }

private:
    std::string DecompressBody(const std::string &body)
    {
        // algorithm of the hell
        return std::string(body + std::string(" omg i am now decompressed thx algorithm"));
    }
};
