#pragma once

#include <unordered_map>

#include "ziapi/Config.hpp"

namespace ziapi {

/// Do not implement your config like that.
class MockConfig : public IConfig {
public:
    MockConfig(const std::unordered_map<std::string, IConfig::ValueType> &values) : data_(values) {}

    const IConfig::ValueType &Get(const std::string &key) const override { return data_.at(key); }

private:
    std::unordered_map<std::string, IConfig::ValueType> data_;
};

}  // namespace ziapi
