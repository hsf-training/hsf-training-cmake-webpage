---
title: "Functions in CMake"
teaching: 10
exercises: 0
questions:
- "How do I write my own CMake commands?"
objectives:
- "Know how to make a macro or a function in CMake"
keypoints:
- "CMake can be very powerfully customized"
---

Let's take a look at making a CMake macro or function. The only difference is in scope; a macro does not make a new scope, while a function does.

```cmake
function(EXAMPLE_FUNCTION AN_ARGUMENT)
    set(${AN_ARGUMENT}_LOCAL "I'm in the local scope")
    set(${AN_ARGUMENT}_PARENT "I'm in the parent scope" PARENT_SCOPE)
endfunction()

example_function() # Error
example_function(ONE)
example_function(TWO THREE) # Not error

message(STATUS "${ONE_LOCAL}") # What does this print?
message(STATUS "${ONE_PARENT}") # What does this print?
```

We see the basics of functions above. You can specify required positional arguments after the name; all other arguments are set in `ARGN`; `ARGV` holds all arguments, even the listed positional ones. Since you name variables with strings, you can set variables using names. This is enough to recreate any of the CMake commands. But there's one more thing...


### Parsing arguments

You'll have noticed that there are conventions to calling CMake commands; most commands have all-caps keywords that take 0, 1, or an unlimited number of arguments. This handling is standardized in the [`cmake_parse_arguments`](https://cmake.org/cmake/help/latest/command/cmake_parse_arguments.html) command. Here's how it works:

```cmake
function(COMPLEX)
    cmake_parse_arguments(
        COMPLEX_PREFIX
        "SINGLE;ANOTHER"
        "ONE_VALUE;ALSO_ONE_VALUE"
        "MULTI_VALUES"
        ${ARGN}
    )
endfunction()

complex(SINGLE ONE_VALUE value MULTI_VALUES some other values)
```
The first argument is a prefix that will be attached to the results. The next three arguments are lists, one with single keywords (no arguments), one with keywords that take one argument each, and one with keywords that take any number of arguments. The final argument is `${ARGN}` or `${ARGV}`, without quotes (it will be expanded here). If you are in a function and not a macro, you can use `PARSE_ARGV <N>` at the start of the call, where N is the number of positional arguments to expect. This method allows simicolons in the arguments.

Inside the function, you'll find:

```cmake
COMPLEX_PREFIX_SINGLE = TRUE
COMPLEX_PREFIX_ANOTHER = FALSE
COMPLEX_PREFIX_ONE_VALUE = "value"
COMPLEX_PREFIX_ALSO_ONE_VALUE = <UNDEFINED>
COMPLEX_PREFIX_MULTI_VALUES = "some;other;values"
COMPLEX_PREFIX_UNPARSED_ARGUMENTS = <UNDEFINED>
```

The simicolons here are an explicit CMake list; you can use other methods to make this simpler at the cost of more lines of code.

> ## More reading
> 
> * Based on [Modern CMake basics/functions][]
{:.checklist}

[Modern CMake basics/functions]: https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html]

{% include links.md %}
