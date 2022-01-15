cmake_minimum_required(VERSION 3.17)

# The name of the CMake project
project(Template)

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
else()
    # The bin name of your project
    set(BIN binary)
endif()

# The build flags
if(UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)
elseif(WIN32)
    add_compile_options(/W4)
endif()

# The location of your main
set(MAIN src/main.cpp)

# The list of source files
set(SOURCES
    # fill here
)

# The list of tests source files
set(TEST_SOURCES
    tests/test.cpp
)

if(UNIT_TESTS)
    add_executable(${BIN}
        ${SOURCES}
        ${TEST_SOURCES}
    )
    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(${BIN})
    target_link_libraries(${BIN} PRIVATE gtest_main)
else()
    add_executable(${BIN}
        ${MAIN}
        ${SOURCES}
    )
endif()

# The include path of your project
target_include_directories(${BIN} PRIVATE include)