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

Building code is hard. You need long commands to build each part of your code; and you need do to this on many parts of your code.

So people came up with **Build Systems**; these had ways set up dependencies (such as file A needs to be built to build file B), and ways to store the commands used to build each file or type of file. These are language independent (mostly), allowing you to setup builds of almost anything; you can use `make` to build LaTeX documents if you wish. Some common build systems include make (the classic pervasive one), ninja (a newer one from Google designed in the age of build system generators), and rake (Ruby make, nice syntax for Ruby users).

However, this is:

* Mostly hand coded: You have to know all the proper commands
* Platform/compiler dependent: You have to build the commands for each compiler.
* Not aware of dependencies: If you require a library, you have to handle the paths, etc.
* Hard to extend; if you want to use an IDE instead, good luck.

Enter **Build System Generators** (hereby labeled BSGs for brevity). These understand the concepts of your programming language build; they usually support common compilers, languages, libraries, and output formats. These usually write a build system (or IDE) file and then let that do the actually build. The most popular BSG is CMake, which stands for Cross-platform Make. But as we've just shown, it is not really in the same category as make. Other BSGs include Bazel (by Google), SCons (older Python system), Meson (very young Python system), and a few others. But CMake has unparalleled support by IDEs, libraries, and compilers.

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

CMake has really changed dramatically since it was introduced around 2000. And, by the time of 2.8, it was available in lots of Linux Distribution package managers. However, this means there often are really old versions of CMake "available by default" in your environment. Please, please upgrade and design for newer CMake. No one likes writing or debugging build systems. Using a newer version can cut your build system code in less than half, reduce bugs, integrate better with external dependents, and more. Installing CMake can be as little as one line, and doesn't require sudo access. [See more info here](https://cliutils.gitlab.io/modern-cmake/chapters/intro/installing.html).

Somehow, this is difficult to understand, so I'll shout it to make it clearer. **Writing Modern CMake
reduces your chances of build problems**. The tools CMake provides are _better_ than the ones
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
> **If you require CMake 3.1+**, you can set `CXX_STANDARD`, but only on a final target.
>
> **If you require CMake 3.8+**, you can just use `compile_features` to set a _minimium_ feature level
> you require, and all targets using yours will get at least that level set on them!
{: .callout}


## Other sources

There are some other places to find good information on the web. Here are some of them:

{% include showlinks.md %}

{% include links.md %}
