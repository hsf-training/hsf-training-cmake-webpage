cmake_minimum_required(VERSION 3.14...3.18)

project(RootTargetExample LANGUAGES CXX)

find_package(ROOT 6.20 CONFIG REQUIRED)

# Get the generate dictionary command from ROOT
include("${ROOT_DIR}/RootMacros.cmake")

# Make the dictionary, produces G__DictExample.cxx
root_generate_dictionary(G__DictExample DictExample.h LINKDEF DictLinkDef.h)

add_library(DictExample SHARED DictExample.cxx DictExample.h G__DictExample.cxx)
target_include_directories(DictExample PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Normally you need to link to lots of ROOT:: targets, but we aren't using much
# here.
target_link_libraries(DictExample PUBLIC ROOT::Core)
