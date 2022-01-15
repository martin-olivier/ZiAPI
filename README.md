# CppTemplate

## :book: Summary
  - [:book: Summary](#book-summary)
  - [:warning: Requirement](#warning-requirement)
  - [:computer: Usage](#computer-usage)
    - [:rocket: Clone repository](#rocket-clone-repository)
    - [:wrench: Setup repository](#wrench-setup-repository)
  - [:hammer: Build](#hammer-build)
  - [:bust_in_silhouette: Authors](#bust_in_silhouette-authors)

## :warning: Requirement

- [CMake >= 3.17](https://cmake.org/download/)
- [C++17](https://en.cppreference.com/w/cpp/17)
- [Python3](https://www.python.org/download/releases/3.0/)

## :computer: Usage

### :rocket: Clone repository

```sh
git clone https://github.com/martin-olivier/CppTemplate
```

### :wrench: Setup repository

```sh
python3 setup.py
```

## :hammer: Build

With Makefile:
```sh
# to build the program
make
./binary

# to build the tests
make tests
./unit_tests
```

With CMake:
```sh
# to build the program
cmake . -B build
cmake --build build
./binary

# to build the tests
cmake . -B build_tests -DUNIT_TESTS=ON
cmake --build build_tests
./unit_tests
```

## :bust_in_silhouette: Authors

 - [Martin Olivier](https://github.com/martin-olivier)
 - [Coline Seguret](https://github.com/Cleopha)