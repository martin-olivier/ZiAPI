#pragma once

#include <ostream>

#include "Http.hpp"
#include "IConfig.hpp"
#include "Utils.hpp"

namespace ziapi {

class IModule {
public:
    virtual ~IModule() = default;

    virtual void Init(const IConfig &cfg) = 0;

    [[nodiscard]] virtual Version GetVersion() const noexcept = 0;

    [[nodiscard]] virtual Version GetCompatibleApiVersion() const noexcept = 0;

    [[nodiscard]] virtual char *GetName() const noexcept = 0;
};

class ITransportModule : public IModule {
public:
};

class ISessionModule : public IModule {
public:
};

class IPresentationModule : public IModule {
public:
};

class IApplicationParserModule : public IModule {
public:
};

class IApplicationHandlerModule : public IModule {
public:
};

}  // namespace ziapi
