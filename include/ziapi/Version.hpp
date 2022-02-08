#pragma once

namespace ziapi {

/**
 *  Semantic versioning structure with a major and a minor version
 */
struct Version {
    Version(int major, int minor, int patch) : major(major), minor(minor), patch(patch) {}

    inline bool operator==(const Version &other) const noexcept
    {
        return major == other.major && minor == other.minor && patch == other.patch;
    }

    inline bool operator!=(const Version &other) const noexcept { return !(*this == other); }

    inline bool operator>(const Version &other) const noexcept { return (*this >= other) && (*this != other); }

    inline bool operator<(const Version &other) const noexcept { return !(*this > other) && other != *this; }

    inline bool operator>=(const Version &other) const noexcept
    {
        return (major == other.major
                    ? minor == other.minor ? patch == other.patch ? true : patch > other.patch : minor > other.minor
                    : major > other.major);
    }

    inline bool operator<=(const Version &other) const noexcept { return (*this < other) || (*this == other); }

    unsigned int major;
    unsigned int minor;
    unsigned int patch;
};

}  // namespace ziapi
