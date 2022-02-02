#include <gtest/gtest.h>

#include "decompressor/DecompressorModule.hpp"

TEST(Decompressor, UtilsInfo)
{
    DecompressorModule decompressor;

    ASSERT_EQ(std::string(decompressor.GetName()), std::string("DecompressorModule"));
    ASSERT_EQ(std::string(decompressor.GetDescription()),
              std::string("Decompress the response body before sending it to the module pipeline"));
    ASSERT_EQ(decompressor.GetCompatibleApiVersion(), (ziapi::Version{1, 0}));
    ASSERT_EQ(decompressor.GetVersion(), (ziapi::Version{1, 0}));
}

TEST(Decompressor, Decompression)
{
    DecompressorModule decompressor;
    ziapi::http::Context ctx;
    ziapi::http::Request req = {
        11,                                      // version
        ziapi::http::method::kPost,              // method
        "/zipper",                               // target
        std::map<std::string, std::string>({}),  // fields
        std::string("0101010110101"),            // body
    };

    req.fields.insert(std::make_pair<std::string, std::string>("compressed", "true"));

    if (decompressor.ShouldPreProcess(ctx, req)) {
        decompressor.PreProcess(ctx, req);
    }
    ASSERT_EQ(req.body, "0101010110101 omg i am now decompressed thx algorithm");
}
