.. _how_to_use_rf62x_sdk_csharp:

*******************************************************************************
Примеры для С#
*******************************************************************************

.. _how_to_use_rf62x_sdk_csharp_for_search:

Поиск устройств RF62X
===============================================================================

Ниже приведен пример поиска сканеров серии RF627 v2.x.x:

.. code-block:: c#

   using System;
   using System.Collections.Generic;
   using SDK.SCANNERS;

   namespace SEARCH_EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            Console.WriteLine("#########################################");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#         Search Example v2.x.x         #");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#########################################");

            // Initialize sdk library
            RF62X.SdkInit();

            // Print return rf62X sdk version
            Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
            Console.WriteLine("=========================================");

            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            // Print count of discovered rf627smart in network
            Console.WriteLine("Was found\t: {0} RF627 v2.x.x", list.Count);
            Console.WriteLine("=========================================");


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

            // Cleanup resources allocated with SdkInit()
            RF62X.SdkCleanup();

            Console.WriteLine("Press any key to close this window...");
            Console.ReadKey();
         }
      }
   }

Ниже приведён результат вывода приложения при успешном обнаружении сканера в сети:

.. code-block:: txt

   #########################################
   #                                       #
   #         Search Example v2.x.x         #
   #                                       #
   #########################################
   SDK version: 2.17.2
   =========================================
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.2.104
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x

   ID scanner in list: 0
   -----------------------------------------
   Device information:
   * Name          : RF627 scanner
   * Serial        : 190068
   * IP Addr       : 192.168.1.30
   * MAC Addr      : 00:0A:35:6E:07:F5

   Working ranges:
   * Zsmr, mm      : 70
   * Zmr , mm      : 50
   * Xsmr, mm      : 30
   * Xemr, mm      : 42

   Versions:
   * Firmware      : 2.7.1
   * Hardware      : 18.6.20
   -----------------------------------------
   Press any key to close this window...

Вы можете открыть и скомпилировать этот пример с помощью **Visual Studio**:

-  Используя Visual Studio откройте из папки **RF62X-SDK/Examples/CSharp/RF627_smart** проект `RF627_TESTS`.
-  Укажите целевую платформу **x64 Debug** или **x64 Release** 
-  Скомпилируйте **SEARCH\_EXAMPLE**
-  Перед запуском скачайте архив библиотек для C# (смотреть `последние выпуски RF62X-SDK библиотек <https://github.com/RIFTEK-LLC/RF62X-SDK/releases/latest>`__)  
   и скопируйте из архива в папке ``Dependencies`` все файлы с именем **libRF62X-SDK** в 
   папку к исполняемому файлу проекта (``../bin/x64/Debug/`` или ``../bin/x64/Release/``)
-  Запустите пример

.. _how_to_use_rf62x_sdk_csharp_get_profile:

Получение профиля сканера
===============================================================================

Ниже приведен пример получение профиля со сканера серии RF627 v2.x.x:

.. code-block:: c#

   using System;
   using System.Collections.Generic;
   using SDK.SCANNERS;

   namespace SEARCH_EXAMPLE
   {
      class Program
      {

         public static uint profileСount = 0;
         public static uint profileLost = 0;
         public static bool isReceiveRun = true;
         public static void receive_profiles(RF62X.RF627smart scanner)
         {
            // Get profile from scanner's data stream by Service Protocol.
            RF62X.Profile2D profile = null;
            bool zero_points = true;
            bool realtime = false;

            uint last_index = 0;
            bool first_profile = true;
            while (true)
               if ((profile = scanner.GetProfile(zero_points, realtime)) != null)
               {
                  if (first_profile)
                  {
                     last_index = profile.header.measure_count;
                     first_profile = false;
                  }
                  else
                  {
                     profileСount++;
                     if (profile.header.measure_count - last_index > 1)
                        profileLost+=(profile.header.measure_count - last_index);
                     last_index = profile.header.measure_count;
                  }
               }
               else
               {
                  Console.WriteLine("Profile was not received!");
                  Console.WriteLine("-----------------------------------------");
               }
         }

         static void Main(string[] args)
         {
            Console.WriteLine("#########################################");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#         Profile Example v2.x.x        #");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#########################################");

            // Initialize sdk library
            RF62X.SdkInit();

            // Print return rf62X sdk version
            Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
            Console.WriteLine("=========================================");

            // Search for RF627smart devices over network
            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

            // Print count of discovered rf627smart in network
            Console.WriteLine("Was found\t: {0} RF627-Smart", list.Count);
            Console.WriteLine("=========================================");

            int index = -1;
            if (list.Count > 1)
            {
               Console.WriteLine("Select scanner for test: ");
               for (int i = 0; i < list.Count; i++)
                  Console.WriteLine("{0}. Serial: {1}", i, 
                                    list[i].GetInfo().serial_number);
               index = Convert.ToInt32(Console.ReadLine());
            }
            else if (list.Count == 1)
               index = 0;

                        if (index == -1)
                return;

            RF62X.HelloInfo info = list[index].GetInfo();

            Console.WriteLine("-----------------------------------------");
            Console.WriteLine("Device information: ");
            Console.WriteLine("* Name  \t: {0}", info.device_name);
            Console.WriteLine("* Serial\t: {0}", info.serial_number);
            Console.WriteLine("* IP Addr\t: {0}", info.ip_address);
            Console.WriteLine("-----------------------------------------");

            // Establish connection to the RF627 device by Service Protocol.
            bool is_connected = list[index].Connect();

            if (is_connected)
            {
               Thread receiver = new Thread(() => receive_profiles(list[index]));
               isReceiveRun = true;
               receiver.Start();

               Console.WriteLine("Thread of receiving profiles started");
               Console.WriteLine("For interrupt receiving press \"Ctrl+C\"");

               bool isRun = true;
               Console.CancelKeyPress += delegate 
                  (object sender, ConsoleCancelEventArgs consoleArgs) {
                  consoleArgs.Cancel = true;
                  isRun = false;
                  isReceiveRun = false;
               };

               while (isRun)
               {
                  Thread.Sleep(1000);
                  Console.WriteLine("FPS: {0}, Lost: {1}", 
                                    Program.profileСount, profileLost);
                  profileLost = 0;
                  profileСount = 0;
               }

               receiver.Join();
               Console.WriteLine("Thread of receiving profiles interrupted");
               Console.WriteLine("-----------------------------------------");
            }

            // Cleanup resources allocated with sdk_init()
            RF62X.SdkCleanup();

            Console.WriteLine("Press any key to close this window...");
            Console.ReadKey();
         }
      }
   }

Ниже приведён результат вывода приложения при успешном получении профиля:

.. code-block:: txt

   #########################################
   #                                       #
   #         Profile Example v2.x.x        #
   #                                       #
   #########################################
   SDK version: 2.17.2
   =========================================
   Search scanners from:
   * IP Address   : 192.168.1.2
   * Netmask      : 255.255.255.0
   Discovered     : 1 RF627
   -----------------------------------------
   Search scanners from:
   * IP Address   : 192.168.2.104
   * Netmask      : 255.255.255.0
   Discovered     : 0 RF627
   -----------------------------------------
   Was found      : 1 RF627 v2.x.x
   =========================================
   -----------------------------------------
   Device information:
   * Name          : RF627 scanner
   * Serial        : 190068
   * IP Addr       : 192.168.1.30
   -----------------------------------------
   Thread of receiving profiles started
   For interrupt receiving press "Ctrl+C"
   FPS: 494, Lost: 0
   FPS: 490, Lost: 0
   FPS: 491, Lost: 0
   Thread of receiving profiles interrupted
   -----------------------------------------
   Press any key to close this window...

Вы можете открыть и скомпилировать этот пример с помощью **Visual Studio**:

-  Используя Visual Studio откройте из папки **RF62X-SDK/Examples/CSharp/RF627_smart** проект `RF627_TESTS`.
-  Укажите целевую платформу **x64 Debug** или **x64 Release** 
-  Скомпилируйте **PROFILE\_EXAMPLE**
-  Перед запуском скачайте архив библиотек для C# (смотреть `последние выпуски RF62X-SDK библиотек <https://github.com/RIFTEK-LLC/RF62X-SDK/releases/latest>`__)  
   и скопируйте из архива в папке ``Dependencies`` все файлы с именем **libRF62X-SDK** в 
   папку к исполняемому файлу проекта (``../bin/x64/Debug/`` или ``../bin/x64/Release/``)
-  Запустите пример