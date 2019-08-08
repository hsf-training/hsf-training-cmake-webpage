---
title: "Finding Packages"
teaching: 10
exercises: 0
questions:
- "How do I search for packages?"
objectives:
- "Understand FindPackage.cmake"
- "Understand PackageConfig.cmake"
keypoints:
- "CMake can find packages for you"
---

You can [search for packages](https://cmake.org/cmake/help/latest/command/find_package.html) in CMake in [two ways](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html); both of them, however, use the same interface. Here's what it would look like:

```cmake
find_package(MyPackage 1.2)
```

This will look for a file in the `CMAKE_MODULE_PATH` that is named `FindMyPackage.cmake`. If it does not find one, it will look for a file named `MyPackageConfig.cmake` in several places, including `MyPackage_DIR` if that variable exists. You can only perform one of these searches with `MODULE` or `CONFIG`, respectively.

You can add `COMPONENTS` in some cases, if the package supports it, and you can also add `QUIET` to hide extra text, or `REQUIRED` to cause a missing package to fail the configure step.

## FindPackage

The older method for finding packages is the FindPackage.cmake method (`MODULE`). This is a CMake or user supplied search script that knows how to look for a package. While there are some conventions here, and some tools to help, there are not many hard-and-fast requirements. A package should at least set the variable `Package_FOUND`. There are 100 or so find packages included in CMake, refer to the documentation for each.

* See the [included FindPackages here](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html#find-modules).
* Many of the packages took a *long* time to add imported targets
* The old PythonLibs and PythonInterp are in the process of being replaced, but you need a very new version of CMake for the new ones.

## PackageConfig

The "better" way to do things is to have an installed package provide its own details to CMake; these are "CONFIG" files and come with many packages. These files can be simpler and smarter, since they don't have to search for the package and query the options, but rather can be generated with the correct paths and options for a particular install. ROOT is an example of a package that is now providing a CONFIG file; another one that is just beginning to is Boost; while CMake includes a FindBoost.cmake, it has to be updated with each new Boost release, whereas BoostConfig.cmake can be included with each Boost release (first version in 1.70). One issue with some packages (TBB, for example) is that they may provide *optional* CONFIG files, and your packager may not have activated them.


{% include links.md %}
