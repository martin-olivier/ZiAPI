#pragma once

#include <ostream>

#include "Api.hpp"
#include "Http.hpp"
#include "Utils.hpp"

namespace ziapi {

class IModule {
public:
    virtual void Init(IApi &api) = 0;

    virtual Version GetVersion() = 0;

    virtual Version GetCompatibleApiVersion() = 0;

    virtual std::string GetDescription() = 0;

    virtual void Dispose() = 0;
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
