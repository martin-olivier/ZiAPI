# Modules 101

The goal of this guide is to build a module as a dynamic library and load it at runtime

## Documentation

- [modules](https://github.com/martin-olivier/ZiAPI/blob/main/docs/general/MODULES.md)  
- [dylib](https://github.com/martin-olivier/dylib)

## Setup Build

Here is the repo architecture of this example:
```
.
├── CMakeLists.txt
└── src
    ├── main.cpp
    └── module.cpp
```

Let's create a `CMakeLists` to build our binary `zia` and our dynamic library `module`:

```cmake
cmake_minimum_required(VERSION 3.17)

# The name of the CMake project
project(TestZia)

# The C++ standard you want to use for your project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

add_executable(zia src/main.cpp)

# Fetch ZiAPI

include(ExternalProject)

ExternalProject_Add(
    ziapi
    GIT_REPOSITORY  https://github.com/martin-olivier/ZiAPI.git
    GIT_TAG         v1.0.0
    INSTALL_COMMAND ""
    TEST_COMMAND    ""
)

add_dependencies(zia ziapi)
ExternalProject_Get_Property(ziapi SOURCE_DIR)
include_directories(${SOURCE_DIR}/include)

if(UNIX)
    target_link_libraries(zia PRIVATE dl)
endif()

# Build Our Dynamic Lib

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_library(module SHARED src/module.cpp)

# running the below CMake rule will allow you to remove the prefix `lib` for macOS and linux, ensuring
# that the library shares the same name on all the different OS:
# https://github.com/martin-olivier/dylib#remove-the-lib-prefix
set_target_properties(module PROPERTIES PREFIX "")

add_dependencies(module ziapi)
```

After that lets implement `module.cpp` that will be build into a dynamic lib:
```c++
#include "dylib/dylib.hpp"
#include "ziapi/Module.hpp"

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
        return "A module implementation example";
    }
};

DYLIB_API ziapi::IModule *LoadZiaModule() { return new Module; }
```

And then let's implement our `main.cpp` that will load the dynamic lib:

```c++
#include "ziapi/Logger.hpp"
#include "ziapi/Module.hpp"
#include "dylib/dylib.hpp"

int main()
{
    try {
        // Create a dynamic lib object that will load the module
        dylib lib("./module", dylib::extension);
        // Get the function that will generate our module when called
        auto entry_point_fn = lib.get_function<ziapi::IModule *()>("LoadZiaModule");
        // Call the function to get a module instance
        std::unique_ptr<ziapi::IModule> mod(entry_point_fn());
        // Print information about the module using the logger
        ziapi::Logger::Info("Module loaded: ", mod->GetName(), " - ", mod->GetDescription());
    }
    catch (const dylib::exception &e) {
        // Catch exceptions around a dynamic lib (handle or symbol errors) and print them using the logger
        ziapi::Logger::Error(e.what());
    }
    return 0;
}
```

Let's run our binary:
```sh
> ./zia
Sun Jan 23 16:07:41 2022 [i] Module loaded: module_name - A module implementation example
```
