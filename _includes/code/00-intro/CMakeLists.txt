# This is required in all CMakeLists
# Selecting a nice minimum version and range
cmake_minimum_required(VERSION 3.14...3.18)

# We can call the project anything we want
# Listing the language(s) avoids the C + CXX default
project(MyExample00 LANGUAGES C)

# We need an executable target
add_executable(simple_example
  simple.c
)

