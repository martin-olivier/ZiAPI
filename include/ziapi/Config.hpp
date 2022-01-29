#pragma once

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

using Array = std::vector<Node *>;

using Dict = std::unordered_map<std::string, Node *>;

struct Node : public std::variant<Undefined, Null, bool, int, double, String, Array, Dict> {
public:
    Node(const std::initializer_list<Dict::value_type> &values)
        : std::variant<Undefined, Null, bool, int, double, String, Array, Dict>(Dict(values)){};

    Node(const std::initializer_list<Array::value_type> &values)
        : std::variant<Undefined, Null, bool, int, double, String, Array, Dict>(std::vector(values)){};

    Node(const char *str) : std::variant<Undefined, Null, bool, int, double, String, Array, Dict>(std::string(str)){};

    template <typename... Args>
    Node(Args &&...args) : std::variant<Undefined, Null, bool, int, double, String, Array, Dict>(args...){};

    bool AsBool() const { return std::get<bool>(*this); }

    Node &operator[](const char *key) const { return *AsDict().at(key); }

    Node &operator[](const std::string &key) const { return *AsDict().at(key); }

    Node &operator[](std::size_t index) const { return *AsArray().at(index); }

    Dict AsDict() const { return std::get<Dict>(*this); }

    String AsString() const { return std::get<String>(*this); }

    Array AsArray() const { return std::get<Array>(*this); }

    int AsInt() const { return std::get<int>(*this); }

    double AsDouble() const { return std::get<double>(*this); }

    bool IsNull() const { return index() == kNull; }

    bool IsUndefined() const { return index() == kUndefined; }

    operator bool() const { return IsNull() || IsUndefined(); }
};

}  // namespace ziapi::config
