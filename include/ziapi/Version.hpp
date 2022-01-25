#pragma once

namespace ziapi {

/**
 *  Semantic versioning structure with a major and a minor version
 */
struct Version {
    Version(int major, int minor) : major(major), minor(minor) {}

    inline bool operator==(const Version &other) const noexcept
    {
        return this->major == other.major && this->minor == other.minor;
    }

    inline bool operator!=(const Version &other) const noexcept { return !(*this == other); }

    inline bool operator>(const Version &other) const noexcept
    {
        if (this->major > other.major)
            return true;
        if (this->major < other.major)
            return false;
        return this->minor > other.minor;
    }

    inline bool operator<(const Version &other) const noexcept
    {
        if (this->major < other.major)
            return true;
        if (this->major > other.major)
            return false;
        return this->minor < other.minor;
    }

    inline bool operator>=(const Version &other) const noexcept { return (*this > other) || (*this == other); }

    inline bool operator<=(const Version &other) const noexcept { return (*this < other) || (*this == other); }

    unsigned int major;
    unsigned int minor;
};

}  // namespace ziapi
