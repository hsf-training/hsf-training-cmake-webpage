---
title: Building with CMake
teaching: 10
exercises: 10
questions:
- How do I build a project?
objectives:
- Have a reference for installing CMake.
- Learn how to build an existing project.
- Customize the build.
- Learn how to do some basic debugging.
keypoints:
- Build a project.
- Use out-of-source builds.
- Build options and customization.
- Debug a CMakeLists easily.
---

# Installing CMake

It's usually only one line or maybe two to install a recent version of CMake almost anywhere; see
[CMake Instructions][].

# Building with CMake

Before writing CMake, let's make sure you know how to run it to make things. This is true for almost
all CMake projects, which is almost everything.

> ## Try it out
> Let's get a project and try to build it. For fun, let's build CLI11:
>
> ```bash
> git clone https://github.com/CLIUtils/CLI11.git
> cd CLI11
> ```
>
> Now, from the newly downloaded directory, let's try the modern CMake (3.14) build procedure:
>
> ~~~bash
> cmake -S . -B build
> cmake --build build
> cmake --build build -t test
> ~~~
{:.challenge}

This will make a **build directory** (`-B`) if it does not exist, with the **source directory**
defined as `-S`.  CMake will configure and generate makefiles by default, as well as set all options
to their default settings and cache them into a file called `CMakeCache.txt`, which will sit in the
build directory. You can call the build directory anything you want; by convention it should have
the word `build` in it to be ignored by most package's `.gitignore` files.

You can then invoke your build system (line 2). Regardless of whether you used `make` (the default),
`ninja`, or even an IDE-based system, you can build with a uniform command. You can add `-j 2` to
build on two cores, or `-v` to verbosely show commands used to build.

Finally, you can even run your tests from here, by passing the "test" target to the underlying build
system. `-t` (`--target` before CMake 3.15) lets you select a target. There's also a `cmake <dir>
--install` command in CMake 3.15+ that does the install - without invoking the underlying build system!

> ## Warning about in-source builds
>
> Never do an "in-source" build - that is, run `cmake .` from the source directory. It will pollute
> your source directory with build outputs, CMake configuration files, and will disable
> out-of-source builds. A few packages do not allow the source directory to even sit inside the
> build directory; if that is the case, you need to change the relative path `..` accordingly.
>
> Just to clarify, you can point CMake at either the source directory from the build directory, or
> at an *existing* build directory from anywhere.
{: .discussion}

> ## Other syntax choices
>
> The classic, battle hardened method should be shown for completeness:
>
> ~~~bash
> mkdir build
> cd build
> cmake ..
> make
> make test
> ~~~
>
> This has several downsides. If the directory already exists, you have to add `-p`, but that
> doesn't work on Windows. You can't as easily change between build directories, because you are in
> it. It's more lines, and if you forget to change to the build directory, and you use `cmake .`
> instead of `cmake ..`, then you can pollute your source directory.
{: .callout}



## Picking a compiler

Selecting a compiler must be done on the first run in an empty directory. It's not CMake syntax per
se, but you might not be familiar with it. To pick Clang:

```bash
CC=clang CXX=clang++ cmake -S . -B build
```

That sets the environment variables in bash for [`CC`][] and [`CXX`][], and CMake will respect those
variables.  This sets it just for that one line, but that's the only time you'll need those;
afterwards CMake continues to use the paths it deduces from those values.

## Picking a generator

You can build with a variety of tools; `make` is usually the default. To see all the tools CMake
knows about on your system, run

```bash
cmake --help
```

And you can pick a tool with `-G"My Tool"` (quotes only needed if spaces are in the tool name). You
should pick a tool on your first CMake call in a directory, just like the compiler. Feel free to
have several build directories, like `build` and `build-xcode`.  You can set the environment variable
[`CMAKE_GENERATOR`][] to control the default generator (CMake 3.15+).  Note that makefiles will only
run in parallel if you explicitly pass a number of threads, such as `make -j2`, while Ninja will
automatically run in parallel. You can directly pass a parallelization option such as `-j 2` to the
`cmake --build .` command in recent versions of CMake as well.

## Setting options

You set options in CMake with `-D`. You can see a list of options with `-L`, or a list with
human-readable help with `-LH`.

## Verbose and partial builds

Again, not really CMake, but if you are using a command line build tool like `make`, you can get
verbose builds:

```bash
cmake --build build -v
```

If you are using make directly, you can write `VERBOSE=1 make` or even `make VERBOSE=1`, and make
will also do the right thing, though writing a variable after a command is a feature of `make` and
not the command line in general.

You can also build just a part of a build by specifying a target, such as the name of a library or
executable you've defined in CMake, and make will just build that target. That's the `--target`
(`-t` in CMake 3.15+) option.

## Options

CMake has support for cached options. A Variable in CMake can be marked as "cached", which means it
will be written to the cache (a file called `CMakeCache.txt` in the build directory) when it is
encountered. You can preset (or change) the value of a cached option on the command line with `-D`.
When CMake looks for a cached variable, it will use the existing value and will not overwrite it.

### Standard options

These are common CMake options to most packages:

* [`CMAKE_BUILD_TYPE`][]: Pick from `Release`, `RelWithDebInfo`, `Debug`, or sometimes more.
* [`CMAKE_INSTALL_PREFIX`][]: The location to install to. System install on UNIX would often be
  `/usr/local` (the default), user directories are often `~/.local`, or you can pick a folder.
* [`BUILD_SHARED_LIBS`][]: You can set this `ON` or `OFF` to control the default for shared libraries
  (the author can pick one vs. the other explicitly instead of using the default, though)
* [`BUILD_TESTING`][`CTest`]: This is a common name for enabling tests, not all packages use it, though,
  sometimes with good reason.

> ## Try it out
>
> In the CLI11 repository you cloned:
>
> * Check to see what options are available
> * Change a value; maybe set [`CMAKE_CXX_STANDARD`][] to `14` or turn off testing.
> * Configure with `CMAKE_INSTALL_PREFIX=install`, then install it into that local directory. Make
>   sure it shows up there!
>
{:.challenge}

## Debugging your CMake files

We've already mentioned verbose output for the build, but you can also see verbose CMake configure
output too. The `--trace` option will print every line of CMake that is run. Since this is very
verbose, CMake 3.7 added `--trace-source="filename"`, which will print out every executed line of
just the file you are interested in when it runs. If you select the name of the file you are
interested in debugging (usually with a parent directory if you are debugging a CMakeLists.txt,
since all of those have the same name), you can just see the lines that run in that file. Very
useful!

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
> > No, the "build" here is the directory. This will configure (create build system files). To
> > build, you would add `--build` before the directory, or use your build tool, such as `make`.
> {:.solution}
{:.challenge}

> ## More reading
>
> * Based on [Modern CMake intro/running][]
{:.checklist}

[Modern CMake intro/running]: https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html

{% include links.md %}

{% include cmake_links.md %}
