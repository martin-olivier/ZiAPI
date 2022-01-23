#include "ziapi/Module.hpp"

#include <iostream>
#include <memory>

#include "dylib/dylib.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define EXPORT_SYM extern "C++" __declspec(dllexport)
#else
#define EXPORT_SYM extern "C++"
#endif

class Module : public ziapi::IModule {
public:
    Module() = default;
    ~Module() override = default;
    void Init(const ziapi::Config &) override {}
    ziapi::Version GetVersion() const noexcept override { return {1, 0}; }
    ziapi::Version GetCompatibleApiVersion() const noexcept override { return {1, 0}; }

    [[nodiscard]] virtual const char *GetName() const noexcept override { return "module_name"; }

    [[nodiscard]] virtual const char *GetDescription() const noexcept override
    {
        return "A module implementation example !";
    }
};

EXPORT_SYM std::unique_ptr<ziapi::IModule> LoadModule() { return std::make_unique<Module>(); }