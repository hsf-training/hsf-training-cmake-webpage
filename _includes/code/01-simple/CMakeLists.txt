cmake_minimum_required(VERSION 3.15...3.21)

project(MyExample01 LANGUAGES CXX)

# This is the library Including the headers is not required, but is nice for
# users
add_library(simple_lib simple_lib.cpp simple_lib.hpp)

# The above line *did not* set the includes - we need to We can also set ., and
# it should be expanded to the current source dir

target_include_directories(simple_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Adding definitions
target_compile_definitions(simple_lib PUBLIC MYLIB_PUBLIC)
target_compile_definitions(simple_lib PRIVATE MYLIB_PRIVATE)

# Require a C++ feature (here: at least C++11)
target_compile_features(simple_lib PUBLIC cxx_std_11)

# Now add the executable
add_executable(simple_example simple_example.cpp)

# Adding the all-important link to simple-lib
target_link_libraries(simple_example PUBLIC simple_lib)
