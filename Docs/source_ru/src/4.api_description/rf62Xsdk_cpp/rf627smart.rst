

.. _rf62x_wrappers_description_cpp_rf627old:

*******************************************************************************
Класс rf627smart
*******************************************************************************

Данный класс определён в файле ``rf62Xsdk.h`` и предоставляет интерфейс 
для работы со сканерами серии RF62X v2.X.X


**search**
===============================================================================

**Прототип:**
   *static std::vector<std::shared_ptr<rf627smart>> search(uint32_t timeout = 300, bool only_available_result = true, PROTOCOLS protocol = PROTOCOLS::SERVICE);*

**Описание:**
   *Метод поиска устройств RF62X v2.x.x в сети* 

**Параметры:**
   - ``timeout`` *- Время поиска на каждом Ethernet интерфейсе (мс).*
   - ``only_available_result`` *- Без сохраниения истории поиска (только доступные сканера на текущий момент).*
   - ``protocol`` *- Тип протокола, по которому будет осуществляться поиск (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   *Вектор rf627smart устройств*

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 35

   /** @file rf62Xsdk.h */

   /**
    * @brief search - Search for RF627smart devices over network
    *
    * @param timeout Search timeout[ms] for each Ethernet interface 
    * @param only_available_result Without saving search history
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    * 
    * @return vector of rf627smart devices
    */
   static std::vector<std::shared_ptr<rf627smart>> search(
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
      std::vector<std::shared_ptr<rf627smart>> list;
      // Search for rf627smart devices over network
      list = rf627smart::search(500);

      // Print count of discovered rf627smart in network
      std::cout << "Was found\t: " << list.size() << " RF627-Smart";
      
      // some code...

   }

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
   :emphasize-lines: 41-60

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
      std::vector<std::shared_ptr<rf627smart>> list;
      // Search for rf627smart devices over network
      list = rf627smart::search(500);

      // Print count of discovered rf627smart in network by Service Protocol
      std::cout << "Was found\t: "<<list.size()<<" RF627-Smart"<< std::endl;
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
   :emphasize-lines: 42-47

   /** @file rf62Xsdk.h */

   /**
    * @brief connect - Establish connection to the RF627old device
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
      std::vector<std::shared_ptr<rf627smart>> list;
      // Search for rf627smart devices over network
      list = rf627smart::search(500);

      // Print count of discovered rf627smart in network by Service Protocol
      std::cout << "Was found\t: "<<list.size()<<" RF627-Smart"<< std::endl;
      std::cout << "=========================================" << std::endl;


      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         bool isConnected = scanner->connect();
         if (!isConnected){
            std::cout << "Failed to connect to scanner!" << std::endl;
            continue;
         }

         // some actions with scanner...

      }
   }

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> list = rf627smart::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         
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
    * RF627smart device
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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> list = rf627smart::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         
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
   :emphasize-lines: 42-53

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> list = rf627smart::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         
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

**get_frame**
===============================================================================

**Прототип:**
   *std::shared_ptr<frame> get_frame(PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод получения кадров видео с матрицы сканера* 

**Параметры:**
   - ``zero_points`` *- Включать нулевые точки в возвращаемом профиле.*
   - ``realtime`` *- Получение профиля в реальном времени (буферизация отключена).*
   - ``protocol`` *- Тип протокола, по которому будет получен кадр (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``std::shared_ptr<frame>`` *при успехе, иначе -* ``nullptr``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 38-44

   /** @file rf62Xsdk.h */

   /**
    * @brief get_frame - Get RAW frame from scanner
    *
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return frame if success, else - null
    */
   std::shared_ptr<frame> get_frame(PROTOCOLS protocol = PROTOCOLS::CURRENT);

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> list = rf627smart::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         bool isConnected = scanner->connect();
         if (isConnected) {
            // Get Frame from scanner.
            std::shared_ptr<frame> frame = scanner->get_frame();
            if (frame != nullptr) {
               std::cout << "Frame was successfully received!" << std::endl;
               // some actions with profile...
            }else
               std::cout << "Frame was not received!" << std::endl;
         }
         // some code...
      }
   }

.. _rf62x_wrappers_cpp_read_params:

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
   :emphasize-lines: 38-44

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> list = rf627smart::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         
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

**get_param**
===============================================================================

**Прототип:**
   *std::shared_ptr<param> get_param(std::string param_name);*

**Описание:**
   *Метод получения конкретного параметра по его имени (ключу). При вызове* 
   *данной функции SDK осуществляет поиск нужного параметра из последних прочитанных*
   *при вызове функции* :ref:`rf62x_wrappers_cpp_read_params` *. В случае, если* 
   *запрашиваемый параметр отсутствует в конкретном сканере, функция вернёт nullptr.* 

**Параметры:**
   - ``param_name`` *- Имя (ключ) параметра.*

**Возвращаемое значение:**
   ``std::shared_ptr<param>`` *при успехе, иначе -* ``nullptr``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 40-45, 47-52

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

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
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj`__

**set_param**
===============================================================================

**Прототип:**
   *bool set_param(std::string name, T value);*

**Описание:**
   *Метод установки конкретного параметра. При вызове данного метода происходит*
   установка параметра в списке параметров во внутренней памяти SDK.*
   *Для отправки изменений в сканер необходимо вызвать метод* :ref:`rf62x_wrappers_cpp_write_params` *.*

**Параметры:**
   - ``param_name`` *- Имя (ключ) параметра.*
   - ``value`` *- Новое значение параметра

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 40, 43, 46-47

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

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
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj`__

**set_param_by_key**
===============================================================================

**Прототип:**
   *bool set_param_by_key(std::string name, std::string key);*

**Описание:**
   *Метод установки конкретного параметра по ключу. При вызове данного метода* 
   *происходит установка параметра в списке параметров во внутренней памяти SDK.*
   *Для отправки изменений в сканер необходимо вызвать метод* :ref:`rf62x_wrappers_cpp_write_params` *.*

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

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
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj`__

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
   :emphasize-lines: 44-48

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

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
   :emphasize-lines: 45-49

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

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

**load_recovery_params**
===============================================================================

**Прототип:**
   *bool load_recovery_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);*

**Описание:**
   *Метод загрузки значений параметров устройства из области восстановления.* 
   *Загруженные значения будут записаны в пользовательскую область*

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет отправлена команда на восстановлениен параметров (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 37-41

   /** @file rf62Xsdk.h */

   /**
    * @brief load_recovery_params - Loading parameters from recovery area
    * @details The device will automatically reboot.
    *
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return true on success, else - false
    */
   bool load_recovery_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
      
         // Load parameters from recovery area
         bool isLoaded = scanner->load_recovery_params();
         if (isLoaded) 
            std::cout << "Recovery parameters loaded successfully!";
         else 
            std::cout << "Recovery parameters were not loaded!";

      }
      // some code...
   }


**start_dump_recording**
===============================================================================

**Прототип:**
   *bool start_dump_recording(uint32_t count_of_profiles = 0);*

**Описание:**
   *Метод включения записи профилей во внутреннюю память устройства - запуск записи дампа.* 
   *Запись остановится, когда количество записанных профилей превысит максимально* 
   *допустимый размер дампа, или когда будет превышено количество переданного в метод параметра* 
   ``count_of_profiles`` *, или когда будет вызван метод остановки записи* :ref:`rf62x_wrappers_cpp_stop_dump_recording` *.*

**Параметры:**
   - ``count_of_profiles`` *- Количество профилей для записи дампа*

**Возвращаемое значение:**
   ``true`` *если запись началась успешно, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 45-50

   /** @file rf62Xsdk.h */

   /**
    * @brief start_dump_recording - enabling profile recording to the internal
    * memory of the device - generating a dump.
    * @details Recording will stop when the number of recorded profiles exceeds
    * the maximum allowed dump size, or when the count_of_profiles number is
    * exceeded, or when the stop_dump_recording method is called.
    *
    * @param count_of_profiles The number of profiles to record the dump:
    * if count_of_profiles == 0 - Recording will continue until the maximum
    * dump size is reached, or until recording is stopped by calling
    * the stop_dump_recording method;
    * if count_of_profiles > 0  - Recording will continue until the number
    * of recorded profiles exceeds the specified number.
    *
    * @return true if recording started successfully, else - false
    */
    bool start_dump_recording(uint32_t count_of_profiles = 0);

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
      
         // Start dump recording
         uint32_t count_of_profiles = 1000;
         bool isStarted = scanners[i]->start_dump_recording(count_of_profiles);
         if (isStarted) 
            std::cout << "Dump recording started...";
         else 
            std::cout << "Dump recording failed!";

         // Next steps in stop_dump_recording example...

      }
   }


**stop_dump_recording**
===============================================================================

**Прототип:**
   *bool stop_dump_recording(uint32_t& count_of_profiles);*

**Описание:**
   *Метод остановки записи профилей во внутреннюю память устройства - остановка записи дампа.* 
   
**Параметры:**
   - ``count_of_profiles`` *- Количество записанных профилей в дампе*

**Возвращаемое значение:**
   ``true`` *если запись остановлена успешно, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 44-49

   /** @file rf62Xsdk.h */

   /**
    * @brief stop_dump_recording - disabling profile recording to the internal
    * memory of the device.
    *
    * @param count_of_profiles The number of recorded profiles
    *
    * @return true if recording was stopped successfully, else - false
    */
   bool stop_dump_recording(uint32_t& count_of_profiles);

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
      
         // Start dump recording
         scanners[i]->start_dump_recording();

         // Waiting 1 sec
         std::this_thread::sleep_for(std::chrono::seconds(1));
         
         // Stop dump recording
         uint32_t count_of_profiles = 0;
         bool isStopped = scanners[i]->stop_dump_recording(count_of_profiles);
         if (isStopped) 
            std::cout << "Current profiles in dump: " << count_of_profiles;
         else 
            std::cout << "Failed to stop dump recording!";

         // Next steps in get_dumps_profiles example...

      }
   }

**get_dumps_profiles**
===============================================================================

**Прототип:**
   *std::vector<std::shared_ptr<profile2D>> get_dumps_profiles(uint32_t index, uint32_t count, uint32_t timeout = 10000);*

**Описание:**
   *Метод скачивания дампа из внутренней памяти устройства* 
   
**Параметры:**
   - ``index`` *- Начальный номер запрашиваемого профиля из дампа*
   - ``count`` *- Количество скачиваемых профилей относительно начального номера* ``index``
   - ``timeout`` *- Время ожидания скачивания дампа.*

**Возвращаемое значение:**
   *Вектор профилей*

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 39-40, 43-48, 50-51

   /** @file rf62Xsdk.h */

   /**
    * @brief get_dumps_profiles - getting the content of the profile dump
    *
    * @param index Start number of the requested profile from memory
    * @param count The count of requested profiles
    * @param timeout Waiting time for dump download
    *
    * @return Vector profiles
    */
   std::vector<std::shared_ptr<profile2D>> get_dumps_profiles(
           uint32_t index, uint32_t count, uint32_t timeout = 10000);

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
      
         // Start dump recording
         uint32_t count_of_profiles = 1000;
         scanners[i]->start_dump_recording(count_of_profiles);

         // Print information about the current dump size
         uint32_t size = 0;
         do {
            scanners[i]->read_params();
            size =scanners[i]->get_param("user_dump_size")->getValue<uint32_t>();
            std::cout << "Current profiles in the dump: " << size << std::endl;
         }while(size < count_of_profiles);

         std::vector<std::shared_ptr<profile2D>> dump =
                  list[i]->get_dumps_profiles(0, count_of_profiles);

         std::cout << dump.size() << " Profiles were received! " << std::endl;

         // Next steps with dumps...

      }
   }

**start_profile_capturing**
===============================================================================

**Прототип:**
   *std::vector<std::shared_ptr<profile2D>> get_dumps_profiles(uint32_t index, uint32_t count, uint32_t timeout = 10000);*

**Описание:**
   *Метод начала выполнения измерений. Используется только в режиме запуска* 
   *программного измерения (параметр* ``user_sensor_syncSource = "SYNC_SOFTWARE"`` или ``user_sensor_syncSource = "SYNC_SOFTWARE_EXT"``
   *). При получении команды устройство запускает цикл измерения, после чего выполняется* 
   *расчет и отправляется стандартный пакет с профилем* 

   *В режиме "программного измерения" метод* :ref:`rf62x_wrappers_cpp_get_profile2D` 
   *должен использоваться с переметром* ``realtime = false`` *, чтобы избежать потери* 
   *запрашиваемых профилей.*
   
**Параметры:**
   - ``count_of_profiles`` *- Количество запрашиваемых измерений.*

**Возвращаемое значение:**
   ``true`` *если измерения запущены успешно, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 39-40, 43-48, 50-51

   /** @file rf62Xsdk.h */

   /**
    * @brief start_profile_capturing - Command to start profiles measuring.
    * @details This command is used only in the "software measurement" mode:
    * when parameter "user_sensor_syncSource" == "SYNC_SOFTWARE"
    * or "SYNC_SOFTWARE_EXT". Device starts a measurement cycle immediately
    * after receiving this command.
    * ! In "software measurement" mode the get_profile2D method must be used
    * with the realtime == false argument to avoid loss of requested profiles.
    *
    * @param count_of_profiles The count of measurements
    *
    * @return true if measuring was started successfully, else - false
    */
   bool start_profile_capturing(uint32_t count_of_profiles = 0);

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
      
         // Start dump recording
         uint32_t count_of_profiles = 1000;
         scanners[i]->start_dump_recording(count_of_profiles);

         // Print information about the current dump size
         uint32_t size = 0;
         do {
            scanners[i]->read_params();
            size =scanners[i]->get_param("user_dump_size")->getValue<uint32_t>();
            std::cout << "Current profiles in the dump: " << size << std::endl;
         }while(size < count_of_profiles);

         std::vector<std::shared_ptr<profile2D>> dump =
                  list[i]->get_dumps_profiles(0, count_of_profiles);

         std::cout << dump.size() << " Profiles were received! " << std::endl;

         // Next steps with dumps...

      }
   }

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> scanners = rf627smart::search();

      for (size_t i = 0; i < scanners.size(); i++)
      {
         scanners[i]->connect();
      
         // Start device reboot
         scanners[i]->reboot_device();
         
         // Waiting 10 sec
         std::this_thread::sleep_for(std::chrono::seconds(10));

         bool isAvailable = scanners[i]->check_connection();
         if (!isAvailable){
            std::cout << "Scanner has been successfully restarted" << std::endl;
         }

         // some other actions with scanner...

      }
   }

send_cmd()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция отправки команд в сканер

.. doxygenfunction:: SDK::SCANNERS::RF62X::rf627old::send_cmd(const char *, int, ...)

Для более детального описания команд и их свойств см. :ref:`rf62x_more_description_commands`