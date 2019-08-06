---
title: "Variables explained"
teaching: 10
exercises: 20
questions:
- "How do variables work?"
objectives:
- "Know how to use variables"
keypoints:
- "Work with variables in CMake"
---


# Variables

For this exercise, we will just directly run a CMake Script, instead of running `CMakeLists.txt`. The command to do so is:

```bash
cmake -P example.cmake
```

This way, we don't have so many little builds sitting around. 

## Local variables

Let's start with a local variable.

```cmake
# local.cmake
set(MY_VARIABLE "I am a variable")
message(STATUS "${MY_VARIABLE}")
```

Here we see the set command, which sets a variable, and the message command, which prints out a string. We are printing a `STATUS` message - there are other types (many other types in CMake 3.15+).

> ## More about variables
> 
> Try the following:
> * Remove the quotes in set. What happens?
> * Remove the quotes in message. What happens? Why?
> * Try setting a cached variable using `-DMY_VARIABLE=something` *before* the `-P`. Which variable is shown?
> 
{:.challenge}


## Cached variables

Now, let's look at cached variables; a key ingredient in all CMake builds. In a build, cached variables are set in the command line or in a graphical tool (such as ccmake, cmake-gui), and then written to a file called `CMakeCache.txt`. When you rerun, the cache is read in before starting, so that CMake "remembers" what you ran it with. For our example, we will use CMake in script mode, and that will not write out a cache, which makes it easier to play with. Feel free to look back at the example you built in the last lesson and investigate the `CMakeCache.txt` file in your build directory there. Things like the compiler location, as discovered or set on the first run, are cached.


Here's what a cached variable looks like:

```cmake
# cache.cmake
set(MY_CACHE_VAR "I am a cached variable" CACHE STRING "Description")
message(STATUS "${MY_CACHE_VAR}")
```

We have to include the variable type here, which we didn't have to do before (but we could have) - it helps graphical CMake tools show the correct options. The main difference is the `CACHE` keyword and the description. If you were to run `cmake -L` or `cmake -LH`, you would see all the cached variables and descriptions.

The normal set command *only* sets the cached variable if it is not already set - this allows you to override cached variables with `-D`. Try:

```bash
cmake -DMY_CACHE_VAR="command line" -P cache.cmake
```

You can use `FORCE` to set a cached variable even if it already set; this should not be very common. Since cached variables are global, sometimes they get used as a makeshift global variable - the keyword `INTERNAL` is identical to `STRING FORCE`, and hides the variable from listings/GUIs.

Since bool cached variables are so common for builds, there is a shortcut syntax for making one:

```cmake
 option(MY_OPTION "On or off" OFF)
```

## Other variables

You can get environment variables with `$ENV{name}`. Properties are a form of variable that is attached to a target; you can use `get_property` and `set_property`, or `get_target_properties` and `set_target_properties` (stylistic preference) to access and set these.


> ## Handy tip:
> Use `include(CMakePrintHelpers)` to add the useful commands `cmake_print_properties` and `cmake_print_variables` to save yourself some typing when debugging variables and properties.
{:.callout}

## Globbing

There are several commands that help with strings, files, lists, and the like. Let's take a quick look at one of the most interesting: glob.

```cmake
file(GLOB OUTPUT_VAR *.cxx)
```

This will make a list of all files that match the pattern and put it into `OUTPUT_VAR`. You can also use `GLOB_RECURSE`, which will recurse subdirectories. There are several useful options, which you can look at [in the documentation](https://cmake.org/cmake/help/latest/command/file.html?highlight=glob#filesystem), but one is particularly important: `CONFIGURE_DEPENDS` (CMake 3.12+).

When you rerun the *build* step (not the configure step), then unless you set`CONFIGURE_DEPENDS`, your build tool will not check to see if you have added any new files that now pass the glob. This is the reason poorly written CMake projects often have issues when you are trying to add files; some people are in the habit of rerunning `cmake` before every build because of this. You shouldn't ever have to manually reconfigure; the build tool will rerun CMake as needed with this one exception. If you add `CONFIGURE_DEPENDS`, then *most* build tools will actually start checking glob too. The classic rule of CMake was "never glob"; the new rule is "never glob, but if you have to, add `CONFIGURE_DEPENDS`".

> ## More reading
> 
> * Based on [Modern CMake basics/variables][]
> * Also see [CMake's docs](https://cmake.org/cmake/help/latest/index.html)
{:.checklist}


[Modern CMake basics/variable]: https://cliutils.gitlab.io/modern-cmake/chapters/basics/variables.html