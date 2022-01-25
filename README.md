![RF62X_SDK](Docs/source_ru/resources/img/RF62X_SDK(v2).png)


# CONTENTS
- [OVERVIEW](#overview)
- [GETTING STARTED](#getting-started)
  - [Download project](#download-project)
  - [Running SDK examples](#running-sdk-examples)
- [CREATING PROJECT](#creating-project)
  - [Creating a C/C++ project](#creating-a-cc-project)
  - [Creating a C# project](#creating-a-c-project)
  - [Creating a Python project](#creating-a-python-project)
- [COMPILING RF62X-SDK](#compiling-rf62x-sdk)
  - [COMPILING CORE LIBRARY](#compiling-core-library)
  - [COMPILING WRAPPER LIBRARIES](compiling-wrapper-libraries)
    - [C WRAPPER](#c-wrapper)
    - [C++ WRAPPER](#c-wrapper-1)
    - [.NET WRAPPER](#net-wrapper)
    - [PYTHON WRAPPER](#python-wrapper)


# OVERVIEW

**RF62X-SDK** a Software Development Kit for work with laser scanners series RF62X (RF627 v20.X.X.X, RF627 v2.X.X, RF629 v2.X.X) manufactured by RIFTEK LLC.

The RF62X-SDK consists of two parts:
* **RF62X-Core** - a «Core» library with a basic functions and types for working
with lasers. This library is written in the C programming language
in accordance with the C99 standard (ISO/IEC 9899:1999). To use
this library, it is necessary to implement platform-dependent functions (working with memory,
working with the network, input/output functions).
* **RF62X-Wrappers** - «wrapper»-libraries, in which platform-dependent «Core» functions
for a specific platform are already implemented. The use of wrapper libraries simplifies
the process of developing applications in the following programming languages: C, C++, С#, 
Python, LabVew, MatLab.


# GETTING STARTED

Developers who want to use **ready-made RF62X-SDK** libraries can download the latest release (download the 
[RF62X-SDK libraries](https://github.com/RIFTEK-LLC/RF62X-SDK/releases) 
for C, C++, C#, Python).

Developers who prefer to compile RF62X-SDK libraries from sources, the manual contains instructions 
for downloading sources (see [Download project](#download-project)) and installing the necessary software.

## Download project 

For developers who want to download the library from source using the Git-client,
follow these instructions:
#### 1. Install the git-client on your local computer (if not already installed):
* On Linux, use the terminal command: `sudo apt install git`
* On MacOS, use the terminal command: `brew install git`
* For other platforms see [git installation documentation](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
#### 2. Open a command prompt/terminal on your computer:
* On Linux, click on the launchpad and look for `terminal`
* In OS X, press commandspace and find `terminal`
* On Windows, click the Start menu and find the `cmd` (command line).
#### 3. Download the project:
```bash
git clone https://github.com/RIFTEK-LLC/RF62X-SDK.git
cd RF62X-SDK
git submodule update --init --recursive
```
> We recommend to use a git client for downloading and Qt Creator for project building 

## Running SDK examples
Here is a basic example of using the method to find, get profiles/frames, set/get parameters for RF62X devices in different languages by different ways.\
You can create a new project yourself or you can just open an existing project example and build it.

<details><summary>Running a C/C++ example </summary> 
  
#### 1. Open and compile examples project in **Qt Creator**:  
*  Load the `CMakeLists.txt` file from the `RF62X-SDK/Examples/Cpp` folder via **File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC, Clang, etc..) and click **Configure Project**
*  Compile and Run it
#### 2. Create project and compile examples in **Visual Studio 2019**:  
*  From the `RF62X-SDK/Examples/Cpp` folder, enter the following command in the terminal (console):
```bash
mkdir build && cd build
cmake ..
```
*  Open the resulting `RF62XSDK-EXAMPLES.sln` solution in `build` folder by Visual Studio
*  Compile and Run it
 
</details>

<details><summary>Running a C# example</summary> 
  
#### Open and compile examples project in **Visual Studio**:  
*  Open one of the examples (RF627_smart, RF627_old, RF62X_WinForms) from the `RF62X-SDK/Examples/CSharp` folder by Visual Studio
*  Select **x64 Debug** or **x64 Release** target platform
*  Add the **RF62X-SDK.dll** C# WRAPPER library to project's **references** 
*  Copy all **libRF62X-SDK** dll-s from archive for C# (see [RF62X-SDK releases](https://github.com/RIFTEK-LLC/RF62X-SDK/releases) link) into the path of the project executable (`../bin/x64/Debug/` or `../bin/x64/Release/`)
*  Compile project

</details>
  
<details><summary> Running a Python example</summary> 
  
#### Open and compile examples project in **Visual Studio Code**:  
*  Open one of the examples (RF627_SMART, RF627_OLD) from the `RF62X-SDK/Examples/Python` folder by Visual Studio Code
*  Copy all **libRF62X-SDK** dll-s from archive for Python (see [RF62X-SDK releases](https://github.com/RIFTEK-LLC/RF62X-SDK/releases) link) into the path of the project executable
*  Run example

</details>
  
# CREATING PROJECT
## Creating a C/C++ project 

<details><summary>Create a new project in Qt Creator by CMake with using shared(static) SDK-library</summary> 
  
*  Open **File > New File or Project**, select **Qt Console Application** and click **Choose** button
*  Enter project name, Browse project location and click **Next** button
*  Choose **CMake** build system and click **Next** button twice
*  Select one of 64bit compilers (MinGW, MSVC, Clang, etc..), click **Next** button and finish project setup.
*  Download **RF62X-SDK** archive for C++ (see [RF62X-SDK releases](https://github.com/RIFTEK-LLC/RF62X-SDK/releases) link)
*  Modify your `CMakeLists.txt` file according to the example below:
```cmake
cmake_minimum_required(VERSION 3.14)

###############################################################################
## EXECUTABLE-PROJECT
## name and version
###############################################################################
project(RF62X_Search_Example LANGUAGES CXX)

###############################################################################
## SETTINGS
## basic project settings before use
###############################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")

###############################################################################
## TARGET
## create target and add include path
###############################################################################
# create glob files for *.h, *.cpp
file (GLOB H_FILES   ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# concatenate the results (glob files) to variable
set  (SOURCES ${CPP_FILES} ${H_FILES})
# create executable from src
add_executable(${PROJECT_NAME} ${SOURCES})

###############################################################################
## FIND PACKEGE AND LINK LIBRARIES
## linking all dependencies
###############################################################################
SET(RF62X_SDK_LIBRARY_TYPE "STATIC")
if (MSVC)
    find_package(RF62X-SDK PATHS "../RF62X-SDK_cpp/MSVC2019_64bit/CMake")
elseif(MINGW)
    find_package(RF62X-SDK PATHS "../RF62X-SDK_cpp/MinGW_64bit/CMake")
else()
  find_package(RF62X-SDK PATHS "../RF62X-SDK_cpp/GCC_64bit/CMake")
endif()
target_link_directories(${PROJECT_NAME} PUBLIC ${RF62X_SDK_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${RF62X_SDK_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${RF62X_SDK_INCLUDE_DIRS})
```
*  Modify your `main.cpp` file according to the example below:

```c++
#include <string>
#include <iostream>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;

int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#         Search Example v2.x.x         #"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#########################################\n"<< std::endl;

    // Initialize sdk library
    sdk_init();

    // Print return rf62X sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<std::shared_ptr<rf627smart>> list;
    // Search for rf627smart devices over network
    list = rf627smart::search(500);

    // Print count of discovered rf627smart in network by Service Protocol
    std::cout << "Was found\t: " << list.size()<< " RF627-Smart" << std::endl;
    std::cout << "========================================="     << std::endl;


    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<hello_info> info = list[i]->get_info();

        std::cout << "\n\nID scanner's list: " << i               << std::endl;
        std::cout << "-----------------------------------------"  << std::endl;
        std::cout << "Device information: "                       << std::endl;
        std::cout << "* Name  \t: "   << info->device_name()      << std::endl;
        std::cout << "* Serial\t: "   << info->serial_number()    << std::endl;
        std::cout << "* IP Addr\t: "  << info->ip_address()       << std::endl;
        std::cout << "* MAC Addr\t: " << info->mac_address()      << std::endl;

        std::cout << "\nWorking ranges: "                         << std::endl;
        std::cout << "* Zsmr, mm\t: " << info->z_smr()            << std::endl;
        std::cout << "* Zmr , mm\t: " << info->z_mr()             << std::endl;
        std::cout << "* Xsmr, mm\t: " << info->x_smr()            << std::endl;
        std::cout << "* Xemr, mm\t: " << info->x_emr()            << std::endl;

        std::cout << "\nVersions: "                               << std::endl;
        std::cout << "* Firmware\t: " << info->firmware_version() << std::endl;
        std::cout << "* Hardware\t: " << info->hardware_version() << std::endl;
        std::cout << "-----------------------------------------"  << std::endl;
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}
```
>  If `SET(RF62X_SDK_LIBRARY_TYPE "SHARED")` copy **RF62X-SDK.dll** into the path of the project executable (PROJECT_BINARY_DIR)
*  Select **Debug** or **Release** build type, Run CMake and Run project 

</details>
  
<details><summary>Create a new project in Qt Creator by CMake with using SDK-sources </summary> 
  
*  Open **File > New File or Project**, select **Qt Console Application** and click **Choose** button
*  Enter project name, Browse project location and click **Next** button
*  Choose **CMake** build system and click **Next** button twice
*  Select one of 64bit compilers (MinGW, MSVC, Clang, etc..), click **Next** button and finish project setup.
*  Download the project:
```bash
git clone https://github.com/RIFTEK-LLC/RF62X-SDK.git
cd RF62X-SDK
git submodule update --init --recursive
```
*  Modify your `CMakeLists.txt` file according to the example below and update `RF62XSDK_DIR` according to your path to `RF62X-Wrappers/Cpp` folder:
```cmake
cmake_minimum_required(VERSION 3.13)

###############################################################################
## EXECUTABLE-PROJECT
## name and version
###############################################################################
project(RF62X_Search_Example LANGUAGES CXX)

###############################################################################
## SETTINGS
## basic project settings before use
###############################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")

###############################################################################
## TARGET
## create target and add include path
###############################################################################
# create glob files for *.h, *.cpp
file (GLOB H_FILES   ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# concatenate the results (glob files) to variable
set  (SOURCES ${CPP_FILES} ${H_FILES})
# create executable from src
add_executable(${PROJECT_NAME} ${SOURCES})

###############################################################################
## INCLUDING SUBDIRECTORIES AND LINK LIBRARIES
## linking all dependencies
###############################################################################
# set RF62XSDK path variable
set(RF62XSDK_DIR "../RF62X-Wrappers/Cpp")
# add subdirectory of RF62X-SDK lib
add_subdirectory(${RF62XSDK_DIR} RF62X-SDK)
target_link_libraries(${PROJECT_NAME} RF62X-SDK)
```
*  Modify your `main.cpp` file according to the example below:

```c++
#include <string>
#include <iostream>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;

int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#         Search Example v2.x.x         #"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#########################################\n"<< std::endl;

    // Initialize sdk library
    sdk_init();

    // Print return rf62X sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<std::shared_ptr<rf627smart>> list;
    // Search for rf627smart devices over network
    list = rf627smart::search(500);

    // Print count of discovered rf627smart in network by Service Protocol
    std::cout << "Was found\t: " << list.size()<< " RF627-Smart" << std::endl;
    std::cout << "========================================="     << std::endl;


    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<hello_info> info = list[i]->get_info();

        std::cout << "\n\nID scanner's list: " << i               << std::endl;
        std::cout << "-----------------------------------------"  << std::endl;
        std::cout << "Device information: "                       << std::endl;
        std::cout << "* Name  \t: "   << info->device_name()      << std::endl;
        std::cout << "* Serial\t: "   << info->serial_number()    << std::endl;
        std::cout << "* IP Addr\t: "  << info->ip_address()       << std::endl;
        std::cout << "* MAC Addr\t: " << info->mac_address()      << std::endl;

        std::cout << "\nWorking ranges: "                         << std::endl;
        std::cout << "* Zsmr, mm\t: " << info->z_smr()            << std::endl;
        std::cout << "* Zmr , mm\t: " << info->z_mr()             << std::endl;
        std::cout << "* Xsmr, mm\t: " << info->x_smr()            << std::endl;
        std::cout << "* Xemr, mm\t: " << info->x_emr()            << std::endl;

        std::cout << "\nVersions: "                               << std::endl;
        std::cout << "* Firmware\t: " << info->firmware_version() << std::endl;
        std::cout << "* Hardware\t: " << info->hardware_version() << std::endl;
        std::cout << "-----------------------------------------"  << std::endl;
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}
```
*  Select **Debug** or **Release** build type, Run CMake and Run project 

</details>
  
<details><summary>Create a new project in Visual Studio 2019 with using shared(static) SDK-library</summary> 
  
*  Open Visual Studio and chose **Create a new project**, then select **Empty Project** and click **Next** button
*  Enter project name, Browse project location and click **Next** button
*  Add `main.cpp` file to project and modify it according to the example below:
```c++
#include <string>
#include <iostream>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;


int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#         Search Example v2.x.x         #"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#########################################\n"<< std::endl;

    // Initialize sdk library
    sdk_init();

    // Print return rf62X sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<std::shared_ptr<rf627smart>> list;
    // Search for rf627smart devices over network
    list = rf627smart::search(500);

    // Print count of discovered rf627smart in network by Service Protocol
    std::cout << "Was found\t: " << list.size()<< " RF627-Smart" << std::endl;
    std::cout << "========================================="     << std::endl;


    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<hello_info> info = list[i]->get_info();

        std::cout << "\n\nID scanner's list: " << i               << std::endl;
        std::cout << "-----------------------------------------"  << std::endl;
        std::cout << "Device information: "                       << std::endl;
        std::cout << "* Name  \t: "   << info->device_name()      << std::endl;
        std::cout << "* Serial\t: "   << info->serial_number()    << std::endl;
        std::cout << "* IP Addr\t: "  << info->ip_address()       << std::endl;
        std::cout << "* MAC Addr\t: " << info->mac_address()      << std::endl;

        std::cout << "\nWorking ranges: "                         << std::endl;
        std::cout << "* Zsmr, mm\t: " << info->z_smr()            << std::endl;
        std::cout << "* Zmr , mm\t: " << info->z_mr()             << std::endl;
        std::cout << "* Xsmr, mm\t: " << info->x_smr()            << std::endl;
        std::cout << "* Xemr, mm\t: " << info->x_emr()            << std::endl;

        std::cout << "\nVersions: "                               << std::endl;
        std::cout << "* Firmware\t: " << info->firmware_version() << std::endl;
        std::cout << "* Hardware\t: " << info->hardware_version() << std::endl;
        std::cout << "-----------------------------------------"  << std::endl;
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}
```
*  Select **x64** or **x86** and **Debug** or **Release** target platform
*  Download `RF62X-SDK` dll-s from archive for C++ wrapper (see [RF62X-SDK releases](https://github.com/RIFTEK-LLC/RF62X-SDK/releases) link) and copy `include` folder into the project directory.
*  Open **Project > Properties**, choose **Configuration Properties > VC++ Directories** and add paths of downloaded header files and libraries to **Include Directories** and **Library Directories**.
*  Compile project
*  Copy the **RF62X-SDK** libs into the path of the project executable (`../bin/x64/Debug/` or `../bin/x64/Release/`)
*  Run project

</details>
  
## Creating a C\# project 
<details><summary>Create a new project in Visual Studio 2019 with using SDK-libraries</summary> 
  
*  Open Visual Studio and chose **Create a new project**, then select **Empty Project** and click **Next** button
*  Enter project name (e.g RF627_search), Browse project location and click **Next** button
*  Modify your `Program.cs` file according to the example below:
```csharp
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
*  Select **x64** or **x86** and **Debug** or **Release** target platform
*  Download `RF62X-SDK` dll-s from archive for C# wrapper (see [RF62X-SDK releases](https://github.com/RIFTEK-LLC/RF62X-SDK/releases) link).
*  Open **Project > Add References**, click **Browse...** button and add downloaded `RF62X-SDK.dll` library.
*  Compile project
*  Copy the **libRF62X-SDK.dll** into the path of the project executable (`../bin/x64/Debug/` or `../bin/x64/Release/`)
*  Run project

</details>
  
## Creating a Python project 

<details><summary>Create a new project in Visual Studio Code with using SDK-libraries</summary> 
  
*  Create a project directory and add new **py-file** (e.g demo.py) in this project directory 
*  Download `RF62X-SDK` dll-s from archive for Python wrapper (see [RF62X-SDK releases](https://github.com/RIFTEK-LLC/RF62X-SDK/releases) link) into the project directory.
*  Modify your **py-file** (e.g demo.py) according to the example below:
```python
from PYSDK_SMART import *

if __name__ == '__main__':

    print("#########################################")
    print("#                                       #")
    print("#          Search Example v2.x.x        #")
    print("#                                       #")
    print("#########################################")
    
    # Initialize sdk library
    sdk_init()

    # Print return rf627 sdk version
    print('SDK version', sdk_version())
    print("=========================================")

    # Create value for scanners vector's type
    list_scanners=search(500)
    print("Was found\t:", len(list_scanners), "RF627-Smart")
    print("=========================================")


    # Iterate over all available network adapters in the current operating
    # system to send "Hello" requests.
    i=0
    for scanner in list_scanners: 
        info = get_info(scanner, kSERVICE)
        i+=1
        #  Print short information about the scanner
        print("\n\nID scanner's list:", i)
        print("-----------------------------------------")
        print("Device information:")
        print("* Name\t\t: ",   info['user_general_deviceName'])
        print("* Serial\t: ",   info['fact_general_serial'])
        print("* IP Addr\t: ",  info['user_network_ip'])
        print("* MAC Addr\t: ",  info['fact_network_macAddr'])

        print("\nWorking ranges: ")
        print("* Zsmr, mm\t: ", info["fact_general_smr"])
        print("* Xsmr, mm\t: ", info["fact_general_xsmr"])

        print("\nVersions: " )
        print("* Firmware\t: ", info["firmware_version"])
        print("* Hardware\t: ", info["hardware_version"])
        print("-----------------------------------------")

    # Cleanup resources allocated with sdk_init()
    sdk_cleanup()
```

</details>
  

# COMPILING RF62X-SDK
## C WRAPPER
> for more information about project downloading steps, see an [Download project](#download-project)

<details><summary>CMake</summary> 
  
To build the C wrapper:
```bash
cd RF62X-SDK
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. -D_WRAPPER_LANGUAGE:STRING=C -D_SUBMODULE_CACHE_OVERWRITE=OFF
cmake --build . 
```
 
</details>
  
<details><summary>Qt Creator</summary> 
  
To build the code:
*  Load the `CMakeLists.txt` file from the `RF62X-SDK` folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Select a wrapper programming language (`SET(${PARENT}_WRAPPER_LANGUAGE "C" CACHE STRING "" ${REWRITE_FORCE})`)
*  Compile project
  
</details>
  
<details><summary>Visual Studio</summary> 
  
To build the code:
```bash
cd RF62X-SDK
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. -D_WRAPPER_LANGUAGE:STRING=C -D_SUBMODULE_CACHE_OVERWRITE=OFF
```
*  Open RF62X-SDK.sln with Visual Studio
*  Compile

</details>
  
## C++ WRAPPER
> for more information about project downloading steps, see an [Download project](#download-project)

<details><summary>CMake</summary> 
    
To build the C wrapper:
```bash
cd RF62X-SDK
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. -D_WRAPPER_LANGUAGE:STRING=C++ -D_SUBMODULE_CACHE_OVERWRITE=OFF
cmake --build . --config Release
```

</details>
  
<details><summary>Qt Creator</summary> 
  
To build the code:
*  Load the `CMakeLists.txt` file from the `RF62X-SDK` folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Select a wrapper programming language (`SET(${PARENT}_WRAPPER_LANGUAGE "C++" CACHE STRING "" ${REWRITE_FORCE})`)
*  Compile project

</details>
  
<details><summary>Visual Studio</summary> 
  
To build the code:
```bash
cd RF62X-SDK
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. -D_WRAPPER_LANGUAGE:STRING=C++ -D_SUBMODULE_CACHE_OVERWRITE=OFF
```
*  Open RF62X-SDK.sln with Visual Studio
*  Compile
  
</details>
  
## .NET WRAPPER
> for more information about project downloading steps, see an [Download project](#download-project)

<details><summary>Visual Studio</summary> 
  
To build the code:
*  Download or build the libRF62X-SDK dll-s for C wrapper (you should use one of the previously described 
methods - see [compilation C WRAPPER](#c-wrapper))
*  Open `RF62X-SDK.sln` from the `RF62X-Wrappers/CSharp/` folder with Visual Studio
*  Compile
  
</details>
  
## PYTHON WRAPPER
> for more information about project downloading steps, see an [Download project](#download-project)

*  Download or build the libRF62X-SDK dll-s for C wrapper (you should use one of the previously described 
methods - see [compilation C WRAPPER](#c-wrapper))
*  Copy RF62X-SDK dll-s, PYSDK_SMART.py to your own project folder
