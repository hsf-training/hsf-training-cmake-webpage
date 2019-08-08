---
title: "Common Problems and Solutions"
teaching: 5
exercises: 0
questions:
- "What could go possibly wrong?"
objectives:
- "Identify some common mistakes"
- "Fix problems"
keypoints:
- "Some mistakes are fixable"
---


Now let's take a look at some common problems with CMake code and with builds.

## 1: Low minimum CMake version

```cmake
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
```


Okay, I had to put this one in. But in some cases, just increasing this number fixes problems. 3.0 or less, for example, has a tendency to do the wrong thing when linking on macOS.

Solution: Either set a high minimum version or use the version range feature and CMake 3.12 or better.

## 2: Building inplace

CMake should never be used to build in-place; but it's easy to accidentally do so. And once it happens, you have to manually clean the directory before you can do an out-of-source build again. Because of this, while you can run `cmake .` from the build directory after the initial run, it's best to avoid this form just in case you forget and run it from the source directory. Also, you can add the following check to your CMakeLists.txt:

```cmake
### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()
```

One or two generated files cannot be avoided, but if you put this near the top, you can avoid most of the generated files as well as immediately notifying the user (possibly you) that you've made a mistake.

## 3: Picking a compiler

CMake may pick the wrong compiler on systems with multiple compilers. You can use the environment variables `CC` and `CXX` when you first configure, or CMake variables - but you need to pick the compiler *on the first run*; you can't just reconfigure to get a new compiler.




{% include links.md %}
