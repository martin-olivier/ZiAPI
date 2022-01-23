#pragma once

namespace ziapi {

/**
 *  Semantic versioning structure with a major and a minor version
 */
struct Version {
    bool operator==(const Version &other) const { return this->major == other.major && this->minor == other.minor; }

    bool operator!=(const Version &other) const { return this->major != other.major || this->minor != other.minor; }

    unsigned int major;
    unsigned int minor;
};

}  // namespace ziapi
