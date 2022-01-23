# Modules Documentation

The ZIAPI features 4 different types of modules:
- `INetworkModule`
- `IPreProcessorModule`
- `IHandlerModule`
- `IPostProcessorModule`

Each module is invoked at a different stage in the request lifecycle. If you remember from the [Getting started](GETTING_STARTED.md) page of the documentation, a goes through 5 different steps when received by our HTTP server. Let's see which steps correspond to which module.
- **1. Receive** step is handled by `INetworkModule`.
- **2. Pre-process** step is handled by `IPreProcessorModule`.
- **3. Handle** step is handled by `IHandlerModule`.
- **4. Post-process** step is handled by `IPostProcessorModule`.
- **5. Send** step is handled by `INetworkModule`.

We'll see each of these modules types detail, but first, let's look at the `IModule` interface.

## The `IModule` interface

Each **ZIAPI** module type inherits from `IModule`. It features very basic methods to make it easier to manage modules.

```c++
void IModule::Init(const IConfig &cfg);

Version IModule::GetVersion() const;

Version IModule::GetCompatibleApiVersion() const;

const char *IModule::GetName() const;

const char *IModule::GetDescription() const;
```

There's not much to say about this interface. Every module must implement it so we can have access to its version, name, description...

## `INetworkModule`

## `IPreProcessingModule`

## `IHandlerModule`

## `IPostProcessingModule`
