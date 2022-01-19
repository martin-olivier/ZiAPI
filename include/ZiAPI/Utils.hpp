#pragma once

namespace ziapi {

// Semantic versioning structure with a major and minor version.
struct Version {
    int major;
    int minor;
};

#if defined(_WIN32) || defined(_WIN64)
// Windows macro for marking a symbol as exportable.
#define ZIAPI_EXPORT extern "C" __declspec(dllexport)
#else
// Linux macro for marking a symbol as exportable.
#define ZIAPI_EXPORT extern "C"
#endif

}  // namespace ziapi
