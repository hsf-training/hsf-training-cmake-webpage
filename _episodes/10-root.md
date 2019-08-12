---
title: "ROOT"
teaching: 10
exercises: 10
questions:
- "How do I use ROOT?"
objectives:
- "Use ROOT a couple of different ways"
keypoints:
- "ROOT has a CONFIG package"
---

Let's try a couple of ROOT examples; one with the classic variable/global configure and one with the newer target method. You will need a ROOT install or a ROOT docker container to run these examples. If you don't want to use the ATLAS one, you can use `rootproject/root:latest`, which is an official fedora based build. Conda-Forge ROOT + CMake would work too, if you like Conda.

For these examples, you should be using a recent version of ROOT - especially for targets, which is still being worked on. The CONFIG files were added in 6.10, and targets received a lot of work in 6.14+. 6.16 has pretty decent targets.

## Example 1: UseROOT

Change to the `code/05a-root` directory.  Run:

```bash
cmake -S . -B build
cd build
make
root -b -q -x ../CheckLoad.C
```

{% highlight cmake %}
{% include code/05a-root/CMakeLists.txt %}
{% endhighlight %}



## Example 2: Targets

Change to the `code/05b-root` directory. Run the same command above.

{% highlight cmake %}
{% include code/05b-root/CMakeLists.txt %}
{% endhighlight %}

{% include links.md %}
