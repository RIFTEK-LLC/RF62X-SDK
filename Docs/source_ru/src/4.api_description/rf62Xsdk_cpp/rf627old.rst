

.. _rf62x_wrappers_cpp_rf627old:

*******************************************************************************
Класс rf627old
*******************************************************************************

Данный класс определён в файле ``rf62Xsdk.h`` и предоставляет интерфейс 
для работы со сканерами серии RF627 v20.x.x.x

.. _rf62x_wrappers_cpp_rf627old_search:

**search**
===============================================================================

**Прототип:**
   *static std::vector<std::shared_ptr<rf627old>> search(uint32_t timeout = 300, bool only_available_result = true, PROTOCOLS protocol = PROTOCOLS::SERVICE);*

**Описание:**
   *Метод поиска устройств RF62X v2.x.x в сети* 

**Параметры:**
   - ``timeout`` *- Время поиска на каждом Ethernet интерфейсе (мс).*
   - ``only_available_result`` *- Без сохраниения истории поиска (только доступные сканера на текущий момент).*
   - ``protocol`` *- Тип протокола, по которому будет осуществляться поиск (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   *Вектор rf627old устройств*

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 35

   /** @file rf62Xsdk.h */

   /**
    * @brief search - Search for rf627old devices over network
    *
    * @param timeout Search timeout[ms] for each Ethernet interface 
    * @param only_available_result Without saving search history
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    * 
    * @return vector of rf627old devices
    */
   static std::vector<std::shared_ptr<rf627old>> search(
           uint32_t timeout = 300, bool only_available_result = true,
           PROTOCOLS protocol = PROTOCOLS::SERVICE);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Create value for scanners vector's type
      std::vector<std::shared_ptr<rf627old>> list;
      // Search for rf627old devices over network
      list = rf627old::search(500);

      // Print count of discovered rf627old in network
      std::cout << "Was found\t: " << list.size() << " RF627 v20.x.x.x";
      
      // some code...

   }

.. _rf62x_wrappers_cpp_rf627old_get_info:

**get_info**
===============================================================================

**Прототип:**
   *std::shared_ptr<hello_info> get_info(PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод получения информации о сканере из пакета приветствия (Hello-пакет)* 

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому был получен пакет приветствия (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``hello_info`` *в случае успеха, иначе -* ``null``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 41, 46-49, 52-55, 58-59

   /** @file rf62Xsdk.h */

   /**
    * @brief get_info - Get information about scanner from hello packet
    *
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return hello_info on success, else - nullptr
    */
   std::shared_ptr<hello_info> get_info(
           PROTOCOLS protocol = PROTOCOLS::CURRENT);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Create value for scanners vector's type
      std::vector<std::shared_ptr<rf627old>> list;
      // Search for rf627old devices over network
      list = rf627old::search(500);

      // Print count of discovered rf627old in network by Service Protocol
      std::cout << "Was found\t: "<<list.size()<<" RF627-Old"<< std::endl;
      std::cout << "=========================================" << std::endl;


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
      
      // some code...
   }

.. _rf62x_wrappers_cpp_rf627old_connect:

**connect**
===============================================================================

**Прототип:**
   *bool connect(PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод установки соединения со сканером* 

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет выполнено подключение (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 43

   /** @file rf62Xsdk.h */

   /**
    * @brief connect - Establish connection to the rf627old device
    * 
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    * 
    * @return true on success, else - false
    */
    bool connect(PROTOCOLS protocol = PROTOCOLS::CURRENT);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Create value for scanners vector's type
      std::vector<std::shared_ptr<rf627old>> list;
      // Search for rf627old devices over network
      list = rf627old::search(500);

      // Print count of discovered rf627old in network by Service Protocol
      std::cout << "Was found\t: "<<list.size()<<" RF627-Old"<< std::endl;
      std::cout << "=========================================" << std::endl;


      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627old> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         bool isConnected = scanner->connect();
         if (!isConnected){
            std::cout << "Failed to connect to scanner!" << std::endl;
            continue;
         }

         // some actions with scanner...

      }
   }

.. _rf62x_wrappers_cpp_rf627old_is_connected:

**is_connected**
===============================================================================

**Прототип:**
   *bool is_connected();*

**Описание:**
   *Получение статуса подключения к сканеру методом* :ref:`rf62x_wrappers_cpp_rf627old_connect`

**Возвращаемое значение:**
   ``true`` *, если соединение со сканером было успешно установлено, иначе - * ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 38

   /** @file rf62Xsdk.h */

   /**
    * @brief is_connected - Scanner connection status by the
    * connect() method.
    *
    * @return true, if a connection to the scanner was previously
    * established using the connect() method, else - false.
    */
   bool is_connected();

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> list = rf627old::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627old> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         scanner->connect();

         bool result = scanner->is_connected()
         if (result) {
            std::cout << "Connection has been established";
         }
      }
   }

.. _rf62x_wrappers_cpp_rf627old_disconnect:

**disconnect**
===============================================================================

**Прототип:**
   *bool disconnect(PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод закрытия ранее установленного соединения со сканером* 

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет выполнено отключение (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 45

   /** @file rf62Xsdk.h */

   /**
    * @brief disconnect - Close connection to the device
    *
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return true on success, else - false
    */
    bool disconnect(PROTOCOLS protocol = PROTOCOLS::CURRENT);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> list = rf627old::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627old> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         bool isConnected = scanner->connect();
         if (!isConnected){
            std::cout << "Failed to connect to scanner!" << std::endl;
            continue;
         }

         // some actions with scanner...

         // Disconnect from scanner.
        scanner->disconnect();
      }
   }

.. _rf62x_wrappers_cpp_rf627old_check_connection:

**check_connection**
===============================================================================

**Прототип:**
   *bool check_connection(uint32_t timeout = 500, PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод проверки доступности сканера в сети (после подключения к нему)* 

**Параметры:**
   - ``timeout`` *- Время проверки соединения со сканером (мс).*
   - ``protocol`` *- Тип протокола, по которому будет выполнена проверка (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 45

   /** @file rf62Xsdk.h */

   /**
    * @brief check_connection - Сheck the connection with the
    * rf627old device
    *
    * @param timeout Connection check timeout
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return true on success, else - false
    */
   bool check_connection(
           uint32_t timeout = 500, PROTOCOLS protocol = PROTOCOLS::CURRENT);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> list = rf627old::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627old> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         bool isConnected = scanner->connect();
         if (!isConnected){
            std::cout << "Failed to connect to scanner!" << std::endl;
            continue;
         }

         bool isAvailable = scanner->check_connection(300);
         if (!isAvailable){
            std::cout << "Scanner is not available now, "
                      << "please call back later!" << std::endl;
            continue;
         }

         // some actions with scanner...
      }
   }

.. _rf62x_wrappers_cpp_rf627old_is_available:

**is_available**
===============================================================================

**Прототип:**
   *bool is_available();*

**Описание:**
   *Метод получения статуса доступности сканера в сети. Значение, возвращаемое*
   *методом, зависит от результатов выполнения методов* :ref:`rf62x_wrappers_cpp_rf627old_search` *и* :ref:`rf62x_wrappers_cpp_rf627old_check_connection` 

**Возвращаемое значение:**
   ``true`` *если сканер доступен, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 42

   /** @file rf62Xsdk.h */

   /**
    * @brief is_available - Scanner availability status on the network.
    * @details The value returned by the method depends on the results
    * of the execution of the search() and check_connection() methods.
    *
    * @return true, if the scanner is available, otherwise - false.
    */
   bool is_available();

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> list = rf627old::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627old> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         scanner->connect();

         // some time after using the scanner...

         // Check network connections to scanner
         scanner->check_connection(300);
         bool isAvailable = scanner->is_available();
         if (!isAvailable){
            std::cout << "Scanner is not available!" << std::endl;
            std::cout << "Check the power supply to the scanner.";
         }

         // some code...
         
      }
   }
 
.. _rf62x_wrappers_cpp_rf627old_get_profile2D:

**get_profile2D**
===============================================================================

**Прототип:**
   *std::shared_ptr<profile2D> get_profile2D(bool zero_points = true, bool realtime = true, PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод получения результатов измерений* 

**Параметры:**
   - ``zero_points`` *- Включать нулевые точки в возвращаемом профиле.*
   - ``realtime`` *- Получение профиля в реальном времени (буферизация отключена).*
   - ``protocol`` *- Тип протокола, по которому будет получен профиль (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``std::shared_ptr<profile2D>`` *при успехе, иначе -* ``nullptr``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 47

   /** @file rf62Xsdk.h */

   /**
    * @brief get_profile2D - Get 2D measurement from scanner's data stream
    *
    * @param zero_points Enable zero points in return profile2D
    * @param realtime Enable getting profile in real time (buffering is disabled)
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return profile2D if success, else - nullptr
    */
   std::shared_ptr<profile2D> get_profile2D(
           bool zero_points = true, bool realtime = true,
           PROTOCOLS protocol = PROTOCOLS::CURRENT);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> list = rf627old::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627old> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         bool isConnected = scanner->connect();
         if (isConnected) {
            bool zero_points = true;
            bool realtime = true;
            std::shared_ptr<profile2D> profile = nullptr;
            
            // Get profile from scanner
            profile = scanner->get_profile2D(zero_points, realtime);
            if (profile != nullptr) {
               std::cout << "Profile was successfully received!" << std::endl;
               // some actions with profile...
            }else
               std::cout << "Profile was not received!" << std::endl;
         }
         // some code...
      }
   }

.. _rf62x_wrappers_cpp_rf627old_read_params:

**read_params**
===============================================================================

**Прототип:**
   *bool read_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод получения текущих параметров сканера. При вызове данной функции SDK вычитывает*
   *со сканера все актуальные параметры, сохраняя их ввиде «списка параметров» для дальнейшей*
   *работы во внутренней памяти SDK.* 

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будут прочитаны параметры (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 40

   /** @file rf62Xsdk.h */

   /**
    * @brief read_params - Read parameters from device to
    * internal SDK memory
    *
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return true on success, else - false
    */
   bool read_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> list = rf627old::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627old> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         bool isConnected = scanner->connect();
         if (isConnected) {
            // read params from RF627 device by Service Protocol.
            bool isRead = scanner->read_params();
            if (isRead) {
               std::cout << "Scanner parameters were read successfully!";
               // some actions with params...
            }else 
               std::cout << "Scanner parameters were not read!";
         }
      }
      // some code...
   }

.. _rf62x_wrappers_cpp_rf627old_get_param:

**get_param**
===============================================================================

**Прототип:**
   *std::shared_ptr<param> get_param(std::string param_name);*

**Описание:**
   *Метод получения конкретного параметра по его имени (ключу). При вызове* 
   *данной функции SDK осуществляет поиск нужного параметра из последних прочитанных*
   *при вызове функции* :ref:`rf62x_wrappers_cpp_rf627old_read_params` *. В случае, если* 
   *запрашиваемый параметр отсутствует в конкретном сканере, функция вернёт nullptr.* 

**Параметры:**
   - ``param_name`` *- Имя (ключ) параметра.*

**Возвращаемое значение:**
   ``std::shared_ptr<param>`` *при успехе, иначе -* ``nullptr``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 41, 48

   /** @file rf62Xsdk.h */

   /**
    * @brief get_param - Get parameter by his name
    * Before using read_params() method should be called
    *
    * @param param_name Name of parameter
    *
    * @return param on success, else - null
    */
   std::shared_ptr<param> get_param(std::string param_name);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> scanners = rf627old::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         // Establish connection.
         scanners[i]->connect();
         
         // Read params.
         scanners[i]->read_params();

         // Get parameter of Device Name
         auto name = scanners[i]->get_param("user_general_deviceName");
         if (name != nullptr) {
            std::string str_name = name->getValue<std::string>();
            std::cout << "Current Device Name \t: " << str_name << std::endl;
         }

         // Get parameter of Sensor Framerate
         auto framerate = scanner->get_param("user_sensor_framerate");
         if (framerate != nullptr) {
            uint32_t framerate_value = framerate->getValue<uint32_t>();
            std::cout<<"Current FPS\t\t: "<< framerate_value << std::endl;
         }

         // some actions with other parameters...

      }
      // some code...
   }

.. note::
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__

.. _rf62x_wrappers_cpp_rf627old_set_param:

**set_param**
===============================================================================

**Прототип:**
   *bool set_param(std::string name, T value);*

**Описание:**
   *Метод установки конкретного параметра. При вызове данного метода происходит*
   установка параметра в списке параметров во внутренней памяти SDK.*
   *Для отправки изменений в сканер необходимо вызвать метод* :ref:`rf62x_wrappers_cpp_rf627old_write_params` *.*

**Параметры:**
   - ``param_name`` *- Имя (ключ) параметра.*
   - ``value`` *- Новое значение параметра

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 40, 43, 47

   /** @file rf62Xsdk.h */

   /**
    * @brief set_param - Set parameter
    *
    * @param name Name of parameter
    * @param value Value to set
    *
    * @return true on success, else - false
    */
   template<typename T>
   bool set_param(std::string name, T value);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>
   #include <vector>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> scanners = rf627old::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
         scanners[i]->read_params();

         // Set parameter of Device Name
         scanner->set_param("user_general_deviceName", "RF627 New Name");

         // Sen parameter of Sensor Framerate
         scanner->set_param("user_sensor_framerate", 100);

         // Set parameter of Device IP Addr
         std::vector<uint32_t> ip {192, 168, 1, 31};
         scanner->set_param("user_network_ip", ip);

         // some actions with other parameters...

      }
      // some code...
   }

.. note::
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__

.. _rf62x_wrappers_cpp_rf627old_set_param_by_key:

**set_param_by_key**
===============================================================================

**Прототип:**
   *bool set_param_by_key(std::string name, std::string key);*

**Описание:**
   *Метод установки конкретного параметра по ключу. При вызове данного метода* 
   *происходит установка параметра в списке параметров во внутренней памяти SDK.*
   *Для отправки изменений в сканер необходимо вызвать метод* :ref:`rf62x_wrappers_cpp_rf627old_write_params` *.*

**Параметры:**
   - ``param_name`` *- Имя (ключ) параметра.*
   - ``key`` *- Ключ (enum) параметра

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 38, 42, 46

   /** @file rf62Xsdk.h */

   /**
    * @brief set_param_by_key - Set parameter from Enum
    *
    * @param name Name of parameter
    * @param key Key to set
    *
    * @return true on success, else - false
    */
   bool set_param_by_key(std::string name, std::string key);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> scanners = rf627old::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
         scanners[i]->read_params();

         // Set parameter of Laser Enabled (TRUE or FALSE)
         scanner->set_param_by_key("user_laser_enabled", "FALSE");

         // Sen parameter of Sensor sync source (SYNC_INTERNAL, 
         // SYNC_EXTERNAL, SYNC_SOFTWARE_EXT or SYNC_SOFTWARE)
         scanner->set_param_by_key("user_sensor_syncSource", "SYNC_INTERNAL");

         // Set parameter of Streams Format (DATA_FORMAT_PROFILE or 
         // DATA_FORMAT_RAW_PROFILE)
         scanner->set_param_by_key("user_streams_format", "DATA_FORMAT_PROFILE");

         // some actions with other parameters...

      }
      // some code...
   }

.. note::
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__

.. _rf62x_wrappers_cpp_rf627old_write_params:

**write_params**
===============================================================================

**Прототип:**
   *bool write_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод передачи параметров из внутренней памяти SDK в сканер.* 
   *При вызове данного метода происходит отправка изменённых параметров в сканер*

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будут отправлена команда на установку параметров (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 44

   /** @file rf62Xsdk.h */

   /**
    * @brief write_params - Send current parameters to device
    *
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return true on success, else - false
    */
   bool write_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> scanners = rf627old::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
         scanners[i]->read_params();

         // Set parameter of Device Name
         scanner->set_param("user_general_deviceName", "RF627 New Name");
         // Sen parameter of Sensor Framerate
         scanner->set_param("user_sensor_framerate", 100);

         // some actions with other parameters...

         // Apply changed parameters to the device
         bool isApplied = scanner->write_params();
         if (isApplied) 
            std::cout << "Scanner parameters were applied successfully!";
         else 
            std::cout << "Scanner parameters were not applied!";

      }
      // some code...
   }

.. _rf62x_wrappers_cpp_rf627old_save_params:

**save_params**
===============================================================================

**Прототип:**
   *bool save_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод сохранения параметров сканер во внутреннюю память устройства.* 
   *Сохраненные параметры также будут использоваться после перезапуске устройства* 
   *или после смены(обновления) прошивки.*

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет отправлена команда сохранения параметров (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 44

   /** @file rf62Xsdk.h */

   /**
    * @brief save_params - Save changes to device's memory
    * @details The saved parameters will also be used if the device
    * is restarted or even if the firmware is updated.
    *
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return true on success, else - false
    */
   bool save_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> scanners = rf627old::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
         scanners[i]->read_params();

         // After changing some parameters...

         // Apply changed parameters to the device
         scanner->write_params();
         
         // Save current parameters in the device memory
         bool isSaved = scanner->save_params();
         if (isSaved) 
            std::cout << "Scanner parameters saved successfully!";
         else 
            std::cout << "Scanner parameters were not saved!";

      }
      // some code...
   }

.. _rf62x_wrappers_cpp_rf627old_reboot_device:

**reboot_device**
===============================================================================

**Прототип:**
   *bool reboot_device(PROTOCOLS protocol = PROTOCOLS::CURRENT)*

**Описание:**
   *Метод перезагрузки устройства*
   
**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет отправлена команда на перезагрузку устройства (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 37

   /** @file rf62Xsdk.h */

   /**
    * @brief reboot_device - The scanner will restart
    * 
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    * 
    * @return true on success, else - false
    */
   bool reboot_device(PROTOCOLS protocol = PROTOCOLS::CURRENT);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>
   #include <chrono>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> scanners = rf627old::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
      
         // Start device reboot
         scanners[i]->reboot_device();
         
         // Waiting 10 sec
         std::this_thread::sleep_for(std::chrono::seconds(10));

         bool isAvailable = scanners[i]->check_connection();
         if (isAvailable){
            std::cout << "Scanner has been successfully restarted" << std::endl;
         }

         // some other actions with scanner...

      }
   }

.. _rf62x_wrappers_cpp_rf627old_send_cmd:

**send_cmd**
===============================================================================

**Прототип:**
   *bool send_cmd(std::string command_name, std::vector<uint8_t> in, std::vector<uint8_t>& out);*

**Описание:**
   *Метод отправки команды в сканер*
   
**Параметры:**
   - ``command_name`` *- Название команды. (CID_PERIPHERY_SEND, CID_PROFILE_SET_COUNTERS, и др.)*
   - ``in`` *- Данные для отправки.*
   - ``out`` *- Данные, которые были получены.*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 44, 53

   /** @file rf62Xsdk.h */

   /**
    * @brief send_cmd - Send command to scanner
    *
    * @param command_name Name of command:
    * CID_PERIPHERY_SEND - send/receive data to/from a peripheral device
    * CID_PROFILE_SET_COUNTERS - set counters in devices
    * @param input Data to send in command payload
    * @param output Data to receive from command payload
    *
    * @return true on success, else - false
    */
   bool send_cmd(std::string command_name,
                 std::vector<uint8_t> in, std::vector<uint8_t>& out);

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>
   #include <chrono>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      sdk_init();

      // Search for rf627old devices over network
      std::vector<std::shared_ptr<rf627old>> scanners = rf627old::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
      
         // Send data to periphery
         std::vector<uint8_t> in { 1, 2, 3, 4, 5};
         std::vector<uint8_t> out;
         bool isSent = scanners[i]->send_cmd("CID_PERIPHERY_SEND", in, out);
         if (isSent){
            std::cout << "The data was sent successfully." << std::endl;
            std::cout << "Size of received data: " << out.size() << std::endl;
         }

         // Reset counters
         std::vector<uint8_t> in(0);
         std::vector<uint8_t> out;
         isSent = scanners[i]->send_cmd("CID_PROFILE_SET_COUNTERS", in, out);
         if (isSent){
            std::cout << "The counters was reset successfully." << std::endl;
         }

         // some other actions with scanner...
      }
   }