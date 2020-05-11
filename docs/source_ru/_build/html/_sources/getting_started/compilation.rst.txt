.. _compilation:

*******************************************************************************
Компиляция из исходников
*******************************************************************************

Как упоминалось ранее, RF62X-SDK состоит из двух частей:

- **RF62X CORE** - это основная библиотека (ядро) с базовым набором функций для 
  работы со сканерами, а также платформозависимыми функциями (такими как работа 
  с памятью, работа с сетью, функциями ввода/вывода и т.п.), 
  требующими предварительной инициализации. Библиотека написана на языке 
  программирования CИ в соответствии со стандартом C99 (ISO / IEC 9899: 1999).
- **RF62X WRAPPERS** - это библиотеки-«обёртки», в которых уже реализованы 
  платформозависимые функции библиотеки RF62X CORE для конкретной платформы. 
  Тем самым, используя библиотеку-«обёртку», вы упрощаете процесс разработки приложений 
  для работы со сканерами на удобном для вас языке программирования (С++, С#, PYTHON).
    
.. _compilation_rf62x_core:

RF62X CORE
===============================================================================

.. table:: Последние выпуски:

   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Compiler      | 64bit                                                                         | Includes                                                                  |
   +===============+===============================================================================+===========================================================================+
   | MinGW 7.3.0   | `rf62Xcore.dll </uploads/8d5bdec0c244ec9afb6c977014dc870e/rf62Xcore.dll>`__   | `include.zip </uploads/94210ce658946e97df0facd217d9d230/include.zip>`__   |
   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | MSVC2017      | `rf62Xcore.dll </uploads/5ff2632b9bb0a4a4f1344f58e71966c4/rf62Xcore.dll>`__   | `include.zip </uploads/94210ce658946e97df0facd217d9d230/include.zip>`__   |
   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Clang 9.1.0   | `rf62Xcore.dll </uploads/79520e5615eed8632f807bd667df3880/rf62Xcore.dll>`__   | `include.zip </uploads/94210ce658946e97df0facd217d9d230/include.zip>`__   |
   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+

.. _how_to_compile_rf62x_core:

Как скомпилировать
-------------------------------------------------------------------------------

RF62X CORE может быть скомпилирован при помощи консоли или среды разработки (Visual Studio, Qt Creator)

Во-первых, вы должны загрузить проект (если не сделали этого ранее)

.. note::
   для получения дополнительной информации о шагах загрузки проекта см. :ref:`clone_rf62x_sdk`

.. _how_to_compile_rf62x_core_cmake:

CMake
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Находясь в папке с проектом, для построения RF62X CORE (rf62Xcore библиотеки) 
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd rf62Xcore
   mkdir build
   cd build
   cmake ..
   cmake --build .

.. _how_to_compile_rf62x_core_qt_creator:

Qt Creator
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Для построения RF62X CORE (rf62Xcore библиотеки) с использованием IDE Qt Creator: 

-  Загрузите файл CMakeLists.txt из папки **rf62Xcore** через 
   **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Откройте **Build Settings** и отметьте пункт **install** для **Build Steps**
-  Скомпилируйте проект

.. _how_to_compile_rf62x_core_vs:

Visual Studio
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Находясь в папке с проектом, для построения RF62X CORE (rf62Xcore библиотеки) 
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd rf62Xcore
   mkdir build
   cd build
   cmake ..

-  Откройте полученное решение rf62Xcore.sln в Visual Studio
-  Скомпилируйте проект

.. _compilation_rf62x_sdk:

RF62X WRAPPERS
===============================================================================

Библиотеки-«обёртки» помогают создавать программы для работы со сканерами серии 
RF62X на разных языках для различных платформ, тем самым упрощая использование 
RF62X CORE (rf62Xcore библиотеки).

.. _compilation_rf62x_sdk_cpp:

Библиотека-«обёртка» на C++
-------------------------------------------------------------------------------

Эта библиотека позволяет упростить разработку приложений на языке C++

Для её использования в проектах C++ разработчик должен включить необходимые 
h-файлы библиотеки в свой проект и собрать статическую или динамическую 
программную библиотеку. 


.. table:: Последние выпуски:

   +---------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Compiler      | 64bit                                                                                                                                                  | Includes                                                                  |
   +===============+========================================================================================================================================================+===========================================================================+
   | MinGW 7.3.0   | `rf62Xsdk.dll </uploads/ecbe8feab6232f0885b5b1e6db607aa8/rf62Xsdk.dll>`__                                                                              | `include.zip </uploads/c4e61f8dd8068d9360c42865408c7242/include.zip>`__   |
   +---------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | MSVC2017      | `rf62Xsdk.dll </uploads/09ea279c561d242dec0a93447d4efb9a/rf62Xsdk.dll>`__, `rf62Xsdk.lib </uploads/f254cb872337f25c21a9fb7b7f065518/rf62Xsdk.lib>`__   | `include.zip </uploads/c4e61f8dd8068d9360c42865408c7242/include.zip>`__   |
   +---------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Clang 9.1.0   | `rf62Xsdk.dll </uploads/32d124be918aa349a213a1b75124026f/rf62Xsdk.dll>`__                                                                              | `include.zip </uploads/c4e61f8dd8068d9360c42865408c7242/include.zip>`__   |
   +---------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------+

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

Помимо приведенных ниже примеров, где каждый может быть скомпилирован и выполнен, 
вы также можете прочитать документацию на библиотеку-«обёртку» на C++, где каждая 
функция содержит отдельный пример кода. 

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

-  Загрузите файл CMakeLists.txt из папки **examples\Cpp\RF627\_old** 
   через **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Выберите в качестве запускаемого проета **RF627\_search**
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


Ниже приведён результат вывода приложения при успешном получении профиля со сканера:

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

-  Загрузите файл CMakeLists.txt из папки **examples\Cpp\RF627\_old** 
   через **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Выберите в качестве запускаемого проета **RF627\_profile**
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

-  Загрузите файл CMakeLists.txt из папки **examples\Cpp\RF627\_old** 
   через **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Выберите в качестве запускаемого проета **RF627\_params**
-  Запустите проект

.. _compilation_rf62x_sdk_csharp:

Библиотека-«обёртка» на C#
-------------------------------------------------------------------------------

Эта «обёртка» представляет собой библиотеку .NET, написанную на языке C#? которая 
позволяет может быть использована в приложениях на C#, Visual Basic .NET, C++/CLI 
и JScript .NET

Для её использования в проектах .NET разработчик должен собрать или скачать динамическую 
программную библиотеку **rf62Xsdk.dll**, после чего добавить библиотеку к ссылкам 
(references) проекта, а также собрать или скачать **rf62Xcore.dll** добавив её 
в папку к исполняемому файлу проекта.


.. table:: Последние выпуски:

    +---------------------------------+-----------------------------------------------------------------------------+-------------------------------------------------------------------------------+
    | Platform                        | 64bit                                                                       | Dependencies (x64)                                                            |
    +=================================+=============================================================================+===============================================================================+
    | .NET Framework 4.5 (or above)   | `rf62Xsdk.dll </uploads/8d0e1e7d20de6c00bc6ccc0a9bd0696b/rf62Xsdk.dll>`__   | `rf62Xcore.dll </uploads/8d5bdec0c244ec9afb6c977014dc870e/rf62Xcore.dll>`__   |
    +---------------------------------+-----------------------------------------------------------------------------+-------------------------------------------------------------------------------+

.. _how_to_compile_rf62x_sdk_csharp:

Как скомпилировать
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Библиотека-«обёртка» rf62Xsdk может быть скомпилирован при помощи среды 
разработки Visual Studio

Во-первых, вы должны загрузить проект (если вы уже сделали это, пропустите следующие шаги)

.. code-block:: bash

   git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
   cd RF62X-SDK
   git submodule update --init --recursive

.. note::
   для получения дополнительной информации о шагах загрузки проекта см. `Скачивание проекта <#overview>`__

.. _how_to_compile_rf62x_sdk_csharp_vs:

Visual Studio
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

-  Откройте решение rf62Xsdk.sln по пути **rf62Xwrappers/CSharp/rf62Xsdk** в Visual Studio
-  Скомпилируйте проект

.. _how_to_use_rf62x_sdk_csharp:

Как использовать
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Помимо приведенных ниже примеров, где каждый может быть скомпилирован и выполнен, 
вы также можете прочитать документацию на библиотеку-«обёртку» на C#, где каждая 
функция содержит отдельный пример кода. 

Вы можете открыть и построить этот пример с помощью **Visual Studio**:

-   Откройте решение **RF627\_TESTS.sln** из папки
    **rf62Xwrappers/CSharp/RF627\_old**
-   Выберите **x64 Debug** или **x64 Release** в качестве целевой платформы
-   Добвавьте **rf62Xsdk.dll** библиотеку к ссылкам (**references**) проекта
-   Скопируйте **rf62Xcore.dll** в путь к исполняемому файлу проекта
    (**../bin/x64/Debug/** или **../bin/x64/Release/**)
-   Скомпилируйте проект


.. _how_to_use_rf62x_sdk_csharp_for_search:

Поиск устройств RF62X
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример поиска сканеров серии RF627-old в сети 

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

            }
        }
    }

.. _how_to_use_rf62x_sdk_csharp_get_profile:

Получение профиля сканера
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример получения профилей от сканеров серии RF627-old


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
            }

            Console.WriteLine("{0}Press any key to end \"Search-test\"", Environment.NewLine);
            Console.ReadKey();
         }
      }
   }

.. _how_to_use_rf62x_sdk_csharp_get_set_params:

Получение и установка параметров
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример получения и изменения имени сканера, установки IP адреса, смены 
состояния лазера (включение или отключение):

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

               Scanners[i].WriteParams();
            }
            Console.WriteLine("{0}Press any key to end \"Parameters-test\"", Environment.NewLine);
            Console.ReadKey();
         }
      }
   }