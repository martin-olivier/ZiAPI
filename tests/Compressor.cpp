#include "examples/modules/CompressorModule.hpp"

#include <gtest/gtest.h>

TEST(Compressor, UtilsInfo)
{
    CompressorModule compressor;

    ASSERT_EQ(compressor.GetName(), "CompressorModule");
    ASSERT_EQ(compressor.GetDescription(), "Compress the response body before sending it back to the network");
    ASSERT_EQ(compressor.GetCompatibleApiVersion(), Version(1, 0));
    ASSERT_EQ(compressor.GetVersion(), Version(1, 0));
}

TEST(Compressor, compressionRate)
{
    CompressorModule compressor;
    ziapi::http::Context ctx;
    ziapi::http::Response res;

    res.version = 11;
    res.status_code = 200;
    res.reason = std::string("OK");
    res.fields.insert(std::make_pair<std::string, std::string>("Content-Type", "application/json"));
    res.body = std::string("not compressed stuff blabla omg so long");

    compressor.PostProcess(ctx, res);
    ASSERT_EQ(res.body, "hihihi i'm compressed bro");
}

