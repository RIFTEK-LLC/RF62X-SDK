
.. _rf62x_core_description:

*******************************************************************************
API «ядра» на C
*******************************************************************************

**RF62X-CORE** - основная библиотека («Ядро») с базовым набором функций и типов  
для работы с лазерными сканерами серии RF62X. Библиотека написана на языке 
программирования CИ в соответствии со стандартом C99 (ISO / IEC 9899: 1999) и 
является кросс-платформенной. Для использования данной библиотеки необходима 
реализация платформозависимых функций (работа с памятью, работа с сетью, функции 
ввода/вывода). 

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

Инициализация «ядра»
===============================================================================
При желании использовать библиотеку RF62X-CORE вместо предоставляемых библиотек-«обёрток» 
разработчику необходимо самостоятельно реализовать платформозависимую часть «ядра» 
(см. :ref:`компиляция и запуск «ядра» <compilation_rf62x_core>`).

Файл ``rf62X_core.h`` является заголовочным файлом с описанием функций для запуска «ядра».
Этот файл содержит определения основных функций, используемых при его инициализации:

init_platform_dependent_methods()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция инициализация платформозависимой части «ядра»

.. doxygenfunction:: init_platform_dependent_methods

core_version()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения текущей версии «ядра»:

.. doxygenfunction:: core_version

Обзор программного интерфейса 
===============================================================================

Файл ``rf62X_sdk.h`` является основным файлом программного интерфейса (API) «ядра» 
и определяет его функциональность. 
``rf62X_sdk.h`` содержит следующий набор базовых функций для разработки:

set_platform_adapter_settings()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для передачи текущих настроек адаптера в ядро. Данная функция используется 
в том случае, если произошли какие-либо изменения настроек в используемом ядром сетевом адаптаре.

.. doxygenfunction:: set_platform_adapter_settings

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 19

   // Create value for scanners vector's type
   vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
   
   //Initialization vector
   vector_init(&scanners);

   
   // Iterate over all available network adapters in the current operating
   // system to send "Hello" requests.
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

search_scanners()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для поиска устройств RF62X по сети

.. doxygenfunction:: search_scanners

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 13

   // Create value for scanners vector's type
   vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));   
   //Initialization vector
   vector_init(&scanners);

   // set IP Addr and NetMask for setting in network adapter settings.
   uint32_t host_ip_addr = ntohl(inet_addr("192.168.1.2"));
   uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
   // call the function to change adapter settings inside the library.
   set_platform_adapter_settings(host_mask, host_ip_addr);

   // Search for RF627-old devices over network by Service Protocol.
   search_scanners(scanners, kRF627_OLD, kSERVICE);
   

get_info_about_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения информации о сканере из пакета приветствия (Hello-пакет)

.. doxygenfunction:: get_info_about_scanner

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 17-18

   // Create value for scanners vector's type
   vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));   
   //Initialization vector
   vector_init(&scanners);

   // set IP Addr and NetMask for setting in network adapter settings.
   uint32_t host_ip_addr = ntohl(inet_addr("192.168.1.2"));
   uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
   // call the function to change adapter settings inside the library.
   set_platform_adapter_settings(host_mask, host_ip_addr);

   // Search for RF627-old devices over network by Service Protocol.
   search_scanners(scanners, kRF627_OLD, kSERVICE);

   // Iterate over all discovered rf627-old in network and get info.
   for(size_t i = 0; i < vector_count(scanners); i++)
      hello_information info = get_info_about_scanner(
                                    (scanner_base_t*)vector_get(scanners,i), kSERVICE);

connect_to_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для установки соединения со сканером серии RF62X

.. doxygenfunction:: connect_to_scanner

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 17

   // Create value for scanners vector's type
   vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));   
   //Initialization vector
   vector_init(&scanners);

   // set IP Addr and NetMask for setting in network adapter settings.
   uint32_t host_ip_addr = ntohl(inet_addr("192.168.1.2"));
   uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
   // call the function to change adapter settings inside the library.
   set_platform_adapter_settings(host_mask, host_ip_addr);

   // Search for RF627-old devices over network by Service Protocol.
   search_scanners(scanners, kRF627_OLD, kSERVICE);

   // Iterate over all discovered rf627-old in network and Establish connection.
   for(size_t i = 0; i < vector_count(scanners); i++)
      connect_to_scanner((scanner_base_t*)vector_get(scanners,i), kSERVICE);


disconnect_from_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для закрытия ранее установленного соединения со сканером серии RF62X

.. doxygenfunction:: disconnect_from_scanner

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 21

   // Create value for scanners vector's type
   vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));   
   //Initialization vector
   vector_init(&scanners);

   // set IP Addr and NetMask for setting in network adapter settings.
   uint32_t host_ip_addr = ntohl(inet_addr("192.168.1.2"));
   uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
   // call the function to change adapter settings inside the library.
   set_platform_adapter_settings(host_mask, host_ip_addr);

   // Search for RF627-old devices over network by Service Protocol.
   search_scanners(scanners, kRF627_OLD, kSERVICE);

   // Iterate over all discovered rf627-old in network and Establish connection.
   for(size_t i = 0; i < vector_count(scanners); i++)
      connect_to_scanner((scanner_base_t*)vector_get(scanners,i), kSERVICE);

   // Iterate over all discovered rf627-old in network for Disabling connection.
   for(size_t i = 0; i < vector_count(scanners); i++)
      disconnect_from_scanner((scanner_base_t*)vector_get(scanners,i), kSERVICE);


get_profile2D_from_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения профиля со сканеров серии RF62X

.. doxygenfunction:: get_profile2D_from_scanner

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 24, 33-36

   // Create value for scanners vector's type
   vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));   
   //Initialization vector
   vector_init(&scanners);

   // set IP Addr and NetMask for setting in network adapter settings.
   uint32_t host_ip_addr = ntohl(inet_addr("192.168.1.2"));
   uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
   // call the function to change adapter settings inside the library.
   set_platform_adapter_settings(host_mask, host_ip_addr);

   // Search for RF627-old devices over network by Service Protocol.
   search_scanners(scanners, kRF627_OLD, kSERVICE);

   // Iterate over all discovered rf627-old in network and Establish connection.
   for(size_t i = 0; i < vector_count(scanners); i++)
   {
      scanner_base_t* scanner = vector_get(scanners,i);
      connect_to_scanner(scanner, kSERVICE);

      // Flag for included zero points in return profile2D
      bool zero_points = true;
      // Get profile from scanner's data stream by Service Protocol.
      rf627_profile2D_t* profile = get_profile2D_from_scanner(scanner, zero_points, kSERVICE);

      {
         // some actions with profile
      }

      disconnect_from_scanner(scanner, kSERVICE);

      // Freeing memory after using profile structure
      free(profile->rf627_profile2D->intensity);
      free(profile->rf627_profile2D->pixels_format.pixels);
      free(profile->rf627_profile2D);
      free(profile);
   }

.. _rf62x_core_description_read_params_from_scanner:

read_params_from_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения текущих параметров сканера. При вызове данной функции «ядро» вычитывает 
со сканера все актуальные параметры, сохраняя их ввиде «списка параметров» для дальнейшей 
работы.

.. doxygenfunction:: read_params_from_scanner

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 22

   // Create value for scanners vector's type
   vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));   
   //Initialization vector
   vector_init(&scanners);

   // set IP Addr and NetMask for setting in network adapter settings.
   uint32_t host_ip_addr = ntohl(inet_addr("192.168.1.2"));
   uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
   // call the function to change adapter settings inside the library.
   set_platform_adapter_settings(host_mask, host_ip_addr);

   // Search for RF627-old devices over network by Service Protocol.
   search_scanners(scanners, kRF627_OLD, kSERVICE);

   // Iterate over all discovered rf627-old in network and Establish connection.
   for(size_t i = 0; i < vector_count(scanners); i++)
   {
      scanner_base_t* scanner = vector_get(scanners,i);
      connect_to_scanner(scanner, kSERVICE);

      // Read parameters from device to the internal structure of the core
      read_params_from_scanner(scanner, kSERVICE);

      {
         // some actions with params
      }

      disconnect_from_scanner(scanner, kSERVICE);
   }

get_parameter()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения конкретного параметра по его имени (ключу). При вызове 
данной функции «ядро» осуществляет поиск нужного параметра из последних прочитанных 
при вызове функции :ref:`read_params_from_scanner`. В случае, если запрашиваемый 
параметр отсутствует в конкретном сканере, функция вернёт null.

.. doxygenfunction:: get_parameter

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 25-30

   // Create value for scanners vector's type
   vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));   
   //Initialization vector
   vector_init(&scanners);

   // set IP Addr and NetMask for setting in network adapter settings.
   uint32_t host_ip_addr = ntohl(inet_addr("192.168.1.2"));
   uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
   // call the function to change adapter settings inside the library.
   set_platform_adapter_settings(host_mask, host_ip_addr);

   // Search for RF627-old devices over network by Service Protocol.
   search_scanners(scanners, kRF627_OLD, kSERVICE);

   // Iterate over all discovered rf627-old in network and Establish connection.
   for(size_t i = 0; i < vector_count(scanners); i++)
   {
      scanner_base_t* scanner = vector_get(scanners,i);
      connect_to_scanner(scanner, kSERVICE);

      // Read parameters from device to the internal structure of the core
      read_params_from_scanner(scanner, kSERVICE);

      // Get parameter of Device Name
      parameter_t* name = get_parameter(scanner, "user_general_deviceName");
      if ((name != NULL) && (strcmp(name->type, "string_t")==0)
      {
         char* str_name = name->val_str->value;
         printf("Current Device Name: %s\n", str_name);
      }
      
      disconnect_from_scanner(scanner, kSERVICE);
   }

Для более удобной работы с параметрами можно использовать соответствующие «ключи» 
(ключ имени параметра, тип параметра и доступ к параметру). Для этого в файле 
``rt62X_types.h`` находятся следующие ``enum``:

.. doxygenenum:: paramValueType_t

.. doxygenenum:: paramAccessType_t

.. doxygenenum:: parameter_name_keys_t

Пример использования с ключами:

.. code-block:: cpp
   :emphasize-lines: 25-30

   {
   ...Search devices
   ...Establish connections
   ...Read parameters
   }

   // Get parameter of Device Name
   parameter_t* name = get_parameter(scanner, parameter_names_array[USER_GENERAL_DEVICENAME]);
   if ((name != NULL) && (strcmp(name->type, parameter_value_types[PVT_STRING])==0)
   {
      char* str_name = name->val_str->value;
      printf("Current Device Name: %s\n", str_name);
   }

Для более детального описания каждого параметра и его свойств см. :ref:`rf62x_more_description_params`

set_parameter()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция установки конкретного параметра. При вызове данной функции происходит установка 
передаваемого параметра в локальном списке параметров в «ядре». Для отправки изменений 
в сканер необходимо вызвать функцию ``write_params_to_scanner``.

.. doxygenfunction:: set_parameter

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 31-33, 37

   // Create value for scanners vector's type
   vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));   
   //Initialization vector
   vector_init(&scanners);

   // set IP Addr and NetMask for setting in network adapter settings.
   uint32_t host_ip_addr = ntohl(inet_addr("192.168.1.2"));
   uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
   // call the function to change adapter settings inside the library.
   set_platform_adapter_settings(host_mask, host_ip_addr);

   // Search for RF627-old devices over network by Service Protocol.
   search_scanners(scanners, kRF627_OLD, kSERVICE);

   // Iterate over all discovered rf627-old in network and Establish connection.
   for(size_t i = 0; i < vector_count(scanners); i++)
   {
      scanner_base_t* scanner = vector_get(scanners,i);
      connect_to_scanner(scanner, kSERVICE);

      // Read parameters from device to the internal structure of the core
      read_params_from_scanner(scanner, kSERVICE);

      // Get parameter of Device Name
      parameter_t* name = get_parameter(scanner, "user_general_deviceName");
      if ((name != NULL) && (strcmp(name->type, "string_t")==0)
      {
         char* str_name = name->val_str->value;
         printf("Current Device Name: %s\n", str_name);

         char* new_name = "NEW NAME";
         memcpy(name->val_str->value, new_name, strlen(new_name)+1);
         set_parameter(scanner, name);
      }
      
      //  Write changes parameters to the device's memory
      write_params_to_scanner(scanner, kSERVICE);

      disconnect_from_scanner(scanner, kSERVICE);
   }


write_params_to_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция записи локальных параметров из «ядра» в сканер. При вызове данной функции 
происходит отправка списка локальных параметров из «ядра» в сканер.

.. doxygenfunction:: write_params_to_scanner

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 26

   {
   ...Search devices
   ...Establish connections
   ...Read parameters
   }

   // Get parameter of Laser Enabled
   parameter_t* laser_enabled = get_parameter(scanner, "user_laser_enabled");
   if ((name != NULL) && (strcmp(name->type, "uint32_t")==0)
   {
      uint32_t is_enabled = laser_enabled->val_uint32->value;
      printf("Current Laser State: %s\n", is_enabled == 0 ? "OFF" : "ON");
         
      uint32_t new_state;
      if (is_enabled == 1)
         new_state = 0;
      else 
         new_state = 1;

      laser_enabled->val_uint32->value = new_state;

      set_parameter(scanner, laser_enabled);
   }
      
   //  Write changes parameters to the device's memory
   write_params_to_scanner(scanner, kSERVICE);
   

send_command()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция отправки команд в сканер

.. doxygenfunction:: send_command

Для более детального описания команд и их свойств см. :ref:`rf62x_more_description_commands`
