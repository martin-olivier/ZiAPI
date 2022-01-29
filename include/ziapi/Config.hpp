#pragma once

#include <any>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace ziapi {

/// Queryable key-value store intended for (but not limited to) use with YAML
/// or JSON.
class IConfig {
public:
    /// Declines all the possible configuration values. Supports all the
    /// possible data types of YAML, JSON and XML.
    /// There is an important distinction betweeen the variants nullptr and
    /// nullopt. A nullptr represents an explicit null value while a nullopt
    /// represents the value of a key which doesn't exist in the dictionary.
    using ValueType =
        std::variant<std::nullopt_t, std::nullptr_t, bool, int, double, std::string, std::vector<IConfig *>, IConfig *>;

    virtual ~IConfig() = default;

    /// Get a value by key. Accessing nested keys such as "user.name" directly
    /// is non-standard and may not be supported by every implementation. To
    /// access nested values you should get the initial top level key ("user"
    /// for example) and then perform a variant cast as an IConfig unique_ptr
    /// before accessing the final key.
    virtual const ValueType &Get(const std::string &key) const = 0;
};

}  // namespace ziapi
