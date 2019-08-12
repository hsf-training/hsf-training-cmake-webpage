---
title: "Your first CMakeLists.txt file"
teaching: 10
exercises: 10
questions:
- "How little can I get away with in my CMakeLists?"
objectives:
- "Know how to write a CMakeLists.txt file"
keypoints:
- "Write CMakeLists.txt files"
---


# Writing a CMakeLists

The following file is fine for the following examples:

```c
/* simple.c or simple.cpp */
#include <stdio.h>

int main() {
    printf("Hello, World!");
    return 0;
}
```

This file can be compiled with C or C++.

## Starting off

This is the simplest possible CMakeLists:

```cmake
cmake_minimum_required(VERSION 3.11)

project(MyProject)
   
add_executable(myexample simple.cpp)
```

Let's look at the three lines:

1. The `cmake_minimum_required` command sets the policies so that the build is exactly like it would be on the listed version of CMake - in other words, CMake "dumbs itself down" to the version you request for any features that could produce a different build.
2. You need to be working on a project, and it needs at least a name. CMake assumes a `CXX` (that's C++) and `C` mixed project if you don't give any `LANGUAGES`.
3. You need at least one library or executable to do anything interesting.

Those commands have a few extra arguments that you can give:

```cmake
cmake_minimum_required(VERSION 3.11...3.15)

project(MyProject
  VERSION
    1.0
  DESCRIPTION
    "Very nice project"
  LANGUAGES
    CXX
)
   
add_executable(myexample simple.cpp)
```

1. You can specify a range of minimum versions - this will cause the minimum version to be set to the highest supported value in that range.
2. Projects can have versions, descriptions, and languages.


> ## Try it out
> 
> Build and run the example code with the example `CMakeLists.txt`.
{:.challenge}


> ## More reading
> 
> * Based on [Modern CMake basics][]
{:.checklist}

[Modern CMake Basics]: https://cliutils.gitlab.io/modern-cmake/chapters/basics.html
