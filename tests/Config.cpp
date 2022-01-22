#include "ziapi/Config.hpp"

#include <gtest/gtest.h>

#include <map>

struct position {
    int x, y;
};

TEST(Config, get_values)
{
    ziapi::Config conf{{"mod_path", std::make_any<std::string>("./modules")},
                       {"std", std::make_any<int>(17)},
                       {"position", std::make_any<position>(position{50, 100})}};

    ASSERT_EQ(std::any_cast<std::string>(conf["mod_path"]), "./modules");
    ASSERT_EQ(std::any_cast<int>(conf["std"]), 17);
    auto pos = std::any_cast<position>(conf["position"]);
    ASSERT_EQ(pos.x, 50);
    ASSERT_EQ(pos.y, 100);
}

TEST(Config, set_values)
{
    ziapi::Config conf{{"mod_path", std::make_any<std::string>("./modules")},
                       {"std", std::make_any<int>(17)},
                       {"position", std::make_any<position>(position{50, 100})}};

    conf["mod_path"] = std::make_any<std::string>("/usr/local/mod");
    ASSERT_EQ(std::any_cast<std::string>(conf["mod_path"]), "/usr/local/mod");

    conf["std"] = std::make_any<int>(20);
    ASSERT_EQ(std::any_cast<int>(conf["std"]), 20);
}

TEST(Config, bad_key)
{
    ziapi::Config conf{{"mod_path", std::make_any<std::string>("./modules")},
                       {"std", std::make_any<int>(17)},
                       {"position", std::make_any<position>(position{50, 100})}};

    auto val = conf["bad_key"];
    ASSERT_EQ(val.has_value(), false);
}
