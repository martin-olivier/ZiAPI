#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace ziapi::config {

enum Type {
    kUndefined = 0,
    kNull,
    kBool,
    kInt,
    kDouble,
    kString,
    kArray,
    kDict,
};

struct Node;

struct Undefined {
};

using Null = std::nullptr_t;

using String = std::string;

using Array = std::vector<std::shared_ptr<Node>>;

/// Datatype for json/yaml-like data
using Dict = std::unordered_map<std::string, std::shared_ptr<Node>>;

using NodeVariant = std::variant<Undefined, Null, bool, int, double, String, Array, Dict>;

struct Node : public NodeVariant {
public:
    using NodeVariant::NodeVariant;

    /// Simpler way to construct an Array node, it instantiates an std::shared_ptr for each value
    static Node MakeArray(const std::initializer_list<Node> &values)
    {
        Array arr;

        for (auto &value : values) {
            arr.push_back(std::make_shared<Node>(value));
        }
        return arr;
    }

    /// Constructs an Array node from a vector, it instantiates an std::shared_ptr for each value
    static Node MakeArray(const std::vector<Node> &values)
    {
        Array arr;

        for (auto &value : values) {
            arr.push_back(std::make_shared<Node>(value));
        }
        return arr;
    }

    /// Simpler way to construct a Dict node, it instantiates an std::shared_ptr for each value
    static Node MakeDict(const std::initializer_list<std::pair<std::string, Node>> &values)
    {
        Dict dict;

        for (auto &value : values) {
            dict[value.first] = std::make_shared<Node>(value.second);
        }
        return dict;
    }

    /// Constructs a Dict node from a vector, it instantiates an std::shared_ptr for each value
    static Node MakeDict(const std::unordered_map<std::string, Node> &values)
    {
        Dict dict;

        for (auto &[key, value] : values) {
            dict[key] = std::make_shared<Node>(value);
        }
        return dict;
    }

    /// Used to construct a Node from a string
    Node(const char *str) : NodeVariant(std::string(str)){};

    /// Shorthand, `node->AsDict()["something"]` become `node["something"]`
    Node &operator[](const char *key) const { return *AsDict().at(key); }

    /// Shorthand, `node->AsDict()["something"]` become `node["something"]`
    Node &operator[](const std::string &key) const { return *AsDict().at(key); }

    /// Shorthand, `node->AsArray()[5]` become `node[5]`
    Node &operator[](std::size_t index) const { return *AsArray().at(index); }

    /// Casts the variant as a bool. Will throw if actual type differs.
    bool AsBool() const { return std::get<bool>(*this); }

    /// Casts the variant as a Dict. Will throw if actual type differs.
    Dict AsDict() const { return std::get<Dict>(*this); }

    /// Casts the variant as a String. Will throw if actual type differs.
    String AsString() const { return std::get<String>(*this); }

    /// Casts the variant as a Array. Will throw if actual type differs.
    Array AsArray() const { return std::get<Array>(*this); }

    /// Casts the variant as a int. Will throw if actual type differs.
    int AsInt() const { return std::get<int>(*this); }

    /// Casts the variant as a double. Will throw if actual type differs.
    double AsDouble() const { return std::get<double>(*this); }

    /// Check if your Node value is null
    bool IsNull() const { return index() == kNull; }

    /// Check if your Node value is undefined
    bool IsUndefined() const { return index() == kUndefined; }

    /// Check if your Node is not empty
    operator bool() const { return !IsNull() && !IsUndefined(); }
};

}  // namespace ziapi::config
