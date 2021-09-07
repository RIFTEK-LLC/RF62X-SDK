

.. _rf62x_wrappers_description_c_rf627old:

*******************************************************************************
Интерфейс работы с rf627old
*******************************************************************************

Файлы ``rf62X_sdk.h``, ``rf62X_types.h`` и ``rf62Xcore.h`` предоставляют весь 
необходимый интерфейс для работы со сканерами серии RF627Old

search_scanners()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для поиска устройств RF627 доступных в сети

.. doxygenfunction::  search_scanners(vector_t *, scanner_types_t, protocol_types_t)

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 20

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


get_info_about_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения информации о сканере из пакета приветствия (Hello-пакет)

.. doxygenfunction:: get_info_about_scanner(scanner_base_t *, protocol_types_t)

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 27-56

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

   

connect_to_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для установки соединения со сканером серии RF627

.. doxygenfunction:: connect_to_scanner(scanner_base_t *, protocol_types_t)


disconnect_from_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для закрытия ранее установленного соединения со сканером серии RF627

.. doxygenfunction:: disconnect_from_scanner(scanner_base_t *, protocol_types_t)

   
get_profile2D_from_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения профиля со сканеров серии RF627

.. doxygenfunction:: get_profile2D_from_scanner(scanner_base_t *, rfBool, protocol_types_t)


.. _rf62x_wrappers_c_description_rf627old_read_params:

read_params_from_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения текущих параметров сканера. При вызове данной функции SDK вычитывает 
со сканера все актуальные параметры, сохраняя их ввиде «списка параметров» для дальнейшей 
работы.

.. doxygenfunction:: read_params_from_scanner(scanner_base_t *, protocol_types_t)

get_parameter()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения конкретного параметра по его имени (ключу). При вызове 
данной функции SDK осуществляет поиск нужного параметра из последних прочитанных 
при вызове функции :ref:`read_params_from_scanner`. В случае, если запрашиваемый 
параметр отсутствует в конкретном сканере, функция вернёт null.

.. doxygenfunction:: get_parameter(scanner_base_t *, const rfChar *)


set_parameter()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция установки конкретного параметра. При вызове данной функции происходит установка 
передаваемого параметра в локальном списке параметров в SDK. Для отправки изменений 
в сканер необходимо вызвать функцию ``write_params``.

.. doxygenfunction:: set_parameter(scanner_base_t *, parameter_t *)


write_params_to_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция записи локальных параметров из SDK в сканер. При вызове данной функции 
происходит отправка списка локальных параметров из SDK в сканер.

.. doxygenfunction:: write_params_to_scanner(scanner_base_t *, protocol_types_t)