cmake_minimum_required(VERSION 3.14...3.18)

project(RootTargetExample LANGUAGES CXX)

# 6.16 fixes a bug in ROOT_EXE_LINKER_FLAGS, expecially on macOS
find_package(ROOT 6.16 CONFIG REQUIRED)

# Get the generate dictionary command from ROOT
if(ROOT_VERSION VERSION_LESS 6.20)
  include("${ROOT_DIR}/modules/RootNewMacros.cmake")
else()
  include("${ROOT_DIR}/RootMacros.cmake")
endif()

# Make the dictionary, produces G__DictExample.cxx
root_generate_dictionary(G__DictExample DictExample.h LINKDEF DictLinkDef.h)

add_library(DictExample SHARED DictExample.cxx DictExample.h G__DictExample.cxx)
target_include_directories(DictExample PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Normally you need to link to lots of ROOT:: targets, but we aren't using much
# here.
target_link_libraries(DictExample PUBLIC ROOT::Core)
