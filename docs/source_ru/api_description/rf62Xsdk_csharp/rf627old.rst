

.. _rf62x_wrappers_description_cpp_rf627old:

*******************************************************************************
Класс rf627old
*******************************************************************************

Данный класс определён в файле ``rf62Xsdk.cs`` и пердоставляет интерфейс 
для работы со сканерами серии RF627Old

.. doxygenclass:: SDK::SCANNERS::RF62X::RF627old

Search()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для поиска устройств RF627 доступных в сети

.. doxygenfunction:: Search

Пример использования:

.. code-block:: c#
   :emphasize-lines: 9

   // Start initialization of the library core
   RF62X.SdkInit();

   // Print return rf62X sdk version
   Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
   Console.WriteLine("=========================================");

   // Search for RF627old devices over network
   List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
   
   // Print count of discovered RF627Old in network by Service Protocol
   Console.WriteLine("Discovered {0} scanners", Scanners.Count);


GetInfo()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения информации о сканере из пакета приветствия (Hello-пакет)

.. doxygenfunction:: GetInfo

Пример использования:

.. code-block:: c#
   :emphasize-lines: 12-31

   // Start initialization of the library core
   RF62X.SdkInit();

   // Search for RF627old devices over network
   List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
   
   // Print count of discovered RF627Old in network by Service Protocol
   Console.WriteLine("Discovered {0} scanners", Scanners.Count);

   for (int i = 0; i < Scanners.Count; i++)
   {
      RF62X.HelloInfo info = Scanners[i].GetInfo();

      Console.WriteLine("\n\n\nID scanner's list: {0}", i);
      Console.WriteLine("-----------------------------------------");
      Console.WriteLine("Device information: ");
      Console.WriteLine("* Name\t: {0}", info.device_name);
      Console.WriteLine("* Serial\t: {0}", info.serial_number);
      Console.WriteLine("* IP Addr\t: {0}", info.ip_address);
      Console.WriteLine("* MAC Addr\t: {0}", info.mac_address);

      Console.WriteLine("Working ranges: ");
      Console.WriteLine("* Zsmr, mm\t: {0}", info.z_smr);
      Console.WriteLine("* Zmr , mm\t: {0}", info.z_mr);
      Console.WriteLine("* Xsmr, mm\t: {0}", info.x_smr);
      Console.WriteLine("* Xemr, mm\t: {0}", info.x_emr);

      Console.WriteLine("\nVersions: ");
      Console.WriteLine("* Firmware\t: {0}", info.firmware_version);
      Console.WriteLine("* Hardware\t: {0}", info.hardware_version);
      Console.WriteLine("-----------------------------------------");
   }

   // Cleanup resources allocated with sdk_init()
   RF62X.SdkCleanup();
   

Connect()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для установки соединения со сканером серии RF627

.. doxygenfunction:: Connect

Пример использования:

.. code-block:: c#
   :emphasize-lines: 13-14

   // Start initialization of the library core
   RF62X.SdkInit();

   // Search for RF627old devices over network
   List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
   
   // Print count of discovered RF627Old in network by Service Protocol
   Console.WriteLine("Discovered {0} scanners", Scanners.Count);

   for (int i = 0; i < Scanners.Count; i++)
   {
      // Establish connection to the RF627 device by Service Protocol.
      if (Scanners[i].Connect())
         Console.WriteLine("Connected to scanner №{0} successfully", i);
   }

   // Cleanup resources allocated with sdk_init()
   RF62X.SdkCleanup();


Disconnect()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для закрытия ранее установленного соединения со сканером серии RF627

.. doxygenfunction:: Disconnect

Пример использования:

.. code-block:: c#
   :emphasize-lines: 19

   // Start initialization of the library core
   RF62X.SdkInit();

   // Search for RF627old devices over network
   List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
   
   // Print count of discovered RF627Old in network by Service Protocol
   Console.WriteLine("Discovered {0} scanners", Scanners.Count);

   // Establish connection to the RF627 device by Service Protocol.
   for (int i = 0; i < Scanners.Count; i++)
      Scanners[i].Connect();

   {
   ...some actions with scanners
   }

   for (int i = 0; i < Scanners.Count; i++)
      Scanners[i].Disconnect();

   
GetProfile()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения профиля со сканеров серии RF627

.. doxygenfunction:: GetProfile

Пример использования:

.. code-block:: c#
   :emphasize-lines: 17

   // Start initialization of the library core
   RF62X.SdkInit();

   // Search for RF627old devices over network
   List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
   
   // Print count of discovered RF627Old in network by Service Protocol
   Console.WriteLine("Discovered {0} scanners", Scanners.Count);

   // foreach over an scanners list
   for (int i = 0; i < Scanners.Count; i++)
   {
      // Establish connection to the RF627 device by Service Protocol.
      Scanners[i].Connect();

      // Get profile from scanner's data stream by Service Protocol.
      RF62X.Profile profile = Scanners[i].GetProfile();
      if (profile.header != null)
      {
         Console.WriteLine("Profile information: ");
         switch (profile.header.data_type)
         {
         case RF62X.PROFILE_TYPE.PIXELS_NORMAL:
            Console.WriteLine("* DataType\t: PIXELS");
            Console.WriteLine("* Count\t: {0}", profile.pixels.Count);
            break;
         case RF62X.PROFILE_TYPE.PROFILE_NORMAL:
            Console.WriteLine("* DataType\t: PROFILE");
            Console.WriteLine("* Size\t: {0}", profile.points.Count);
            break;
         case RF62X.PROFILE_TYPE.PIXELS_INTERPOLATED:
            Console.WriteLine("* DataType\t: PIXELS");
            Console.WriteLine("* Count\t: {0}", profile.pixels.Count);
            break;
         case RF62X.PROFILE_TYPE.PROFILE_INTERPOLATED:
            Console.WriteLine("* DataType\t: PROFILE");
            Console.WriteLine("* Size\t: {0}", profile.points.Count);
            break;
         default:
            break;
         }
         Console.WriteLine("Profile was successfully received!");
         Console.WriteLine("-----------------------------------------");
      }else
      {
         Console.WriteLine("Profile was not received!");
         Console.WriteLine("-----------------------------------------");
      }
      
      // Disconnect from scanner.
      Scanners[i].Disconnect();
   }

   // Cleanup resources allocated with sdk_init()
   RF62X.SdkCleanup();

.. _rf62x_wrappers_cpp_description_rf627old_read_params:

ReadParams()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения текущих параметров сканера. При вызове данной функции SDK вычитывает 
со сканера все актуальные параметры, сохраняя их ввиде «списка параметров» для дальнейшей 
работы.

.. doxygenfunction:: ReadParams

Пример использования:

.. code-block:: c#
   :emphasize-lines: 17

   // Start initialization of the library core
   RF62X.SdkInit();

   // Search for RF627old devices over network
   List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
   
   // Print count of discovered RF627Old in network by Service Protocol
   Console.WriteLine("Discovered {0} scanners", Scanners.Count);

   // foreach over an scanners list
   for (int i = 0; i < Scanners.Count; i++)
   {
      // Establish connection to the RF627 device by Service Protocol.
      Scanners[i].Connect();

      // read params from RF627 device by Service Protocol.
      Scanners[i].ReadParams();

      {
      ...some actions with params
      }

      // Disconnect from scanner.
      Scanners[i].Disconnect();
   }

GetParam()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения конкретного параметра по его имени (ключу). При вызове 
данной функции SDK осуществляет поиск нужного параметра из последних прочитанных 
при вызове функции :ref:`ReadParams`. В случае, если запрашиваемый 
параметр отсутствует в конкретном сканере, функция вернёт null.

.. doxygenfunction:: GetParam(string)

Пример использования:

.. code-block:: c#
   :emphasize-lines: 13, 21, 29

   {
   ...Initialize sdk library
   ...Search for RF627old
   }

   // Establish connection to the RF627 device by Service Protocol.
   Scanners[i].Connect();

   // read params from RF627 device by Service Protocol.
   Scanners[i].ReadParams();

   // Get parameter of Device Name
   RF62X.Param<string> name = Scanners[i].GetParam("user_general_deviceName");
   if (name != null)
   {
      string strName = name.GetValue();
      Console.WriteLine("\n\nCurrent Device Name \t: {0}", strName);
   }

   // Get parameter of Device IP Addr
   RF62X.Param<List<uint>> ipAddr = Scanners[i].GetParam("user_network_ip");
   if (ipAddr != null)
   {
      List<uint> ip = ipAddr.GetValue();
      Console.WriteLine("Current Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);
   }

   // Get parameter of Laser Enabled
   RF62X.Param<uint> laserEnabled = Scanners[i].GetParam("user_laser_enabled");
   if (laserEnabled != null)
   {
      bool isLaserEnabled = Convert.ToBoolean(laserEnabled.GetValue());
      Console.WriteLine("Current Laser State\t: {0}", isLaserEnabled ? "ON" : "OFF");
   }

Для более удобной работы с параметрами можно использовать соответствующие «ключи» 
(ключ имени параметра, тип параметра и доступ к параметру).

.. doxygenfunction:: GetParam(Params.Description)

Для этого в файле ``rt62Xtypes.cs`` находятся ``class``:

.. doxygenclass:: SDK::SCANNERS::RF62X::Params
   :members:
   :protected-members:
   :private-members:
   :undoc-members:
   :outline:
   :no-link:

Пример использования с ключами:

.. code-block:: c#
   :emphasize-lines: 13, 21, 29

   {
   ...Initialize sdk library
   ...Search for RF627old
   }

   // Establish connection to the RF627 device by Service Protocol.
   Scanners[i].Connect();

   // read params from RF627 device by Service Protocol.
   Scanners[i].ReadParams();

   // Get parameter of Device Name
   RF62X.Param<string> name = Scanners[i].GetParam(RF62X.Params.User.General.deviceName);
   if (name != null)
   {
      string strName = name.GetValue();
      Console.WriteLine("\n\nCurrent Device Name \t: {0}", strName);
   }

   // Get parameter of Device IP Addr
   RF62X.Param<List<uint>> ipAddr = Scanners[i].GetParam(RF62X.Params.User.NetWork.ip);
   if (ipAddr != null)
   {
      List<uint> ip = ipAddr.GetValue();
      Console.WriteLine("Current Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);
   }

   // Get parameter of Laser Enabled
   RF62X.Param<uint> laserEnabled = Scanners[i].GetParam(RF62X.Params.User.Laser.enabled);
   if (laserEnabled != null)
   {
      bool isLaserEnabled = Convert.ToBoolean(laserEnabled.GetValue());
      Console.WriteLine("Current Laser State\t: {0}", isLaserEnabled ? "ON" : "OFF");
   }

Для более детального описания каждого параметра и его свойств см. :ref:`rf62x_more_description_params`

SetParam()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция установки конкретного параметра. При вызове данной функции происходит установка 
передаваемого параметра в локальном списке параметров в SDK. Для отправки изменений 
в сканер необходимо вызвать функцию ``write_params``.

.. doxygenfunction:: SetParam(param_t *)

Пример использования:

.. code-block:: c#
   :emphasize-lines: 20-21, 25, 36-37, 41, 52-53, 57, 61

   {
   ...Initialize sdk library
   ...Search for RF627old
   }

   // Establish connection to the RF627 device by Service Protocol.
   Scanners[i].Connect();

   // read params from RF627 device by Service Protocol.
   Scanners[i].ReadParams();

   // Get parameter of Device Name
   RF62X.Param<string> name = Scanners[i].GetParam(RF62X.Params.User.General.deviceName);
   if (name != null)
   {
      string strName = name.GetValue();
      Console.WriteLine("\n\nCurrent Device Name \t: {0}", strName);

      // Add "_TEST" to the ending of the current name
      strName += "_TEST";
      name.SetValue(strName);
      Console.WriteLine("New Device Name \t: {0}", strName);
      Console.WriteLine("-----------------------------------------");

      Scanners[i].SetParam(name);
   }

   // Get parameter of Device IP Addr
   RF62X.Param<List<uint>> ipAddr = Scanners[i].GetParam(RF62X.Params.User.NetWork.ip);
   if (ipAddr != null)
   {
      List<uint> ip = ipAddr.GetValue();
      Console.WriteLine("Current Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);

      // Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
      ip[3]++;                    
      ipAddr.SetValue(ip);
      Console.WriteLine("New Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);
      Console.WriteLine("-----------------------------------------");

      Scanners[i].SetParam(ipAddr);
   }

   // Get parameter of Laser Enabled
   RF62X.Param<uint> laserEnabled = Scanners[i].GetParam(RF62X.Params.User.Laser.enabled);
   if (laserEnabled != null)
   {
      bool isLaserEnabled = Convert.ToBoolean(laserEnabled.GetValue());
      Console.WriteLine("Current Laser State\t: {0}", isLaserEnabled ? "ON" : "OFF");

      // Change the current state to the opposite
      isLaserEnabled = !isLaserEnabled;
      laserEnabled.SetValue((uint)(Convert.ToUInt32(isLaserEnabled)));
      Console.WriteLine("New Laser State\t\t: {0}", isLaserEnabled ? "ON" : "OFF");
      Console.WriteLine("-----------------------------------------");

      Scanners[i].SetParam(laserEnabled);
   }

   //  Write changes parameters to the device's memory
   Scanners[i].WriteParams();



WriteParams()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция записи локальных параметров из SDK в сканер. При вызове данной функции 
происходит отправка списка локальных параметров из SDK в сканер.

.. doxygenfunction:: WriteParams

Пример использования:

.. code-block:: cpp
   :emphasize-lines: 17

   {
   ...Initialize sdk library
   ...Search for RF627old
   }

   // Establish connection to the RF627 device by Service Protocol.
   Scanners[i].Connect();

   // read params from RF627 device by Service Protocol.
   Scanners[i].ReadParams();

   {
   ...Some steps to change scanner's parameters
   }

   //  Write changes parameters to the device's memory
   Scanners[i].WriteParams();

   // Disconnect from scanner.
   Scanners[i].Disconnect();
   