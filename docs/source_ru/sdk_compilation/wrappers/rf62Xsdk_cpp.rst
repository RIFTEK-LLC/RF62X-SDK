.. _compilation_rf62x_sdk_cpp:

Компиляция «обёртки» на C++
-------------------------------------------------------------------------------

Эта библиотека позволяет упростить разработку приложений на языке C++

Для её использования в проектах C++ разработчик должен включить необходимые 
h-файлы библиотеки в свой проект и собрать статическую или динамическую 
программную библиотеку. 

.. _rf62Xsdk_cpp_dll_mingw_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/2148ca77659e21b2f7aec9e5cbb072ab/rf62Xsdk.dll
.. _rf62Xsdk_cpp_a_mingw_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/5a2fdb2b2fc3317fdeec78bbe0c00cc3/rf62Xsdk.a
.. _rf62Xsdk_cpp_mingw_64_include: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/e69dc9279a6dcba800a98142a8b32c8d/include.zip

.. _rf62Xsdk_cpp_dll_msvc17_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/912890213476c43b26bf8f178b1d2c5a/rf62Xsdk.dll
.. _rf62Xsdk_cpp_lib_msvc17_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/e42dadfe318fc3201d6b6f1e280040a9/rf62Xsdk.lib
.. _rf62Xsdk_cpp_msvc17_64_include: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/5e490e8b89b3c2870ec8102540a32b1a/include.zip

.. _rf62Xsdk_cpp_dll_clang_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/fc19b0fac252c78ed93d4fa86ebfc7eb/rf62Xsdk.dll
.. _rf62Xsdk_cpp_lib_clang_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/70b57c76ace11faa6c0e6d3ac8493a86/rf62Xsdk.lib
.. _rf62Xsdk_cpp_clang_64_include: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/e69dc9279a6dcba800a98142a8b32c8d/include.zip

.. _rf62x_sdk_cpp_last_release:

.. table:: Последние выпуски:

   +---------------+---------------------------------------------------------------------------------------------+--------------------------------------------------+
   | Compiler      | 64bit                                                                                       | Includes                                         |
   +===============+=============================================================================================+==================================================+
   | MinGW 7.3.0   | `rf62Xsdk.dll <rf62Xsdk_cpp_dll_mingw_64_>`_ `rf62Xsdk.a <rf62Xsdk_cpp_a_mingw_64_>`_       | `include.zip <rf62Xsdk_cpp_mingw_64_include>`_   |
   +---------------+---------------------------------------------------------------------------------------------+--------------------------------------------------+
   | MSVC2017      | `rf62Xsdk.dll <rf62Xsdk_cpp_dll_msvc17_64_>`_ `rf62Xsdk.lib <rf62Xsdk_cpp_lib_msvc17_64_>`_ | `include.zip <rf62Xsdk_cpp_msvc17_64_include>`_  |
   +---------------+---------------------------------------------------------------------------------------------+--------------------------------------------------+
   | Clang 9.1.0   | `rf62Xsdk.dll <rf62Xsdk_cpp_dll_clang_64_>`_ `rf62Xsdk.lib <rf62Xsdk_cpp_lib_clang_64_>`_   | `include.zip <rf62Xsdk_cpp_clang_64_include>`_   |
   +---------------+---------------------------------------------------------------------------------------------+--------------------------------------------------+

.. _how_to_compile_rf62x_sdk_cpp:

Как скомпилировать
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Библиотека-«обёртка» rf62Xsdk может быть скомпилирован при помощи консоли или 
среды разработки (Visual Studio, Qt Creator)

Во-первых, вы должны загрузить проект (если не сделали этого ранее)

.. note::
   для получения дополнительной информации о шагах загрузки проекта см. :ref:`clone_rf62x_sdk`

.. _how_to_compile_rf62x_sdk_cpp_cmake:

CMake
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Находясь в папке с проектом, для построения библиотеки-«обёртки» (rf62Xsdk библиотеки) 
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd rf62Xwrappers/Сpp/rf62Xsdk
   mkdir build
   cd build
   cmake ..
   cmake --build .

.. _how_to_compile_rf62x_sdk_cpp_qt_creator:

Qt Creator
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Для построения библиотеки-«обёртки» (rf62Xsdk библиотеки) с использованием IDE Qt Creator: 

-  Загрузите файл CMakeLists.txt из папки **rf62Xwrappers/Сpp/rf62Xsdk** через 
   **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Откройте **Build Settings** и отметьте пункт **install** для **Build Steps**
-  Скомпилируйте проект

.. _how_to_compile_rf62x_sdk_cpp_vs:

Visual Studio
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Находясь в папке с проектом, для построения RF62X CORE (rf62Xcore библиотеки) 
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd rf62Xwrappers/Сpp/rf62Xsdk
   mkdir build
   cd build
   cmake ..

-  Откройте полученное решение rf62Xsdk.sln в Visual Studio
-  Скомпилируйте проект

.. _how_to_use_rf62x_sdk_cpp:

Как использовать
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Вы можете **создать свой проект**, включив в него статическую или динамическую библиотеку и 
необходимые заголовочные файлы, или вы можете **открыть и скомпилировать** один из 
приведенных ниже примеров использования из папки **examples/Cpp/RF627\_old/**. 

.. note:: 
   Помимо приведенных ниже примеров, где каждый может быть скомпилирован и выполнен, 
   вы также можете прочитать документацию для «обёртки» на C++ (см. :ref:`rf62x_wrappers_description_cpp`), 
   где каждая функция содержит отдельный пример кода. 

.. _how_to_use_rf62x_sdk_cpp_for_search:

Поиск устройств RF62X
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример поиска сканеров серии RF627-old в сети 

.. code-block:: cpp

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

      system("pause");
   }


Ниже приведён результат вывода приложения при успешном обнаружении сканера в сети:

.. code-block:: bash

   SDK version: 1.3.0
   =========================================
   Discovered: 1 rf627-old

   ID scanner's list: 0
   -----------------------------------------
   Device information: 
   * Name      : RF627
   * Serial    : 190068
   * IP Addr   : 192.168.1.32
   * MAC Addr  : 00:0a:35:6e:07:f5

   Working ranges: 
   * Zsmr, mm  : 70
   * Zmr , mm  : 50
   * Xsmr, mm  : 30
   * Xemr, mm  : 42

   Versions: 
   * Firmware  : 19.11.12
   * Hardware  : 18.6.20
   -----------------------------------------
   Press any key to continue . . . 


Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл CMakeLists.txt из папки **examples/Cpp/RF627\_old/RF627\_search** 
   через **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Запустите проект


.. _how_to_use_rf62x_sdk_cpp_for_get_profile:

Получение профиля сканера
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример получения профилей от сканеров серии RF627-old


.. code-block:: cpp

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
      for(size_t i = 0; i < scanners.size(); i++)
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
            case (uint8_t)PROFILE_DATA_TYPE::PROFILE:
                std::cout << "* DataType\t: "<< "PROFILE"           << std::endl;
                std::cout << "* Size\t: "  << profile->points.size()<< std::endl;
                break;
            case (uint8_t)PROFILE_DATA_TYPE::PIXELS_INTRP:
                std::cout << "* DataType\t: "<< "PIXELS_INTRP"      << std::endl;
                std::cout << "* Count\t: " << profile->pixels.size()<< std::endl;
                break;
            case (uint8_t)PROFILE_DATA_TYPE::PROFILE_INTRP:
                std::cout << "* DataType\t: "<< "PROFILE_INTRP"     << std::endl;
                std::cout << "* Size\t: "  << profile->points.size()<< std::endl;
                break;
            }
            std::cout << "Profile was successfully received!"       << std::endl;
            std::cout << "-----------------------------------------"<< std::endl;
         }else
         {
            std::cout << "Profile was not received!"                << std::endl;
            std::cout << "-----------------------------------------"<< std::endl;
         }

      }
   
      system("pause");
   }


Ниже приведён результат вывода приложения при успешном получении профиля от сканера:

.. code-block:: bash

   SDK version: 1.3.0
   =========================================
   Discovered: 1 rf627-old


   ID scanner's list: 0
   -----------------------------------------
   Device information: 
   * Name      : RF627
   * Serial    : 190068
   * IP Addr   : 192.168.1.32
   Profile information: 
   * DataType  : PROFILE
   * Size      : 648
   Profile was successfully received!
   -----------------------------------------
   Press any key to continue . . . 

.. _how_to_use_rf62x_sdk_cpp_for_get_set_params:

   
Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл CMakeLists.txt из папки **examples/Cpp/RF627\_old/RF627\_profile** 
   через **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Запустите проект

Получение и установка параметров
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример получения и изменения имени сканера, установки IP адреса, смены 
состояния лазера (включение или отключение):


.. code-block:: cpp

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

      }

      system("pause");

   }


Ниже приведён результат вывода приложения при успешной установке новых параметров:

.. code-block:: bash

   SDK version: 1.3.0
   =========================================
   Discovered: 1 rf627-old


   ID scanner's list: 0
   -----------------------------------------
   Current Device Name  : RF627
   New Device Name      : RF627_TEST
   -----------------------------------------
   Current Device IP    : 192.168.1.32.
   New Device IP        : 192.168.1.33.
   -----------------------------------------
   Current Laser State  : ON
   New Laser State      : OFF
   -----------------------------------------
   
   Press any key to continue . . . 


Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл CMakeLists.txt из папки **examples/Cpp/RF627\_old/RF627\_params** 
   через **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Запустите проект