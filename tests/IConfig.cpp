#include <gtest/gtest.h>
#include <map>
#include <any>
#include "ZiAPI/IConfig.hpp"

struct position
{
    int x, y;
};

class Config : public ziapi::IConfig {
private:
    std::map<std::string, std::any> m_config_map;
public:
    Config()
    {
        m_config_map["mod_path"] = "./modules";
        m_config_map["std"] = 17;
        m_config_map["ipv4"] = std::string("192.168.1.10");
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

    ASSERT_EQ(std::any_cast<const char *>(conf["mod_path"]), "./modules");
    ASSERT_EQ(std::any_cast<int>(conf["std"]), 17);
    ASSERT_EQ(std::any_cast<std::string>(conf["ipv4"]), "192.168.1.10");
    auto pos = std::any_cast<position>(conf["position"]);
    ASSERT_EQ(pos.x, 50);
    ASSERT_EQ(pos.y, 100);
}

TEST(IConfig, set_values)
{
    Config conf;

    conf["std"] = 20;
    ASSERT_EQ(std::any_cast<int>(conf["std"]), 20);

    conf["ipv4"] = std::string("1.1.1.1");
    ASSERT_EQ(std::any_cast<std::string>(conf["ipv4"]), "1.1.1.1");
}

TEST(IConfig, bad_key)
{
    Config conf;

    auto val = conf["bad_key"];
    ASSERT_EQ(val.has_value(), false);
}