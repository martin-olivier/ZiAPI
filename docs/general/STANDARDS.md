# ZIAPI Standards

A set of rules that define a standard implementation of a ZIAPI module to make it easier to share modules between groups.

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119).

## `Z0` - Module Documentation

Each module **MUST** be shipped with a `README.md` providing basic documentation for the module.

## `Z1` - Module Configuration Documentation

ZIAPI doesn't impose a norm for configuration files. However modules **MUST** be shipped with sufficient documentation regarding the configuration fields they expect.

#### Example

If the module `tls` depends on the following configuration:

```c++
void Init(const ziapi::config::Node &cfg) override {
    auto enable_tls = cfg["modules"]["tls"]["enableTls"].AsBool();
    auto certificate_path = cfg["modules"]["tls"]["certficiatePath"].AsString();
}
```

Then the `tls` module's documentation should explicitly state that the module expects:
- `modules.tls.enableTls` to be defined as a boolean
- `modules.tls.certificatePath` to be defined as a string

## `Z2` - Configuration File Layout

To limit friction when sharing modules, all groups **MAY** implement the following configuration file layout where:
- The top level node is a `ziapi::config::Dict`
- It contains a `modules` key which is a `ziapi::config::Dict` too.
- Each module which requires a configuration fetches its configuration information from `modules.<module_name>*`

#### Example

To illustrate this, let's look at a YAML configuration file example.

Let's say we have two modules respectively named `tls` and `directoryListing`. By applying rule Z2 we get the following configuration.

```yaml
modules:
    tls:
        foo: bar
    directoryListing:
        foo: bar
```

Therefore it is **NOT RECOMMENDED** to depend on configuration fields outside of the `modules.<module_name>` scope like so:

```c++
void MyModule::Init(const ziapi::config::Node &cfg) override {
    /// Not C2 compliant, the module depends on a node outside of "modules.<module_name>".
    auto enable_tls = cfg["enableTls"].AsBool();
    auto certificate_path = cfg["certficiatePath"].AsString();
}
```

## `Z3` - Request/Response Context Documentation

ZIAPI doesn't impose a norm for the request/response context. However, modules **MUST** be shipped with sufficient documentation regarding the context fields they write to and read from.

Modules **SHOULD** try to populate the context with primitive types only or basic `std` types (Like `std::string`).

#### Example

If the `MyPreProcessor` module depends on the following context:

```c++
void MyPreProcessor::PreProcess(http::Context &ctx, http::Request &req)
{
    auto client_address = std::any_cast<std::string>(ctx["client.socket.address"]);
    ctx["php_cgi.user.is_authenticated"] = (client_address == "127.0.0.1");
}
```

Then the `MyPreProcessor` module's documentation must explicitly state that it expects:
- `ctx["client.socket.address"]` to be defined as a `std::string`

The documentation must also state that the module plans to:
- Write a boolean value inside `ctx["user.is_authenticated"]`

## `Z4` - Standard Request/Response Context Fields

Each request/response is associated with a `ziapi::http::Context` to allow modules to communicate data.

The following fields are standard fields and **SHOULD** be populated according to the following specification.

| Key                     | Type            | Description                                                                |
|-------------------------|-----------------|----------------------------------------------------------------------------|
| `client.socket.address` | `std::string`   | The IP address of the client. May only be mutated by `INetworkModule`s     |
| `client.socket.port`    | `std::uint16_t` | The port of the client's socket. May only be mutated by  `INetworkModule`s |
