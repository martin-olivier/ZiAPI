#pragma once

#include <any>
#include <map>
#include <string>

namespace ziapi {

/**
 *  Class that manages the actual configuration data
 */
using Config = std::map<std::string, std::any>;

}  // namespace ziapi
