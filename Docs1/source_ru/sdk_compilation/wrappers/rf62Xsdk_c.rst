.. _compilation_rf62x_sdk_cpp:

Компиляция «обёртки» на C
-------------------------------------------------------------------------------

Эта библиотека позволяет упростить разработку приложений на языке C

Для её использования в проектах C разработчик должен включить необходимые 
h-файлы библиотеки в свой проект и собрать статическую или динамическую 
программную библиотеку. 

.. _rf62Xsdk_c_dll_mingw_32_D: http://cloud.riftek.com/index.php/s/dR9ikNPdfxaAqDH/download
.. _rf62Xsdk_c_dll_mingw_32_R: http://cloud.riftek.com/index.php/s/fsCjkg6mJADXy42/download
.. _rf62Xsdk_c_dll_mingw_64_D: http://cloud.riftek.com/index.php/s/FSA9EmgxK4WyAaF/download
.. _rf62Xsdk_c_dll_mingw_64_R: http://cloud.riftek.com/index.php/s/wSDtPPZJn3WiPCp/download
.. _rf62Xsdk_c_mingw_include: http://cloud.riftek.com/index.php/s/NdZNQPgrfNtPBHy/download

.. _rf62Xsdk_c_dll_msvc_32_D: http://cloud.riftek.com/index.php/s/3iZNDkKRJAc3dKc/download
.. _rf62Xsdk_c_lib_msvc_32_D: http://cloud.riftek.com/index.php/s/owJAAAmJg5TBMD7/download
.. _rf62Xsdk_c_dll_msvc_32_R: http://cloud.riftek.com/index.php/s/CFE4kAyMxGCbLCK/download
.. _rf62Xsdk_c_lib_msvc_32_R: http://cloud.riftek.com/index.php/s/RN5rtxaC4P2Fgc9/download
.. _rf62Xsdk_c_dll_msvc_64_D: http://cloud.riftek.com/index.php/s/qSjfEx9PcSFSxsK/download
.. _rf62Xsdk_c_lib_msvc_64_D: http://cloud.riftek.com/index.php/s/dkPKD4yXSfKefJE/download
.. _rf62Xsdk_c_dll_msvc_64_R: http://cloud.riftek.com/index.php/s/Lg7Xon3eTNoB727/download
.. _rf62Xsdk_c_lib_msvc_64_R: http://cloud.riftek.com/index.php/s/PetSMf8MYrncybm/download
.. _rf62Xsdk_c_msvc_include: http://cloud.riftek.com/index.php/s/JxEaAxHkpe2b6yS/download

.. _rf62x_sdk_c_last_release:

.. table:: Последние выпуски:

   +---------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+----------------------------------------------+
   | Compiler      | 32bit(Debug)                                                                                | 32bit(Release)                                                                              | 64bit(Debug)                                                                                | 64bit(Release)                                                                              | Includes                                     |
   +===============+=============================================================================================+=============================================================================================+=============================================================================================+=============================================================================================+==============================================+
   | MinGW 7.3.0   | `rf62Xsdk.dll <rf62Xsdk_c_dll_mingw_32_D_>`_                                                | `rf62Xsdk.dll <rf62Xsdk_c_dll_mingw_32_R_>`_                                                | `rf62Xsdk.dll <rf62Xsdk_c_dll_mingw_64_D_>`_                                                | `rf62Xsdk.dll <rf62Xsdk_c_dll_mingw_64_R_>`_                                                | `includes <rf62Xsdk_c_mingw_include_>`_      |
   +---------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+----------------------------------------------+
   | MSVC 2017     | `rf62Xsdk.dll <rf62Xsdk_c_dll_msvc_32_D_>`_ `rf62Xsdk.lib <rf62Xsdk_c_lib_msvc_32_D_>`_     | `rf62Xsdk.dll <rf62Xsdk_c_dll_msvc_32_R_>`_ `rf62Xsdk.lib <rf62Xsdk_c_lib_msvc_32_R_>`_     | `rf62Xsdk.dll <rf62Xsdk_c_dll_msvc_64_D_>`_ `rf62Xsdk.lib <rf62Xsdk_c_lib_msvc_64_D_>`_     | `rf62Xsdk.dll <rf62Xsdk_c_dll_msvc_64_R_>`_ `rf62Xsdk.lib <rf62Xsdk_c_lib_msvc_64_R_>`_     | `includes <rf62Xsdk_c_msvc_include_>`_       |
   +---------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+----------------------------------------------+

.. _how_to_compile_rf62x_sdk_c:

Как скомпилировать
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Библиотека-«обёртка» rf62Xsdk может быть скомпилирован при помощи консоли или 
среды разработки (Visual Studio, Qt Creator)

Во-первых, вы должны загрузить проект (если не сделали этого ранее)

.. note::
   для получения дополнительной информации о шагах загрузки проекта см. :ref:`clone_rf62x_sdk`

.. _how_to_compile_rf62x_sdk_c_cmake:

CMake
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Находясь в папке с проектом, для построения библиотеки-«обёртки» (rf62Xsdk библиотеки) 
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd rf62Xwrappers/С/rf62Xsdk
   mkdir build
   cd build
   cmake ..
   cmake --build .

.. _how_to_compile_rf62x_sdk_c_qt_creator:

Qt Creator
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Для построения библиотеки-«обёртки» (rf62Xsdk библиотеки) с использованием IDE Qt Creator: 

-  Загрузите файл CMakeLists.txt из папки **rf62Xwrappers/С/rf62Xsdk** через 
   **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Откройте **Build Settings** и отметьте пункт **install** для **Build Steps**
-  Скомпилируйте проект

.. _how_to_compile_rf62x_sdk_c_vs:

Visual Studio
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Находясь в папке с проектом, для построения RF62X CORE (rf62Xcore библиотеки) 
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd rf62Xwrappers/С/rf62Xsdk
   mkdir build
   cd build
   cmake ..

-  Откройте полученное решение rf62Xsdk.sln в Visual Studio
-  Скомпилируйте проект

Как использовать
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Вы можете **создать свой проект**, включив в него статическую или динамическую библиотеку и 
необходимые заголовочные файлы, или вы можете **открыть и скомпилировать** один из 
приведенных ниже примеров использования из папки **examples/C/RF627\_old/**. 

.. note:: 
   Помимо приведенных ниже примеров, где каждый может быть скомпилирован и выполнен, 
   вы также можете прочитать документацию для «обёртки» на C++ (см. :ref:`rf62x_wrappers_description_c`), 
   где каждая функция содержит отдельный пример кода. 

.. _how_to_use_rf62x_sdk_c_for_search:

Поиск устройств RF62X
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример поиска сканеров серии RF627Old в сети 

.. code-block:: cpp

   #include <network.h>

   #include <stdio.h>
   #include <stdlib.h>

   #include <rf62Xcore.h>
   #include <rf62X_sdk.h>
   #include <rf62X_types.h>

   using namespace SDK::SCANNERS::RF62X;

   int main()
   {

      // Initialize sdk library
      core_init();

      // Print return rf627 sdk version
      printf("SDK version: %s\n", sdk_version());
      printf("=========================================\n");

      // Create value for scanners vector's type
      vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
      //Initialization vector
      vector_init(&scanners);

      //Iterate over all available network adapters in the current operating
      //system to send "Hello" requests.
      for (int i=0; i<GetAdaptersCount(); i++)
      {
         // get another IP Addr and set this changes in network adapter settings.
         uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
         uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
         // call the function to change adapter settings inside the library.
         set_platform_adapter_settings(host_mask, host_ip_addr);

         // Search for RF627-old devices over network by Service Protocol.
         search_scanners(scanners, kRF627_OLD, kSERVICE);
      }


      // Print count of discovered RF627Old in network by Service Protocol
      printf("Discovered: %d rf627-old\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         hello_information info = get_info_about_scanner(vector_get(scanners,i), kSERVICE);

         printf("\n\n\nID scanner's list: %d\n", i);
         printf("-----------------------------------------\n");
         printf("Device information: \n");
         printf("* Name\t: %s\n", info.rf627old.hello_info_service_protocol->device_name);
         printf("* Serial\t: %d\n", info.rf627old.hello_info_service_protocol->serial_number);
         printf("* IP Addr\t: %d.%d.%d.%d\n",
                info.rf627old.hello_info_service_protocol->ip_address[0],
                info.rf627old.hello_info_service_protocol->ip_address[1],
                info.rf627old.hello_info_service_protocol->ip_address[2],
                info.rf627old.hello_info_service_protocol->ip_address[3]);
         printf("* MAC Addr\t: %d:%d:%d:%d:%d:%d\n",
                info.rf627old.hello_info_service_protocol->mac_address[0],
                info.rf627old.hello_info_service_protocol->mac_address[1],
                info.rf627old.hello_info_service_protocol->mac_address[2],
                info.rf627old.hello_info_service_protocol->mac_address[3],
                info.rf627old.hello_info_service_protocol->mac_address[4],
                info.rf627old.hello_info_service_protocol->mac_address[5]);

         printf("\nWorking ranges: \n");
         printf("* Zsmr, mm\t: %d\n", info.rf627old.hello_info_service_protocol->z_begin);
         printf("* Zmr , mm\t: %d\n", info.rf627old.hello_info_service_protocol->z_range);
         printf("* Xsmr, mm\t: %d\n", info.rf627old.hello_info_service_protocol->x_begin);
         printf("* Xemr, mm\t: %d\n", info.rf627old.hello_info_service_protocol->x_end);

         printf("\nVersions: \n");
         printf("* Firmware\t: %d\n", info.rf627old.hello_info_service_protocol->firmware_version);
         printf("* Hardware\t: %d\n", info.rf627old.hello_info_service_protocol->hardware_version);
         printf("-----------------------------------------\n");
      }

      // Cleanup resources allocated with core_init()
      FreeAdapterAddresses();
      WinSockDeinit();
   }


Ниже приведён результат вывода приложения при успешном обнаружении сканера в сети:

.. code-block:: bash

   SDK version: 1.3.0
   =========================================
   Discovered: 1 RF627Old

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

-  Загрузите файл CMakeLists.txt из папки **examples/C/RF627\_old/RF627\_search** 
   через **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Запустите проект