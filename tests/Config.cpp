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
    Node node_1(10);
    Node node_2("Hello world");
    Node node_3(14.5f);
    Node array({
        &node_1,
        &node_2,
        &node_3,
    });

    ASSERT_EQ(array.AsArray()[0]->AsInt(), 10);
    ASSERT_EQ(array.AsArray()[1]->AsString(), "Hello world");
    ASSERT_EQ(array.AsArray()[2]->AsDouble(), 14.5f);
}

TEST(Config, SimpleDict)
{
    Node modules_count(10);
    Node dict = {
        {"modules_count", &modules_count},
    };

    ASSERT_EQ(dict.AsDict()["modules_count"]->AsInt(), 10);
}

TEST(Config, NestedAccess)
{
    Node root("/var/www");
    Node root_node({
        {"root", &root},
    });
    Node modules_node({
        {"directoryListing", &root_node},
    });
    Node cfg({
        {"modules", &modules_node},
    });

    ASSERT_EQ(cfg["modules"]["directoryListing"]["root"].AsString(), "/var/www");
}
