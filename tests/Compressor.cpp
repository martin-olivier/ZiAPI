#include <gtest/gtest.h>

#include "compressor/CompressorModule.hpp"

TEST(Compressor, UtilsInfo)
{
    CompressorModule compressor;

    ASSERT_EQ(std::string(compressor.GetName()), std::string("CompressorModule"));
    ASSERT_EQ(std::string(compressor.GetDescription()),
              std::string("Compress the response body before sending it back to the network"));
    ASSERT_EQ(compressor.GetCompatibleApiVersion(), (ziapi::Version{3, 1, 0}));
    ASSERT_EQ(compressor.GetVersion(), (ziapi::Version{3, 1, 0}));
}

TEST(Compressor, compressionRate)
{
    CompressorModule compressor;
    ziapi::http::Context ctx;
    ziapi::http::Response res = {
        ziapi::http::Version::kV1_1,                             // Version
        ziapi::http::Code::kOK,                                  // Status code
        std::string("OK"),                                       // reason
        std::map<std::string, std::string>({}),                  // fields
        std::string("not compressed stuff blabla omg so long"),  // body
    };
    res.fields.insert(std::make_pair<std::string, std::string>("Content-Type", "application/json"));

    if (compressor.ShouldPostProcess(ctx, res)) {
        compressor.PostProcess(ctx, res);
    }
    ASSERT_EQ(res.body, "not compressed stuf");
}
