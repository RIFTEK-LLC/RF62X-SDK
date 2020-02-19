# RF627SDK

## CONTENTS
- [RF627 CORE](#rf627-core)
  - [How to compile](#how-to-compile)
- [RF627 SDK-WRAPPERS]()
  - [C++](#c++)
    - [How to compile](#how-to-compile1)
    - [Examples](#examples1)
  - [C#](#c#)
    - [How to compile](#how-to-compile2)
    - [Examples](#examples2)
  - [Python](#python)
    - [How to compile](#how-to-compile3)
    - [Examples](#examples3)

## OVERVIEW
The RF627SDK project uses [git](http://git-scm.com/) for source code management 
and [GitLab](https://about.gitlab.com/) for source code hosting.

For developers who simply want to use this SDK for work with scanners, can be 
downloaded last libraries and read usage examples.

For developers who wish to download and build the latest code:
*  [install a git client](https://git-scm.com/downloads) on your local computer
*  "clone" the project to download "master" to your local computer
*  build/compile the project

## RF627 CORE
The base library for the following scanner series: 
*  RF627-old
*  RF627-smart


### How to compile
#### 1. Get the code
If you get Qt Creator or Visual Studio Community, you should be able to use Git 
from the IDE. Just clone `https://gitlab.com/riftek_llc/software/sdk/scanners/rf627sdk.git`
to get the full code.

In case you didn't install an IDE, you will need to manually [install Git](https://git-scm.com/downloads)
on your local computer and do the following build instructions:

```CMake
git clone https://gitlab.com/riftek_llc/software/sdk/scanners/rf627sdk.git
cd rf627sdk
git submodule update --init --recursive
cd rf627core
cmake .
cmake --build . 
```
##### IDE
###### CMake
###### Qt Creator
###### Visual Studio Community