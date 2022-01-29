#include "ziapi/Config.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <unordered_map>

#include "MockConfig.hpp"

TEST(Config, SimpleMockConfig)
{
    std::unordered_map<std::string, ziapi::IConfig::ValueType> config_values = {
        {"int", 10},    {"nullopt", std::nullopt}, {"null", nullptr}, {"config", (ziapi::IConfig *)nullptr},
        {"bool", true},
    };
    auto cfg = std::unique_ptr<ziapi::IConfig>(new ziapi::MockConfig(config_values));
    auto _int = std::get<int>(cfg->Get("int"));
    // auto _nullopt = std::get<std::nullopt_t>(cfg->Get("nullopt"));
    auto _bool = std::get<bool>(cfg->Get("bool"));
    auto _null = std::get<std::nullptr_t>(cfg->Get("null"));
    auto _config = std::get<ziapi::IConfig *>(cfg->Get("config"));

    ASSERT_EQ(_int, 10);
    // ASSERT_EQ(_nullopt);
    ASSERT_EQ(_bool, true);
    ASSERT_EQ(_null, nullptr);
    ASSERT_EQ(_config, nullptr);
}
