#include <gtest/gtest.h>

#include "decompressor/DecompressorModule.hpp"

TEST(Decompressor, UtilsInfo)
{
    DecompressorModule decompressor;

    ASSERT_EQ(decompressor.GetName(), "DecompressorModule");
    ASSERT_EQ(decompressor.GetDescription(), "Decompress the response body before sending it to the module pipeline");
    ASSERT_EQ(decompressor.GetCompatibleApiVersion(), (ziapi::Version{1, 0}));
    ASSERT_EQ(decompressor.GetVersion(), (ziapi::Version{1, 0}));
}

TEST(Decompressor, Decompression)
{
    DecompressorModule decompressor;
    ziapi::http::Context ctx;
    ziapi::http::Request req = {
        .version = 11,
        .method = ziapi::http::method::POST,
        .target = "/zipper",
        .fields = std::map<std::string, std::string>({}),
        .body = std::string("0101010110101"),
    };

    req.fields.insert(std::make_pair<std::string, std::string>("compressed", "true"));

    if (decompressor.ShouldPreProcess(ctx, req)) {
        decompressor.PreProcess(ctx, req);
    }
    ASSERT_EQ(req.body, "0101010110101 omg i am now decompressed thx algorithm");
}
