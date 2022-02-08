#include "ziapi/Config.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <unordered_map>

using namespace ziapi::config;

TEST(Config, SimpleInt)
{
    Node node(10);

    ASSERT_EQ(node.AsInt(), 10);
}

TEST(Config, SimpleString)
{
    Node node(String("Hello world"));

    ASSERT_EQ(node.AsString(), "Hello world");
}

TEST(Config, SimpleDouble)
{
    Node node(45.647f);

    ASSERT_EQ(node.AsDouble(), 45.647f);
}

TEST(Config, SimpleBool)
{
    Node node(true);

    ASSERT_EQ(node.AsBool(), true);
}

TEST(Config, SimpleArray)
{
    Node array({
        std::make_shared<Node>(10),
        std::make_shared<Node>("Hello world"),
        std::make_shared<Node>(14.5f),
    });

    ASSERT_EQ(array.AsArray()[0]->AsInt(), 10);
    ASSERT_EQ(array.AsArray()[1]->AsString(), "Hello world");
    ASSERT_EQ(array.AsArray()[2]->AsDouble(), 14.5f);
}

TEST(Config, SimpleDict)
{
    Node modules_count(10);
    Node dict = {
        {"modules_count", std::make_shared<Node>(modules_count)},
    };

    ASSERT_EQ(dict.AsDict()["modules_count"]->AsInt(), 10);
}

TEST(Config, NestedAccess)
{
    Node root("/var/www");
    Node root_node({
        {"root", std::make_shared<Node>(root)},
    });
    Node modules_node({
        {"directoryListing", std::make_shared<Node>(root_node)},
    });
    Node cfg({
        {"modules", std::make_shared<Node>(modules_node)},
    });

    ASSERT_EQ(cfg["modules"]["directoryListing"]["root"].AsString(), "/var/www");
}

TEST(Config, OperatorBool)
{
    Node undefined(Undefined{});
    Node null(nullptr);
    Node string("Hello");

    ASSERT_EQ(undefined.operator bool(), false);
    ASSERT_EQ(null.operator bool(), false);
    ASSERT_EQ(string.operator bool(), true);
}
