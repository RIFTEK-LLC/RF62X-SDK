.. _compilation_rf62x_sdk_csharp:

Компиляция «обёртки» на C#
-------------------------------------------------------------------------------

Эта «обёртка» представляет собой библиотеку .NET, написанную на языке C#, которая 
может быть использована в приложениях на C#, Visual Basic .NET, C++/CLI и JScript .NET.

Для её использования в проектах .NET разработчик должен собрать или скачать динамическую 
программную библиотеку **rf62Xsdk.dll**, после чего добавить библиотеку к ссылкам 
(references) проекта, а также собрать или скачать **rf62Xcore.dll**, добавив её 
в папку к исполняемому файлу проекта.


.. table:: Последние выпуски:

    +---------------------------------+-----------------------------------------------------------------------------+-------------------------------------------------------------------------------+
    | Platform                        | 64bit                                                                       | Dependencies (x64)                                                            |
    +=================================+=============================================================================+===============================================================================+
    | .NET Framework 4.5 (or above)   | `rf62Xsdk.dll </uploads/8d0e1e7d20de6c00bc6ccc0a9bd0696b/rf62Xsdk.dll>`__   | `rf62Xcore.dll </uploads/8d5bdec0c244ec9afb6c977014dc870e/rf62Xcore.dll>`__   |
    +---------------------------------+-----------------------------------------------------------------------------+-------------------------------------------------------------------------------+

.. _how_to_compile_rf62x_sdk_csharp:

Как скомпилировать
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Библиотека-«обёртка» rf62Xsdk может быть скомпилирован при помощи среды 
разработки Visual Studio.

Во-первых, вы должны загрузить проект (если не сделали этого ранее)

.. code-block:: bash

   git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
   cd RF62X-SDK
   git submodule update --init --recursive

.. note::
   для получения дополнительной информации о шагах загрузки проекта см. `Скачивание проекта <#overview>`__

.. _how_to_compile_rf62x_sdk_csharp_vs:

Visual Studio
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

-  Откройте решение rf62Xsdk.sln по пути **rf62Xwrappers/CSharp/rf62Xsdk** в Visual Studio
-  Скомпилируйте проект

.. _how_to_use_rf62x_sdk_csharp:

Как использовать
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Вы можете открыть примеры использования с помощью **Visual Studio**, для этого:

-   Откройте решение **RF627\_TESTS.sln** из папки
    **rf62Xwrappers/CSharp/RF627\_old**
-   Выберите **x64 Debug** или **x64 Release** в качестве целевой платформы
-   Добвавьте **rf62Xsdk.dll** библиотеку к ссылкам (**references**) проекта
-   Скопируйте **rf62Xcore.dll** в путь к исполняемому файлу проекта
    (**../bin/x64/Debug/** или **../bin/x64/Release/**)
-   Скомпилируйте проект

Помимо приведённых ниже примеров использования библиотеки из решении 
**RF627\_TESTS.sln**, где каждый пример может быть скомпилирован и выполнен 
отдельно, вы также дополнительно можете прочитать документацию на 
библиотеку-«обёртку» на C#, где каждая функция содержит отдельный пример кода. 

.. _how_to_use_rf62x_sdk_csharp_for_search:

Поиск устройств RF62X
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример поиска сканеров серии RF627-old в сети 

.. code-block:: csharp

    using System;
    using System.Collections.Generic;
    using SDK.SCANNERS;

    namespace RF627_search
    {
        class Program
        {
            static void Main(string[] args)
            {
        
               // Start initialization of the library core
               RF62X.SdkInit();

               // Print return rf62X sdk version
               Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
               Console.WriteLine("=========================================");

               // Search for RF627old devices over network
               Console.WriteLine("- Start searching device");
               List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
               Console.WriteLine("+ {0} scanners detected", Scanners.Count);
            
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

               Console.WriteLine("{0}Press any key to end \"Search-test\"", Environment.NewLine);
               Console.ReadKey();

            }
        }
    }

.. _how_to_use_rf62x_sdk_csharp_get_profile:

Получение профиля сканера
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример получения профилей от сканеров серии RF627-old


.. code-block:: csharp

   using System;
   using System.Collections.Generic;
   using SDK.SCANNERS;

   namespace RF627_profile
   {
      class Program
      {
         static void Main(string[] args)
         {
        
            // Start initialization of the library core
            RF62X.SdkInit();


            // Search for RF627old devices over network
            Console.WriteLine("- Start searching device");
            List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);


            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
               RF62X.HelloInfo info = Scanners[i].GetInfo();

               Console.WriteLine("\n\n\nID scanner's list: {0}", i);
               Console.WriteLine("-----------------------------------------");
               Console.WriteLine("Device information: ");
               Console.WriteLine("* Name\t: {0}", info.device_name);
               Console.WriteLine("* Serial\t: {0}", info.serial_number);
               Console.WriteLine("* IP Addr\t: {0}", info.ip_address);

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
            }

            Console.WriteLine("{0}Press any key to end \"Search-test\"", Environment.NewLine);
            Console.ReadKey();
         }
      }
   }

.. _how_to_use_rf62x_sdk_csharp_get_set_params:

Получение и установка параметров
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример получения и изменения имени сканера, установки IP адреса, смены 
состояния лазера (включение или отключение):

.. code-block:: csharp

   using System;
   using System.Collections.Generic;
   using SDK.SCANNERS;

   namespace RF627_params
   {
      class Program
      {
         static void Main(string[] args)
         {
       
            // Start initialization of the library core
            RF62X.SdkInit();

            // Search for RF627old devices over network
            Console.WriteLine("- Start searching device");
            List<RF62X.RF627old> Scanners = RF62X.RF627old.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);

            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
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

               Scanners[i].WriteParams();
            }
            Console.WriteLine("{0}Press any key to end \"Parameters-test\"", Environment.NewLine);
            Console.ReadKey();
         }
      }
   }
