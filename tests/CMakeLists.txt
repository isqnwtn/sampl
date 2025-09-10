cmake_minimum_required(VERSION 3.10)

project(sampl-tests)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(sampl-tests main.cpp)
    target_link_libraries(sampl-tests PRIVATE lib
        # this causes some free() error
        #Boost::unit_test_framework
    )
endif()
