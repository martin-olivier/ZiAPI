#include "ziapi/Module.hpp"

class DecompressorModule : public ziapi::IPreProcessorModule {
public:
    ~DecompressorModule() = default;

    void Init([[maybe_unused]] const ziapi::IConfig &cfg) override
    {
        // Don't need anything to configure in this implementation
    }

    [[nodiscard]] ziapi::Version GetVersion() const noexcept override { return ziapi::Version{1, 0}; }

    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override { return ziapi::Version{1, 0}; }

    [[nodiscard]] const char *GetName() const noexcept override { return "DecompressorModule"; }

    [[nodiscard]] const char *GetDescription() const noexcept override
    {
        return "Decompress the response body before sending it to the module pipeline";
    }

    void PreProcess([[maybe_unused]] ziapi::http::Context &ctx, ziapi::http::Request &req) override
    {
        req.body = DecompressBody(req.body);
    }

    [[nodiscard]] double GetPreProcessorPriority() const noexcept override
    {
        // Decompressor need to be run the first just before sending data back
        return 0;
    }

    [[nodiscard]] bool ShouldPreProcess([[maybe_unused]] const ziapi::http::Context &ctx,
                                        [[maybe_unused]] const ziapi::http::Request &req) const override
    {
        // Only use if compressed header is set
        return req.fields.at("compressed") == std::string("true");
    }

private:
    std::string DecompressBody(const std::string &body)
    {
        // algorithm of the hell
        return std::string(body + std::string(" omg i am now decompressed thx algorithm"));
    }
};
