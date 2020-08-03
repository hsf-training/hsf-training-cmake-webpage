---
title: "Project Structure"
teaching: 10
exercises: 10
questions:
- "What should my project look like?"
objectives:
- "Understand best practices for project structure"
keypoints:
- "Projects should have a standard structure"
---


For this section, we will be looking at the project in `code/03-structure`.

First, take a look at the main `CMakeLists.txt` file. This is an example of a nice project file in
CMake 3.14, so enjoy it for a minute. Now let's look at specifics!

### Protect project code

The parts of the project that only make sense if we are building this as the main project are
protected; this allows the project to be included in a larger master project with
`add_subdirectory`.

### Testing handled in the main CMakeLists

We have to do a little setup for testing in the main CMakeLists, because you can't run
`enable_testing` from a subdirectory (and thereby `include(CTest)`). Also, notice that
`BUILD_TESTING` does not turn on testing unless this is the main project.

### Finding packages

We find packages in our main CMakeLists, then use them in subdirectories. We could have also put
them in a file that was `inlude`d, such as `cmake/find_pakages.cmake`. If your CMake is new enough,
you can even add a subdirectory with the find packages commands, but you have to set
`IMPORTED_GLOBAL` on the targets you want to make available if you do that. For small to mid-size
projects, the first option is most common, and large projects use the second option (currently).

All the find packages here provide imported targets. If you do not have an imported target, **make
one**! Never use the raw variables past the lines immediately following the `find_package` command.

In this project, I use the new FetchContent to download several dependencies; although normally I
prefer git submodules in `/extern`.

### Source

Now follow the `add_subdirectory` command to see the src folder, where a library is created.

The headers are listed along with the sources in the `add_library` command. This would have been
another way to do it in CMake 3.11+:

```cmake
add_library(modern_library)
target_sources(modern_library
  PRIVATE
    lib.cpp
  PUBLIC
    ${HEADER_LIST}
)
```

Notice that we have to use `target_include_directories`; just adding a header to the sources does
not tell CMake what the correct include directory for it should be.

We also set up the `target_link_libraries` with the appropriate targets.

### App

Now take a look at `apps/CMakeLists.txt`. This one is pretty simple, since all the leg work for
using our library was done on the library target, as it should be.


### Docs and Tests


Feel free to look at `docs` and `tests` for their `CMakeLists.txt`.


> ## More reading
>
> * Based on [Modern CMake basics/structure][]
{:.checklist}


[Modern CMake basics/structure]: https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html



{% include links.md %}
