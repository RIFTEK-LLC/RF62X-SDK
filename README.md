***
![RF62X_SDK_v5_](/uploads/32dd3154010ecc0cfa5c366ca7ad7838/RF62X_SDK_v5_.png)
***

## CONTENTS
- [OVERVIEW](#overview)
  - [Core features](#core-features)
  - [Supported compilers](#supported-compilers)
  - [Resources](#resources)
- [GETTING STARTED](#getting-started)
  - [Installing software](#installing-software)
  - [Running RF62X SDK tutorials](#)
- [RF62X CORE](#rf62x-core)
  - [How to compile](#how-to-compile)
- [RF62X WRAPPER LIBRARIES](#rf62x-wrapper-libraries)
  - [C++ LIBRARY](#c-library)
    - [How to compile](#how-to-compile-1)
    - [How to use](#how-to-use)
  - [.NET LIBRARY](#net-library)
    - [How to compile](#how-to-compile-2)
    - [How to use](#how-to-use-1)
  - [PYTHON LIBRARY](#python-library)
    - [How to compile](#how-to-compile-3)
    - [How to use](#how-to-use-2)



## OVERVIEW

**RF62X SDK** is a library that supports rapid development of software that deals with scanners series RF62X (RF627-old, RF627-smart).

The RF627X SDK consist of two parts:
*  **RF62X CORE** is the main library with basic functionality for work with scanners and platform dependent methods (such as memory, network, output/input methods, etc.) requiring initialization.
*  **RF62X WRAPPER** is the library that helps to develop programs in a definite programming language and for the selected platform, simplifying the use of the main library (RF62X CORE).


### Core features
*  Search scanners
*  Get scanner's profile
*  Get/set scanner's parameters

### Supported compilers
*  GCC 5.x or newer on Linux
*  XCode 8.0 or newer on OS X
*  Visual Studio 2017 or newer on Windows

### Resources
This project uses [git](http://git-scm.com/) for source code management and [GitLab](https://about.gitlab.com/) for source code hosting.
*  Code: www.gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK
*  Document: www.riftek.com  
*  Website: www.riftek.com



## GETTING STARTED

**For developers** who simply **want to use this SDK** for work with scanners, can **download last libraries** and read usage examples ([C++](#how-to-use), [C#](#how-to-use-1), [PYTHON](#how-to-use-2)).\
**For others** who want to **build the latest code**, should be able to use Git and do the **[Installing instructions](#installing-software)**

### Installing software

###### 1. Install a git client on your local computer (if you haven’t yet)
*  On Linux use the terminal command: `sudo apt install git`
*  On MacOS use the terminal command: `brew install git`
*  For other platforms see the [git installation documentation](https://git-scm.com/downloads).
###### 2. Open a command prompt/terminal on your computer
*  On Linux, click the launch bar and search for 'terminal'
*  On OS X, hit ⌘-space and search for 'terminal'
*  On Windows, click the Start menu and search for 'command line'.
###### 3. Clone the repository using the following commands:
```bash
git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
cd RF62X-SDK
git submodule update --init --recursive
```

For developers who wish to download and build the latest code using Git from the 
IDE (Qt Creator or Visual Studio Community) should follow these instructions:
1.  Create a Git project in one of the IDEs 
2.  Clone `https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git`
3.  Download submodules 

> We recommend to use a git client for downloading and Qt Creator for project building 

### Running RF62X SDK tutorials
Here a basic example how to use method for searching RF62X devices in different languages by different ways.\
You can create a new project yourself or you can just open an existing project example and build it.
#### Compiling examples in C++ from source
##### 1) Open and compile examples project in **Qt Creator**:  
*  Load the CMakeLists.txt file from the **examples/Cpp/RF627_TESTS** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)

![](/uploads/78032febfdfd6b2954b93ff3cfac2967/Аннотация_2020-03-10_153146.jpg)

*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**

![](/uploads/aea9094ca516e84609b41ff70412ac37/Аннотация2.jpg)

*  Choose one of the examples, Compile and Run it

##### 2) Generate a project for **Visual Studio** and compile examples
*  Generate Visual Studio solution by calling CMake from the console
```bash
cd examples/Cpp/RF627_old
mkdir build
cd build

:: Run one of the following lines based on your Visual Studio version
cmake -G "Visual Studio 15 2017 Win64" ..
cmake -G "Visual Studio 16 2019 Win64" ..
```
*  Open the **ALL_BUILD.vcxproj** from the **examples/Cpp/RF627_old** folder by Visual Studio
*  Select the build type and target platform - **x64 Debug** or **x64 Release**
*  Rebuild the **ALL_BUILD** target
*  Choose one of the examples, Compile and Run it

#### Creating a new project in C++ with using shared or static SDK-library
##### 1) Create a new project in **Qt Creator** by СMake
*  Open **File > New File or Project**, select **Qt Console Application** and click **Choose** button

![](/uploads/46932e911f2c5676f18ad43cc8214246/note2.png)

*  Enter project name, Browse project location and click **Next** button
*  Choose **CMake** build system and click **Next** button twice
*  Select one of 64bit compilers (MinGW, MSVC2017, Clang, etc..), click **Next** button and finish project setup.
*  [Download](#c-library) **include.zip** archive and unzip it into the project directory. Also download **rf62Xsdk.dll** and copy it into the project directory next to the main.cpp file

![](/uploads/f772d702180bb91cf67cad8621090b40/note3.png)

*  Modify your **CMakeLists.txt** file according to the example below:
```cmake
cmake_minimum_required(VERSION 3.5)

project(TestProject LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include *.h rf62Xsdk files from directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# find rf62Xsdk lib in paths and copy full file name to RF62XSDK_LIBRARY
find_library(
    RF62XSDK_LIBRARY
    rf62Xsdk
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_executable(${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME} ${RF62XSDK_LIBRARY})
```
*  Modify your **main.cpp** file according to the example below:

```c++
#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <iostream>

using namespace SDK::SCANNERS::RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();


    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE_PROTOKOL);


    // Print count of discovered rf627-old in network by Service Protocol
    std::cout << "Discovered " << list.size() << " rf627-old" << std::endl;

    return 0;
}
```
*  Copy **rf62Xsdk.dll** into the path of the project executable (PROJECT_BINARY_DIR)

You can do it in two ways:
1) Copy rf62Xsdk.dll to the executable folder (near with *.exe) yourself.
2) Or add a "copy command" to the end of the CMakeLists.txt file:

```cmake
# copy rf62Xsdk lib from cmake current source directory to project build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${RF62XSDK_LIBRARY} ${PROJECT_BINARY_DIR})
```
    
*  Select **Debug** or **Release** build type, Run CMake and Run project 

Beside this example, you may want to check the documentation where each function contains a separate code example. All example project can be compiled and executed.

## RF62X CORE
RF62X CORE is the main library with basic functionality for work with scanners and platform dependent methods (such as memory, network, output/input methods, etc.) requiring initialization.
This library was written in C programming language in accordance with C99 Sdandart (ISO/IEC 9899:1999).

##### Last release libraries:

| Compiler | 64bit | Includes |
| ------   | ------| ------|
| MinGW 7.3.0 | [rf62Xcore.dll](/uploads/371108d8ea80d3865aec88d2e194282e/rf62Xcore.dll) | [include.zip](/uploads/a526db902d8fc61a61db37341354815c/include.zip) |
| MSVC2017 | [rf62Xcore.dll](/uploads/c95087a6f5d18a0a01eacee2bdc1ce5e/rf62Xcore.dll) | [include.zip](/uploads/406956fd8a722ef55097b555cf8425d9/include.zip) |
| Clang 9.1.0 | [rf62Xcore.dll](/uploads/c5e6ec52a8955a369669c4edeedd5aa8/rf62Xcore.dll) | [include.zip](/uploads/62aa9d4dd96e056570a84576c947d3cd/include.zip) |

***


### HOW TO COMPILE
RF62X CORE can be built on the console or in an IDE.\
Firstly, you should download the project (if you have already done it, skip next commands)
```bash
git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
cd RF62X-SDK
git submodule update --init --recursive
```
> for more information about project downloading steps, see an [overview](#overview)

###### CMake
To build the code:

```bash
cd rf62Xcore
mkdir build
cd build
cmake ..
cmake --build .
```

###### Qt Creator
To build the code:
*  Load the CMakeLists.txt file from the **rf62Xcore** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Open **Build Settings** and check ***install*** target for **Build Steps** 
*  Compile project

###### Visual Studio
To build the code:

```bash
cd rf62Xcore
mkdir build
cd build
cmake ..
```
*  Open rf62Xcore.sln with Visual Studio
*  Compile

## RF62X WRAPPER LIBRARIES
Wrappers are help to make programs in different languages and for different platforms using the rf62Xcore library easier.

### C++ LIBRARY
This project is a C++ library that simplifies the integration of C++ 
applications with following scanner series: 
*  RF627-old
*  RF627-smart

##### Last release libraries:

| Compiler | 64bit | Includes |
| ------ | ------ | ------|
| MinGW 7.3.0 | [rf62Xsdk.dll](/uploads/fbb23942872b3bfda058b72361b8210a/rf62Xsdk.dll) | [include.zip](/uploads/8e63d0af13b2f921c724468da426d7b3/include.zip) |
| MSVC2017 | [rf62Xsdk.dll](/uploads/ffb7e3e02403f448008f8892c60cdedb/rf62Xsdk.dll), [rf62Xsdk.lib](/uploads/8ad08a8bfbc71f5dde329eb60cc3ff1b/rf62Xsdk.lib) | [include.zip](/uploads/1c58da93d1843013eef422b850168c22/include.zip) |
| Clang 9.1.0 | [rf62Xsdk.dll](/uploads/0bc7dd16f5834330c453f6fafeafc018/rf62Xsdk.dll) | [include.zip](/uploads/b4e28e11321de2962bb38972cd4ea816/include.zip) |

#### HOW TO COMPILE
RF62X SDK (C++) can be built on the console or in an IDE.\
Firstly, you should download the project (if you have already done it, skip next commands)
```bash
git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
cd RF62X-SDK
git submodule update --init --recursive
```
> for more information about project downloading steps, see an [overview](#overview)

###### CMake
To build the С++ wrapper:

```bash
cd rf62Xsdk/Cpp/rf62Xsdk
mkdir build
cd build
cmake ..
cmake --build . 
```

###### Qt Creator
To build the code:
*  Load the CMakeLists.txt file from the **rf62Xsdk/Cpp/rf62Xsdk** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Compile project

###### Visual Studio
To build the code:

```bash
cd rf62Xsdk/Cpp/rf62Xsdk
mkdir build
cd build
cmake ..
```
*  Open rf62Xsdk.sln with Visual Studio
*  Compile

#### HOW TO USE
Beside the examples below, you may want to check the documentation where each function 
contains a separate code example. All example project can be compiled and executed.
##### Search for RF62X devices
Here are some examples how to use search methods
###### Search for RF627-old devices over network by service protocol
```c++
#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();
    // Print return rf62X sdk version
    std::cout << sdk_version() << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE_PROTOKOL);


    // Print count of discovered rf627-old in network by Service Protocol
    std::cout << "Discovered " << list.size() << " rf627-old" << std::endl;

}
```
You can open and build this example by **Qt Creator**:  
*  Load the CMakeLists.txt file from the **examples/Cpp/RF627_old/RF627_search** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Compile project

##### Get Profile from RF62X devices
Here are some examples how to use get profile methods
###### Get Profile from RF627-old devices over network by service protocol
```c++
#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();
    // Print return rf62X sdk version
    std::cout << sdk_version() << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> scanners;
    // Search for RF627old devices over network
    scanners = rf627old::search(PROTOCOLS::SERVICE_PROTOKOL);

    
    // Iterate over all discovered rf627-old in network, connect to each of
    // them and get a profile.
    for(size_t i = 0; i < scanners.size(); i++)
    {
        // Establish connection to the RF627 device by Service Protocol.
        scanners[i]->connect();
        
        
        // Get profile from scanner's data stream by Service Protocol.
        profile_t* profile = scanners[i]->get_profile();
        // Print the serial number of the scanner to which the profile belongs.
        std::cout << profile->header.serial_number << std::endl;
        
    }
    
}
```
You can open and build this example by **Qt Creator**:  
*  Load the CMakeLists.txt file from the **examples/Cpp/RF627_old/RF627_profile** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Compile project

##### Get/Set RF62X-old parameters
Here are some examples how to work with device's parameters
###### Get/Set RF627-old parameters devices over network
```c++
#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();
    // Print return rf62X sdk version
    std::cout << sdk_version() << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> scanners;
    // Search for RF627old devices over network
    scanners = rf627old::search(PROTOCOLS::SERVICE_PROTOKOL);


    // Iterate over all discovered rf627-old in network, connect to each of
    // them and read/set parameters.
    for(size_t i = 0; i < scanners.size(); i++)
    {
        // Establish connection to the RF627 device by Service Protocol.
        scanners[i]->connect();


        // read params from RF627 device by Service Protocol.
        scanners[i]->read_params();


        // Get parameter by it's name from last read
        param_t* param = scanners[i]->get_param(USER_GENERAL_DEVICENAME);
        if (param->type == param_value_types[STRING_PARAM_TYPE])
        {
            // Print current scanner's name
            std::cout << param->get_value<value_str_t>() << std::endl;

            // set new scanner's name and write changed parameters to scanner
            param->set_value<value_str_t>("Test Name");
            scanners[i]->set_param(param);
            scanners[i]->write_params();
        }


        // Check that the parameter is set correctly
        // Read arain all params from RF627 device by Service Protocol.
        scanners[i]->read_params();


        // Get device name
        param = scanners[i]->get_param(USER_GENERAL_DEVICENAME);
        if (param->get_value<value_str_t>() == "Test Name")
            std::cout << "Changed parameters write successfully" << std::endl;
        else 
            std::cout << "Error changing parameters" << std::endl;
    }
    
}
```
You can open and build this example by **Qt Creator**:  
*  Load the CMakeLists.txt file from the **examples/Cpp/RF627_old/RF627_params** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Compile project

### .NET LIBRARY
This project is a .NET library, written in C# language, that simplifies the integration of C#, 
Visual Basic .NET, C++/CLI and JScript .NET applications with following scanner series: 
*  RF627-old
*  RF627-smart

##### Last release libraries:

| Platform | 64bit | Dependencies (x64) |
| ------ | ------ |------ |
| .NET Framework 4.5 (or above) | [rf62Xsdk.dll](/uploads/2d04f23757e4cc36dadd1e0e36e6e880/rf62Xsdk.dll) | [rf62Xcore.dll](/uploads/18b4411bcea75af28b588d1368215049/rf62Xcore.dll) |


#### HOW TO COMPILE
RF62X SDK (C#) can be built in an Visual Studio IDE.\
Firstly, you should download the project (if you have already done it, skip next commands)
```bash
git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
cd RF62X-SDK
git submodule update --init --recursive
```
> for more information about project downloading steps, see an [overview](#overview)

###### Visual Studio
To build the code:

*  Open rf62Xsdk.sln from the **rf62Xsdk/CSharp/RF627_old** folder with Visual Studio
*  Compile

#### HOW TO USE
Beside the examples below, you may want to check the documentation where each function 
contains a separate code example. All example project can be compiled and executed.

You can open and build these examples by **Visual Studio**:  
*  Open **RF627_TESTS.sln** from the **rf62Xsdk/CSharp/RF627_old** folder with Visual Studio
*  Select **x64 Debug** or **x64 Release** target platform
*  Add the **rf62Xsdk.dll** library to project's **references** 
*  Copy the **rf62Xcore.dll** into the path of the project executable (**../bin/x64/Debug/** or **../bin/x64/Release/**)
*  Compile project

##### Search for RF62X devices
Here are some examples how to use search methods
###### Search for RF627-old devices over network by service protocol
```c#
using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace RF627_search
{
    class Program
    {
        static void Main(string[] args)
        {
        
            // Start initialization of the library core
            RF62X.SdkInit();

            // Print return rf62X sdk version
            Console.WriteLine("Current rf62X sdk version: {0}", RF62X.SdkVersion());


            // Search for RF627old devices over network
            Console.WriteLine("- Start searching device");
            List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);
            
        }
    }
}
```

##### Get Profile from RF62X devices
Here are some examples how to use get profile methods
###### Get Profile from RF627-old devices over network by service protocol
```c#
using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace RF627_profile
{
    class Program
    {
        static void Main(string[] args)
        {
        
            // Start initialization of the library core
            RF62X.SdkInit();


            // Search for RF627old devices over network
            List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();


            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
                // Establish connection to the RF627 device
                Scanners[i].Connect();
                
                
                //Receive profile
                RF62X.Profile profile = Scanners[i].GetProfile();
                if (profile.header != null)
                    Console.WriteLine("Received profile successfully);
                else 
                    Console.WriteLine("Profile is null");
            }
            
        }
    }
}
```

##### Get/Set RF62X-old parameters
Here are some examples how to work with device's parameters
###### Get/Set RF627-old parameters devices over network
```c#
using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace RF627_params
{
    class Program
    {
        static void Main(string[] args)
        {
        
            // Start initialization of the library core
            RF62X.SdkInit();


            // Search for RF627old devices over network
            List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();


            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
                // Establish connection to the RF627 device
                Scanners[i].Connect();


                // Try to read params
                Scanners[i].ReadParams();


                // Get scanner's name
                RF62X.Param<string> deviceName = 
                        Scanners[i].GetParam(RF62X.Params.User.General.deviceName);


                // Set new scanner's name and write changed parameters to scanner
                deviceName.SetValue("New Name");
                Scanners[i].SetParam(deviceName);


                // Send command to scanner to write changed parameters
                Scanners[i].WriteParams();


                // Check that the parameter is set correctly
                // Read again all params from RF627 device.
                Scanners[i].ReadParams();


                // Get scanner's name
                RF62X.Param<string> newDeviceName = 
                        Scanners[i].GetParam(RF62X.Params.User.General.deviceName);
                if (newDeviceName.GetValue() == "New Name")
                    Console.WriteLine("Changed parameters write successfully");
                else 
                    Console.WriteLine("Error changing parameters");
            }
            
        }
    }
}
```


Also you can open and build **Windows Forms** application for searching, getting/setting parameters and viewing profiles:  
*  Open **RF62X_WinForms.sln** from the **rf62Xsdk/CSharp/RF62X_WinForms** folder with Visual Studio
*  Select **x64 Debug** or **x64 Release** target platform
*  Add the **rf62Xsdk.dll** library to project's **references** 
*  Copy the **rf62Xcore.dll** into the path of the project executable (**../bin/x64/Debug/** or **../bin/x64/Release/**)
*  Compile project

![photo_2020-04-13_17-50-20](/uploads/36ec7848dc4b2e2d9a4f0993208e63da/photo_2020-04-13_17-50-20.jpg)

### PYTHON LIBRARY
#### HOW TO COMPILE
#### HOW TO USE