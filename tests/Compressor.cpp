#include <gtest/gtest.h>

#include "compressor/CompressorModule.hpp"

TEST(Compressor, UtilsInfo)
{
    CompressorModule compressor;

    ASSERT_EQ(compressor.GetName(), "CompressorModule");
    ASSERT_EQ(compressor.GetDescription(), "Compress the response body before sending it back to the network");
    ASSERT_EQ(compressor.GetCompatibleApiVersion(), (ziapi::Version{1, 0}));
    ASSERT_EQ(compressor.GetVersion(), (ziapi::Version{1, 0}));
}

TEST(Compressor, compressionRate)
{
    CompressorModule compressor;
    ziapi::http::Context ctx;
    ziapi::http::Response res = {
        .version = 11,
        .status_code = 200,
        .reason = std::string("OK"),
        .fields = std::map<std::string, std::string>({}),
        .body = std::string("not compressed stuff blabla omg so long"),
    };
    res.fields.insert(std::make_pair<std::string, std::string>("Content-Type", "application/json"));

    if (compressor.ShouldPostProcess(ctx, res)) {
        compressor.PostProcess(ctx, res);
    }
    ASSERT_EQ(res.body, "not compressed stuf");
}
