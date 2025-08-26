add_executable(app main.cpp)
# add_executable(gpt cgpt.cpp)

# Link the app to the library
target_link_libraries(app PRIVATE lib)
