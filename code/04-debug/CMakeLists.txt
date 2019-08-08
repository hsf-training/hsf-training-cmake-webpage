cmake_minimum_required(VERSION 3.11)

project(MyDebugExample LANGUAGES C)

set(SOURCES simple_lib.c)
set(HEADERS simple_lib.h)

add_library(simple_lib
    ${SOURCES}
    ${HEADERS}
)

add_executable(simple_example
  simple_example.c
)

target_link_libraries(simple_example PUBLIC simple_lib)
