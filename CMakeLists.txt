cmake_minimum_required(VERSION 3.17)

# The name of the CMake project
project(ziapi)

# The C++ standard you want to use for your project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

option(UNIT_TESTS "When sets to ON, build the unit tests" OFF)

if(UNIT_TESTS)

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
)

add_executable(${BIN}
    ${SOURCES}
    ${TEST_SOURCES}
)
enable_testing()
include(GoogleTest)
gtest_discover_tests(${BIN})
target_link_libraries(${BIN} PRIVATE gtest_main)

# The include path
include_directories(${PROJECT_SOURCE_DIR}/include)

endif()