*******************************************************************************
RF62X Wrappers
*******************************************************************************

Wrappers are help to make programs in different languages and for 
different platforms using the rf62Xcore library easier.

C++ Library
===============================================================================

This project is a C++ library that simplifies the integration of C++
applications with following scanner series: \* RF627-old \* RF627-smart

.. table:: Last release libraries:

   +---------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Compiler      | 64bit                                                                                                                                                  | Includes                                                                  |
   +===============+========================================================================================================================================================+===========================================================================+
   | MinGW 7.3.0   | `rf62Xsdk.dll </uploads/ecbe8feab6232f0885b5b1e6db607aa8/rf62Xsdk.dll>`__                                                                              | `include.zip </uploads/c4e61f8dd8068d9360c42865408c7242/include.zip>`__   |
   +---------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | MSVC2017      | `rf62Xsdk.dll </uploads/09ea279c561d242dec0a93447d4efb9a/rf62Xsdk.dll>`__, `rf62Xsdk.lib </uploads/f254cb872337f25c21a9fb7b7f065518/rf62Xsdk.lib>`__   | `include.zip </uploads/c4e61f8dd8068d9360c42865408c7242/include.zip>`__   |
   +---------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Clang 9.1.0   | `rf62Xsdk.dll </uploads/32d124be918aa349a213a1b75124026f/rf62Xsdk.dll>`__                                                                              | `include.zip </uploads/c4e61f8dd8068d9360c42865408c7242/include.zip>`__   |
   +---------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------+

How to compile
-------------------------------------------------------------------------------

RF62X SDK (C++) can be built on the console or in an IDE.
Firstly, you should download the project (if you have already done it, skip next commands)

.. code-block:: bash

   git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
   cd RF62X-SDK
   git submodule update --init --recursive

.. note::
   for more information about project downloading steps, see an `overview <#overview>`__

CMake
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To build the С++ wrapper:

.. code-block:: bat

   cd wrappers/cpp/CMake/rf62Xsdk
   cmake .
   cmake --build . 

Qt Creator
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To build the code:

-  Load the CMakeLists.txt file from the **wrappers/cpp/CMake/rf62Xsdk**
   folder via **File > Open File or Project** (Select the CMakeLists.txt file)

-  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**

-  Compile project

Visual Studio
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To build the code:

.. code-block:: bat

    cd wrappers/cpp/CMake/rf62Xsdk
    cmake .

-  Open rf62Xsdk.sln with Visual Studio
-  Compile

How to use
-------------------------------------------------------------------------------

Beside the examples below, you may want to check the documentation where
each function contains a separate code example. All example project can
be compiled and executed. 

Search for RF62X devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are some examples how to use search methods 

Search for RF627-old devices over network by service protocol 
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: cpp

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


You can open and build this example by **Qt Creator**:

-  Load the CMakeLists.txt file from the
   **samples/win64/CMake/RF627\_search** folder via **File > Open File or Project** 
   (Select the CMakeLists.txt file)
   
-  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**

-  Compile project

Get Profile from RF62X devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are some examples how to use get profile methods 

Get Profile from RF627-old devices over network by service protocol
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: cpp

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

   
You can open and build this example by **Qt Creator**:

-  Load the CMakeLists.txt file from the
   **samples/win64/CMake/RF627\_profile** folder via **File > Open File or Project**
   (Select the CMakeLists.txt file)
   
-  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**

-  Compile project

Get/Set RF62X-old parameters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are some examples how to work with device's parameters 

Get/Set RF627-old parameters devices over network 
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: cpp

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


You can open and build this example by **Qt Creator**:

-   Load the CMakeLists.txt file from the
    **samples/win64/CMake/RF627\_params** folder via **File > Open File or Project** 
    (Select the CMakeLists.txt file)
    
-   Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure Project**

-   Compile project

.NET Library
===============================================================================

This project is a .NET library, written in C# language, that simplifies
the integration of C#, Visual Basic .NET, C++/CLI and JScript .NET
applications with following scanner series: \* RF627-old \* RF627-smart

.. table:: Last release libraries:

    +---------------------------------+-----------------------------------------------------------------------------+-------------------------------------------------------------------------------+
    | Platform                        | 64bit                                                                       | Dependencies (x64)                                                            |
    +=================================+=============================================================================+===============================================================================+
    | .NET Framework 4.5 (or above)   | `rf62Xsdk.dll </uploads/8d0e1e7d20de6c00bc6ccc0a9bd0696b/rf62Xsdk.dll>`__   | `rf62Xcore.dll </uploads/8d5bdec0c244ec9afb6c977014dc870e/rf62Xcore.dll>`__   |
    +---------------------------------+-----------------------------------------------------------------------------+-------------------------------------------------------------------------------+


How to compile
-------------------------------------------------------------------------------

RF62X SDK (C#) can be built in an Visual Studio IDE.
Firstly, you should download the project (if you have already done it, skip next commands)

.. code:: bat

    git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
    cd RF62X-SDK
    git submodule update --init --recursive

.. note::
    for more information about project downloading steps, see an `overview <#overview>`__

Visual Studio
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To build the code:

-  Open rf62Xsdk.sln from the **wrappers/csharp/VS2019/rf62Xsdk** folder 
   with Visual Studio

-  Compile

How to use
-------------------------------------------------------------------------------

Beside the examples below, you may want to check the documentation where
each function contains a separate code example. All example project can
be compiled and executed.

You can open and build these examples by **Visual Studio**:

-   Open **RF627\_TESTS.sln** from the
    **wrappers/csharp/VS2019/RF627\_TESTS** folder with Visual Studio

-   Select **x64 Debug** or **x64 Release** target platform

-   Add the **rf62Xsdk.dll** library to project's **references**

-   Copy the **rf62Xcore.dll** into the path of the project executable
    (**../bin/x64/Debug/** or **../bin/x64/Release/**)

-   Compile project

Search for RF62X devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are some examples how to use search methods 

Search for RF627-old devices over network by service protocol 
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: csharp

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


Get Profile from RF62X devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are some examples how to use get profile methods 

Get Profile from RF627-old devices over network by service protocol
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: csharp

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


Get/Set RF62X-old parameters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are some examples how to work with device's parameters 

Get/Set RF627-old parameters devices over network 
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: csharp

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

