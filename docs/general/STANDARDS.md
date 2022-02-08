# ZIAPI Standards

A set of rules that define a standard implementation of a ZIAPI module to make it easier to share modules between groups.

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119).

## C1 - Module Configuration Documentation

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

## C2 - Configuration file layout

To limit friction when sharing modules, all groups **MAY** implement the following configuration file layout where:
- The top level node is a `ziapi::config::Dict`
- It contains a `modules` key which is a `ziapi::config::Dict` too.
- Each module which requires a configuration fetches its configuration information from `modules.<module_name>*`

#### Example

To illustrate this, let's look at a YAML configuration file example.

Let's say we have two modules respectively named `tls` and `directoryListing`. By applying rule C2 we get the following configuration.

```yaml
modules:
    tls:
        foo: bar
    directoryListing:
        foo: bar
```

Therefore it is **NOT RECOMMENDED** to depend on configuration fields outside of the `modules.<module_name>` scope like so:

```c++
void Init(const ziapi::config::Node &cfg) override {
    /// Not C2 compliant, the module depends on a node outside of "modules.<module_name>".
    auto enable_tls = cfg["enableTls"].AsBool();
    auto certificate_path = cfg["certficiatePath"].AsString();
}
```
