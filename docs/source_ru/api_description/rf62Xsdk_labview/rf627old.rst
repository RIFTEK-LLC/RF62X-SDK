

.. _rf62x_wrappers_description_cpp_rf627old:

*******************************************************************************
Класс rf627old
*******************************************************************************

Данный класс определён в файле ``rf62Xsdk.h`` и предоставляет интерфейс 
для работы со сканерами серии RF627Old

.. doxygenclass:: SDK::SCANNERS::RF62X::rf627old

search()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для поиска устройств RF627 доступных в сети

.. doxygenfunction:: search

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 11

   // Initialize sdk library
   sdk_init();

   // Print return rf627 sdk version
   std::cout << "SDK version: " << sdk_version()                << std::endl;
   std::cout << "========================================="     << std::endl;

   // Create value for scanners vector's type
   std::vector<rf627old*> list;
   // Search for RF627old devices over network
   list = rf627old::search(PROTOCOLS::SERVICE);

   // Print count of discovered RF627Old in network by Service Protocol
   std::cout << "Discovered: " << list.size() << " RF627Old"   << std::endl;


get_info()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения информации о сканере из пакета приветствия (Hello-пакет)

.. doxygenfunction:: get_info

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 18-37

   // Initialize sdk library
   sdk_init();

   // Print return rf627 sdk version
   std::cout << "SDK version: " << sdk_version()                << std::endl;
   std::cout << "========================================="     << std::endl;

   // Create value for scanners vector's type
   std::vector<rf627old*> list;
   // Search for RF627old devices over network
   list = rf627old::search(PROTOCOLS::SERVICE);

   // Print count of discovered RF627Old in network by Service Protocol
   std::cout << "Discovered: " << list.size() << " RF627Old"   << std::endl;

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

   // Cleanup resources allocated with sdk_init()
   sdk_cleanup();
   

connect()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для установки соединения со сканером серии RF627

.. doxygenfunction:: connect

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 14-15

   // Initialize sdk library
   sdk_init();

   // Create value for scanners vector's type
   std::vector<rf627old*> list;
   // Search for RF627old devices over network
   list = rf627old::search(PROTOCOLS::SERVICE);

   // Print count of discovered RF627Old in network by Service Protocol
   std::cout << "Discovered: " << list.size() << " RF627Old"   << std::endl;

   for (size_t i = 0; i < list.size(); i++)
   {
      if (list[i]->connect())
         std::cout << "Connected to scanner №" << i << " successfully" << std::endl;
   }


disconnect()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для закрытия ранее установленного соединения со сканером серии RF627

.. doxygenfunction:: disconnect

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 19-20

   // Initialize sdk library
   sdk_init();

   // Create value for scanners vector's type
   std::vector<rf627old*> list;
   // Search for RF627old devices over network
   list = rf627old::search(PROTOCOLS::SERVICE);

   // Print count of discovered RF627Old in network by Service Protocol
   std::cout << "Discovered: " << list.size() << " RF627Old"   << std::endl;

   for (size_t i = 0; i < list.size(); i++)
      list[i]->connect();

   {
   ...some actions with scanners
   }

   for (size_t i = 0; i < list.size(); i++)
      list[i]->disconnect();

   
get_profile2D()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения профиля со сканеров серии RF627

.. doxygenfunction:: get_profile2D

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 20, 42

   // Initialize sdk library
   sdk_init();

   // Create value for scanners vector's type
   std::vector<rf627old*> list;
   // Search for RF627old devices over network
   list = rf627old::search(PROTOCOLS::SERVICE);

   // Print count of discovered RF627Old in network by Service Protocol
   std::cout << "Discovered: " << list.size() << " RF627Old"   << std::endl;

   // Iterate over all discovered RF627Old in network, connect to each of
   // them and get a profile.
   for(size_t i = 0; i < list.size(); i++)
   {
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
         case (uint8_t)PROFILE_DATA_TYPE::PIXELS_INTRP:
            std::cout << "* DataType\t: "<< "PIXELS_INTRP"      << std::endl;
            std::cout << "* Count\t: " << profile->pixels.size()<< std::endl;
            break;
         case (uint8_t)PROFILE_DATA_TYPE::PROFILE:
            std::cout << "* DataType\t: "<< "PROFILE"           << std::endl;
            std::cout << "* Size\t: "  << profile->points.size()<< std::endl;
            break;
         case (uint8_t)PROFILE_DATA_TYPE::PROFILE_INTRP:
            std::cout << "* DataType\t: "<< "PROFILE_INTRP"     << std::endl;
            std::cout << "* Size\t: "  << profile->points.size()<< std::endl;
            break;
         }
         delete profile;            
         std::cout << "Profile was successfully received!"       << std::endl;
         std::cout << "-----------------------------------------"<< std::endl;
      }else
      {
         std::cout << "Profile was not received!"                << std::endl;
         std::cout << "-----------------------------------------"<< std::endl;
      }

      // Disconnect from scanner.
      list[i]->disconnect();
   }

   // Cleanup resources allocated with sdk_init()
   sdk_cleanup();

.. _rf62x_wrappers_cpp_description_rf627old_read_params:

read_params()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения текущих параметров сканера. При вызове данной функции SDK вычитывает 
со сканера все актуальные параметры, сохраняя их ввиде «списка параметров» для дальнейшей 
работы.

.. doxygenfunction:: read_params

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 20

   // Initialize sdk library
   sdk_init();

   // Create value for scanners vector's type
   std::vector<rf627old*> scanners;
   // Search for RF627old devices over network
   scanners = rf627old::search(PROTOCOLS::SERVICE);

   // Print count of discovered RF627Old in network by Service Protocol
   std::cout << "Discovered: " << scanners.size() << " RF627Old"  << std::endl;

   // Iterate over all discovered RF627Old in network, connect to each of
   // them and read/set parameters.
   for(size_t i = 0; i < scanners.size(); i++)
   {
      // Establish connection to the RF627 device by Service Protocol.
      scanners[i]->connect();

      // read params from RF627 device by Service Protocol.
      scanners[i]->read_params();

      {
      ...some actions with params
      }

      // Disconnect from scanner.
      scanners[i]->disconnect();
   }

get_param()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения конкретного параметра по его имени (ключу). При вызове 
данной функции SDK осуществляет поиск нужного параметра из последних прочитанных 
при вызове функции :ref:`read_params`. В случае, если запрашиваемый 
параметр отсутствует в конкретном сканере, функция вернёт null.

.. doxygenfunction:: get_param(std::string)

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 13, 21, 29

   {
   ...Initialize sdk library
   ...Search for RF627old
   }

   // Establish connection to the RF627 device by Service Protocol.
   scanners[i]->connect();

   // read params from RF627 device by Service Protocol.
   scanners[i]->read_params();

   // Get parameter of Device Name
   param_t* name = scanners[i]->get_param("user_general_deviceName");
   if (name->type == "string_t")
   {
      std::string str_name = name->get_value<value_str>();
      std::cout << "Current Device Name \t: " << str_name     << std::endl;
   }

   // Get parameter of Device IP Addr
   param_t* ip_addr = scanners[i]->get_param("user_network_ip");
   if (ip_addr->type == "u32_arr_t")
   {
      std::vector <uint32_t> ip = ip_addr->get_value<array_uint32>();
      std::cout << "Current Device IP\t: ";
   }

   // Get parameter of Laser Enabled
   param_t* laser_enabled = scanners[i]->get_param("user_laser_enabled");
   if (laser_enabled->type == "uint32_t")
   {
      bool isEnabled = laser_enabled->get_value<value_uint32>();
      std::cout<<"Current Laser State\t: "<<(isEnabled?"ON":"OFF")<<std::endl;
   }

Для более удобной работы с параметрами можно использовать соответствующие «ключи» 
(ключ имени параметра, тип параметра и доступ к параметру).

.. doxygenfunction:: get_param(PARAM_NAME_KEY)

Для этого в файле ``rt62Xtypes.h`` находятся следующие ``enum``:

.. doxygenenum:: PARAM_VALUE_TYPE

.. doxygenenum:: PARAM_ACCESS_TYPE

.. doxygenenum:: PARAM_NAME_KEY

Пример использования с ключами:

.. code-block:: cpp
   :emphasize-lines: 13, 21, 29

   {
   ...Initialize sdk library
   ...Search for RF627old
   }

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
   }

   // Get parameter of Device IP Addr
   param_t* ip_addr = scanners[i]->get_param(PARAM_NAME_KEY::USER_NETWORK_IP);
   if (ip_addr->type == param_value_types[(int)PARAM_VALUE_TYPE::UINT32_ARRAY_PARAM_TYPE])
   {
      std::vector <uint32_t> ip = ip_addr->get_value<array_uint32>();
      std::cout << "Current Device IP\t: ";
   }

   // Get parameter of Laser Enabled
   param_t* laser_enabled = scanners[i]->get_param(PARAM_NAME_KEY::USER_LASER_ENABLED);
   if (laser_enabled->type == param_value_types[(int)PARAM_VALUE_TYPE::UINT_PARAM_TYPE])
   {
      bool isEnabled = laser_enabled->get_value<value_uint32>();
      std::cout<<"Current Laser State\t: "<<(isEnabled?"ON":"OFF")<<std::endl;
   }

Для более детального описания каждого параметра и его свойств см. :ref:`rf62x_more_description_params`

set_param()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция установки конкретного параметра. При вызове данной функции происходит установка 
передаваемого параметра в локальном списке параметров в SDK. Для отправки изменений 
в сканер необходимо вызвать функцию ``write_params``.

.. doxygenfunction:: set_param(param_t *)

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 20-21, 25, 37-38, 43, 54-55, 59, 63

   {
   ...Initialize sdk library
   ...Search for RF627old
   }

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

      // Change the current state to the opposite
      isEnabled = !isEnabled;
      laser_enabled->set_value<value_uint32>(!isEnabled);
      std::cout<<"New Laser State\t: "<<(isEnabled?"ON":"OFF")<<std::endl;
      std::cout << "-----------------------------------------"<< std::endl;

      scanners[i]->set_param(laser_enabled);
   }

   //  Write changes parameters to the device's memory
   scanners[i]->write_params();

   // Disconnect from scanner.
   scanners[i]->disconnect();


write_params()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция записи локальных параметров из SDK в сканер. При вызове данной функции 
происходит отправка списка локальных параметров из SDK в сканер.

.. doxygenfunction:: write_params

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 17

   {
   ...Initialize sdk library
   ...Search for RF627old
   }

   // Establish connection to the RF627 device by Service Protocol.
   scanners[i]->connect();

   // Read params from RF627 device by Service Protocol.
   scanners[i]->read_params();

   {
   ...Some steps to change scanner's parameters
   }

   //  Write changes parameters to the device's memory
   scanners[i]->write_params();

   // Disconnect from scanner.
   scanners[i]->disconnect();
   

send_cmd()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция отправки команд в сканер

.. doxygenfunction:: send_cmd

Для более детального описания команд и их свойств см. :ref:`rf62x_more_description_commands`