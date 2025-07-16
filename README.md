# FatModules

`General Algorithms & Utilities`
--------------------------------
This is my personal library written in C++23 `(ISO/IEC 14882:2024)` with support for modules, to be used with latest versions of Clang and MSVC compilers.
It supports C++20 by default but I used std module everywhere so it must be built with C++23. Also see: issue [#75](https://github.com/fatpound/FatModules/issues/75)

`Using The Library`
-------------------
Clone this repo to your project's include folder with this Git command: `git clone --recursive https://github.com/fatpound/FatModules.git`\
or\
Clone this repo to your project's include folder and update the submodules recursively: `git submodule update --init --recursive`\
This repo can be used directly as a (static) library project in Visual Studio 2022

`About The Code`
----------------
Supports C++20 `(ISO/IEC 14882:2020)` modules

No warnings on `clang++19` with [these](https://github.com/fatpound/CxxMade/blob/main/CompileOptions.cmake#L54-L98) compiler options\
No warnings on `MSVC v19.43.34808` with [these](https://github.com/fatpound/CxxMade/blob/main/CompileOptions.cmake#L128-L205) compiler options\
No warnings with `Microsoft C++ Native Recommended Rules` and some more [rules](https://github.com/fatpound/FatLibrary/blob/main/_misc/FatRules.ruleset)\
No warnings in `clang-tidy 19` with [these](https://github.com/fatpound/CxxMade/blob/main/.clang-tidy) checks\
No warnings in `PVS-Studio v7.35`
