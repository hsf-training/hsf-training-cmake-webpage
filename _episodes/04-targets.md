---
title: Working with Targets
teaching: 10
exercises: 15
questions:
- How do targets work?
objectives:
- Know how to set up targets
- Understand linking and INTERFACE properties
- Make INTERFACE targets
keypoints:
- Libraries and executables are targets.
- Targets have lots of useful properties.
- Targets can be linked to other target.
- You can control what parts of a target get inherited when linking.
- You can make INTERFACE targets instead of making variables.
---


# Targets

Now you know how to compile a single file using three lines of CMake. But what happens if you have
more than one file with dependencies? You need to be able to tell CMake about the structure of your
project, and it will help you build it. To do so, you will need targets.

You've already seen a target:

```cmake
add_executable(myexample simple.cpp)
```

This creates an "executable" target with the name `myexample`. Target names must be unique (and there
is a way to set the executable name to something other than the target name if you really want to).

Targets are much like "objects" in other languages; they have properties (member variables) that
hold information. The [`SOURCES`][] property, for example, will have `simple.cpp` in it.

Another type of target is a library:

```cmake
add_library(mylibrary simplelib.cpp)
```

You can add the keywords `STATIC`, `SHARED`, or `MODULE` if you know what kind of library you want
to make; the default is sort-of an "auto" library that is user selectable with `BUILD_SHARED_LIBS`.

You can make non-built libraries too. More on that later, once we see what we can do with targets.

## Linking

Once you have several targets, you can describe the relationship between them with
[`target_link_libraries`][] and a keyword; one of `PUBLIC`, `PRIVATE`, and `INTERFACE`. Don't forget
this keyword when making a library! CMake goes into an old compatibility mode for this target that
generally breaks things.

> ## Question
>
> You have a library, `my_lib`, made from `my_lib.hpp` and `my_lib.cpp`. It requires at least C++14
> to compile. If you then add `my_exe`, and it needs `my_lib`, should that force `my_exe` to compile
> with C++14 or better?
>
> > ## Answer
> >
> > This depends on the header. If the header contains C++14, this is a PUBLIC requirement - both
> > the library and it's users need it. However, if the header is valid in all versions of C++, and
> > only the implementations inside `my_lib.cpp` require C++14, then this is a `PRIVATE` requirement
> > - users don't need to be forced into C++14 mode.
> >
> > Maybe you do require users have C++14, but your library can compile with any version of C++.
> > This would be an `INTERFACE` requirement.
> {:.solution}
>
{:.challenge}



![Example of Public and Private inheritance](../fig/04-mermaid-libs.svg){:height="500px" }

<!--
Spaces added to -- > to allow comment to continue
graph TD
P(Public Library) -- > |PUBLIC| M((Main Library))
R(Private Library) -- > |PRIVATE| M
I(Interface Library) -- > |INTERFACE| T
P -- > |PUBLIC| T
M -- > T{Target: mylibrary}
T -- > E[Target: myprogram]
-->

Figure 1: Example of PUBLIC, PRIVATE, and INTERFACE. `myprogram` will build the three libraries it
sees through `mylibrary`; the private library will not affect it.

There are two collections of properties on every target that can be filled with values; the
"private" properties control what happens when you build that target, and the "interface" properties
tell targets linked to this one what to do when building. The `PUBLIC` keyword fills both property
fields at the same time.

## Example 1: Include directories

When you run [`target_include_directories(TargetA PRIVATE mydir)`][`target_include_directories`], then
the [`INCLUDE_DIRECTORIES`][] property of `TargetA` has `mydir` appended. If you use the keyword
`INTERFACE` instead, then [`INTERFACE_INCLUDE_DIRECTORIES`][] is appended to, instead. If you use
`PUBLIC`, then both properties are appended to at the same time.

## Example 2: C++ standard

There is a C++ standard property - [`CXX_STANDARD`][]. You can set this property, and like many
properties in CMake, it gets it's default value from a [`CMAKE_CXX_STANDARD`][] variable if it is set,
but there is no INTERFACE version - you cannot force a [`CXX_STANDARD`][] via a target. What would you
do if you had a C++11 interface target and a C++14 interface target and linked to both?

By the way, there _is_ a way to handle this - you can specify the minimum compile features you need
to compile a target; the `cxx_std_11` and similar meta-features are perfect for this - your target
will compile with at least the highest level specified, unless [`CXX_STANDARD`][] is set (and that's
a nice, clear error if you set [`CXX_STANDARD`][] too low). [`target_compile_features`][] can fill
[`COMPILE_FEATURES`][] and [`INTERFACE_COMPILE_FEATURES`][], just like directories in example 1.


<div class="challenge"><h2>Try it out</h2>
{%- capture tmp -%}
Get this repository and go to the example. Try to write a CMakeLists that will correctly build.

~~~bash
git clone https://github.com/hsf-training/hsf-training-cmake-webpage.git
cd hsf-training-cmake-webpage/code/01-simple
~~~

The files here are:
* simple_lib.cpp: Must be compiled with `MYLIB_PRIVATE` and `MYLIB_PUBLIC` defined.
* simple_example.cpp: Must be compiled with `MYLIB_PUBLIC` defined, but not `MYLIB_PRIVATE`

Use [`target_compile_definitions(<target> <private or public>
<definition(s)>)`][`target_compile_definitions`] to set the definitions on `simple_lib`.
{%- endcapture %}
{{ tmp | markdownify }}
<div class="solution"><h2>Solution</h2>
{% include hl_code.html lang="cmake" file="code/01-simple/CMakeLists.txt" %}
</div>
</div>


### Things you can set on targets
* [`target_link_libraries`][]: Other targets; can also pass library names directly
* [`target_include_directories`][]: Include directories
* [`target_compile_features`][]: The compiler features you need activated, like `cxx_std_11`
* [`target_compile_definitions`][]: Definitions
* [`target_compile_options`][]: More general compile flags
* [`target_link_directories`][]: Don't use, give full paths instead (CMake 3.13+)
* [`target_link_options`][]: General link flags (CMake 3.13+)
* [`target_sources`][]: Add source files

See more [commands here](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html).

## Other types of targets

You might be really excited by targets and are already planning out how you can describe your
programs in terms of targets. That's great! However, you'll quickly run into two more situations
where the target language is useful, but you need some extra flexibility over what we've covered.

First, you might have a library that conceptually should be a target, but doesn't actually have any
built components - a "header-only" library. These are called interface libraries in CMake and you
would write:

```cmake
add_library(some_header_only_lib INTERFACE)
```

Notice you didn't need to add any source files. Now you can set `INTERFACE` properties on this only
(since there is no built component).

The second situation is if you have a pre-built library that you want to use. This is called an
imported library in CMake, and uses the keyword `IMPORTED`.  Imported libraries can also be
`INTERFACE` libraries, they can be built and modified using the same syntax as other libraries
(starting in CMake 3.11), and they can have `::` in their name. (`ALIAS` libraries, which simply
rename some other library, are also allowed to have `::`). Most of the time you will get imported
libraries from other places, and will not be making your own.

> ## INTERFACE IMPORTED
>
> What about [`INTERFACE IMPORTED`](https://cmake.org/cmake/help/latest/command/add_library.html#id6)?
> The difference comes down to two things:
>
> 1. `IMPORTED` targets are not exportable. If you save your targets, you can't save IMPORTED ones -
>    they need to be recreated (or found again).
> 2. `IMPORTED` header include directories will always be marked as `SYSTEM`.
>
> Therefore, an `IMPORTED` target should represent something that is not directly part of your
> package.
{:.callout}



> ## More reading
>
> * Based on [Modern CMake basics][]
> * Also see [CMake's docs](https://cmake.org/cmake/help/latest/index.html)
{:.checklist}

{% include cmake_links.md %}


[Modern CMake Basics]: https://cliutils.gitlab.io/modern-cmake/chapters/basics.html
