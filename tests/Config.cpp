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
    Array array;
    Node node_1(10);
    Node node_2("Hello world");
    Node node_3(14.5f);
    array.emplace_back(&node_1);
    array.emplace_back(&node_2);
    array.emplace_back(&node_3);
    Node array_node(array);

    ASSERT_EQ(array_node.AsArray()[0]->AsInt(), 10);
    ASSERT_EQ(array_node.AsArray()[1]->AsString(), "Hello world");
    ASSERT_EQ(array_node.AsArray()[2]->AsDouble(), 14.5f);
}

TEST(Config, SimpleDict)
{
    Node modules_count(10);
    Dict dict = {
        {"modules_count", &modules_count},
    };
    Node node(dict);

    ASSERT_EQ(node.AsDict()["modules_count"]->AsInt(), 10);
}
