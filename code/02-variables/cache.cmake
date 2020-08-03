# This is a CMake script

message(STATUS "Starting script")

set(MY_CACHE_VAR
    "I am a cached variable"
    CACHE STRING "Description")

message(STATUS "${MY_CACHE_VAR}")
