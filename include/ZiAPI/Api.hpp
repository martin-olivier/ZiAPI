#pragma once

#include <cstdint>

namespace ziapi {

enum class ApiEvent : std::uint32_t {

};

class IApi {
public:
    virtual void On(ApiEvent evt) = 0;
};

}  // namespace ziapi
