# ZiAPI

## :book: Summary
  - [:book: Summary](#book-summary)
  - [:computer: Usage](#computer-usage)
    - [:rocket: Fetch ZiAPI using CMake](#rocket-fetch-ziapi-using-cmake)
    - [:white_check_mark: Build and run unit tests](#white_check_mark-build-and-run-unit-tests)
  - [:bust_in_silhouette: Authors](#bust_in_silhouette-authors)

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
