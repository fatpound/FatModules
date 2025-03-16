# FatModules

`General Algorithms & Utilities`
------------------------------
This is my personal library written in C++23 `(ISO/IEC 14882:2024)` with support for modules, to be used with latest versions of MSVC and Clang++ compilers.

`Using The Library`
-----------------
Clone this repo to your project's include folder with this Git command: `git clone --recursive https://github.com/fatpound/FatModules.git`\
or\
Clone this repo to your project's include folder and update the submodules recursively: `git submodule update --init --recursive`\
This repo can be used directly as a (static) library project in Visual Studio 2022

`About The Code`
---------------------
Supports C++20 `(ISO/IEC 14882:2020)` modules\

No warnings on `Clang++19` with options `-Wall -Wextra -Weverything -pedantic` and `-Wno-c++98-compat` `-Wno-c++98-compat-pedantic` `-Wno-c++20-compat` `-Wno-c++20-extensions` `-Wno-padded`\
No warnings on `MSVC v19.43.34808` with options `/Wall /permissive-` [except these](https://github.com/fatpound/FatProps/blob/main/FatCpp.props#L17)\
No warnings with `Microsoft C++ Native Recommended Rules` and [some optional rules](https://github.com/fatpound/FatModules/blob/main/_misc/FatRules.ruleset)\
No warnings in `PVS-Studio v7.35`
