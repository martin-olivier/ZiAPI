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

    [[nodiscard]] virtual char *GetDescription() const noexcept = 0;
};

class ITransportMediator {
public:
    virtual void SendDataReceived(http::Connection &c, std::string data) = 0;
};

class ITransportModule : public IModule {
public:
    virtual void Run(ITransportMediator &mediator) { mediator.SendDataReceived(conn, data); }
};

class ISessionMediator {
public:
};

class ISessionModule : public IModule {
public:
    virtual void OnDataReceived(ISessionMediator &mediator, http::Connection &conn, std::string &data) {}
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
