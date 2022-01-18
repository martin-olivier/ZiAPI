#pragma once

#include <any>

namespace ziapi {
/**
 *  Class that manages the actual configuration data
 */
class IConfig {
public:
    virtual ~IConfig() = default;
    virtual std::any &operator[](const std::string &key) = 0;
    virtual const std::any &operator[](const std::string &key) const = 0;
};
}