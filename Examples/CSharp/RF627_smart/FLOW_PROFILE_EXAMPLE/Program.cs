using System;
using System.Collections.Generic;
using System.Threading;
using SDK.SCANNERS;

namespace FLOW_PROFILE_EXAMPLE
{
    internal class Program
    {
        private static uint profileCount;
        private static uint profileLost;
        private static bool isReceiveRun = true;

        private static void ReceiveProfiles(RF62X.RF627smart scanner)
        {
            RF62X.Profile2D profile = null;
            bool zeroPoints = true;
            bool realtime = false;

            uint lastIndex = 0;
            bool firstProfile = true;

            while (isReceiveRun)
            {
                profile = scanner.GetProfile(zeroPoints, realtime);
                if (profile != null)
                {
                    if (firstProfile)
                    {
                        lastIndex = profile.header.measure_count;
                        firstProfile = false;
                    }
                    else
                    {
                        profileCount++;
                        if (profile.header.measure_count - lastIndex > 1)
                            profileLost += profile.header.measure_count - lastIndex;

                        lastIndex = profile.header.measure_count;
                    }
                }
                else
                {
                    Console.WriteLine("Profile was not received!");
                    Console.WriteLine("-----------------------------------------");
                }
            }
        }

        private static int SelectScanner(List<RF62X.RF627smart> list)
        {
            if (list.Count == 0)
                return -1;

            if (list.Count == 1)
                return 0;

            Console.WriteLine("Select scanner for test: ");
            for (int i = 0; i < list.Count; i++)
                Console.WriteLine("{0}. Serial: {1}", i, list[i].GetInfo().serial_number);

            if (int.TryParse(Console.ReadLine(), out int index) &&
                index >= 0 &&
                index < list.Count)
            {
                return index;
            }

            return -1;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("#########################################");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#      Flow Profile Example v2.x.x      #");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#########################################");

            RF62X.SdkInit();
            try
            {
                Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
                Console.WriteLine("=========================================");

                List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

                Console.WriteLine("Was found\t: {0} RF627 v2.x.x", list.Count);
                Console.WriteLine("=========================================");

                int index = SelectScanner(list);
                if (index < 0)
                    return;

                RF62X.HelloInfo info = list[index].GetInfo();

                Console.WriteLine("-----------------------------------------");
                Console.WriteLine("Device information: ");
                Console.WriteLine("* Name  \t: {0}", info.device_name);
                Console.WriteLine("* Serial\t: {0}", info.serial_number);
                Console.WriteLine("* IP Addr\t: {0}", info.ip_address);
                Console.WriteLine("-----------------------------------------");

                if (!list[index].Connect())
                    return;

                try
                {
                    Thread receiver = new Thread(() => ReceiveProfiles(list[index]));
                    isReceiveRun = true;
                    profileCount = 0;
                    profileLost = 0;
                    receiver.Start();

                    Console.WriteLine("Thread of receiving profiles started");
                    Console.WriteLine("For interrupt receiving press \"Ctrl+C\"");

                    bool isRun = true;
                    Console.CancelKeyPress += delegate (object sender, ConsoleCancelEventArgs consoleArgs)
                    {
                        consoleArgs.Cancel = true;
                        isRun = false;
                        isReceiveRun = false;
                    };

                    while (isRun)
                    {
                        Thread.Sleep(1000);
                        Console.WriteLine("FPS: {0}, Lost: {1}", profileCount, profileLost);
                        profileCount = 0;
                        profileLost = 0;
                    }

                    receiver.Join();
                    Console.WriteLine("Thread of receiving profiles interrupted");
                    Console.WriteLine("-----------------------------------------");
                }
                finally
                {
                    list[index].Disconnect();
                }
            }
            finally
            {
                RF62X.SdkCleanup();
            }

            Console.WriteLine("Press any key to close this window...");
            Console.ReadKey();
        }
    }
}
