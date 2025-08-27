# Create the library from source files
add_library(lib
    src/ast.cpp

    # parser combinator
    src/parser/basic.cpp
    src/parser/util.cpp
    src/parser/extended.cpp
)


target_include_directories(lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
