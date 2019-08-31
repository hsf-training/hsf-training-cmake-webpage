---
title: "Building with CMake"
teaching: 10
exercises: 10
questions:
- "How do I build a project?"
objectives:
- "Know how to build a project with CMake"
keypoints:
- "Use out-of-source builds"
---

# Installing CMake

It's usually only 1 or so lines to install a recent version of CMake almost anywhere; see [CMake Instructions][].

# Building with CMake

Before writing CMake, let's make sure you know how to run it to make things. This is true for almost all CMake projects, which is almost everything.

> ## Try it out
> Let's get a project and try to build it. For fun, let's build CLI11:
>
> ```bash
> git clone --recursive https://github.com/CLIUtils/CLI11.git
> cd CLI11
> ```
>
> Note: the `--recursive` flag, which is spelled `--recurse-submodules` in newer versions of git (the old spelling still works) just tells git to download any submodules too, if you haven't seen that before. If you are short on space, use `--recurse-submodules=extern/googletest` to only get the one submodule we care about. If you forget to add the flag, running `git submodule update --init` will get all the submodules for you after you've cloned.
>
> Now, from the newly downloaded directory, let's try the classic CMake build procedure:
>
> ~~~bash
> mkdir build
> cd build
> cmake ..
> make
> ctest
> ~~~
{:.challenge}

This will make a **build directory**, change to it, then run the `cmake` command *from the build directory, pointing to the source directory*. CMake will configure and generate makefiles by default, as well as set all options to their default settings and cache them into a file called CMakeCache.txt, which will sit here in the build directory. You can call the build directory anything you want; by convention it should have the word `build` in it to be ignored by most package's `.gitignore` files.

> ## Warning about in-source builds
>
> Never do an "in-source" build - that is, run `cmake .` from the source directory. It will pollute your source directory with build outputs, CMake configuration files, and will disable out-of-source builds. A few packages do not allow the source directory to even sit inside the build directory; if that is the case, you need to change the relative path `..` accordingly.
>
> Just to clarify, you can point CMake at either the source directory from the build directory, or at an *existing* build directory from anywhere.
{: .discussion}

> ## Other syntax choices
>
> You have some freedom here. You can use:
>
> ~~~bash
> cmake --build .
> ~~~
>
> to build without referring to the build tool itself.
>
> A very new way to work with CMake (3.13+) and build directories is to run CMake from the source directory:
>
> ~~~bash
> cmake -S . -B build
> cmake --build build
> ~~~
>
> In some cases this may be more natural, and requires much less directory switching. A few commands (like `ctest` do not work outside the build directory, though.
{: .callout}



## Picking a compiler

Selecting a compiler must be done on the first run in an empty directory. It's not CMake syntax per se, but you might not be familiar with it. To pick Clang:

```bash
# From build directory
CC=clang CXX=clang++ cmake ..

# Or from source directory (CMake 3.13+)
CC=clang CXX=clang++ cmake -S . -B build
```

That sets the environment variables in bash for CC and CXX, and CMake will respect those variables. This sets it just for that one line, but that's the only time you'll need those; afterwards CMake continues to use the paths it deduces from those values.

## Picking a generator

You can build with a variety of tools; `make` is usually the default. To see all the tools CMake knows about on your system, run

```bash
cmake --help
```

And you can pick a tool with `-G"My Tool"` (quotes only needed if spaces are in the tool name). You should pick a tool on your first CMake call in a directory, just like the compiler. Feel free to have several build directories, like `build` and `buildXcode`.
You can set the environment variable `CMAKE_GENERATOR` to control the default generator (CMake 3.15+).
Note that makefiles will only run in parallel if you explicitly pass a number of threads, such as `make -j2`, while Ninja will automatically run in parallel. You can directly pass a parallelization option such as `-j2` to the `cmake --build .` command in recent versions of CMake.

## Setting options

You set options in CMake with `-D`. You can see a list of options with `-L`, or a list with human-readable help with `-LH`. If you don't list the source/build directory, the listing will not rerun CMake (`cmake -L` instead of `cmake -L .`).

## Verbose and partial builds

Again, not really CMake, but if you are using a command line build tool like `make`, you can get verbose builds:

```bash
VERBOSE=1 make
```

You can actually write `make VERBOSE=1`, and make will also do the right thing, though that's a feature of `make` and not the command line in general. In CMake 3.14, verbose mode was added to the build options, so `cmake --build . -v` will activate the verbose mode of your build tool.

You can also build just a part of a build by specifying a target, such as the name of a library or executable you've defined in CMake, and make will just build that target.

## Options

CMake has support for cached options. A Variable in CMake can be marked as "cached", which means it will be written to the cache (a file called `CMakeCache.txt` in the build directory) when it is encountered. You can preset (or change) the value of a cached option on the command line with `-D`. When CMake looks for a cached variable, it will use the existing value and will not overwrite it.

### Standard options

These are common CMake options to most packages:

* `-DCMAKE_BUILD_TYPE=` Pick from `Release`, `RelWithDebInfo`, `Debug`, or sometimes more.
* `-DCMAKE_INSTALL_PREFIX=` The location to install to. System install on UNIX would often be `/usr/local` (the default), user directories are often `~/.local`, or you can pick a folder.
* `-DBUILD_SHARED_LIBS=` You can set this `ON` or `OFF` to control the default for shared libraries (the author can pick one vs. the other explicitly instead of using the default, though)
* `-DBUILD_TESTING=` This is a common name for enabling tests, not all packages use it, though, sometimes with good reason.

> ## Try it out
>
> In the CLI11 repository you cloned:
>
> * Check to see what options are available
> * Change a value; maybe set `CLI11_CXX_STD` to 14 or turn off testing.
>
{:.challenge}

## Debugging your CMake files

We've already mentioned verbose output for the build, but you can also see verbose CMake configure output too. The `--trace` option will print every line of CMake that is run. Since this is very verbose, CMake 3.7 added `--trace-source="filename"`, which will print out every executed line of just the file you are interested in when it runs. If you select the name of the file you are interested in debugging (usually with a parent directory if you are debugging a CMakeLists.txt, since all of those have the same name), you can just see the lines that run in that file. Very useful!

> ## Try it out
>
> Run the following from the source directory:
>
> ```bash
> cmake build --trace-source="CMakeLists.txt"
> ```
{:.challenge}

> ## Answer this
> Question: Does `cmake build` build anything?
>
> > ## Answer
> > No, the "build" here is the directory. This will configure (create build system files). To build, you would add `--build` before the directory, or use your build tool, such as `make`.
> {:.solution}
{:.challenge}

> ## More reading
>
> * Based on [Modern CMake intro/running][]
{:.checklist}

[Modern CMake intro/running]: https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html]

{% include links.md %}
