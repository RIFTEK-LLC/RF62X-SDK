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

For developers who wish to download and build the latest code, should be able to 
use Git and do the following instructions:
###### 1. Install a git client on your local computer (if you haven’t yet)
*  On Linux use the terminal command: `sudo apt install git`
*  On MacOS use the terminal command: `brew install git`
*  For other platforms see the [git installation documentation](https://git-scm.com/downloads).
###### 2. Open a command prompt/terminal on your computer
*  On Linux, click the launch bar and search for 'terminal'
*  On OS X, hit ⌘-space and search for 'terminal'
*  On Windows, click the Start menu and search for 'command line'.
###### 3. Clone the repository using the following commands:
```
git clone https://gitlab.com/riftek_llc/software/sdk/scanners/rf627sdk.git
cd rf627sdk
git submodule update --init --recursive
```

For developers who wish to download and build the latest code using Git from the 
IDE (Qt Creator or Visual Studio Community) should follow these instructions:
1.  Create a Git project in one of the IDEs 
2.  Clone `https://gitlab.com/riftek_llc/software/sdk/scanners/rf627sdk.git`
3.  Download submodules 

> We recommend to use a git client for downloading and Qt Creator for project building 

## RF627 CORE
The base library for the following scanner series: 
*  RF627-old
*  RF627-smart


### HOW TO COMPILE
RF627 CORE can be built on the console or in an IDE.\
Firstly, you should download the project (if you have already done it, skip next commands)
```
git clone https://gitlab.com/riftek_llc/software/sdk/scanners/rf627sdk.git
cd rf627sdk
git submodule update --init --recursive
```
> for more information about project downloading steps, see an [overview](#overview)

###### CMake
To build the code:

```CMake
cd rf627core
cmake .
cmake --build . 
```

###### Qt Creator
To build the code:
*  Load the CMakeLists.txt file in the rf627core folder via **File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Open **Build Settings** and check **install** target for **Build Steps** 
*  Compile project

###### Visual Studio Community
To build the code:

```CMake
cd rf627core
cmake .
```
*  Open rf627core.sln with Visual Studio
*  Compile
