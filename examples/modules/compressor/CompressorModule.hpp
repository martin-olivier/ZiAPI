#include "ziapi/Module.hpp"

class CompressorModule : public ziapi::IPostProcessorModule {
public:
    ~CompressorModule() = default;

    void Init(const Config &cfg) override
    {
        // Don't need anything to configure in this implementation
    }

    [[nodiscard]] Version GetVersion() const noexcept override
    {
        return Version{1, 0};
    }

    [[nodiscard]] Version GetCompatibleApiVersion() const noexcept override
    {
        return Version{1, 0};
    }

    [[nodiscard]] const char *GetName() const noexcept override
    {
        return "CompressorModule";
    }

    [[nodiscard]] const char *GetDescription() const noexcept override
    {
        return "Compress the response body before sending it back to the network";
    }


    void PostProcess([[maybe_unused]] http::Context &ctx, http::Response &res) override
    {
        res.body = compress(res.body)
    }

    [[nodiscard]] double GetPostProcessorPriority() const noexcept override
    {
        // Compressor need to be run the last just before sending data back
        return 1;
    }

    [[nodiscard]] bool ShouldPostProcess(const http::Context &ctx, const http::Response &res) const override
    {
        // Compressor will alwaus be used as it's always useful
        return true;
    }

private:
    std::string CompressBody(const std::string &body)
    {
        // algorithm of the hell
        return "hihihi i'm compressed bro";
    }
};
