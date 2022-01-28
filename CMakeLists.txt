cmake_minimum_required(VERSION 3.17)

# The name of the CMake project
project(ziapi)

# The C++ standard you want to use for your project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

option(UNIT_TESTS "When sets to ON, build the unit tests" OFF)

if(UNIT_TESTS)

# Fetch GoogleTest
find_package(googletest QUIET)
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# The bin name for your unit tests
set(BIN unit_tests)
include(import/FetchGoogleTest.cmake)

# The build flags
if(UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)
elseif(WIN32)
    add_compile_options(/W4)
endif()

# The list of tests source files
set(TEST_SOURCES
    tests/Logger.cpp
    tests/Config.cpp
    tests/Compressor.cpp
    tests/Decompressor.cpp
    tests/Module.cpp
    tests/Version.cpp
)

add_executable(${BIN}
    ${SOURCES}
    ${TEST_SOURCES}
)
enable_testing()
include(GoogleTest)
gtest_discover_tests(${BIN})
target_link_libraries(${BIN} PRIVATE gtest_main)

if(UNIX)
    target_link_libraries(${BIN} PRIVATE dl)
endif()

# The include path
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/examples/modules
)

add_library(module SHARED examples/dylib/Module.cpp)
set_target_properties(module PROPERTIES PREFIX "")

add_dependencies(${BIN} module)

endif()
