

.. _rf62x_wrappers_cpp_rf627smart:

*******************************************************************************
Класс rf627smart
*******************************************************************************

Данный класс определён в файле ``rf62Xsdk.h`` и предоставляет интерфейс 
для работы со сканерами серии RF62X v2.x.x

.. _rf62x_wrappers_cpp_rf627smart_search:

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
    * @brief search - Search for rf627smart devices over network
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
      std::cout << "Was found\t: " << list.size() << " RF62X v2.x.x";
      
      // some code...

   }

.. _rf62x_wrappers_cpp_rf627smart_get_info:

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

.. _rf62x_wrappers_cpp_rf627smart_connect:

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
    * @brief connect - Establish connection to the rf627smart device
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

.. _rf62x_wrappers_cpp_rf627smart_is_connected:

**is_connected**
===============================================================================

**Прототип:**
   *bool is_connected();*

**Описание:**
   *Получение статуса подключения к сканеру методом* :ref:`rf62x_wrappers_cpp_rf627smart_connect`

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> list = rf627smart::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         
         // Establish connection to the RF627 device by Service Protocol.
         scanner->connect();

         bool result = scanner->is_connected()
         if (result) {
            std::cout << "Connection has been established";
         }
      }
   }

.. _rf62x_wrappers_cpp_rf627smart_disconnect:

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

.. _rf62x_wrappers_cpp_rf627smart_check_connection:

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
    * rf627smart device
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

.. _rf62x_wrappers_cpp_rf627smart_is_available:

**is_available**
===============================================================================

**Прототип:**
   *bool is_available();*

**Описание:**
   *Метод получения статуса доступности сканера в сети. Значение, возвращаемое*
   *методом, зависит от результатов выполнения методов* :ref:`rf62x_wrappers_cpp_rf627smart_search` *и* :ref:`rf62x_wrappers_cpp_rf627smart_check_connection` 

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

      // Search for rf627smart devices over network
      std::vector<std::shared_ptr<rf627smart>> list = rf627smart::search();

      for (size_t i = 0; i < list.size(); i++)
      {
         std::shared_ptr<rf627smart> scanner = list[i];
         
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
 
.. _rf62x_wrappers_cpp_rf627smart_get_profile2D:

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

.. _rf62x_wrappers_cpp_rf627smart_get_frame:

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
   :emphasize-lines: 39

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

.. _rf62x_wrappers_cpp_rf627smart_read_params:

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

.. _rf62x_wrappers_cpp_rf627smart_get_param:

**get_param**
===============================================================================

**Прототип:**
   *std::shared_ptr<param> get_param(std::string param_name);*

**Описание:**
   *Метод получения конкретного параметра по его имени (ключу). При вызове* 
   *данной функции SDK осуществляет поиск нужного параметра из последних прочитанных*
   *при вызове функции* :ref:`rf62x_wrappers_cpp_rf627smart_read_params` *. В случае, если* 
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
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__

.. _rf62x_wrappers_cpp_rf627smart_set_param:

**set_param**
===============================================================================

**Прототип:**
   *bool set_param(std::string name, T value);*

**Описание:**
   *Метод установки конкретного параметра. При вызове данного метода происходит*
   установка параметра в списке параметров во внутренней памяти SDK.*
   *Для отправки изменений в сканер необходимо вызвать метод* :ref:`rf62x_wrappers_cpp_rf627smart_write_params` *.*

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
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__

.. _rf62x_wrappers_cpp_rf627smart_set_param_by_key:

**set_param_by_key**
===============================================================================

**Прототип:**
   *bool set_param_by_key(std::string name, std::string key);*

**Описание:**
   *Метод установки конкретного параметра по ключу. При вызове данного метода* 
   *происходит установка параметра в списке параметров во внутренней памяти SDK.*
   *Для отправки изменений в сканер необходимо вызвать метод* :ref:`rf62x_wrappers_cpp_rf627smart_write_params` *.*

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
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__

.. _rf62x_wrappers_cpp_rf627smart_write_params:

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

.. _rf62x_wrappers_cpp_rf627smart_save_params:

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

.. _rf62x_wrappers_cpp_rf627smart_load_recovery_params:

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
   :emphasize-lines: 37

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

.. _rf62x_wrappers_cpp_rf627smart_start_dump_recording:

**start_dump_recording**
===============================================================================

**Прототип:**
   *bool start_dump_recording(uint32_t count_of_profiles = 0);*

**Описание:**
   *Метод включения записи профилей во внутреннюю память устройства - запуск записи дампа.* 
   *Запись остановится, когда количество записанных профилей превысит максимально* 
   *допустимый размер дампа, или когда будет превышено количество переданного в метод параметра* 
   ``count_of_profiles`` *, или когда будет вызван метод остановки записи* :ref:`rf62x_wrappers_cpp_rf627smart_stop_dump_recording` *.*

**Параметры:**
   - ``count_of_profiles`` *- Количество профилей для записи дампа*

**Возвращаемое значение:**
   ``true`` *если запись началась успешно, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 46

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

.. _rf62x_wrappers_cpp_rf627smart_stop_dump_recording:

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
   :emphasize-lines: 45

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

.. _rf62x_wrappers_cpp_rf627smart_get_dumps_profiles:

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
   :emphasize-lines: 50-51

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

.. _rf62x_wrappers_cpp_rf627smart_start_profile_capturing:

**start_profile_capturing**
===============================================================================

**Прототип:**
   *std::vector<std::shared_ptr<profile2D>> get_dumps_profiles(uint32_t index, uint32_t count, uint32_t timeout = 10000);*

**Описание:**
   *Метод начала выполнения измерений. Используется только в режиме запуска* 
   *программного измерения (параметр* ``user_sensor_syncSource = "SYNC_SOFTWARE"`` или ``user_sensor_syncSource = "SYNC_SOFTWARE_EXT"``
   *). При получении команды устройство запускает цикл измерения, после чего выполняется* 
   *расчет и отправляется стандартный пакет с профилем* 

   *В режиме "программного измерения" метод* :ref:`rf62x_wrappers_cpp_rf627smart_get_profile2D` 
   *должен использоваться с переметром* ``realtime = false`` *, чтобы избежать потери* 
   *запрашиваемых профилей.*
   
**Параметры:**
   - ``count_of_profiles`` *- Количество запрашиваемых измерений.*

**Возвращаемое значение:**
   ``true`` *если измерения запущены успешно, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 46

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
         
         // Select SYNC_SOFTWARE measurement mode
         scanners[i]->set_param_by_key("user_sensor_syncSource", "SYNC_SOFTWARE");
         
         // Start profile capturing
         uint32_t count_of_profiles = 1000;
         scanners[i]->start_profile_capturing(count_of_profiles);

         // realtime must be set to false
         bool realtime = false; /// It is important!
         bool zero_points = true;
         // Get profile from scanner
         std::shared_ptr<profile2D> profile =
            scanner[i]->get_profile2D(zero_points, realtime);

         // some actions with profiles...
      }
   }

.. _rf62x_wrappers_cpp_rf627smart_reboot_device:

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
         if (isAvailable){
            std::cout << "Scanner has been successfully restarted" << std::endl;
         }

         // some other actions with scanner...

      }
   }

.. _rf62x_wrappers_cpp_rf627smart_reboot_sensor:

**reboot_sensor**
===============================================================================

**Прототип:**
   *bool reboot_sensor(PROTOCOLS protocol = PROTOCOLS::CURRENT)*

**Описание:**
   *Метод переинициализация CMOS-сенсора устройства, необходимо использовать,* 
   *если сенсор "завис" при воздействии внешней помехи.*
   
**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет отправлена команда на переинициализацию CMOS-сенсора устройства (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 37

   /** @file rf62Xsdk.h */

   /**
    * @brief reboot_sensor - Reboot CMOS-sensor
    *
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return true on success, else - false
    */
   bool reboot_sensor(PROTOCOLS protocol = PROTOCOLS::CURRENT);

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
      
         // Reboot CMOS-sensor
         scanners[i]->reboot_sensor();
         
         // Waiting 100 milliseconds
         std::this_thread::sleep_for(std::chrono::milliseconds(100));

         // some other actions with scanner...

      }
   }

.. _rf62x_wrappers_cpp_rf627smart_send_to_periphery:

**send_to_periphery**
===============================================================================

**Прототип:**
   *bool send_to_periphery(std::string iface_name, std::vector<char> in, std::vector<char>& out, uint32_t timeout)*

**Описание:**
   *Метод отправки данных к периферийному устройству. Под периферией понимаются*
   *"внешние" по отношению к сканеру устройства, например: драйверы шаговых*
   *двигателей, пневматические клапаны, устройства термостатирования и т.д.*
   *Периферия подключается по стандартным интерфейсам, например USART, I2C и т.д.*
   *Команды работы с периферией обеспечивают "прозрачный" обмен, не добавляя и*
   *не убирая никаких данных.*
   
**Параметры:**
   - ``iface_name`` *- Имя интерфейса, на который будут отправляться данные. Если интерфейс не существует, будет возвращена ошибка "RF_WRONG_ARGUMENT". Поддерживаемые значения: "Usart0" - отправка на периферию, подключенную через USART0.*
   - ``in`` *- Данные для отправки. Если данных для отправки нет, будет возвращена ошибка "RF_NO_DATA". Ограничение длины: 1024 байта. Если длина данных превышает лимит, будет возвращена ошибка "RF_OUT_OF_BOUNDS".*
   - ``out`` *- Данные, которые были получены.*
   - ``timeout`` *- Таймаут ответа в мс. Если таймаут равен 0, будут возвращены данные, уже находящиеся в буфере устройства.*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 57

   /** @file rf62Xsdk.h */

   /**
    * @brief send_to_periphery - sending data to a peripheral device.
    * @details Peripherals are devices "external" to the scanner,
    * for example: stepper motors, pneumatic valves, thermostats, etc.
    * Peripherals are connected via standard interfaces such as USART,
    * I2C, etc. Peripheral commands provide transparent exchange without
    * adding or removing any data.
    *
    * @param iface_name The name of the interface where the
    * data will be sent. If the interface does not exist,
    * the error "RF_WRONG_ARGUMENT" will be returned.
    * Supported values:
    * "Usart0" - sending to the peripherals connected via the USART0.
    * @param in The data to be sent. If there is no data to send,
    * then the error "RF_NO_DATA" will be returned.
    * Length limit: 1024 bytes. If the data length is greater than
    * the limit, the error "RF_OUT_OF_BOUNDS" will be returned.
    * @param out The data that was received.
    * @param timeout Response timeout in ms. If the timeout is 0,
    * the data already in the device buffer will be returned.
    *
    * @return true on success, else - false
    */
   bool send_to_periphery(
           std::string iface_name, std::vector<char> in,
           std::vector<char>& out, uint32_t timeout);

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
      
         // Send data to periphery
         std::vector<char> in {'H', 'E', 'L', 'L', 'O'};
         std::vector<char> out;
         bool isSent = scanners[i]->send_to_periphery("Usart0", in, out, 1000);
         if (isSent){
            std::cout << "The data was sent successfully." << std::endl;
            std::cout << "Size of received data: " << out.size() << std::endl;
         }
            
         // some other actions with scanner...

      }
   }

.. _rf62x_wrappers_cpp_rf627smart_receive_from_periphery:

**receive_from_periphery**
===============================================================================

**Прототип:**
   *bool receive_from_periphery(std::string iface_name, uint16_t count, std::vector<char>& out, uint32_t timeout)*

**Описание:**
   *Метод приема данных от периферийного устройства.*
   
**Параметры:**
   - ``iface_name`` *- Имя интерфейса с которого будут прочитаны данные. Если интерфейс не существует, будет возвращена ошибка "RF_WRONG_ARGUMENT". Поддерживаемые значения: "Usart0" - получение с периферии, подключенную через USART0.*
   - ``count`` *- Количество байт, которые ожидается принять. Если* ``count`` *равен 0, то будет возвращена ошибка "RF_NO_DATA". Ограничение длины: 1024 байта. Если длина данных для разового получения превышает лимит, будет возвращена ошибка "RF_OUT_OF_BOUNDS".*
   - ``out`` *- Данные, которые были получены.*
   - ``timeout`` *- Таймаут ответа в мс. Если требуемое количество байт не было принято по истечении данного времени, то будет возвращено принятое количество байт. Если таймаут равен 0, будут возвращены данные, уже находящиеся в буфере устройства.*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 50

   /** @file rf62Xsdk.h */

   /**
    * @brief receive_from_periphery - receiving data from a
    * peripheral device
    *
    * @param iface_name The name of the interface from which the data
    * will be received. If the interface does not exist, the error
    * "RF_WRONG_ARGUMENT" will be returned.
    * Supported values:
    * "Usart0" - sending to the peripherals connected via the USART0.
    * @param count The number of bytes expected to be received
    * @param out The data that was received.
    * @param timeout Response timeout in ms. If the requested number of
    * bytes is not received after this time, will be returned current
    * number of bytes.
    *
    * @return true on success, else - false
    */
   bool receive_from_periphery(
           std::string iface_name, uint16_t count,
           std::vector<char>& out, uint32_t timeout);

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
      
         // Receive data from periphery
         std::vector<char> out;
         scanners[i]->receive_from_periphery("Usart0", 512, out, 1000);
         
         std::cout << "Size of received data: " << out.size() << std::endl;
            
         // some other actions with scanner...

      }
   }