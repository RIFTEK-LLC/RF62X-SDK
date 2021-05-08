
.. _how_to_use_rf62x_sdk_cpp:

*******************************************************************************
Примеры для C
*******************************************************************************

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

   int main()
   {

      // Initialize sdk library
      score_init();

      // Print return rf627 sdk version
      printf("SDK version: %s\n", sdk_version());
      printf("=========================================\n");

      // Create value for scanners vector's type
      vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
      // Initialization vector
      vector_init(&scanners);

      uint32_t host_ip_addr = ntohl(inet_addr("192.168.1.1"));
      uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));

      // call the function to change adapter settings inside the library.
      set_platform_adapter_settings(host_mask, host_ip_addr);

      // Search for RF627-old devices over network by Service Protocol.
      search_scanners(scanners, kRF627_OLD, kSERVICE);

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


