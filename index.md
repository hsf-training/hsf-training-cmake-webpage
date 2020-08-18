---
layout: lesson      # DON'T CHANGE THIS.
carpentry: "hsf"      # what kind of Carpentry (must be either "lc" or "dc" or "swc").
                      # Be sure to update the Carpentry type in _config.yml as well.
venue: "Virtual"         # brief name of host site without address (e.g., "Euphoric State University")
address: "Zoom"      # full street address of workshop (e.g., "Room A, 123 Forth Street, Blimingen, Euphoria")
country: "us"      # lowercase two-letter ISO country code such as "fr" (see https://en.wikipedia.org/wiki/ISO_3166-1#Current_codes)
language: "en"     # lowercase two-letter ISO language code such as "fr" (see https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes)
latlng: "37.876170,-122.242910"       # decimal latitude and longitude of workshop venue (e.g., "41.7901128,-87.6007318" - use https://www.latlong.net/)
humandate: "Aug 22, 2020"    # human-readable dates for the workshop (e.g., "Feb 17-18, 2020")
humantime: "9:00 am - 12:00 pm"    # human-readable times for the workshop (e.g., "9:00 am - 4:30 pm")
startdate: 2020-08-20      # machine-readable start date for the workshop in YYYY-MM-DD format like 2015-01-01
enddate: 2020-08-20        # machine-readable end date for the workshop in YYYY-MM-DD format like 2015-01-02
instructor: ["Henry Schreiner"] # boxed, comma-separated list of instructors' names as strings, like ["Kay McNulty", "Betty Jennings", "Betty Snyder"]
helper: ["FIXME"]     # boxed, comma-separated list of helpers' names, like ["Marlyn Wescoff", "Fran Bilas", "Ruth Lichterman"]
email: ["fixme@example.org"]    # boxed, comma-separated list of contact email addresses for the host, lead instructor, or whoever else is handling questions, like ["marlyn.wescoff@example.org", "fran.bilas@example.org", "ruth.lichterman@example.org"]
collaborative_notes:             # optional: URL for the workshop collaborative notes, e.g. an Etherpad or Google Docs document
eventbrite:           # optional: alphanumeric key for Eventbrite registration, e.g., "1234567890AB" (if Eventbrite is being used)
---


{% comment %}
For a workshop please delete the following block
{% endcomment %}

{% if page.carpentry != site.carpentry %}
<div class="alert alert-warning">
You specified <code>carpentry: {{page.carpentry}}</code> in <code>index.md</code> and
<code>carpentry: {{site.carpentry}}</code> in <code>_config.yml</code>. Make sure you edit both files. After editing <code>_config.yml</code>, you need to run <code>make serve</code> again to
see the changes take effect locally.
</div>
{% endif %}



Welcome to the FIRST-HEP CMake tutorial! The aim of this tutorial is to cover the basics of using CMake. This tutorial is based on the online book [Modern CMake][], with a focus on CMake 3.14+. This is in what is [called the "More Modern" era](https://github.com/Bagira80/More-Modern-CMake) of CMake (which is 3.12+), and includes the fantastic command line improvements in CMake π (notes for 3.11+ compatible features will be included usually). We will cover the basics of making and building a project, and some details of design.

First taught at the [2019 USATLAS Computing Bootcamp at LBNL](https://smeehan12.github.io/2019-08-19-usatlas-computing-bootcamp/).

> ## Prereqs
>
> On your computer, you need to have:
>
> * `git`
> * `cmake` (Version 3.14 or newer). See the [instructions here][CMake Instructions].
> * A C++ compiler - system default is fine.
> * `make` or `ninja`
>
> A quick and minimal docker works well, too:
>
> ```bash
> docker run --rm -it alpine
> apk add git g++ cmake make
> git clone https://github.com/henryiii/cmake_workshop.git
> cd cmake_workshop
> ```
>
>
> This does *not* make a volume, so you will lose whatever you do in here when it exits - that's probably a good thing mostly.
>
{: .prereq}

{% include curriculum.html %}

{% include links.md %}
