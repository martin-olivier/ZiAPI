# ZiAPI

[![ZiAPI](https://img.shields.io/badge/ZiAPI-v1.0.0-blue.svg)](https://github.com/martin-olivier/ZiAPI/releases/tag/v1.0.0)
[![CPP Version](https://img.shields.io/badge/C++-17_and_above-darkgreen.svg)](https://isocpp.org/)

[![GitHub watchers](https://img.shields.io/github/watchers/martin-olivier/ZiAPI?style=social)](https://github.com/martin-olivier/ZiAPI/watchers/)
[![GitHub forks](https://img.shields.io/github/forks/martin-olivier/ZiAPI?style=social)](https://github.com/martin-olivier/ZiAPI/network/members/)
[![GitHub stars](https://img.shields.io/github/stars/martin-olivier/ZiAPI?style=social)](https://github.com/martin-olivier/ZiAPI/stargazers/)

[![workflow](https://github.com/martin-olivier/ZiAPI/actions/workflows/CI.yml/badge.svg)](https://github.com/martin-olivier/ZiAPI/actions/workflows/CI.yml)

## :book: Summary
  - [:book: Summary](#book-summary)
  - [:speech_balloon: Introduction](#speech_balloon-introduction)
  - [:computer: Usage](#computer-usage)
    - [:rocket: Fetch ZiAPI using CMake](#rocket-fetch-ziapi-using-cmake)
    - [:white_check_mark: Build and run unit tests](#white_check_mark-build-and-run-unit-tests)
  - [:bust_in_silhouette: Authors](#bust_in_silhouette-authors)

## :speech_balloon: Introduction

- ziapi documentation is available [HERE](https://github.com/martin-olivier/ZiAPI/tree/main/docs)  
- dylib documentation is available [HERE](https://github.com/martin-olivier/dylib)

## :computer: Usage

### :rocket: Fetch ZiAPI using CMake

Add the following content to your CMakeLists to fetch the API and include its header files in your project:
```cmake
include(ExternalProject)

ExternalProject_Add(
    ziapi
    GIT_REPOSITORY  https://github.com/martin-olivier/ZiAPI.git
    GIT_TAG         origin/main
    INSTALL_COMMAND ""
    TEST_COMMAND    ""
)

add_dependencies(zia ziapi)
ExternalProject_Get_Property(ziapi SOURCE_DIR)
target_include_directories(zia PRIVATE ${SOURCE_DIR}/include)
```

> :bulb: Don't forget to link with `libdl` on Unix is you use `dylib`:
```cmake
if(UNIX)
    target_link_libraries(zia PRIVATE dl)
endif()
```

### :white_check_mark: Build and run unit tests

After cloning the repository, run the following commands:
```sh
cmake . -B build -DUNIT_TESTS=ON
cmake --build build
./unit_tests
```

## :bust_in_silhouette: Authors

 - [Martin Olivier](https://github.com/martin-olivier)
 - [Diego Rojas](https://github.com/rojasdiegopro)
 - [Edouard Sengeissen](https://github.com/edouard-sn)
 - [Nicolas Allain](https://github.com/Nirasak)
 - [Romain Minguet](https://github.com/Romain-1)
 - [Allan Debeve](https://github.com/Gfaim)
