#pragma once

#include <memory>
#include <optional>
#include <string>
#include <type_traits>
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

using Array = std::vector<std::unique_ptr<Node>>;

/// Datatype for json/yaml-like data
using Dict = std::unordered_map<std::string, std::unique_ptr<Node>>;

using NodeVariant = std::variant<Undefined, Null, bool, int, double, String, Array, Dict>;

struct Node : public NodeVariant {
public:
    using NodeVariant::NodeVariant;

    /// Used to construct a Node from a Dict
    Node(std::initializer_list<Dict::value_type> values)
    {
        std::visit(
            [&](auto &d) {
                if constexpr (std::is_same_v<decltype(&d), Dict &>) {
                    for (auto &pair : values) {
                        d.try_emplace(std::move(pair));
                    }
                }
            },
            (NodeVariant &)*this);
    }

    /// Used to construct a Node from an Array
    Node(std::initializer_list<Array::value_type> values)
    {
        std::visit(
            [&](auto &d) {
                if constexpr (std::is_same_v<decltype(&d), Array &>) {
                    for (auto &pair : values) {
                        d.try_emplace(std::move(pair));
                    }
                }
            },
            (NodeVariant &)*this);
    }

    /// Used to construct a Node from a string
    Node(const char *str) : NodeVariant(std::string(str)){};

    /// Shorthand, `node->AsDict()["something"]` become `node["something"]`
    const Node &operator[](const char *key) const { return *AsDict().at(key); }

    /// Shorthand, `node->AsDict()["something"]` become `node["something"]`
    const Node &operator[](const std::string &key) const { return *AsDict().at(key); }

    /// Shorthand, `node->AsArray()[5]` become `node[5]`
    const Node &operator[](std::size_t index) const { return *AsArray().at(index); }

    /// Casts the variant as a bool. Will throw if actual type differs.
    bool AsBool() const { return std::get<bool>(*this); }

    /// Casts the variant as a Dict. Will throw if actual type differs.
    const Dict &AsDict() const { return std::get<Dict>(*this); }

    /// Casts the variant as a String. Will throw if actual type differs.
    String AsString() const { return std::get<String>(*this); }

    /// Casts the variant as a Array. Will throw if actual type differs.
    const Array &AsArray() const { return std::get<Array>(*this); }

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
