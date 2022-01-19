#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define ZIAPI_EXPORT extern "C" __declspec(dllexport)
#else
#define ZIAPI_EXPORT extern "C"
#endif
