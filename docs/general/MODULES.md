# Modules Documentation

Let's see how all these different steps translate into modules!

The **ZIAPI** features multiple **module types**.
- `INetworkModule`
- `IPreProcessingModule`
- `IHandlerModule`
- `IPostProcessingModule`

Let's take a look at each of them but first let's check the `IModule` interface.

## `IModule`

Each **ZIAPI** module type inherits from `IModule`. It features very basic methods to make it easier to manage modules.

```c++
void IModule::Init(const IConfig &cfg);

Version IModule::GetVersion() const;

Version IModule::GetCompatibleApiVersion() const;

const char *IModule::GetName() const;

const char *IModule::GetDescription() const;
```

## `INetworkModule`

## `IPreProcessingModule`

## `IHandlerModule`

## `IPostProcessingModule`
