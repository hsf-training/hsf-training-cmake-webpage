#!/usr/bin/env python3

import requests
from bs4 import BeautifulSoup

# Instructions:
#     python -m venv venv
#     . venv/bin/activate
#     pip install lxml bs4 requests
#     ./data/cmake_links.py > _includes/cmake_links.md
#     deactivate

pages = [
    "https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html",
    "https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html",
    "https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html",
    "https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html",
    "https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html",
]

lang = "<LANG>"
langs = ["CXX"]

for page in pages:
    res = requests.get(page)

    soup = BeautifulSoup(res.content, "lxml")

    for a in soup.find_all('a', attrs={"class":"reference internal"}):
        if "#" not in a["href"]:
            link = a["href"].replace("..", "https://cmake.org/cmake/help/latest")
            start = f"[`{a.text}`]:"
            print(f"{start:50}{link}")

            if "<LANG>" in start:
                for l in langs:
                    print(f"{start.replace(lang, l):50}{link}")
