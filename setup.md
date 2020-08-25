---
title: Pre-workshop Material
---

Before working through the tutorial, please be diligent and read through this page and ensure you
are familiar with all of these computing skills.  They are essential for any HEP physicist
and will benefit you throughout your career.  However, if you are pressed for time in the next days
then **be sure to install and familiarize yourself with Docker**.

You can run these examples on any Linux-like system (or on Windows) if you have a compiler setup. To
keep this simple as possible, you can use a docker image to keep your modifications separate from
your system.

On your computer, you need to have:

* `git`
* `cmake` (Version 3.14 or newer). See the [instructions here][CMake Instructions].
* A C++ compiler - system default is fine.
* `make` or `ninja` (unless you are using Xcode/MSVC)

## [Docker][] based setup

[Docker][] is a powerful tool that allows you
to perform a virtualisation of your environment but completely in software.  It
allows you to bundle up the installation of tools for use by others in a uniform way
without changing your underlying system, and works on all major OS's (latest Windows 10 Update
_highly_ recommended, and required if you have Windows 10 Home).

### Setup: Ephemeral


A quick and minimal docker:

```bash
docker run --rm -it alpine
apk add git g++ cmake make
git clone https://github.com/hsf-training/hsf-training-cmake-webpage.git
cd hsf-training-cmake-webpage
```


This does *not* make a volume, so you will lose whatever you do in here when it exits.

### Setup: Persistent

This will allow you to keep your changes, which is both good (if you want to revisit them) and bad
(if you want to know exactly what went into making them).

```bash
git clone https://github.com/hsf-training/hsf-training-cmake-webpage.git
cd hsf-training-cmake-webpage
docker run -v $PWD:/cmake_work --rm -it alpine

apk add g++ cmake make
cd /cmake_work
```

The folder on your computer and docker folder are linked. Permissions/users will come from the
docker container.

{% include links.md %}
