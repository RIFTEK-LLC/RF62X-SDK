***
![RF62X_SDK_v5_](/uploads/32dd3154010ecc0cfa5c366ca7ad7838/RF62X_SDK_v5_.png)
***

![](docs/source_ru/_static/RF62X_SDK.png)

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

**For developers** who simply **want to use this SDK** for work with scanners, can **download last libraries** and read usage examples ([C++](#how-to-use), [C#](#net-library), [PYTHON](#how-to-use-2)).\
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

    // Print return rf627 sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE);


    // Print count of discovered rf627-old in network by Service Protocol
    std::cout << "Discovered: " << list.size() << " rf627-old"   << std::endl;


    for (size_t i = 0; i < list.size(); i++)
    {
        rf627old::hello_info info = list[i]->get_info();

        std::cout << "\n\n\nID scanner's list: " << i            << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Device information: "                      << std::endl;
        std::cout << "* Name\t: "     << info.device_name()      << std::endl;
        std::cout << "* Serial\t: "   << info.serial_number()    << std::endl;
        std::cout << "* IP Addr\t: "  << info.ip_address()       << std::endl;
        std::cout << "* MAC Addr\t: " << info.mac_address()      << std::endl;

        std::cout << "\nWorking ranges: "                        << std::endl;
        std::cout << "* Zsmr, mm\t: " << info.z_smr()            << std::endl;
        std::cout << "* Zmr , mm\t: " << info.z_mr()             << std::endl;
        std::cout << "* Xsmr, mm\t: " << info.x_smr()            << std::endl;
        std::cout << "* Xemr, mm\t: " << info.x_emr()            << std::endl;

        std::cout << "\nVersions: "                              << std::endl;
        std::cout << "* Firmware\t: " << info.firmware_version() << std::endl;
        std::cout << "* Hardware\t: " << info.hardware_version() << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
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
| MinGW 7.3.0 | [rf62Xcore.dll](/uploads/178471d04d864e6110deba9ac9074df1/rf62Xcore.dll) [rf62Xcore.a](/uploads/4391dcfc692165676df647cbc65fb570/rf62Xcore.a) | [include.zip](/uploads/e2dc04f462b16838265ffcd069f9324c/include.zip) |
| MSVC2017 | [rf62Xcore.dll](/uploads/b97b1cec97a78ab3c9b09de946fd7e70/rf62Xcore.dll) [rf62Xcore.lib](/uploads/4eb42c2565bc2f61ed6714fc1bcf9d90/rf62Xcore.lib) | [include.zip](/uploads/912861a038055097ae482022a9003702/include.zip) |
| Clang 9.1.0 | [rf62Xcore.dll](/uploads/49e8e99d59fba95fa9f952c5befe8e92/rf62Xcore.dll) [rf62Xcore.lib](/uploads/5f96d0e7bb69d9a6ad60f41644a7e72d/rf62Xcore.lib) | [include.zip](/uploads/e2dc04f462b16838265ffcd069f9324c/include.zip) |

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
| MinGW 7.3.0 | [rf62Xsdk.dll](/uploads/2148ca77659e21b2f7aec9e5cbb072ab/rf62Xsdk.dll) [rf62Xsdk.a](/uploads/5a2fdb2b2fc3317fdeec78bbe0c00cc3/rf62Xsdk.a) | [include.zip](/uploads/e69dc9279a6dcba800a98142a8b32c8d/include.zip) |
| MSVC2017 | [rf62Xsdk.dll](/uploads/912890213476c43b26bf8f178b1d2c5a/rf62Xsdk.dll) [rf62Xsdk.lib](/uploads/e42dadfe318fc3201d6b6f1e280040a9/rf62Xsdk.lib) | [include.zip](/uploads/5e490e8b89b3c2870ec8102540a32b1a/include.zip) |
| Clang 9.1.0 | [rf62Xsdk.dll](/uploads/fc19b0fac252c78ed93d4fa86ebfc7eb/rf62Xsdk.dll) [rf62Xsdk.lib](/uploads/70b57c76ace11faa6c0e6d3ac8493a86/rf62Xsdk.lib) | [include.zip](/uploads/e69dc9279a6dcba800a98142a8b32c8d/include.zip) |

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
#include <string>
#include <iostream>

using namespace SDK::SCANNERS::RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf627 sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE);


    // Print count of discovered rf627-old in network by Service Protocol
    std::cout << "Discovered: " << list.size() << " rf627-old"   << std::endl;


    for (size_t i = 0; i < list.size(); i++)
    {
        rf627old::hello_info info = list[i]->get_info();

        std::cout << "\n\n\nID scanner's list: " << i            << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Device information: "                      << std::endl;
        std::cout << "* Name\t: "     << info.device_name()      << std::endl;
        std::cout << "* Serial\t: "   << info.serial_number()    << std::endl;
        std::cout << "* IP Addr\t: "  << info.ip_address()       << std::endl;
        std::cout << "* MAC Addr\t: " << info.mac_address()      << std::endl;

        std::cout << "\nWorking ranges: "                        << std::endl;
        std::cout << "* Zsmr, mm\t: " << info.z_smr()            << std::endl;
        std::cout << "* Zmr , mm\t: " << info.z_mr()             << std::endl;
        std::cout << "* Xsmr, mm\t: " << info.x_smr()            << std::endl;
        std::cout << "* Xemr, mm\t: " << info.x_emr()            << std::endl;

        std::cout << "\nVersions: "                              << std::endl;
        std::cout << "* Firmware\t: " << info.firmware_version() << std::endl;
        std::cout << "* Hardware\t: " << info.hardware_version() << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
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
#include <string>
#include <iostream>

using namespace SDK::SCANNERS::RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf627 sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE);


    // Print count of discovered rf627-old in network by Service Protocol
    std::cout << "Discovered: " << list.size() << " rf627-old"   << std::endl;


    // Iterate over all discovered rf627-old in network, connect to each of
    // them and get a profile.
    for(size_t i = 0; i < list.size(); i++)
    {
        rf627old::hello_info info = list[i]->get_info();

        // Print information about the scanner to which the profile belongs.
        std::cout << "\n\n\nID scanner's list: " << i            << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Device information: "                      << std::endl;
        std::cout << "* Name\t: "     << info.device_name()      << std::endl;
        std::cout << "* Serial\t: "   << info.serial_number()    << std::endl;
        std::cout << "* IP Addr\t: "  << info.ip_address()       << std::endl;

        // Establish connection to the RF627 device by Service Protocol.
        list[i]->connect();

        // Get profile from scanner's data stream by Service Protocol.
        profile2D_t* profile = list[i]->get_profile2D();
        if (profile != nullptr)
        {
            std::cout << "Profile information: "                    << std::endl;
            switch (profile->header.data_type) {
            case (uint8_t)PROFILE_DATA_TYPE::PIXELS:
                std::cout << "* DataType\t: "<< "PIXELS"            << std::endl;
                std::cout << "* Count\t: " << profile->pixels.size()<< std::endl;
                break;
            case (uint8_t)PROFILE_DATA_TYPE::PIXELS_INTRP:
                std::cout << "* DataType\t: "<< "PIXELS_INTRP"      << std::endl;
                std::cout << "* Count\t: " << profile->pixels.size()<< std::endl;
                break;
            case (uint8_t)PROFILE_DATA_TYPE::PROFILE:
                std::cout << "* DataType\t: "<< "PROFILE"           << std::endl;
                std::cout << "* Size\t: "  << profile->points.size()<< std::endl;
                break;
            case (uint8_t)PROFILE_DATA_TYPE::PROFILE_INTRP:
                std::cout << "* DataType\t: "<< "PROFILE_INTRP"     << std::endl;
                std::cout << "* Size\t: "  << profile->points.size()<< std::endl;
                break;
            }
            delete profile;
            std::cout << "Profile was successfully received!"       << std::endl;
            std::cout << "-----------------------------------------"<< std::endl;
        }else
        {
            std::cout << "Profile was not received!"                << std::endl;
            std::cout << "-----------------------------------------"<< std::endl;
        }

        // Disconnect from scanner.
        list[i]->disconnect();
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
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
#include <string>

using namespace SDK::SCANNERS::RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf62X SDK version
    std::cout << "SDK version: " << sdk_version()                   << std::endl;
    std::cout << "========================================="        << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> scanners;
    // Search for RF627old devices over network
    scanners = rf627old::search(PROTOCOLS::SERVICE);


    // Print count of discovered rf627-old in network by Service Protocol
    std::cout << "Discovered: " << scanners.size() << " rf627-old"  << std::endl;


    // Iterate over all discovered rf627-old in network, connect to each of
    // them and read/set parameters.
    for(size_t i = 0; i < scanners.size(); i++)
    {
        rf627old::hello_info info = scanners[i]->get_info();

        std::cout << "\n\n\nID scanner's list: " << i               << std::endl;
        std::cout << "-----------------------------------------"    << std::endl;

        // Establish connection to the RF627 device by Service Protocol.
        scanners[i]->connect();

        // read params from RF627 device by Service Protocol.
        scanners[i]->read_params();

        // Get parameter of Device Name
        param_t* name = scanners[i]->get_param(PARAM_NAME_KEY::USER_GENERAL_DEVICENAME);
        if (name->type == param_value_types[(int)PARAM_VALUE_TYPE::STRING_PARAM_TYPE])
        {
            std::string str_name = name->get_value<value_str>();
            std::cout << "Current Device Name \t: " << str_name     << std::endl;

            // Add "_TEST" to the ending of the current name
            str_name += "_TEST";
            name->set_value<value_str>(str_name);
            std::cout << "New Device Name \t: " << str_name         << std::endl;
            std::cout << "-----------------------------------------"<< std::endl;

            scanners[i]->set_param(name);
        }

        // Get parameter of Device IP Addr
        param_t* ip_addr = scanners[i]->get_param(PARAM_NAME_KEY::USER_NETWORK_IP);
        if (ip_addr->type == param_value_types[(int)PARAM_VALUE_TYPE::UINT32_ARRAY_PARAM_TYPE])
        {
            std::vector <uint32_t> ip = ip_addr->get_value<array_uint32>();
            std::cout << "Current Device IP\t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<<std::endl;

            // Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
            ip[3]++;
            ip_addr->set_value<array_uint32>(ip);
            std::cout << "New Device IP\t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<<std::endl;
            std::cout << "-----------------------------------------"<< std::endl;

            scanners[i]->set_param(ip_addr);
        }

        // Get parameter of Laser Enabled
        param_t* laser_enabled = scanners[i]->get_param(PARAM_NAME_KEY::USER_LASER_ENABLED);
        if (laser_enabled->type == param_value_types[(int)PARAM_VALUE_TYPE::UINT_PARAM_TYPE])
        {
            bool isEnabled = laser_enabled->get_value<value_uint32>();
            std::cout<<"Current Laser State\t: "<<(isEnabled?"ON":"OFF")<<std::endl;

            isEnabled = !isEnabled;
            // Change the current state to the opposite
            laser_enabled->set_value<value_uint32>(!isEnabled);
            std::cout<<"New Laser State\t: "<<(isEnabled?"ON":"OFF")<<std::endl;
            std::cout << "-----------------------------------------"<< std::endl;

            scanners[i]->set_param(laser_enabled);
        }

        //  Write changes parameters to the device's memory
        scanners[i]->write_params();

        // Disconnect from scanner.
        scanners[i]->disconnect();

    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();

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
| .NET Framework 4.5 (and late) | [rf62Xsdk.dll](/uploads/dc42b3db3c48a4d3cc746510a9e66571/rf62Xsdk.dll) | [rf62Xcore.dll](/uploads/178471d04d864e6110deba9ac9074df1/rf62Xcore.dll) |


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
            Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
            Console.WriteLine("=========================================");

            // Search for RF627old devices over network
            Console.WriteLine("- Start searching device");
            List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);

            for (int i = 0; i < Scanners.Count; i++)
            {
                RF62X.HelloInfo info = Scanners[i].GetInfo();

                Console.WriteLine("\n\n\nID scanner's list: {0}", i);
                Console.WriteLine("-----------------------------------------");
                Console.WriteLine("Device information: ");
                Console.WriteLine("* Name\t: {0}", info.device_name);
                Console.WriteLine("* Serial\t: {0}", info.serial_number);
                Console.WriteLine("* IP Addr\t: {0}", info.ip_address);
                Console.WriteLine("* MAC Addr\t: {0}", info.mac_address);

                Console.WriteLine("Working ranges: ");
                Console.WriteLine("* Zsmr, mm\t: {0}", info.z_smr);
                Console.WriteLine("* Zmr , mm\t: {0}", info.z_mr);
                Console.WriteLine("* Xsmr, mm\t: {0}", info.x_smr);
                Console.WriteLine("* Xemr, mm\t: {0}", info.x_emr);

                Console.WriteLine("\nVersions: ");
                Console.WriteLine("* Firmware\t: {0}", info.firmware_version);
                Console.WriteLine("* Hardware\t: {0}", info.hardware_version);
                Console.WriteLine("-----------------------------------------");
            }

            Console.WriteLine("{0}Press any key to end \"Search-test\"", Environment.NewLine);
            Console.ReadKey();

            // Cleanup resources allocated with SdkInit()
            RF62X.SdkCleanup();
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
            Console.WriteLine("- Start searching device");
            List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);

            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
                RF62X.HelloInfo info = Scanners[i].GetInfo();

                Console.WriteLine("\n\n\nID scanner's list: {0}", i);
                Console.WriteLine("-----------------------------------------");
                Console.WriteLine("Device information: ");
                Console.WriteLine("* Name\t: {0}", info.device_name);
                Console.WriteLine("* Serial\t: {0}", info.serial_number);
                Console.WriteLine("* IP Addr\t: {0}", info.ip_address);

                // Establish connection to the RF627 device by Service Protocol.
                Scanners[i].Connect();

                // Get profile from scanner's data stream by Service Protocol.
                RF62X.Profile profile = Scanners[i].GetProfile();
                if (profile.header != null)
                {
                    Console.WriteLine("Profile information: ");
                    switch (profile.header.data_type)
                    {
                        case RF62X.PROFILE_TYPE.PIXELS_NORMAL:
                            Console.WriteLine("* DataType\t: PIXELS");
                            Console.WriteLine("* Count\t: {0}", profile.pixels.Count);
                            break;
                        case RF62X.PROFILE_TYPE.PROFILE_NORMAL:
                            Console.WriteLine("* DataType\t: PROFILE");
                            Console.WriteLine("* Size\t: {0}", profile.points.Count);
                            break;
                        case RF62X.PROFILE_TYPE.PIXELS_INTERPOLATED:
                            Console.WriteLine("* DataType\t: PIXELS");
                            Console.WriteLine("* Count\t: {0}", profile.pixels.Count);
                            break;
                        case RF62X.PROFILE_TYPE.PROFILE_INTERPOLATED:
                            Console.WriteLine("* DataType\t: PROFILE");
                            Console.WriteLine("* Size\t: {0}", profile.points.Count);
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine("Profile was successfully received!");
                    Console.WriteLine("-----------------------------------------");
                }else
                {
                    Console.WriteLine("Profile was not received!");
                    Console.WriteLine("-----------------------------------------");
                }

                // Disconnect from scanner.
                Scanners[i].Disconnect();

            }

            Console.WriteLine("{0}Press any key to end \"Search-test\"", Environment.NewLine);
            Console.ReadKey();

            // Cleanup resources allocated with sdk_init()
            RF62X.SdkCleanup();
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
            Console.WriteLine("- Start searching device");
            List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);

            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
                // Establish connection to the RF627 device by Service Protocol.
                Scanners[i].Connect();

                // read params from RF627 device by Service Protocol.
                Scanners[i].ReadParams();

                // Get parameter of Device Name
                RF62X.Param<string> name = Scanners[i].GetParam(RF62X.Params.User.General.deviceName);
                if (name != null)
                {
                    string strName = name.GetValue();
                    Console.WriteLine("\n\nCurrent Device Name \t: {0}", strName);

                    // Add "_TEST" to the ending of the current name
                    strName += "_TEST";
                    name.SetValue(strName);
                    Console.WriteLine("New Device Name \t: {0}", strName);
                    Console.WriteLine("-----------------------------------------");

                    Scanners[i].SetParam(name);

                }

                // Get parameter of Device IP Addr
                RF62X.Param<List<uint>> ipAddr = Scanners[i].GetParam(RF62X.Params.User.NetWork.ip);
                if (ipAddr != null)
                {
                    List<uint> ip = ipAddr.GetValue();
                    Console.WriteLine("Current Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);

                    // Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
                    ip[3]++;                    
                    ipAddr.SetValue(ip);
                    Console.WriteLine("New Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);
                    Console.WriteLine("-----------------------------------------");

                    Scanners[i].SetParam(ipAddr);
                }

                // Get parameter of Laser Enabled
                RF62X.Param<uint> laserEnabled = Scanners[i].GetParam(RF62X.Params.User.Laser.enabled);
                if (laserEnabled != null)
                {
                    bool isLaserEnabled = Convert.ToBoolean(laserEnabled.GetValue());
                    Console.WriteLine("Current Laser State\t: {0}", isLaserEnabled ? "ON" : "OFF");

                    // Change the current state to the opposite
                    isLaserEnabled = !isLaserEnabled;
                    laserEnabled.SetValue((uint)(Convert.ToUInt32(isLaserEnabled)));
                    Console.WriteLine("New Laser State\t\t: {0}", isLaserEnabled ? "ON" : "OFF");
                    Console.WriteLine("-----------------------------------------");


                    Scanners[i].SetParam(laserEnabled);
                }

                //  Write changes parameters to the device's memory
                Scanners[i].WriteParams();

                // Disconnect from scanner.
                Scanners[i].Disconnect();
            }
            Console.WriteLine("{0}Press any key to end \"Parameters-test\"", Environment.NewLine);
            Console.ReadKey();

            // Cleanup resources allocated with SdkInit()
            RF62X.SdkCleanup();
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