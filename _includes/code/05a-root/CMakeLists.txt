cmake_minimum_required(VERSION 3.15...3.21)

project(RootUseFileExample LANGUAGES CXX)

# 6.16 fixes a bug in ROOT_EXE_LINKER_FLAGS, especially on macOS
find_package(ROOT 6.16 CONFIG REQUIRED)

include("${ROOT_USE_FILE}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(DictExample SHARED DictExample.cxx DictExample.h G__DictExample.cxx)

root_generate_dictionary(G__DictExample DictExample.h LINKDEF DictLinkDef.h)

target_link_libraries(DictExample PUBLIC ${ROOT_LIBRARIES})
