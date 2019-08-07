---
title: "Debugging"
teaching: 0
exercises: 0
questions:
- "What is CMake?"
objectives:
- "Understand why CMake is used"
- "Understand that CMake is not Make"
keypoints:
- "CMake is a build system generator"
---

Building code is hard. You need long commands to build each part of your code; and you need do to this on many parts of your code.

So people came up with **Build Systems**; these had ways set up dependencies (such as file A needs to be built to build file B), and ways to store the commands used to build each file or type of file. These are language independent (mostly), allowing you to setup builds of almost anything; you can use `make` to build LaTeX documents if you wish. Some common build systems include make (the classic pervasive one), ninja (a newer one from Google designed in the age of build system generators), and rake (Ruby make, nice syntax for Ruby users).

However, this is:

* Mostly hand coded: You have to know all the proper commands
* Platform/compiler dependent: You have to build the commands for each compiler.
* Not aware of dependencies: If you require a library, you have to handle the paths, etc.
* Hard to extend; if you want to use an IDE instead, good luck.

Enter **Build System Generators** (hereby labeled BSGs for brevity). These understand the concepts of your programming language build; they usually support common compilers, languages, libraries, and output formats. These usually write a build system (or IDE) file and then let that do the actually build. The most popular BSG is CMake, which stands for Cross-platform Make. But as we've just shown, it is not really in the same category as make. Other BSGs include Meson (by Google), SCons (older Python system), Meson (very young Python system), and a few others. But CMake has unparalleled support by IDEs, libraries, and compilers.

Note that both CMake and Make are custom languages rather than being built in an existing language, like rake and SCons, etc. While it is nice to consolidate languages, the requirement that you have an external language installed and configured was too high for any of these to catch on for general use.

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

CMake has really changed dramatically since it was introduced around 2000. And, by the time of 2.8, it was available in lots of Linux Distribution package managers. However, this means there often are really old versions of CMake "available by default" in your environment. Please, please upgrade and design for newer CMake. No one likes writing or debugging build systems[^1]. Using a newer version can cut your build system code in less than half, reduce bugs, integrate better with external dependants, and more. Installing CMake can be as little as one line, and doesn't require sudo access. [See more info here](https://cliutils.gitlab.io/modern-cmake/chapters/intro/installing.html).

## Other sources

There are some other places to find good information on the web. Here are some of them:

* [Modern CMake][]: The book this tutorial derives from.
* [The official help](https://cmake.org/cmake/help/latest/): Really amazing documentation. Nicely organized, great search, and you can toggle versions at the top. It just doesn't have a great "best practices tutorial", which is what this book tries to fill in.
* [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1): A great list of do's and don'ts.
* [Embracing Modern CMake](https://steveire.wordpress.com/2017/11/05/embracing-modern-cmake/): A post with good description of the term
* [It's time to do CMake Right](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/): A nice set of best practices for Modern CMake projects.
* [The Ultimate Guide to Modern CMake](https://rix0r.nl/blog/2015/08/13/cmake-guide/): A slightly dated post with similar intent.
* [More Modern CMake](https://youtu.be/y7ndUhdQuU8): A great presentation from Meeting C++ 2018 that recommends CMake 3.12+. This talk makes calls CMake 3.0+ "Modern CMake" and CMake 3.12+ "More Modern CMake".
* [toeb/moderncmake](https://github.com/toeb/moderncmake): A nice presentation and examples about CMake 3.5+, with intro to syntax through project organization

[Modern CMake]: https://cliutils.gitlab.io/modern-cmake/

{% include links.md %}
