

.. _rf62x_wrappers_csharp_rf627smart:

*******************************************************************************
Класс rf627smart
*******************************************************************************

Данный класс определён в файле ``RF62X-SDK.cs`` и предоставляет интерфейс 
для работы со сканерами серии RF627 v2.x.x

.. _rf62x_wrappers_csharp_rf627smart_search:

**Search**
===============================================================================

**Прототип:**
   *static List<RF627smart> Search(uint timeout = 300, PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод поиска устройств RF62X v2.x.x в сети* 

**Параметры:**
   - ``timeout`` *- Время поиска на каждом Ethernet интерфейсе (мс).*
   - ``protocol`` *- Тип протокола, по которому будет осуществляться поиск (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   *Список обнаруженных в сети сканеров серии RF627 v2.x.x.

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 31

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Search for RF627smart devices over network
   /// </summary>
   /// <param name="timeout">Search timeout for each Ethernet interface</param>
   /// <param name="protocol">Protocol's type</param>
   /// <returns>List of RF627smart devices</returns>
   static List<RF627smart> Search(
         uint timeout = 300, PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            // Print count of discovered rf627smart in network
            Console.WriteLine("Was found\t: {0} RF627-Smart", list.Count);
            Console.WriteLine("=========================================");

            // some code...

            // Cleanup resources allocated with SdkInit()
            RF62X.SdkCleanup(); 
         }
      }
   }

.. _rf62x_wrappers_csharp_rf627smart_get_info:

**GetInfo**
===============================================================================

**Прототип:**
   *HelloInfo GetInfo(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод получения информации о сканере из пакета приветствия (Hello-пакет)*

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет осуществляться поиск (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``HelloInfo`` *в случае успеха*

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 33, 38-41, 44-47, 50-51

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Get information about scanner from hello packet
   /// </summary>
   /// <param name="protocol">protocol’s type</param>
   /// <returns>Hello_info on success</returns>
   HelloInfo GetInfo(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               RF62X.HelloInfo info = list[i].GetInfo();

               Console.WriteLine("\n\nID scanner's list: {0}", i);
               Console.WriteLine("-----------------------------------------");
               Console.WriteLine("Device information: ");
               Console.WriteLine("* Name\t: {0}", info.device_name);
               Console.WriteLine("* Serial\t: {0}", info.serial_number);
               Console.WriteLine("* IP Addr\t: {0}", info.ip_address);
               Console.WriteLine("* MAC Addr\t: {0}", info.mac_address);

               Console.WriteLine("\nWorking ranges: ");
               Console.WriteLine("* Zsmr, mm\t: {0}", info.z_smr);
               Console.WriteLine("* Zmr , mm\t: {0}", info.z_mr);
               Console.WriteLine("* Xsmr, mm\t: {0}", info.x_smr);
               Console.WriteLine("* Xemr, mm\t: {0}", info.x_emr);

               Console.WriteLine("\nVersions: ");
               Console.WriteLine("* Firmware\t: {0}", info.firmware_version);
               Console.WriteLine("* Hardware\t: {0}", info.hardware_version);
               Console.WriteLine("-----------------------------------------");
            }
         }
      }
   }


.. _rf62x_wrappers_csharp_rf627smart_connect:

**Connect**
===============================================================================

**Прототип:**
   *bool Connect(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод установки соединения со сканером* 

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет выполнено подключение (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 34

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Establish connection to the RF627smart device
   /// </summary>
   /// <param name="protocol">protocol’s type</param>
   /// <returns>true on success</returns>
   bool Connect(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               // Establish connection to the RF627 device.
               bool isConnected = list[i].Connect();
               if (!isConnected){
                  Console.WriteLine("Failed to connect to scanner!");
                  continue;
               }

               // some actions with scanner...
            }
         }
      }
   }

.. _rf62x_wrappers_csharp_rf627smart_disconnect:

**Disconnect**
===============================================================================

**Прототип:**
   *bool Disconnect(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод закрытия ранее установленного соединения со сканером* 

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет выполнено отключение (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 43

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Close connection to the device
   /// </summary>
   /// <param name="protocol">protocol’s type</param>
   /// <returns>true on success</returns>
   bool Disconnect(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               // Establish connection to the RF627 device.
               bool isConnected = list[i].Connect();
               if (!isConnected){
                  Console.WriteLine("Failed to connect to scanner!");
                  continue;
               }

               // some actions with scanner...

               // Disconnect from scanner.
               list[i].Disconnect();
            }
         }
      }
   }

.. _rf62x_wrappers_csharp_rf627smart_check_connection:

**CheckConnection**
===============================================================================

**Прототип:**
   *bool CheckConnection(uint timeout = 300, PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод проверки доступности сканера в сети (после подключения к нему)* 

**Параметры:**
   - ``timeout`` *- Время проверки соединения со сканером (мс).*
   - ``protocol`` *- Тип протокола, по которому будет выполнена проверка (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 43

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Check connection with RF627smart device
   /// </summary>
   /// <param name="timeout">Connection check timeout</param>
   /// <param name="protocol">Protocol’s type</param>
   /// <returns>true on success</returns>
   bool CheckConnection(
         uint timeout = 300, PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               // Establish connection to the RF627 device.
               bool isConnected = list[i].Connect();
               if (!isConnected){
                  Console.WriteLine("Failed to connect to scanner!");
                  continue;
               }

               // Check connection with device
               bool isAvailable = list[i].CheckConnection(500);
               if (!isAvailable){
                  Console.WriteLine("Scanner is not available now.");
                  Console.WriteLine("Please call back later!");
                  continue;
               }

               // some actions with scanner...
            }
         }
      }
   }
  
.. _rf62x_wrappers_csharp_rf627smart_get_profile:

**GetProfile**
===============================================================================

**Прототип:**
   *Profile2D GetProfile(bool zero_points = true, bool realtime = true, PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод получения результатов измерений* 

**Параметры:**
   - ``zero_points`` *- Включать нулевые точки в возвращаемом профиле.*
   - ``realtime`` *- Получение профиля в реальном времени (буферизация отключена).*
   - ``protocol`` *- Тип протокола, по которому будет получен профиль (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``Profile2D`` *при успехе, иначе -* ``null``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 46

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Get 2D measurement from scanner’s data stream
   /// </summary>
   /// <param name="zero_points">include zero points in return Profile</param>
   /// <param name="realtime">Enable getting profile in real time</param>
   /// <param name="protocol">protocol’s type</param>
   /// <returns>Profile</returns>
   Profile2D GetProfile(
         bool zero_points = true, bool realtime = true,
         PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               // Establish connection to the RF627 device.
               list[i].Connect();
               
               // Get profile from scanner's data stream by Service Protocol.
               RF62X.Profile2D profile = null;
               bool zero_points = true;
               bool realtime = true;

               // Get profile from scanner
               profile = list[i].GetProfile(zero_points, realtime);
               if (profile != null) {
                  Console.WriteLine("Profile was successfully received!");
               }else
                  Console.WriteLine("Profile was not received!");
            }
         }
      }
   }

.. _rf62x_wrappers_csharp_rf627smart_get_frame:

**GetFrame**
===============================================================================

**Прототип:**
   *Frame GetFrame(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод получения кадров видео с матрицы сканера* 

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будет получен кадр (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``Frame`` *при успехе, иначе -* ``null``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 37

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Get RAW frame from scanner
   /// </summary>
   /// <param name="protocol">protocol’s type</param>
   /// <returns>Frame</returns>
   Frame GetFrame(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               // Establish connection to the RF627 device.
               list[i].Connect();
               
               // Get Frame from scanner.
               RF62X.Frame frame = list[i].GetFrame();
               if (frame != null) {
                  Console.WriteLine("Frame was successfully received!");
               }else
                  Console.WriteLine("Frame was not received!");
            }
         }
      }
   }


.. _rf62x_wrappers_csharp_rf627smart_read_params:

**ReadParams**
===============================================================================

**Прототип:**
   *bool ReadParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод получения текущих параметров сканера. При вызове данного метода SDK вычитывает*
   *со сканера все актуальные параметры, сохраняя их в виде «списка параметров» для дальнейшей*
   *работы во внутренней памяти SDK.* 

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будут прочитаны параметры (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 37

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Read parameters from device to internal structure.
   /// </summary>
   /// <param name="protocol">protocol’s type</param>
   /// <returns>true on success</returns>
   bool ReadParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               // Establish connection to the RF627 device.
               list[i].Connect();
               
               // Read params from RF627 device.
               bool isRead = list[i].ReadParams();
               if (isRead) {
                  Console.WriteLine("Scanner parameters were read!");
               }else
                  Console.WriteLine("Scanner parameters were not read!");
            }
         }
      }
   }

.. _rf62x_wrappers_csharp_rf627smart_get_param:

**GetParam**
===============================================================================

**Прототип:**
   *dynamic GetParam(string nameKey);*

**Описание:**
   *Метод получения конкретного параметра по его имени (ключу). При вызове* 
   *данного метода SDK осуществляет поиск нужного параметра из последних прочитанных*
   *при вызове метода* :ref:`rf62x_wrappers_csharp_rf627smart_read_params` *. В случае, если* 
   *запрашиваемый параметр отсутствует в конкретном сканере, функция вернёт null.* 

**Параметры:**
   - ``param_name`` *- Имя (ключ) параметра.*
   
**Возвращаемое значение:**
   ``Parameter`` *при успехе, иначе -* ``null``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 39-40, 46-47

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Search parameters by his name
   /// </summary>
   /// <param name="nameKey">name of parameter</param>
   /// <returns>param on success, else - null</returns>
   dynamic GetParam(string nameKey);

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               // Establish connection to the RF627 device.
               list[i].Connect();
               
               // Read params from RF627 device.
               list[i].ReadParams();
               
               RF62X.Parameter<string> name = 
                     list[i].GetParam("user_general_deviceName");
               if (name != null) {
                  string str_name = name.GetValue();
                  Console.WriteLine("Current Device Name \t: {0}", str_name);
               }

               RF62X.Parameter<uint> framerate = 
                     list[i].GetParam("user_sensor_framerate");
               if (framerate != null) {
                  uint framerate_value = framerate.GetValue();
                  Console.WriteLine("Current FPS\t: {0}", framerate_value);
               }
            }
         }
      }
   }

.. note::
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__

.. _rf62x_wrappers_csharp_rf627smart_set_param:

**SetParam**
===============================================================================

**Прототип:**
   *bool SetParam(string name, dynamic value);*

**Описание:**
   *Метод установки конкретного параметра. При вызове данного метода происходит*
   установка параметра в списке параметров во внутренней памяти SDK.*
   *Для отправки изменений в сканер необходимо вызвать метод* :ref:`rf62x_wrappers_csharp_rf627smart_write_params` *.*

**Параметры:**
   - ``param_name`` *- Имя (ключ) параметра.*
   - ``value`` *- Новое значение параметра
   
**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 41, 44

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Set parameter by name
   /// </summary>
   /// <param name="param">Name of parameter</param>
   /// <param name="value">Value to set</param>
   /// <returns>true on success, else - false</returns>
   bool SetParam(string name, dynamic value)

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               // Establish connection to the RF627 device.
               list[i].Connect();
               
               // Read params from RF627 device.
               list[i].ReadParams();
               
               // Set parameter of Device Name
               list[i].SetParam("user_general_deviceName", "RF627 New Name");

               // Set parameter of Sensor Framerate
               list[i].SetParam("user_sensor_framerate", 100);

               // some actions with other parameters...

            }
         }
      }
   }

.. note::
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__

.. _rf62x_wrappers_csharp_rf627smart_write_params:

**WriteParams**
===============================================================================

**Прототип:**
   *bool WriteParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод передачи параметров из внутренней памяти SDK в сканер.* 
   *При вызове данного метода происходит отправка изменённых параметров в сканер*

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будут отправлена команда на установку параметров (Service Protocol, ENIP, Modbus-TCP)*
  
**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 44

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Send current parameters to device
   /// </summary>
   /// <param name="protocol">protocol’s type</param>
   /// <returns>true on success</returns>
   bool WriteParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               list[i].Connect();
               list[i].ReadParams();
               
               // Set parameter of Device Name
               list[i].SetParam("user_general_deviceName", "RF627 New Name");
               // Set parameter of Sensor Framerate
               list[i].SetParam("user_sensor_framerate", 100);

               // some actions with other parameters...

               // Apply changed parameters to the device
               bool isApplied = list[i].WriteParams();
               if (isApplied) 
                  Console.WriteLine("Scanner parameters were applied!");
               else 
                  Console.WriteLine("Scanner parameters were not applied!");
            }
         }
      }
   }


.. _rf62x_wrappers_csharp_rf627smart_save_params:

**SaveParams**
===============================================================================

**Прототип:**
   *bool SaveParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод сохранения параметров сканер во внутреннюю память устройства.* 
   *Сохраненные параметры также будут использоваться после перезапуске устройства* 
   *или после смены(обновления) прошивки.*

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будут отправлена команда на установку параметров (Service Protocol, ENIP, Modbus-TCP)*
  
**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 44

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Save changes to device's memory.
   /// The saved parameters will also be used if the device 
   /// is restarted or even if the firmware is updated.
   /// </summary>
   /// <param name="protocol">protocol’s type</param>
   /// <returns>true on success</returns>
   bool SaveParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               list[i].Connect();
               list[i].ReadParams();
               
               // After changing some parameters...

               // Apply changed parameters to the device
               list[i].WriteParams();

               // Save current parameters in the device memory
               bool isSaved = list[i].SaveParams();
               if (isSaved) 
                  Console.WriteLine("Scanner parameters were applied!");
               else 
                  Console.WriteLine("Scanner parameters were not applied!");
            }
         }
      }
   }

.. _rf62x_wrappers_csharp_rf627smart_load_recovery_params:

**LoadRecoveryParams**
===============================================================================

**Прототип:**
   *bool SaveParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);*

**Описание:**
   *Метод загрузки значений параметров устройства из области восстановления.* 
   *Загруженные значения будут записаны в пользовательскую область*

**Параметры:**
   - ``protocol`` *- Тип протокола, по которому будут отправлена команда на установку параметров (Service Protocol, ENIP, Modbus-TCP)*
  
**Возвращаемое значение:**
   ``true`` *при успехе, иначе -* ``false``

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 37

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// Loading parameters from recovery area. 
   /// The device will automatically reboot.
   /// </summary>
   /// <param name="protocol">protocol’s type</param>
   /// <returns>true on success</returns>
   bool LoadRecoveryParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE);

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            RF62X.SdkInit();
           
            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            for (int i = 0; i < list.Count; i++)
            {
               list[i].Connect();

               // Load parameters from recovery area
               bool isLoaded = list[i].LoadRecoveryParams();
               if (isLoaded) 
                  Console.WriteLine("Recovery parameters loaded successfully!");
               else 
                  Console.WriteLine("Recovery parameters were not loaded!");
            }
         }
      }
   }
