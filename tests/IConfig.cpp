#include <gtest/gtest.h>
#include <map>

#include "ZiAPI/IConfig.hpp"

struct position
{
    int x, y;
};

class Config : public ziapi::IConfig {
private:
    std::map<std::string, std::any> m_config_map{};
public:
    Config()
    {
        m_config_map["mod_path"] = std::string("./modules");
        m_config_map["std"] = 17;
        m_config_map["position"] = position{50, 100};
    }
    ~Config() = default;
    std::any &operator[](const std::string &key) override
    {
        return m_config_map[key];
    }
    const std::any &operator[](const std::string &key) const override
    {
        return m_config_map.at(key);
    }
};

TEST(IConfig, get_values)
{
    Config conf;

    ASSERT_EQ(std::any_cast<std::string>(conf["mod_path"]), "./modules");
    ASSERT_EQ(std::any_cast<int>(conf["std"]), 17);
    auto pos = std::any_cast<position>(conf["position"]);
    ASSERT_EQ(pos.x, 50);
    ASSERT_EQ(pos.y, 100);
}

TEST(IConfig, set_values)
{
    Config conf;

    conf["mod_path"] = std::string("/usr/local/mod");
    ASSERT_EQ(std::any_cast<std::string>(conf["mod_path"]), "/usr/local/mod");

    conf["std"] = 20;
    ASSERT_EQ(std::any_cast<int>(conf["std"]), 20);
}

TEST(IConfig, bad_key)
{
    Config conf;

    auto val = conf["bad_key"];
    ASSERT_EQ(val.has_value(), false);
}