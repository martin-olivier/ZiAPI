#include "ziapi/Module.hpp"

#include <iostream>
#include <memory>

#include "dylib/dylib.hpp"

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

DYLIB_API std::unique_ptr<ziapi::IModule> LoadModule() { return std::make_unique<Module>(); }