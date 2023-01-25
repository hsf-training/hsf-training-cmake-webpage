---
title: Introduction
teaching: 10
exercises: 0
questions:
- What is the difference between a build system and a build system generator?
objectives:
- Learn about build systems and build system generators.
- Understand why CMake is used.
- Newer CMake is better.
keypoints:
- Build systems describe exactly how to build targets.
- Build system generators describe general relationships.
- Modern CMake is simpler and reduces the chance of build problems.
---

Building code is hard. You need long commands to build each part of your code; and you need do to
this on many parts of your code.

So people came up with **Build Systems**; these had ways set up dependencies (such as file A needs
to be built to build file B), and ways to store the commands used to build each file or type of
file. These are language independent (mostly), allowing you to setup builds of almost anything; you
can use `make` to build LaTeX documents if you wish. Some common build systems include make (the
classic pervasive one), ninja (a newer one from Google designed in the age of build system
generators), invoke (a Python one), and rake (Ruby make, nice syntax for Ruby users).

However, this is:

* Mostly hand coded: You have to know all the proper commands
* Platform/compiler dependent: You have to build the commands for each compiler.
* Not aware of dependencies: If you require a library, you have to handle the paths, etc.
* Hard to extend; if you want to use an IDE instead, good luck.

Enter **Build System Generators** (hereby labeled BSGs for brevity). These understand the concepts
of your programming language build; they usually support common compilers, languages, libraries, and
output formats. These usually write a build system (or IDE) file and then let that do the actually
build. The most popular BSG is CMake, which stands for Cross-platform Make. But as we've just shown,
it is not really in the same category as make. Other BSGs include Autotools (old, inflexible), Bazel
(by Google), SCons (older Python system), Meson (young Python system, very opinionated), and a few
others. But CMake has unparalleled support by IDEs, libraries, and compilers.  It also scales very
well, with small projects able to pick it up easily (modern CMake, anyway), and massive projects
 like the CERN experiments being about to use it for thousands of modules.

<script type="text/javascript" src="https://ssl.gstatic.com/trends_nrtr/2674_RC03/embed_loader.js"></script> <script type="text/javascript"> trends.embed.renderExploreWidget("TIMESERIES", {"comparisonItem":[{"keyword":"/m/0cxh7f","geo":"US","time":"2004-01-01 2021-10-18"},{"keyword":"/g/11cmy51gz6","geo":"US","time":"2004-01-01 2021-10-18"},{"keyword":"/g/11bzyq50jp","geo":"US","time":"2004-01-01 2021-10-18"},{"keyword":"/m/0170rr","geo":"US","time":"2004-01-01 2021-10-18"},{"keyword":"/m/04dl04","geo":"US","time":"2004-01-01 2021-10-18"}],"category":0,"property":""}, {"exploreQuery":"date=all&geo=US&q=%2Fm%2F0cxh7f,%2Fg%2F11cmy51gz6,%2Fg%2F11bzyq50jp,%2Fm%2F0170rr,%2Fm%2F04dl04","guestPath":"https://trends.google.com:443/trends/embed/"}); </script>


Note that both CMake and Make are custom languages rather than being built in an existing language,
like rake and SCons, etc. While it is nice to consolidate languages, the requirement that you have
an external language installed and configured was too high for any of these to catch on for general
use.

To recap, you should use CMake if:

* You want to avoid hard-coding paths
* You need to build a package on more than one computer
* You want to use CI (continuous integration)
* You need to support different OSs (maybe even just flavors of Unix)
* You want to support multiple compilers
* You want to use an IDE, but maybe not all of the time
* You want to describe how your program is structured logically, not flags and commands
* You want to use a library
* You want to use tools, like Clang-Tidy, to help you code
* You want to use a debugger


## (More) Modern CMake

CMake has really changed dramatically since it was introduced around 2000. And, by the time of 2.8,
it was available in lots of Linux Distribution package managers. However, this means there often are
really old versions of CMake "available by default" in your environment. Please, please upgrade and
design for newer CMake. No one likes writing or debugging build systems. Using a newer version can
cut your build system code in less than half, reduce bugs, integrate better with external
dependents, and more. Installing CMake can be as little as one line, and doesn't require sudo
access. [See more info
here](https://cliutils.gitlab.io/modern-cmake/chapters/intro/installing.html).

Somehow, this is difficult to understand, so I'll shout it to make it clearer. **Writing Modern
CMake reduces your chances of build problems**. The tools CMake provides are _better_ than the ones
you will try to write yourself. CMake works with more compilers, in more situations, than you do.
So if you try to add a flag, you'll likely get it wrong for some compilers or OSs, but if you can
use a tool CMake gives you instead, then that's CMake's business to get right and not yours.

It's not a big deal to install a newer CMake. The issues people open for "this is broken" *far*
outnumber the issues people open because you required a CMake newer than they want to run (I think
I've only seen one of those, and they came around when they saw the feature they would have to give
up).

> ## Example of Modern CMake
>
> **Bad 2.8 style CMake**: Adding a C++11 flag manually. This is compiler specific, is different for
> CUDA, and locks in a set version, rather than a minimum version.
>
> **If you require CMake 3.1+**, you can set `CXX_STANDARD`, but only on a final target. Or you can
> manually list `compile_features` for individual C++11 and C++14 features, and, and all targets using
> yours will get at least that level set on them.
>
> **If you require CMake 3.8+**, you can just use `compile_features` to set a _minimium_ standard level,
> like `cxx_std_11`, instead of manually listing a bunch of features. This was used for C++17 and later
> C++20 and C__23, exclusively.
>
{: .callout}


## Selecting a minimum in 2023:

What minimum CMake should you _run_ locally, and what minimum should you _support_ for people using your
code? Since you are reading this, you should be able to get a release in the last few versions of CMake;
do that, it will make your development easier. For support, there are two ways to pick minimums: based on
features added (which is what a developer cares about), or on common pre-installed CMakes (which is what a
user cares about).

Never select a minimum version older than the oldest compiler version you support. CMake should always be
at least as new as your compiler.

### What minimum to choose - OS support:

* 3.4: The bare minimum. Never set less.
* 3.7: Debian old-stable.
* 3.10: Ubuntu 18.04.
* 3.11: CentOS 8 (use EPEL or AppSteams, though)
* 3.13: Debian stable.
* 3.16: Ubuntu 20.04.
* 3.19: First to support Apple Silicon.
* latest: pip/conda-forge/homebew/chocolaty, etc.

### What minimum to choose - Features:

* 3.8: C++ meta features, CUDA, lots more
* 3.11: `IMPORTED INTERFACE` setting, faster, FetchContent, `COMPILE_LANGUAGE` in IDEs
* 3.12: C++20, `cmake --build build -j N`, `SHELL:`, FindPython
* 3.14/3.15: CLI, FindPython updates
* 3.16: Unity builds / precompiled headers, CUDA meta features
* 3.17/3.18: Lots more CUDA, metaprogramming
* 3.20: C++23, CUDARCHS, IntelLLVM, NVHPC
* 3.21: Different message types, MSVC 2022, C17 & C23, HIP, MSYS
* 3.24: Package finder integration with downloads, `--fresh`
* 3.25: C++26 support, LTO for CUDA

## Other sources

There are some other places to find good information on the web. Here are some of them:

{% include showlinks.md %}

{% include links.md %}
