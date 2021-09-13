.. _creating_project_rf62Xsdk_csharp:

*******************************************************************************
Создание проекта C#
*******************************************************************************

.. _creating_project_rf62Xsdk_csharp_vs_with_libs:

Visual Studio + RF62X-SDK в качестве библиотеки
===============================================================================

Для создания нового проекта в Visual Studio с использованием 
динамической библиотеки SDK необходимо выполнить следующий порядок 
действий:

-   Откройте Visual Studio и выберите **Create a new project**, 
    затем выберите **Empty Project** и нажмите кнопку **Next**
-   Введите имя проекта в поле **Project Name** (например RF627_search) и укажите путь к папке с проетом 
    в поле **Project Location**, после ввода нажмите кнопку **Next**
-   Измените файл ``Program.cs`` проекта, как показано ниже:

.. code-block:: c#

   using System;
   using System.Collections.Generic;
   using SDK.SCANNERS;

   namespace RF627_search
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
            Console.WriteLine("Was found\t: {0} RF627-Smart", list.Count);
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
         }
      }
   }

-   Выберите тип (*Debug* или *Release*) и разрядность (*x64* или *x86*) целевой платформы.
-   Скачайте архив библиотек для C# (смотреть `последние выпуски RF62X-SDK библиотек <https://github.com/RIFTEK-LLC/RF62X-SDK/releases/latest>`__)  
-   Откройте **Project > Add References**, нажмите кнопку **Browse...** и подключите библиотеку **RF62X-SDK.dll** из скачанного архива в проект.
-   Скомпилируйте проект.
-   Скопируйте библиотеки из скаченного архива в папке ``Dependencies`` в каталог к исполняемому файлу проекта (``../bin/x64/Debug/`` или ``../bin/x64/Release/``).
-   Запустите проект.