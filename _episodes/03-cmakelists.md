---
title: "Your first CMakeLists.txt file"
teaching: 10
exercises: 10
questions:
- "How little can I get away with in my CMakeLists?"
objectives:
- "Know how to write a CMakeLists.txt file"
keypoints:
- "Write CMakeLists.txt files"
---


# Writing a CMakeLists

The following file is fine for the following examples:

```c
/* simple.c or simple.cpp */
#include <stdio.h>

int main() {
    printf("Hello, World!");
    return 0;
}
```

This file can be compiled with C or C++.

## Starting off

This is the simplest possible `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.14)

project(MyProject)

add_executable(myexample simple.cpp)
```

Let's look at the three lines:

1. The `cmake_minimum_required` command sets the policies so that the build is exactly like it would
   be on the listed version of CMake - in other words, CMake "dumbs itself down" to the version you
   request for any features that could produce a different build. This makes CMake almost perfectly
   backwards compatible.
2. You need to be working on a project, and it needs at least a name. CMake assumes a `CXX` (that's
   C++) and `C` mixed project if you don't give any `LANGUAGES`.
3. You need at least one library or executable to do anything interesting. The "thing" you make here
   is called a "target", and the executable/library has the same name, by default, and it has to be
   unique in the project.

Those commands have a few extra arguments that you can give:

```cmake
cmake_minimum_required(VERSION 3.14...3.18)

project(MyProject
  VERSION
    1.0
  DESCRIPTION
    "Very nice project"
  LANGUAGES
    CXX
)

add_executable(myexample simple.cpp)
```

1. You can specify a range of versions - this will cause the policies to be set to
   the highest supported value in that range. As a general rule, set the highest version you've
   tested with here.
2. Projects can have versions, descriptions, and languages.
3. Whitespace doesn't matter. Be clear/pretty, or use
   [cmake-format](https://cmake-format.readthedocs.io/en/latest/).



<div class="challenge"><h2>Try it out</h2>
{%- capture tmp -%}
Build and run the example code with a `CMakeLists.txt` similar to the one above.

~~~bash
git clone https://github.com/henryiii/cmake_workshop.git
cd cmake_workshop/code/00-intro
~~~
{%- endcapture %}
{{ tmp | markdownify }}
<div class="solution"><h2>Solution</h2>
{% highlight cmake %}
{% include code/00-intro/CMakeLists.txt %}
{% endhighlight %}
</div>
</div>


> ## More reading
>
> * Based on [Modern CMake basics][]
{:.checklist}

[Modern CMake Basics]: https://cliutils.gitlab.io/modern-cmake/chapters/basics.html
