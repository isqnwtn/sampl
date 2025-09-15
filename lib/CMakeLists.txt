# Create the library from source files
add_library(lib
    # parser combinator
    src/parser/basic.cpp
    src/parser/util.cpp
    src/parser/extended.cpp
    src/parser/expr.cpp
    src/parser/statement.cpp
    # ast
    src/ast/expr.cpp
)


target_include_directories(lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
