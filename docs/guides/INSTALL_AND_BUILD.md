# Build and install guide

Let's take a look at how to build the project.

## Fetch ZiAPI using CMake

Add the following content to your `CMakeLists` to fetch the `ZiAPI` and include its header files in your project:
```cmake
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
```

> :bulb: Don't forget to link with `libdl` on Unix is you use `dylib`:
```cmake
if(UNIX)
    target_link_libraries(zia PRIVATE dl)
endif()
```

## Build and run unit tests

If you want to run unit tests on `ZiAPI`, do the following steps:
- Clone the ZiAPI repository
- Execute the following commands:
```
cmake . -B build -DUNIT_TESTS=ON
cmake --build build
./unit_tests
```
