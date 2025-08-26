# Create the library from source files
add_library(lib
    src/ast.cpp
    src/parser.cpp

    # parser combinator
    src/parser/combinator/basic.cpp
    src/parser/rdd/basic.cpp
)


target_include_directories(lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
