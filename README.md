[![Licence](https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge)](./LICENSE)
![main workflow](https://github.com/isqnwtn/sampl/actions/workflows/main.yml/badge.svg)

# SaMPL
SaMPL is recursive acronym for SaMPL Meta Programming Language. It is a general purpose, statically typed,
multi-paradigm programming language with compile-time metaprogramming capabilities.

# Building

## Dependencies
- cmake
- gcc
- make
- Boost

## Steps
1. clone the repository
2. create a `build` directory
3. run `cmake ..`
4. run `cmake --build .`

# Testing
The unit tests for this project is written using Boost.Test.

## Steps
### Install Boost
1. Arch Linux - `sudo pacman -S boost`
2. Ubuntu - `sudo apt-get install libboost-all-dev`
3. Mac OS X - `brew install boost`

### Run the tests
1. run `make test`

## Status
- this project is in its early stages of development.

### 2025/08/27
- as of today there's a barely working parser in place.
