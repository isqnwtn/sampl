cmake_minimum_required(VERSION 3.10)

project(sampl-tests)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(expr-tests main.cpp)
    # this linking causes some free() related errors, hence commented it out
    # enable it back after investigating the issue
    # target_link_libraries(foo-tests Boost::unit_test_framework)
endif()
