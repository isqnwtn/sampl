cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_POLICY_DEFAULT_CMP0167 NEW)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set build type
set(CMAKE_BUILD_TYPE Debug)

# for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories
add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(tests)
