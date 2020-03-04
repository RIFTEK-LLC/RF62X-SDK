# RF627SDK

## CONTENTS
- [OVERVIEW](#overview)
- [RF627 CORE](#rf627-core)
  - [How to compile](#how-to-compile)
- [RF627 WRAPPER LIBRARIES](#rf627-wrapper-libraries)
  - [C++ LIBRARY](#c-library)
    - [How to compile](#how-to-compile-1)
    - [How to use](#how-to-use)
  - [C# LIBRARY](#c-library-1)
    - [How to compile](#how-to-compile-2)
    - [How to use](#how-to-use-1)
  - [PYTHON LIBRARY](#python-library)
    - [How to compile](#how-to-compile-3)
    - [How to use](#how-to-use-2)

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
*  Load the CMakeLists.txt file from the **rf627core** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Open **Build Settings** and check ***install*** target for **Build Steps** 
*  Compile project

###### Visual Studio
To build the code:

```CMake
cd rf627core
cmake .
```
*  Open rf627core.sln with Visual Studio
*  Compile

## RF627 WRAPPER LIBRARIES
Wrappers are used to make writing programs using the rf627core library easier.

### C++ LIBRARY
This project is a C++ library that simplifies the integration of C++ 
applications with following scanner series: 
*  RF627-old
*  RF627-smart

#### HOW TO COMPILE
RF627 SDK (C++) can be built on the console or in an IDE.\
Firstly, you should download the project (if you have already done it, skip next commands)
```
git clone https://gitlab.com/riftek_llc/software/sdk/scanners/rf627sdk.git
cd rf627sdk
git submodule update --init --recursive
```
> for more information about project downloading steps, see an [overview](#overview)

###### CMake
To build the С++ wrapper:

```CMake
cd wrappers/cpp/CMake/rf627sdk
cmake .
cmake --build . 
```

###### Qt Creator
To build the code:
*  Load the CMakeLists.txt file from the **wrappers/cpp/CMake/rf627sdk** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Compile project

###### Visual Studio
To build the code:

```CMake
cd wrappers/cpp/CMake/rf627sdk
cmake .
```
*  Open rf627sdk.sln with Visual Studio
*  Compile

#### HOW TO USE
Beside the examples below, you may want to check the documentation where each function 
contains a separate code example. All example project can be compiled and executed.
##### Search for RF627 devices
Here are some examples how to use search methods
###### Search for RF627-old devices over network by service protocol
```c++
#include <rf627sdk.h>
#include <rf627types.h>
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF627;

int main()
{

    // Initialize sdk library
    sdk_init();
    // Print return rf627 sdk version
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
*  Load the CMakeLists.txt file from the **samples/win64/CMake/RF627_search** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Compile project

##### Get Profile from RF627 devices
Here are some examples how to use get profile methods
###### Get Profile from RF627-old devices over network by service protocol
```c++
#include <rf627sdk.h>
#include <rf627types.h>
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF627;

int main()
{

    // Initialize sdk library
    sdk_init();
    // Print return rf627 sdk version
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
        std::cout << profile->profile_header.serial_number << std::endl;
        
    }
    
}
```
You can open and build this example by **Qt Creator**:  
*  Load the CMakeLists.txt file from the **samples/win64/CMake/RF627_profile** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Compile project

##### Get/Set RF627-old parameters
Here are some examples how to work with device's parameters
###### Get/Set RF627-old parameters devices over network
```c++
#include <rf627sdk.h>
#include <rf627types.h>
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF627;

int main()
{

    // Initialize sdk library
    sdk_init();
    // Print return rf627 sdk version
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
*  Load the CMakeLists.txt file from the **samples/win64/CMake/RF627_params** folder via 
**File > Open File or Project** (Select the CMakeLists.txt file)
*  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**
*  Compile project


### C# LIBRARY
This project is a .NET library, written in C# language, that simplifies the integration of C#, 
Visual Basic .NET, C++/CLI and JScript .NET applications with following scanner series: 
*  RF627-old
*  RF627-smart

#### HOW TO COMPILE
RF627 SDK (C#) can be built in an Visual Studio IDE.\
Firstly, you should download the project (if you have already done it, skip next commands)
```
git clone https://gitlab.com/riftek_llc/software/sdk/scanners/rf627sdk.git
cd rf627sdk
git submodule update --init --recursive
```
> for more information about project downloading steps, see an [overview](#overview)

###### Visual Studio
To build the code:

```CMake
cd wrappers/cpp/CMake/rf627sdk
cmake .
```
*  Open rf627sdk.sln from the **wrappers/csharp/VS2019/rf627sdk** folder with Visual Studio
*  Compile

#### HOW TO USE
Beside the examples below, you may want to check the documentation where each function 
contains a separate code example. All example project can be compiled and executed.

You can open and build these examples by **Visual Studio**:  
*  Open **RF627_TESTS.sln** from the **wrappers/csharp/VS2019/RF627_TESTS** folder with Visual Studio
*  Select **x64 Debug** or **x64 Release** target platdorm
*  Add the **rf627sdk.dll** library to project's **references** 
*  Copy the **rf627core.dll** into the path of the project executable (**../bin/x64/Debug/** or **../bin/x64/Release/**)
*  Compile project

##### Search for RF627 devices
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
            RF627.SdkInit();

            // Print return rf627 sdk version
            Console.WriteLine("Current rf627 sdk version: {0}", RF627.SdkVersion());


            // Search for RF627old devices over network
            Console.WriteLine("- Start searching device");
            List<RF627.RF627old> Scanners = RF627.RF627old.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);
            
        }
    }
}
```

##### Get Profile from RF627 devices
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
            RF627.SdkInit();


            // Search for RF627old devices over network
            List<RF627.RF627old> Scanners = RF627.RF627old.Search();


            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
                // Establish connection to the RF627 device
                Scanners[i].Connect();
                
                
                //Receive profile
                RF627.Profile profile = Scanners[i].GetProfile();
                if (profile.header != null)
                    Console.WriteLine("Received profile successfully);
                else 
                    Console.WriteLine("Profile is null");
            }
            
        }
    }
}
```

##### Get/Set RF627-old parameters
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
            RF627.SdkInit();


            // Search for RF627old devices over network
            List<RF627.RF627old> Scanners = RF627.RF627old.Search();


            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
                // Establish connection to the RF627 device
                Scanners[i].Connect();


                // Try to read params
                Scanners[i].ReadParams();


                // Get scanner's name
                RF627.Param<string> deviceName = 
                        Scanners[i].GetParam(RF627.Params.User.General.deviceName);


                // Set new scanner's name and write changed parameters to scanner
                deviceName.SetValue("New Name");
                Scanners[i].SetParam(deviceName);


                // Send command to scanner to write changed parameters
                Scanners[i].WriteParams();


                // Check that the parameter is set correctly
                // Read again all params from RF627 device.
                Scanners[i].ReadParams();


                // Get scanner's name
                RF627.Param<string> newDeviceName = 
                        Scanners[i].GetParam(RF627.Params.User.General.deviceName);
                if (newDeviceName.GetValue() == "New Name")
                    Console.WriteLine("Changed parameters write successfully");
                else 
                    Console.WriteLine("Error changing parameters");
            }
            
        }
    }
}
```


#### HOW TO COMPILE
#### HOW TO USE

### PYTHON LIBRARY
#### HOW TO COMPILE
#### HOW TO USE