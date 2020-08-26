---
title: Debugging
teaching: 10
exercises: 10
questions:
- How do I debug everything?
objectives:
- Know how to find problems in CMake
- Know how to set up builds for debugging
keypoints:
- There are several methods for debugging your CMake code.
- CMake can help you debug and profile your source code.
---

Debugging is easy with CMake. We'll cover two forms of debugging: debugging your CMake code, and
debugging your C++ code.


# CMake debugging

First, let's look at ways to debug a CMakeLists or other CMake file.

### Printing variables

The time honored method of print statements looks like this in CMake:

```cmake
message(STATUS "MY_VARIABLE=${MY_VARIABLE}")
```

However, a built in module makes this even easier:

```cmake
include(CMakePrintHelpers)
cmake_print_variables(MY_VARIABLE)
```

If you want to print out a property, this is much, much nicer! Instead of getting the properties one
by one of of each target (or other item with properties, such as `SOURCES`, `DIRECTORIES`, `TESTS`,
or `CACHE_ENTRIES` - global properties seem to be missing for some reason), you can simply list them
and get them printed directly:

```cmake
cmake_print_properties(
    TARGETS my_target
    PROPERTIES POSITION_INDEPENDENT_CODE
)
```

> ## Warning
>
> You can't acually access [`SOURCES`][], since it conflictes with the `SOURCES` keyword in the
> function.
{:.callout}


### Tracing a run

Have you wanted to watch exactly what happens in your CMake file, and when? The
`--trace-source="filename"` feature is fantastic. Every line run in the file that you give will be
echoed to the screen when it is run, letting you follow exactly what is happening. There are related
options as well, but they tend to bury you in output.

> ## Watching a build
> Let's try this out. Let's go to the [`code/04-debug`]() folder and configure with trace mode on:
>
> ```bash
> cmake -S . -B build --trace-source=CMakeLists.txt
> ```
>
> Try adding `--trace-expand` too. What is the difference? How about replacing
> `--trace-source=CMakeLists.txt` with `--trace`?
>
{:.challenge}

# C++ debugging

To run a C++ debugger, you need to set several flags in your build. CMake does this for you with
"build types". You can run CMake with `CMAKE_BUILD_TYPE=Debug` for full debugging, or
`RelWithDebInfo` for a release build with some extra debug info. You can also use `Release` for an
optimized release build, or `MinSizeRel` for a minimum size release (which I've never used).

<div class="challenge"><h2>Debug example</h2>

<details><summary>C++ code (click to expand)</summary>
{% include hl_code.html lang="cmake" file="code/04-debug/simple_lib.c" %}
</details>

{% capture tmp %}
Let's try it. Go to `code/04-debug`, and build in debug mode. Our program has a bug. Let's try it
out in a debugger.

```bash
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
gdb build-debug/simple_example
```

Now, since we think there's a problem in `my_sin`, let's set a breakpoint in `my_sin`. Note that
I'm providing the gdb commands on the left, and lldb commands on the right.

```
# GDB                # LLDB
break my_sin         breakpoint set --name my_sin
r                    r
```

Now, let's watch what happens to the sign variable. Set a watchpoint:

```
# GDB                # LLDB
watch sign           watchpoint set variable sign
c                    c
```

Keep running continue (`c`). Do you see the problem?
{% endcapture %}
{{ tmp | markdownify }}
</div>

> ## Aside: Linking to math
>
> You may find that the example provided does not work unless it's linked with the math library "m",
> which looks like `-lm` when linking with gcc (llvm does not seem to need to link to it). Let's
> look for the "m" library:
>
> ~~~cmake
> # Does -lm work? (notice this is find_library, not find_package)
>  > find_library(MATH_LIBRARY m)
> ~~~
>
> If it is found, this saves the location of the m library in a variable that we gave it the name
> of, in our case, `MATH_LIBRARY`. We can add the path (not a target) using the same
> [`target_link_libraries`][] command. It is very unfortunate that this command happens to accept
> both targets and raw paths and linker flags, but it's a historical leftover.
>
> ~~~cmake
> # If there is a -lm, let's use it
> if(MATH_LIBRARY)
>     target_link_libraries(simple_lib PUBLIC ${MATH_LIBRARY})
> endif()
> ~~~
{: .callout}


Note that CMake defaults to an "empty" build type, which is neither optimized nor debug. You can
[fix this manually](https://cliutils.gitlab.io/modern-cmake/chapters/features.html), or always
specify a build type.

Adopting a convention from Linux, all build types append compiler flags from the environment variables [`CFLAGS`][], [`CXXFLAGS`][], [`CUDAFLAGS`][], and [`LDFLAGS`][] ([full list](https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html#id4)). This feature is often used by package management software, in conjunction with the already mentioned [`CC`][], [`CXX`][], [`CUDACXX`][], and [`CUDAHOSTCXX`][] environment variables. Otherwise, you can set the release and debug flags separately.

# Common needs

There are several common utilities that CMake can integrate with to help you with your builds. Here
are just a few:

* [`CMAKE_CXX_COMPILER_LAUNCHER`][] can set up a compiler launcher, like `ccache`, to speed up your
  builds.
* [`CMAKE_CXX_CLANG_TIDY`][] can run clang-tidy to help you clean up your code.
* [`CMAKE_CXX_CPPCHECK`][] for cppcheck.
* [`CMAKE_CXX_CPPLINT`][] for cpplint.
* [`CMAKE_CXX_INCLUDE_WHAT_YOU_USE`][] for iwyu.

You can set these when building if you want.

[`code/04-debug`]: {{ site.baseurl }}/code/04-debug

{% include links.md %}
{% include cmake_links.md %}
