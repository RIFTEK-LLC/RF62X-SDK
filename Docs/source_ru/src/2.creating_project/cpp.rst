.. _creating_project_rf62Xsdk_cpp:

*******************************************************************************
Создание проекта C/C++
*******************************************************************************

.. _creating_project_rf62Xsdk_cpp_qt_with_libs:

Qt Creator + CMake + RF62X-SDK в качестве библиотеки
===============================================================================

Для создания нового CMake проекта в Qt Creator с использованием 
динамической/статической линковки SDK необходимо выполнить следующий порядок 
действий:

-   В Qt Creator создайте новый проект открыв в меню **File > New File or Project**, 
    укажите **Qt Console Application** и нажмите кнопку **Choose**
-   Введите имя проекта в поле **Project Name** и укажите путь к папке с проектом 
    в поле **Project Location**, после ввода нажмите кнопку **Next**
-   Выберите **CMake** в качестве системы постояние проекта и нажмите кнопку **Next** дважды
-   Выберите компилятор (*MinGW*, *MSVC*, *Clang*), нажмите кнопку **Next** и завершите настройку проекта
-   Скачайте архив библиотек для C/C++ (смотреть `последние выпуски RF62X-SDK библиотек <https://github.com/RIFTEK-LLC/RF62X-SDK/releases/latest>`__)  
-   Измените файл ``CMakeLists.txt`` вашего проекта в соответствии с приведенным ниже примером:

.. code-block:: cmake

   cmake_minimum_required(VERSION 3.14)

   ##############################################################################
   ## EXECUTABLE-PROJECT
   ## name and version
   ##############################################################################
   project(RF62X_Search_Example LANGUAGES CXX)

   ##############################################################################
   ## SETTINGS
   ## basic project settings before use
   ##############################################################################
   set(CMAKE_INCLUDE_CURRENT_DIR ON)
   set(CMAKE_CXX_STANDARD 11)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)
   # creating output directory architecture in accordance with GNU guidelines
   set(BINARY_DIR "${CMAKE_BINARY_DIR}")
   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
   set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")

   ##############################################################################
   ## TARGET
   ## create target and add include path
   ##############################################################################
   # create glob files for *.h, *.cpp
   file (GLOB H_FILES   ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
   file (GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
   # concatenate the results (glob files) to variable
   set  (SOURCES ${CPP_FILES} ${H_FILES})
   # create executable from src
   add_executable(${PROJECT_NAME} ${SOURCES})

   ##############################################################################
   ## FIND PACKEGE AND LINK LIBRARIES
   ## linking all dependencies
   ##############################################################################
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

.. note::

   Для работы с динамической библиотекой RF62X-SDK необходимо установить параметр `RF62X_SDK_LIBRARY_TYPE` в значение `SHARED` (``SET(RF62X_SDK_LIBRARY_TYPE "SHARED")``) и скопировать библиотеку RF62X-SDK.dll(\*.so) в каталог к исполняемому файлу проекта (PROJECT_BINARY_DIR)


-   Измените файл ``main.cpp`` вашего проекта в соответствии с приведенным ниже примером:

.. code-block:: cpp

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

-   Выберите тип сборки **Debug** или **Release** и запустите построение проекта.

.. _creating_project_rf62Xsdk_cpp_qt_with_source:

Qt Creator + CMake + RF62X-SDK в качестве файлов исходного кода
===============================================================================

Для создания нового CMake проекта в Qt Creator с использованием 
файлов исходного кода SDK необходимо выполнить следующий порядок 
действий:

-   В Qt Creator создайте новый проект открыв в меню **File > New File or Project**, 
    укажите **Qt Console Application** и нажмите кнопку **Choose**
-   Введите имя проекта в поле **Project Name** и укажите путь к папке с проектом 
    в поле **Project Location**, после ввода нажмите кнопку **Next**
-   Выберите **CMake** в качестве системы постояние проекта и нажмите кнопку **Next** дважды
-   Выберите компилятор (*MinGW*, *MSVC*, *Clang*), нажмите кнопку **Next** и завершите настройку проекта
-   Скачайте **RF62X-SDK** проект (для получения дополнительной информации о шагах загрузки проекта см. :ref:`clone_rf62x_sdk`)  
-   Измените файл ``CMakeLists.txt`` вашего проекта в соответствии с приведенным ниже примером и установите в параметре ``RF62XSDK_DIR`` на путь к папке ``RF62X-Wrappers/Cpp`` в соответствии с расположением скачанного проекта **RF62X-SDK** 

.. code-block:: cmake

   cmake_minimum_required(VERSION 3.14)

   ##############################################################################
   ## EXECUTABLE-PROJECT
   ## name and version
   ##############################################################################
   project(RF62X_Search_Example LANGUAGES CXX)

   ##############################################################################
   ## SETTINGS
   ## basic project settings before use
   ##############################################################################
   set(CMAKE_INCLUDE_CURRENT_DIR ON)
   set(CMAKE_CXX_STANDARD 11)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)
   # creating output directory architecture in accordance with GNU guidelines
   set(BINARY_DIR "${CMAKE_BINARY_DIR}")
   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
   set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")

   ##############################################################################
   ## TARGET
   ## create target and add include path
   ##############################################################################
   # create glob files for *.h, *.cpp
   file (GLOB H_FILES   ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
   file (GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
   # concatenate the results (glob files) to variable
   set  (SOURCES ${CPP_FILES} ${H_FILES})
   # create executable from src
   add_executable(${PROJECT_NAME} ${SOURCES})

   ##############################################################################
   ## INCLUDING SUBDIRECTORIES AND LINK LIBRARIES
   ## linking all dependencies
   ##############################################################################
   # set RF62XSDK path variable
   set(RF62XSDK_DIR "../RF62X-Wrappers/Cpp")
   # add subdirectory of RF62X-SDK lib
   add_subdirectory(${RF62XSDK_DIR} RF62X-SDK)
   target_link_libraries(${PROJECT_NAME} RF62X-SDK)


-   Измените файл ``main.cpp`` вашего проекта в соответствии с приведенным ниже примером:

.. code-block:: cpp

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

-   Выберите тип сборки **Debug** или **Release** и запустите построение проекта.

.. _creating_project_rf62Xsdk_cpp_vs_with_libs:

Visual Studio + RF62X-SDK в качестве библиотеки
===============================================================================

Для создания нового проекта в Visual Studio с использованием 
динамической/статической линковки SDK необходимо выполнить следующий порядок 
действий:

-   Откройте Visual Studio и выберите **Create a new project**, 
    затем выберите **Empty Project** и нажмите кнопку **Next**
-   Введите имя проекта в поле **Project Name** и укажите путь к папке с проектом 
    в поле **Project Location**, после ввода нажмите кнопку **Next**
-   Скачайте архив библиотек для C/C++ (смотреть `последние выпуски RF62X-SDK библиотек <https://github.com/RIFTEK-LLC/RF62X-SDK/releases/latest>`__)  
-   Добавьте файл ``main.cpp`` в проект и измените его, как показано ниже:

.. code-block:: cpp

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

-   Выберите тип (*Debug* или *Release*) и разрядность (*x64* или *x86*) целевой платформы.
-   Скопируйте файлы из скаченного архива в папке ``include`` в каталог проекта.
-   Откройте **Project > Properties**, выберите **Configuration Properties > VC++ Directories** и добавьте пути к загруженным файлам заголовков и библиотекам в **Include Directories** и **Library Directories** соответственно.
-   Скомпилируйте проект.
-   Скопируйте библиотеки из скаченного архива в каталог к исполняемому файлу проекта (``../bin/x64/Debug/`` или ``../bin/x64/Release/``).
-   Запустите проект.