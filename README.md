# ZiAPI

## :book: Summary
  - [:book: Summary](#book-summary)
  - [:computer: Usage](#computer-usage)
    - [:rocket: Fetch ZiAPI using CMake](#rocket-fetch-ziapi-using-cmake)
    - [:white_check_mark: Build and run unit tests](#white_check_mark-build-and-run-unit-tests)
  - [:bust_in_silhouette: Authors](#bust_in_silhouette-authors)

## :computer: Usage

### :rocket: Fetch ZiAPI using CMake

Add the following content to your CMakeLists to fetch the project and include the API headers:
```cmake
include(ExternalProject)

ExternalProject_Add(
    ZiAPI
    GIT_REPOSITORY  https://github.com/martin-olivier/ZiAPI
    GIT_TAG         origin/master
    INSTALL_COMMAND ""
    TEST_COMMAND    ""
)
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