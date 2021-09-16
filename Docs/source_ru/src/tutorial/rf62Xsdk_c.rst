
.. _how_to_use_rf62x_sdk_cpp:

*******************************************************************************
Примеры для C
*******************************************************************************

Поиск устройств RF62X
===============================================================================

Ниже приведен пример поиска сканеров серии RF627 v2.x.x:

.. code-block:: c

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      printf("#########################################\n");
      printf("#                                       #\n");
      printf("#         Search Example v2.x.x         #\n");
      printf("#                                       #\n");
      printf("#########################################\n");

      // Initialize sdk library
      core_init();

      // Print return rf627 sdk version
      printf("SDK version: %s\n", sdk_version());
      printf("=========================================\n");


      // Create value for scanners vector's type
      vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
      // Initialization vector
      vector_init(&scanners);

      // Iterate over all available network adapters in the current operating
      // system to send "Hello" requests.
      uint32_t count = 0;
      for (int i=0; i<GetAdaptersCount(); i++)
      {
         uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
         uint32_t host_mask = ntohl(inet_addr(GetAdapterMasks(i)));
         // call the function to change adapter settings inside the library.
         set_platform_adapter_settings(host_mask, host_ip_addr);

         // Search for rf627old devices over network by Service Protocol.
         if (host_ip_addr != 0)
         {
            // Get another IP Addr and set this changes in adapter settings.
            printf("Search scanners from:\n "
                  "* IP Address\t: %s\n "
                  "* Netmask\t: %s\n",
                  GetAdapterAddress(i), GetAdapterMasks(i));
            search_scanners(scanners, kRF627_SMART, 300, kSERVICE);

            // Print count of discovered rf627old in network
            printf("Discovered\t: %d RF627\n",(int)vector_count(scanners)-count);
            printf("-----------------------------------------\n");
            count = (int)vector_count(scanners);
         }
      }

      // Print count of discovered rf627smart in network
      printf("Was found\t: %d RF627 v2.x.x", (int)vector_count(scanners));


      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         hello_information result =
                  get_info_about_scanner(vector_get(scanners,i), kSERVICE);

         rf627_smart_hello_info_by_service_protocol* info =
                  result.rf627smart.hello_info_service_protocol;

         printf("\n\nID scanner in list: %d\n", i);
         printf("-----------------------------------------\n");
         printf("Device information: \n");
         printf("* Name  \t: %s\n", info->user_general_deviceName);
         printf("* Serial\t: %d\n", info->fact_general_serial);
         printf("* IP Addr\t: %s\n", info->user_network_ip);
         printf("* MAC Addr\t: %s\n", info->fact_network_macAddr);

         printf("\nWorking ranges: \n");
         printf("* Zsmr, mm\t: %d\n", info->fact_general_smr);
         printf("* Zmr , mm\t: %d\n", info->fact_general_mr);
         printf("* Xsmr, mm\t: %d\n", info->fact_general_xsmr);
         printf("* Xemr, mm\t: %d\n", info->fact_general_xemr);

         printf("\nVersions: \n");
         printf("* Firmware\t: %d.%d.%d\n",
                info->fact_general_firmwareVer[0],
                info->fact_general_firmwareVer[1],
                info->fact_general_firmwareVer[2]);
         printf("* Hardware\t: %d\n", info->fact_general_hardwareVer);
         printf("-----------------------------------------\n");
      }

      core_cleanup();
   }


Ниже приведён результат вывода приложения при успешном обнаружении сканера в сети:

.. code-block:: txt

   #########################################
   #                                       #
   #         Search Example v2.x.x         #
   #                                       #
   #########################################
   SDK version: 2.17.2
   =========================================
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.2.104
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x

   ID scanner in list: 0
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
   * Hardware      : 302388224
   -----------------------------------------
   Press <RETURN> to close this window...


Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл `CMakeLists.txt` из папки **Examples/C/RF627\_SMART/SEARCH\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект


Получение профиля сканера
===============================================================================

Ниже приведен пример получение профиля со сканера серии RF627 v2.x.x:

.. code-block:: c

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      printf("#########################################\n");
      printf("#                                       #\n");
      printf("#        Profile Example v2.x.x         #\n");
      printf("#                                       #\n");
      printf("#########################################\n");

      // Initialize sdk library
      core_init();

      // Print return rf627 sdk version
      printf("SDK version: %s\n", sdk_version());
      printf("=========================================\n");


      // Create value for scanners vector's type
      vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
      // Initialization vector
      vector_init(&scanners);

      // Iterate over all available network adapters in the current operating
      // system to send "Hello" requests.
      uint32_t count = 0;
      for (int i=0; i<GetAdaptersCount(); i++)
      {
         uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
         uint32_t host_mask = ntohl(inet_addr(GetAdapterMasks(i)));
         // call the function to change adapter settings inside the library.
         set_platform_adapter_settings(host_mask, host_ip_addr);

         // Search for rf627old devices over network by Service Protocol.
         if (host_ip_addr != 0)
         {
            // Get another IP Addr and set this changes in adapter settings.
            printf("Search scanners from:\n "
                   "* IP Address\t: %s\n "
                   "* Netmask\t: %s\n",
                   GetAdapterAddress(i), GetAdapterMasks(i));
            search_scanners(scanners, kRF627_SMART, 300, kSERVICE);

            // Print count of discovered rf627old in network
            printf("Discovered\t: %d RF627\n",(int)vector_count(scanners)-count);
            printf("-----------------------------------------\n");
            count = (int)vector_count(scanners);
         }
      }

      // Print count of discovered rf627smart in network
      printf("Was found\t: %d RF627 v2.x.x", (int)vector_count(scanners));


      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);

         hello_information _info = get_info_about_scanner(scanner, kSERVICE);

         rf627_smart_hello_info_by_service_protocol* info =
                  _info.rf627smart.hello_info_service_protocol;

         printf("\n\nID scanner in list: %d\n", i);
         printf("-----------------------------------------\n");
         printf("Device information: \n");
         printf("* Name\t\t: %s\n", info->user_general_deviceName);
         printf("* Serial\t: %d\n", info->fact_general_serial);
         printf("* IP Addr\t: %s\n", info->user_network_ip);

         // Establish connection to the RF627 device
         uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);
         if (!is_connected)
            continue;

         // Read params from RF627 device
         uint8_t is_read = read_params_from_scanner(scanner, 3000, kSERVICE);
         if (!is_read)
            continue;

         uint8_t zero_points = TRUE;
         uint8_t realtime = TRUE;
         // Get profile from scanner's data stream by Service Protocol.
         rf627_profile2D_t* result = get_profile2D_from_scanner(
                     scanner, zero_points, realtime, kSERVICE);
         rf627_smart_profile2D_t* profile2D = result->rf627smart_profile2D;
         if (profile2D != NULL)
         {
            printf("Profile information: \n");
            switch (profile2D->header.data_type)
            {
            case (int)DTY_PixelsNormal:
            {
                printf("* DataType\t: PIXELS\n");
                uint32_t count = profile2D->pixels_format.pixels_count;
                printf("* Count\t\t: %d\n", count);
                break;
            }
            case (int)DTY_PixelsInterpolated:
            {
                printf("* DataType\t: PIXELS_INTRP\n");
                uint32_t count = profile2D->pixels_format.pixels_count;
                printf("* Count\t\t: %d\n", count);
                break;
            }
            case (int)DTY_ProfileNormal:
            {
                printf("* DataType\t: PROFILE\n");
                uint32_t count = profile2D->profile_format.points_count;
                printf("* Count\t\t: %d\n", count);
                break;
            }
            case (int)DTY_ProfileInterpolated:
            {
                printf("* DataType\t: PROFILE_INTRP\n");
                uint32_t count = profile2D->profile_format.points_count;
                printf("* Count\t\t: %d\n", count);
                break;
            }
            }
            printf("Profile was successfully received!\n");
            printf("-----------------------------------------\n");
            free_profile2D(result);
         }else
         {
            printf("Profile was not received!\n");
            printf("-----------------------------------------\n");
         }

         disconnect_from_scanner(scanner, kSERVICE);
      }

      // Cleanup resources allocated with core_init()
      core_cleanup();
   }

Ниже приведён результат вывода приложения при успешном получении профиля:

.. code-block:: txt

   #########################################
   #                                       #
   #        Profile Example v2.x.x         #
   #                                       #
   #########################################
   SDK version: 2.17.2
   =========================================
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.2.104
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x

   ID scanner in list: 0
   -----------------------------------------
   Device information:
   * Name          : RF627 scanner
   * Serial        : 190068
   * IP Addr       : 192.168.1.30
   Profile information:
   * DataType      : PROFILE
   * Count         : 648
   Profile was successfully received!
   -----------------------------------------
   Press <RETURN> to close this window...


Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл `CMakeLists.txt` из папки **Examples/C/RF627\_SMART/PROFILE\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект


Получение кадра матрицы
===============================================================================

Ниже приведен пример получение кадра матрицы со сканера серии RF627 v2.x.x:

.. code-block:: c

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      printf("#########################################\n");
      printf("#                                       #\n");
      printf("#         Frame Example v2.x.x          #\n");
      printf("#                                       #\n");
      printf("#########################################\n");

      // Initialize sdk library
      core_init();

      // Print return rf627 sdk version
      printf("SDK version: %s\n", sdk_version());
      printf("=========================================\n");


      // Create value for scanners vector's type
      vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
      // Initialization vector
      vector_init(&scanners);

      // Iterate over all available network adapters in the current operating
      // system to send "Hello" requests.
      uint32_t count = 0;
      for (int i=0; i<GetAdaptersCount(); i++)
      {
         uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
         uint32_t host_mask = ntohl(inet_addr(GetAdapterMasks(i)));
         // call the function to change adapter settings inside the library.
         set_platform_adapter_settings(host_mask, host_ip_addr);

         // Search for rf627old devices over network by Service Protocol.
         if (host_ip_addr != 0)
         {
            // Get another IP Addr and set this changes in adapter settings.
            printf("Search scanners from:\n "
                   "* IP Address\t: %s\n "
                   "* Netmask\t: %s\n",
                   GetAdapterAddress(i), GetAdapterMasks(i));
            search_scanners(scanners, kRF627_SMART, 300, kSERVICE);

            // Print count of discovered rf627old in network
            printf("Discovered\t: %d RF627\n",(int)vector_count(scanners)-count);
            printf("-----------------------------------------\n");
            count = (int)vector_count(scanners);
         }
      }

      // Print count of discovered rf627smart in network
      printf("Was found\t: %d RF627 v2.x.x", (int)vector_count(scanners));


      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);

         hello_information _info = get_info_about_scanner(scanner, kSERVICE);

         rf627_smart_hello_info_by_service_protocol* info =
                  _info.rf627smart.hello_info_service_protocol;

         printf("\n\nID scanner in list: %d\n", i);
         printf("-----------------------------------------\n");
         printf("Device information: \n");
         printf("* Name\t\t: %s\n", info->user_general_deviceName);
         printf("* Serial\t: %d\n", info->fact_general_serial);
         printf("* IP Addr\t: %s\n", info->user_network_ip);

         // Establish connection to the RF627 device
         uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);
         if (!is_connected)
            continue;

         // Read params from RF627 device
         uint8_t is_read = read_params_from_scanner(scanner, 3000, kSERVICE);
         if (!is_read)
            continue;

         rf627_frame_t* _frame = get_frame_from_scanner(scanner, kSERVICE);
         if (_frame != NULL && _frame->rf627smart_frame != NULL)
         {
            uint32_t data_size = _frame->rf627smart_frame->data_size;
            uint32_t frame_width = _frame->rf627smart_frame->fact_sensor_width;
            uint32_t frame_height = _frame->rf627smart_frame->fact_sensor_height;

            printf("Frame information: \n");
            printf("* Data Size\t: %d\n", data_size);
            printf("* Frame Width\t: %d\n", frame_width);
            printf("* Frame Height\t: %d\n", frame_height);
            printf("Frame was successfully received!\n");
            printf("-----------------------------------------\n");

            free_frame(_frame);
         }

         disconnect_from_scanner(scanner, kSERVICE);
      }

      // Cleanup resources allocated with core_init()
      core_cleanup();
   }

Ниже приведён результат вывода приложения при успешном получении кадра:

.. code-block:: txt

   #########################################
   #                                       #
   #         Frame Example v2.x.x          #
   #                                       #
   #########################################
   SDK version: 2.17.2
   =========================================
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.2.104
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x

   ID scanner in list: 0
   -----------------------------------------
   Device information:
   * Name          : RF627 scanner
   * Serial        : 190068
   * IP Addr       : 192.168.1.30
   Frame information:
   * Data Size     : 316224
   * Frame Width   : 648
   * Frame Height  : 488
   Frame was successfully received!
   -----------------------------------------
   Press <RETURN> to close this window...


Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл `CMakeLists.txt` из папки **Examples/C/RF627\_SMART/FRAME\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект

Получение и установка параметров
===============================================================================

Ниже приведен пример получения и изменения имени сканера и смены состояния 
лазера (включение/выключение):

.. code-block:: c

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      printf("#########################################\n");
      printf("#                                       #\n");
      printf("#       Parameter Example v2.x.x        #\n");
      printf("#                                       #\n");
      printf("#########################################\n");

      // Initialize sdk library
      core_init();

      // Print return rf627 sdk version
      printf("SDK version: %s\n", sdk_version());
      printf("=========================================\n");


      // Create value for scanners vector's type
      vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
      // Initialization vector
      vector_init(&scanners);

      // Iterate over all available network adapters in the current operating
      // system to send "Hello" requests.
      uint32_t count = 0;
      for (int i=0; i<GetAdaptersCount(); i++)
      {
         uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
         uint32_t host_mask = ntohl(inet_addr(GetAdapterMasks(i)));
         // call the function to change adapter settings inside the library.
         set_platform_adapter_settings(host_mask, host_ip_addr);

         // Search for rf627old devices over network by Service Protocol.
         if (host_ip_addr != 0)
         {
            // Get another IP Addr and set this changes in adapter settings.
            printf("Search scanners from:\n "
                   "* IP Address\t: %s\n "
                   "* Netmask\t: %s\n",
                   GetAdapterAddress(i), GetAdapterMasks(i));
            search_scanners(scanners, kRF627_SMART, 300, kSERVICE);

            // Print count of discovered rf627old in network
            printf("Discovered\t: %d RF627\n",(int)vector_count(scanners)-count);
            printf("-----------------------------------------\n");
            count = (int)vector_count(scanners);
         }
      }

      // Print count of discovered rf627smart in network
      printf("Was found\t: %d RF627 v2.x.x", (int)vector_count(scanners));


      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         printf("\n\nID scanner in list: %d\n", i);
         printf("-----------------------------------------\n");

         // Establish connection to the RF627 device
         uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);
         if (!is_connected)
            continue;

         // Read params from RF627 device
         uint8_t is_read = read_params_from_scanner(scanner, 3000, kSERVICE);
         if (!is_read)
            continue;

         //
         // Example of working with the parameter type:
         // string
         //
         // Get/Set parameter of Device Name
         parameter_t* name = get_parameter(scanner,"user_general_deviceName");
         if (name != NULL)
         {
            char* value = name->val_str->value;
            printf("Current Device Name\t: %s\n", value);
            char* new_value = "TEST NAME";
            printf("New Device Name\t\t: %s\n", new_value);

            parameter_t* temp = create_parameter_from_type(name->base.type);

            uint32_t name_size = strlen(name->base.name) + 1;
            temp->base.name = platform_calloc(name_size, sizeof (char));
            platform_memcpy(temp->base.name, name->base.name, name_size);

            uint32_t value_size = strlen(new_value) + 1;
            temp->val_str->value = platform_calloc(value_size, sizeof (char));
            platform_memcpy(temp->val_str->value, new_value, value_size);
            temp->base.size = value_size;
            printf("-------------------------------------\n");

            set_parameter(scanner, temp);
            free_parameter(temp, scanner->type);
         }


         //
         // Example of working with the parameter type:
         // uint32_t
         //
         // Get/Set parameter of Laser Enabled
         parameter_t* laser = get_parameter(scanner, "user_laser_enabled");
         if (laser != NULL && strcmp(
                     laser->base.type, "uint32_t")== 0)
         {
            uint32_t isEnabled = laser->val_uint32->value;
            printf("Current Laser State\t: %s\n", (isEnabled?"ON":"OFF"));

            // Change the current state to the opposite
            isEnabled = !isEnabled;
            laser->val_uint32->value = isEnabled;
            printf("New Laser State\t\t: %s\n", (isEnabled?"ON":"OFF"));
            printf("-------------------------------------\n");

            set_parameter(scanner, laser);
         }

         // Apply changed parameters to the device
         char answer = 'n';
         printf("Apply changed params to the device? (y/n): ");
         scanf("%c", &answer);
         if (answer == 'y' || answer == 'Y')
         {
            write_params_to_scanner(scanner, 3000, kSERVICE);
            // Save changes to the device's memory
            printf("\nSave changes to device's memory? (y/n): ");
            scanf("%c", &answer);
            if (answer == 'y' || answer == 'Y')
                  save_params_to_scanner(scanner, 3000, kSERVICE);
         }
      }

      // Cleanup resources allocated with core_init()
      core_cleanup();
   }

Ниже приведён результат вывода приложения при успешной установке новых параметров:

.. code-block:: txt

   #########################################
   #                                       #
   #       Parameter Example v2.x.x        #
   #                                       #
   #########################################
   SDK version: 2.17.2
   =========================================
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.2.104
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x

   ID scanner's list: 0
   -----------------------------------------
   Current Device Name     : RF627 scanner
   New Device Name         : TEST NAME
   -----------------------------------------
   Current Laser State     : ON
   New Laser State         : OFF
   -----------------------------------------
   Apply changed params to the device? (y/n): y
   Save changes to device's memory? (y/n): n

   Press <RETURN> to close this window...


Вы можете открыть и скомпилировать этот пример с помощью **Qt Creator**:

-  Загрузите файл `CMakeLists.txt` из папки **Examples/C/RF627\_SMART/PARAMETER\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект


Запись и скачивание дампа
===============================================================================

Ниже приведен пример записи дампа профилей и его скачивание:

.. code-block:: c

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      printf("#########################################\n");
      printf("#                                       #\n");
      printf("#          Dump Example v2.x.x          #\n");
      printf("#                                       #\n");
      printf("#########################################\n");

      // Initialize sdk library
      core_init();

      // Print return rf627 sdk version
      printf("SDK version: %s\n", sdk_version());
      printf("=========================================\n");


      // Create value for scanners vector's type
      vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
      // Initialization vector
      vector_init(&scanners);

      // Iterate over all available network adapters in the current operating
      // system to send "Hello" requests.
      uint32_t count = 0;
      for (int i=0; i<GetAdaptersCount(); i++)
      {
         uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
         uint32_t host_mask = ntohl(inet_addr(GetAdapterMasks(i)));
         // call the function to change adapter settings inside the library.
         set_platform_adapter_settings(host_mask, host_ip_addr);

         // Search for rf627old devices over network by Service Protocol.
         if (host_ip_addr != 0)
         {
            // Get another IP Addr and set this changes in adapter settings.
            printf("Search scanners from:\n "
                   "* IP Address\t: %s\n "
                   "* Netmask\t: %s\n",
                   GetAdapterAddress(i), GetAdapterMasks(i));
            search_scanners(scanners, kRF627_SMART, 300, kSERVICE);

            // Print count of discovered rf627old in network
            printf("Discovered\t: %d RF627\n",(int)vector_count(scanners)-count);
            printf("-----------------------------------------\n");
            count = (int)vector_count(scanners);
         }
      }

      // Print count of discovered rf627smart in network
      printf("Was found\t: %d RF627 v2.x.x", (int)vector_count(scanners));


      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         printf("\n\nID scanner in list: %d\n", i);
         printf("-----------------------------------------\n");

         // Establish connection to the RF627 device
         uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);
         if (!is_connected)
            continue;

         // Read params from RF627 device
         uint8_t is_read = read_params_from_scanner(scanner, 3000, kSERVICE);
         if (!is_read)
            continue;

         uint8_t status = FALSE;
         rf627_profile2D_t** dumps = NULL;
         uint32_t profiles_in_dump = 0;

         uint32_t count_of_profiles = 1000;
         // Get parameter of user_dump_capacity
         parameter_t* capacity = get_parameter(scanner,"user_dump_capacity");
         if (capacity != NULL)
         {
            capacity->val_uint32->value = count_of_profiles;
            set_parameter(scanner, capacity);
            write_params_to_scanner(scanner, 300, kSERVICE);
         }

         // Get parameter of user_dump_enabled
         parameter_t* enabled  = get_parameter(scanner,"user_dump_enabled");
         if (enabled != NULL && strcmp(enabled->base.type,"uint32_t")== 0)
         {
            enabled->val_uint32->value = TRUE;
            set_parameter(scanner, enabled);
            write_params_to_scanner(scanner, 300, kSERVICE);
         }

         printf("Start dump recording...\n");
         printf("-----------------------------------------\n");
         uint32_t size = 0;
         // wait dump recording
         do {
            read_params_from_scanner(scanner, 300, kSERVICE);
            size = get_parameter(scanner,"user_dump_size")->val_uint32->value;
            printf("Current profiles in the dump: %d\n", size);
         }while(size < count_of_profiles);
         printf("-----------------------------------------\n");
         
         printf("Start dump downloading...\n");
         // Get parameter of user_dump_enabled
         parameter_t* unit_size =get_parameter(scanner,"fact_dump_unitSize");
         if (unit_size != NULL && strcmp(unit_size->base.type,"uint32_t")== 0)
         {
            dumps = calloc(count_of_profiles, sizeof (rf627_profile2D_t*));
            uint32_t start_index = 0;
            status = get_dumps_profiles_from_scanner(
                        scanner, start_index, count_of_profiles,
                        10000, kSERVICE,
                        dumps, &profiles_in_dump,
                        unit_size->val_uint32->value);
         }

         if (status) {
            printf("%d Profiles in dump were downloaded!\n", profiles_in_dump);
            printf("-----------------------------------------\n");
         }else {
            printf("Dump was not received!\n");
            printf("-----------------------------------------\n");
         }

         for(uint32_t i = 0; i < profiles_in_dump; i++)
            free_profile2D(dumps[i]);
         free(dumps);
      }

      // Cleanup resources allocated with core_init()
      core_cleanup();
   }

Ниже приведён результат вывода приложения при успешной записи и скачивании дампа профилей:

.. code-block:: txt

   #########################################
   #                                       #
   #       Parameter Example v2.x.x        #
   #                                       #
   #########################################
   SDK version: 2.17.2
   =========================================
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.2.104
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x

   ID scanner's list: 0
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

-  Загрузите файл `CMakeLists.txt` из папки **Examples/C/RF627\_SMART/DUMP\_EXAMPLE** 
   через **File > Open File or Project** (укажите файл `CMakeLists.txt`)
-  Выберите компилятор (*MinGW, MSVC, Clang*) и нажмите **Configure Project** 
-  Запустите проект