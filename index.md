---
layout: lesson
root: .  # Is the only page that doesn't follow the pattern /:path/index.html
permalink: index.html  # Is the only page that doesn't follow the pattern /:path/index.html
carpentry: "hsf"
---


{% if page.carpentry != site.carpentry %}
<div class="alert alert-warning">
You specified <code>carpentry: {{page.carpentry}}</code> in <code>index.md</code> and
<code>carpentry: {{site.carpentry}}</code> in <code>_config.yml</code>. Make sure you edit both files. After editing <code>_config.yml</code>, you need to run <code>make serve</code> again to
see the changes take effect locally.
</div>
{% endif %}

Welcome to HSF CMake tutorial! The aim of this tutorial is to cover the basics of using CMake. This
tutorial is based on the online book [Modern CMake][], with a focus on CMake 3.15+. This is in what
is [called the "More Modern" era](https://github.com/Bagira80/More-Modern-CMake) of CMake (roughly
defined as 3.12+), and includes the fantastic command line improvements in CMake π (3.14) and 3.15.
The current version at the time of writing is CMake 3.21.

This workshop covers the basics of making and building a project, and some details of design.

Designed and first taught at the [2019 USATLAS Computing Bootcamp at
LBNL](https://smeehan12.github.io/2019-08-19-usatlas-computing-bootcamp/) with the support of
[FIRST-HEP][] and [IRIS-HEP][]. Also taught at the [2020 USATLAS Computing Bootcamp](https://matthewfeickert.github.io/usatlas-computing-bootcamp-2020/)
and [2021 USATLAS Computing Bootcamp](https://jghaley.github.io/usatlas-computing-bootcamp-2021/).

> ## Prereqs
>
> * Basic knowledge of C or C++
> * [Basic unix shell](http://swcarpentry.github.io/shell-novice/)
>
>
{: .prereq}

{% include curriculum.html %}

{% include links.md %}
