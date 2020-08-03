cmake_minimum_required(VERSION 3.14...3.18)

project(MyDebugExample LANGUAGES C)

set(SOURCES simple_lib.c)
set(HEADERS simple_lib.h)

add_library(simple_lib ${SOURCES} ${HEADERS})

add_executable(simple_example simple_example.c)

target_link_libraries(simple_example PUBLIC simple_lib)

# Does -lm work? (notice this is find_library, not find_package) Saves the
# location of the m library in a variable named MATH_LIBRARY
find_library(MATH_LIBRARY m)

# If there is a -lm, let's use it
if(MATH_LIBRARY)
  target_link_libraries(simple_lib PUBLIC ${MATH_LIBRARY})
endif()
