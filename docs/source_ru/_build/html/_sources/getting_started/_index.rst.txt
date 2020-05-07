*******************************************************************************
Подготовка к работе
*******************************************************************************

RF62X-SDK предоставляет пользователю простой интерфейс при разработки программного 
обеспечения для сканеров серии RF62X. 

**Для разработчиков**, которые просто хотят использовать **готовые библиотеки SDK** для работы со
сканерами, могут **скачать** их последние версии, а также прочитать **примеры использования**
(`C++ <#how-to-use>`__, `C# <#how-to-use-1>`__, `PYTHON <#how-to-use-2>`__).

**Для разработчиков**, которые предпочитают самостоятельно собрать **библиотеки SDK из исходников**, 
должны воспользоваться Git, а также выполнить некоторые `инструкции по установке <#install-software>`__


Installing software
===============================================================================

1. Install a git client on your local computer (if you haven’t yet)
-------------------------------------------------------------------------------

-  On Linux use the terminal command: ``sudo apt install git``
-  On MacOS use the terminal command: ``brew install git``
-  For other platforms see the `git installation
   documentation <https://git-scm.com/downloads>`__. 
   
2. Open a command prompt/terminal on your computer
-------------------------------------------------------------------------------

-  On Linux, click the launch bar and search for 'terminal'
-  On OS X, hit ⌘-space and search for 'terminal'
-  On Windows, click the Start menu and search for 'command line'.

3. Clone the repository using the following commands:
-------------------------------------------------------------------------------

.. code-block:: bash

    git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
    cd RF62X-SDK
    git submodule update --init --recursive


For developers who wish to download and build the latest code using Git
from the IDE (Qt Creator or Visual Studio Community) should follow these
instructions: 

1. Create a Git project in one of the IDEs 

2. Clone ``https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git`` 

3. Download submodules

.. note:: We recommend to use a git client for downloading and Qt Creator for
  project building

Running RF62X SDK tutorials
===============================================================================

Here a basic example how to use method for searching RF62X devices in
different languages by different ways. You can create a new project 
yourself or you can just open an existing project example and build it. 

Compiling examples in C++ from source
-------------------------------------------------------------------------------

1. Open and compile examples project in **Qt Creator**:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

-  Load the CMakeLists.txt file from the **samples/Cpp/RF627_TESTS**
   folder via **File > Open File or Project** (Select the CMakeLists.txt file)

.. figure:: _static/note1.png
   :alt: 

-  Select compiler (MinGW, MSVC2017, Clang, etc..) and click **Configure
   Project**

.. figure:: _static/note2.png
   :alt: 

-  Choose one of the examples, Compile and Run it

2. Generate a project for **Visual Studio** and compile examples
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

-  Generate Visual Studio solution by calling CMake from the console

.. code-block:: bat

    cd samples/Cpp/RF627_TESTS
    mkdir build
    cd build

    :: Run one of the following lines based on your Visual Studio version
    cmake -G "Visual Studio 15 2017 Win64" ..
    cmake -G "Visual Studio 16 2019 Win64" ..


Creating a new project in C++ with using shared or static SDK-library
-------------------------------------------------------------------------------

1. Create a new project in **Qt Creator** by СMake
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

-   Open **File > New File or Project**, select **Qt Console Application** 
    and click **Choose** button

.. figure:: _static/note3.png
   :alt: 

-  Enter project name, Browse project location and click **Next** button
-  Choose **CMake** build system and click **Next** button twice
-  Select one of 64bit compilers (MinGW, MSVC2017, Clang, etc..), click
   **Next** button and finish project setup.
-  `Download <#c-library>`__ **include.zip** archive and unzip it into
   the project directory. Also download **rf62Xsdk.dll** and copy it
   into the project directory next to the main.cpp file

.. figure:: _static/note4.png
   :alt: 

-  Modify your **CMakeLists.txt** file according to the example below:

.. code-block:: cmake

    cmake_minimum_required(VERSION 3.5)

    project(TestProject LANGUAGES CXX)

    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    add_executable(${PROJECT_NAME} main.cpp)

    # include *.h rf62Xsdk files from directory
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

    # find rf62Xsdk lib in paths and copy full file name to RF62XSDK_LIBRARY
    find_library(
        RF62XSDK_LIBRARY
        rf62Xsdk
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}
        )

    target_link_libraries(${PROJECT_NAME} ${RF62XSDK_LIBRARY})


-  Modify your **main.cpp** file according to the example below:

.. code-block:: cpp
 
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

-  Copy **rf62Xsdk.dll** into the path of the project executable (PROJECT\_BINARY\_DIR)

You can do it in two ways: 

1) Copy rf62Xsdk.dll to the executable folder (near with \*.exe) yourself. 
  
2) Or add a "copy command" to the end of the CMakeLists.txt file:

.. code:: cmake

    # copy rf62Xsdk lib from cmake current source directory to project build directory
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${RF62XSDK_LIBRARY} ${PROJECT_BINARY_DIR})

-  Select **Debug** or **Release** build type, Run CMake and Run project

Beside this example, you may want to check the documentation where each
function contains a separate code example. All example project can be
compiled and executed.