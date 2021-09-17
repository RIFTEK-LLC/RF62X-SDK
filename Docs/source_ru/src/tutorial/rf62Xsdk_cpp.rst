
.. _how_to_use_rf62x_sdk_cpp:

*******************************************************************************
Примеры для C++
*******************************************************************************

Поиск устройств RF62X
===============================================================================

Ниже приведен пример поиска сканеров серии RF627 v2.x.x:

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
      std::cout << "Was found\t: " << list.size()<< " RF627 v2.x.x"<< std::endl;
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

Ниже приведён результат вывода приложения при успешном обнаружении сканера в сети:

.. code-block:: txt

   #########################################
   #                                       #
   #         Search Example v2.x.x         #
   #                                       #
   #########################################

   SDK version: 2.19.0
   =========================================
   Search scanners from:
   * IP Address   : 192.168.2.100
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627-Smart
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627-Smart
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x
   =========================================


   ID scanner's list: 0
   -----------------------------------------
   Device information:
   * Name          : RF627 scanner
   * Serial        : 190068
   * IP Addr       : 192.168.1.30
   * MAC Addr      : 00:0A:35:6E:07:F5

   Working ranges:
   * Zsmr, mm      : 70
   * Zmr , mm      : 50
   * Xsmr, mm      : 30
   * Xemr, mm      : 42

   Versions:
   * Firmware      : 2.7.1
   * Hardware      : 18.6.20
   -----------------------------------------
   Press <RETURN> to close this window...

Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл `CMakeLists.txt` из папки **Examples/Cpp/RF627\_SMART/SEARCH\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект

Получение профиля сканера
===============================================================================

Ниже приведен пример получение профиля со сканера серии RF627 v2.x.x:

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
      std::cout << "#         Profile Example v2.x.x        #"  << std::endl;
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
      list = rf627smart::search();

      // Print count of discovered rf627smart in network by Service Protocol
      std::cout << "Was found\t: " << list.size()<< " RF627 v2.x.x"<< std::endl;
      std::cout << "========================================="     << std::endl;


      // Iterate over all discovered scanners in network, connect to each of them,
      // get a profile and print the main profile-info.
      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         std::shared_ptr<hello_info> info = scanner->get_info();

         // Print information about the scanner to which the profile belongs.
         std::cout << "\n\nID scanner's list: " << i              << std::endl;
         std::cout << "-----------------------------------------" << std::endl;
         std::cout << "Device information: "                      << std::endl;
         std::cout << "* Name  \t: "   << info->device_name()     << std::endl;
         std::cout << "* Serial\t: "   << info->serial_number()   << std::endl;
         std::cout << "* IP Addr\t: "  << info->ip_address()      << std::endl;

         // Establish connection to the RF627 device by Service Protocol.
         bool is_connected = scanner->connect();
         if (!is_connected)
            continue;

         // Get profile from scanner's data stream by Service Protocol.
         std::shared_ptr<profile2D> profile = nullptr;
         bool zero_points = true;
         bool realtime = true;

         if ((profile=scanner->get_profile2D(zero_points,realtime)))
         {
            std::cout << "Profile information: "                    <<std::endl;
            switch ((PROFILE_DATA_TYPES)profile->getHeader().data_type)
            {
            case PROFILE_DATA_TYPES::PIXELS:
               std::cout<<"* DataType\t: "<<"PIXELS"                <<std::endl;
               std::cout<<"* Count\t: "<<profile->getPixels().size()<<std::endl;
               break;
            case PROFILE_DATA_TYPES::PIXELS_INTRP:
               std::cout<<"* DataType\t: "<<"PIXELS_INTRP"          <<std::endl;
               std::cout<<"* Count\t: "<<profile->getPixels().size()<<std::endl;
               break;
            case PROFILE_DATA_TYPES::PROFILE:
               std::cout<<"* DataType\t: "<<"PROFILE"               <<std::endl;
               std::cout<<"* Size\t: "<<profile->getPoints().size() <<std::endl;
               break;
            case PROFILE_DATA_TYPES::PROFILE_INTRP:
               std::cout<<"* DataType\t: "<<"PROFILE_INTRP"         <<std::endl;
               std::cout<<"* Size\t: "<<profile->getPoints().size() <<std::endl;
               break;
            }
            std::cout << "Profile was successfully received!"       <<std::endl;
            std::cout << "-----------------------------------------"<<std::endl;
         }else
         {
            std::cout << "Profile was not received!"                <<std::endl;
            std::cout << "-----------------------------------------"<<std::endl;
         }

         // Disconnect from scanner.
         scanner->disconnect();
      }

      // Cleanup resources allocated with sdk_init()
      sdk_cleanup();
   }

Ниже приведён результат вывода приложения при успешном получении профиля:

.. code-block:: txt

   #########################################
   #                                       #
   #         Profile Example v2.x.x        #
   #                                       #
   #########################################

   SDK version: 2.19.0
   =========================================
   Search scanners from:
   * IP Address   : 192.168.2.100
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627-Smart
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627-Smart
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x
   =========================================


   ID scanner's list: 0
   -----------------------------------------
   Device information:
   * Name          : RF627 scanner
   * Serial        : 190068
   * IP Addr       : 192.168.1.30
   * MAC Addr      : 00:0A:35:6E:07:F5
   Profile information:
   * DataType      : PROFILE
   * Size          : 648
   Profile was successfully received!
   -----------------------------------------
   Press <RETURN> to close this window...

Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл `CMakeLists.txt` из папки **Examples/Cpp/RF627\_SMART/PROFILE\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект

Получение кадра матрицы
===============================================================================

Ниже приведен пример получение кадра матрицы со сканера серии RF627 v2.x.x:

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
      std::cout << "#          Frame Example v2.x.x         #"  << std::endl;
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
      list = rf627smart::search();

      // Print count of discovered rf627smart in network by Service Protocol
      std::cout << "Was found\t: " << list.size()<< " RF627 v2.x.x"<< std::endl;
      std::cout << "========================================="     << std::endl;


      // Iterate over all discovered scanners in network, connect to each of them,
      // get a profile and print the main profile-info.
      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         std::shared_ptr<hello_info> info = scanner->get_info();

         // Print information about the scanner to which the profile belongs.
         std::cout << "\n\nID scanner's list: " << i              << std::endl;
         std::cout << "-----------------------------------------" << std::endl;
         std::cout << "Device information: "                      << std::endl;
         std::cout << "* Name  \t: "   << info->device_name()     << std::endl;
         std::cout << "* Serial\t: "   << info->serial_number()   << std::endl;
         std::cout << "* IP Addr\t: "  << info->ip_address()      << std::endl;

         // Establish connection to the RF627 device by Service Protocol.
         bool is_connected = scanner->connect();
         if (!is_connected)
            continue;

         // Get profile from scanner's data stream by Service Protocol.
         std::shared_ptr<profile2D> profile = nullptr;
         bool zero_points = true;
         bool realtime = true;

         std::shared_ptr<frame> frame = nullptr;
         if ((frame = scanner->get_frame()))
         {
            std::cout << "Frame information: "                          << "\n";
            std::cout << "* Data Size\t: " << frame->getDataSize()      << "\n";
            std::cout << "* Frame Height\t: " << frame->getFrameHeight()<< "\n";
            std::cout << "* Frame Width\t: " << frame->getFrameWidth()  << "\n";
            std::cout << "Frame was successfully received!"             << "\n";
            std::cout << "-----------------------------------------"    << "\n";
         }else
         {
            std::cout << "Frame was not received!"                      << "\n";
            std::cout << "-----------------------------------------"    << "\n";
         }

         // Disconnect from scanner.
         scanner->disconnect();
      }

      // Cleanup resources allocated with sdk_init()
      sdk_cleanup();
   }

Ниже приведён результат вывода приложения при успешном получении кадра:

.. code-block:: txt

   #########################################
   #                                       #
   #          Frame Example v2.x.x         #
   #                                       #
   #########################################

   SDK version: 2.19.0
   =========================================
   Search scanners from:
   * IP Address   : 192.168.2.100
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627-Smart
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627-Smart
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x
   =========================================


   ID scanner's list: 0
   -----------------------------------------
   Device information:
   * Name          : RF627 scanner
   * Serial        : 190068
   * IP Addr       : 192.168.1.30
   * MAC Addr      : 00:0A:35:6E:07:F5
   Frame information:
   * Data Size     : 316224
   * Frame Height  : 488
   * Frame Width   : 648
   Frame was successfully received!
   -----------------------------------------
   Press <RETURN> to close this window...

Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл `CMakeLists.txt` из папки **Examples/Cpp/RF627\_SMART/FRAME\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект

Получение и установка параметров
===============================================================================

Ниже приведен пример получения и изменения имени сканера и смены состояния 
лазера (включение/выключение):

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
      std::cout << "#       Parameter Example v2.x.x        #"  << std::endl;
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
      list = rf627smart::search();

      // Print count of discovered rf627smart in network by Service Protocol
      std::cout << "Was found\t: " << list.size()<< " RF627 v2.x.x"<< std::endl;
      std::cout << "========================================="     << std::endl;


      // Iterate over all discovered scanners in network, connect to each of them,
      // get a profile and print the main profile-info.
      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         std::shared_ptr<hello_info> info = scanner->get_info();

         // Print information about the scanner to which the profile belongs.
         std::cout << "\n\nID scanner's list: " << i              << std::endl;
         std::cout << "-----------------------------------------" << std::endl;
         std::cout << "Device information: "                      << std::endl;
         std::cout << "* Name  \t: "   << info->device_name()     << std::endl;
         std::cout << "* Serial\t: "   << info->serial_number()   << std::endl;
         std::cout << "* IP Addr\t: "  << info->ip_address()      << std::endl;

         // Establish connection to the RF627 device by Service Protocol.
         bool is_connected = scanner->connect();
         if (!is_connected){
            std::cout << "Failed to connect to scanner!" << std::endl;
            continue;
         }

         // read params from RF627 device by Service Protocol.
         bool is_read = scanner->read_params();
         if (!is_read){
            std::cout << "Failed to read scanner parameters!" << std::endl;
            continue;
         }

         //
         // Example of working with the parameter type:
         // std::string
         //
         // Get parameter of Device Name
         auto name = scanner->get_param("user_general_deviceName");
         if (name != nullptr)
         {
            std::string str_name = name->getValue<std::string>();
            std::cout << "Current Device Name \t: " << str_name << std::endl;

            // Add "_TEST" to the ending of the current name
            str_name += "_TEST";
            scanner->set_param("user_general_deviceName", str_name);
            std::cout << "New Device Name \t: " << str_name     << std::endl;
            std::cout << "-------------------------------------"<< std::endl;
         }

         //
         // Example of working with the parameter type:
         // uint32_t
         //
         // Get parameter of Sensor Framerate
         auto fps = scanner->get_param("user_sensor_framerate");
         if (fps != nullptr)
         {
            uint32_t value = fps->getValue<uint32_t>();
            std::cout<<"Current FPS\t\t: "<< value << std::endl;

            // Change the framerate to 100
            scanner->set_param("user_sensor_framerate", 100);
            std::cout<<"New FPS  \t\t: " << 100 << std::endl;
            std::cout << "-------------------------------------"<< std::endl;
         }

         //
         // Example of working with the parameter type:
         // std::vector<uint32_t>
         //
         // Get parameter of Device IP Addr
         auto ip_addr = scanner->get_param("user_network_ip");
         if (ip_addr != nullptr)
         {
            std::vector<uint32_t> ip =ip_addr->getValue<std::vector<uint32_t>>();
            std::cout << "Current Device IP\t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<< "\n";

            // Change last digit of IP address (e.g. 192.168.1.30->192.168.1.31)
            //ip[3]++;
            scanner->set_param("user_network_ip", ip);
            std::cout << "New Device IP    \t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<< "\n";
            std::cout << "-------------------------------------"       << "\n";
         }

         //
         // Example of working with using an Enum:
         // uint32_t
         //
         // Get parameter of Sync Source
         auto syncSource = scanner->get_param("user_sensor_syncSource");
         if (syncSource != nullptr)
         {
            uint32_t value = syncSource->getValue<uint32_t>();
            auto syncEnum = syncSource->getEnum<uint32_t>();
            std::cout << "Current Sync Source\t: "
                      << syncEnum.findLabel(value)
                      << std::endl;

            // Change the current state to SYNC_EXTERNAL (or SYNC_INTERNAL)
            if(value == syncEnum.getValue("SYNC_INTERNAL"))
            {
               scanner->set_param_by_key(
                            "user_sensor_syncSource", "SYNC_EXTERNAL");
               std::cout << "New Sync Source  \t: "
                         << syncEnum.getLabel("SYNC_EXTERNAL")
                         << std::endl;
            }else
            {
               scanner->set_param_by_key(
                            "user_sensor_syncSource", "SYNC_INTERNAL");
               std::cout << "New Sync Source  \t: "
                         << syncEnum.getLabel("SYNC_INTERNAL")
                         << std::endl;
            }
            std::cout << "-------------------------------------"<< std::endl;
         }

         //
         // Example of working with using an Enum:
         // uint32_t
         //
         // Get parameter of Laser Enabled
         std::shared_ptr<param> laser = scanner->get_param("user_laser_enabled");
         if (laser != nullptr)
         {
            uint32_t isEnabled = laser->getValue<uint32_t>();
            auto laserEnum = laser->getEnum<uint32_t>();
            std::cout << "Current Laser State\t: "
                      << laserEnum.findLabel(isEnabled)
                      << std::endl;


            // Change the current state to the opposite
            if(isEnabled == laser->getEnum<uint32_t>().getValue("FALSE"))
            {
               scanner->set_param_by_key("user_laser_enabled", "TRUE");
               std::cout << "New Laser State  \t: "
                         << laserEnum.getLabel("TRUE")
                         << std::endl;
            }else
            {
               scanner->set_param_by_key("user_laser_enabled", "FALSE");
               std::cout << "New Laser State  \t: "
                         << laserEnum.getLabel("FALSE")
                         << std::endl;
            }
            std::cout << "-------------------------------------"<< std::endl;
         }


         // Apply changed parameters to the device
         std::string answer = "n";
         std::cout << "Apply changed params to the device? (y/n): ";
         std::cin >> answer;
         if (answer == "y" || answer == "Y")
         {
            scanner->write_params();
            // Save changes to the device's memory
            std::cout<<std::endl<<"Save changes to device's memory? (y/n): ";
            std::cin >> answer;
            if (answer == "y" || answer == "Y")
               scanner->save_params();
         }

         // Disconnect from scanner.
         scanner->disconnect();
      }

      // Cleanup resources allocated with sdk_init()
      sdk_cleanup();
   }

Ниже приведён результат вывода приложения при успешной установке новых параметров:

.. code-block:: txt

   #########################################
   #                                       #
   #       Parameter Example v2.x.x        #
   #                                       #
   #########################################

   SDK version: 2.19.0
   =========================================
   Search scanners from:
   * IP Address   : 192.168.2.100
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627-Smart
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627-Smart
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x
   =========================================


   ID scanner's list: 0
   -----------------------------------------
   Device information:
   * Name          : RF627 scanner
   * Serial        : 190068
   * IP Addr       : 192.168.1.30
   * MAC Addr      : 00:0A:35:6E:07:F5
   Current Device Name     : RF627 scanner
   New Device Name         : RF627 scanner_TEST
   -------------------------------------
   Current FPS             : 490
   New FPS                 : 100
   -------------------------------------
   Current Device IP       : 192.168.1.30.
   New Device IP           : 192.168.1.30.
   -------------------------------------
   Current Sync Source     : Internal
   New Sync Source         : External
   -------------------------------------
   Current Laser State     : true
   New Laser State         : false
   -------------------------------------
   Apply changed params to the device? (y/n): y
   Save changes to device's memory? (y/n): n
   -----------------------------------------
   Press <RETURN> to close this window...

Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл `CMakeLists.txt` из папки **Examples/Cpp/RF627\_SMART/PARAMETER\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект

Запись и скачивание дампа
===============================================================================

Ниже приведен пример записи дампа профилей и его скачивание:

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
      std::cout << "#          Dump Example v2.x.x          #"  << std::endl;
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
      list = rf627smart::search();

      // Print count of discovered rf627smart in network by Service Protocol
      std::cout << "Was found\t: " << list.size()<< " RF627 v2.x.x"<< std::endl;
      std::cout << "========================================="     << std::endl;


      // Iterate over all discovered scanners in network, connect to each of them,
      // get a profile and print the main profile-info.
      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         std::shared_ptr<hello_info> info = scanner->get_info();

         // Print information about the scanner to which the profile belongs.
         std::cout << "\n\nID scanner's list: " << i              << std::endl;
         std::cout << "-----------------------------------------" << std::endl;
         std::cout << "Device information: "                      << std::endl;
         std::cout << "* Name  \t: "   << info->device_name()     << std::endl;
         std::cout << "* Serial\t: "   << info->serial_number()   << std::endl;
         std::cout << "* IP Addr\t: "  << info->ip_address()      << std::endl;
         std::cout << "-----------------------------------------" << std::endl;

         // Establish connection to the RF627 device by Service Protocol.
         bool is_connected = scanner->connect();
         if (!is_connected){
            std::cout << "Failed to connect to scanner!" << std::endl;
            continue;
         }

         uint32_t count_of_profiles = 1000;
         scanner->start_dump_recording(count_of_profiles);

         std::cout << "Start dump recording..."                   << std::endl;
         std::cout << "-----------------------------------------" << std::endl;
         uint32_t size = 0;
         do {
            scanner->read_params();
            size = scanner->get_param("user_dump_size")->getValue<uint32_t>();
            std::cout << "Current profiles in the dump: "<< size << std::endl;
         }while(size < count_of_profiles);
         std::cout << "-----------------------------------------" << std::endl;

         std::cout << "Start dump downloading..."                 << std::endl;
         std::vector<std::shared_ptr<profile2D>> dump =
                  scanner->get_dumps_profiles(0, count_of_profiles);

         std::cout << dump.size() << " Profiles in dump were downloaded!\n";
         std::cout << "-----------------------------------------" << std::endl;

         // Disconnect from scanner.
         scanner->disconnect();
      }

      // Cleanup resources allocated with sdk_init()
      sdk_cleanup();
   }

Ниже приведён результат вывода приложения при успешной записи и скачивании дампа профилей:

.. code-block:: txt

   #########################################
   #                                       #
   #          Dump Example v2.x.x          #
   #                                       #
   #########################################

   SDK version: 2.19.0
   =========================================
   Search scanners from:
   * IP Address   : 192.168.2.100
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627-Smart
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627-Smart
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x
   =========================================


   ID scanner's list: 0
   -----------------------------------------
   Device information:
   * Name          : RF627 scanner
   * Serial        : 190068
   * IP Addr       : 192.168.1.30
   -----------------------------------------
   Start dump recording...
   -----------------------------------------
   Current profiles in the dump: 0
   Current profiles in the dump: 67
   Current profiles in the dump: 205
   Current profiles in the dump: 415
   Current profiles in the dump: 702
   Current profiles in the dump: 921
   Current profiles in the dump: 1000
   -----------------------------------------
   Start dump downloading...
   1000 Profiles were received!
   -----------------------------------------
   Press <RETURN> to close this window...

Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл `CMakeLists.txt` из папки **Examples/Cpp/RF627\_SMART/DUMP\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект