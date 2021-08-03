using System;
using System.Collections.Generic;
using System.Threading;
using SDK.SCANNERS;

namespace PROFILE_EXAMPLE
{
    class Program
    {
        public static uint profile_count;
        public static uint profile_lost;
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
                        profile_count++;
                        if (profile.header.measure_count - last_index > 1)
                            profile_lost += (profile.header.measure_count - last_index);
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

            // Print count of discovered rf627smart in network by Service Protocol
            Console.WriteLine("Was found\t: {0} RF627-Smart", list.Count);
            Console.WriteLine("=========================================");

            int index = -1;
            if (list.Count > 1)
            {
                Console.WriteLine("Select scanner for test: ");
                for (int i = 0; i < list.Count; i++)
                    Console.WriteLine("{0}. Serial: {1}", i, list[i].GetInfo().serial_number);
                index = Convert.ToInt32(Console.ReadLine());
            }
            else if (list.Count == 1)
                index = 0;


            if (index != -1)
            {
                RF62X.HelloInfo info = list[index].GetInfo();

                Console.WriteLine("-----------------------------------------");
                Console.WriteLine("Device information: ");
                Console.WriteLine("* Name\t: {0}", info.device_name);
                Console.WriteLine("* Serial\t: {0}", info.serial_number);
                Console.WriteLine("* IP Addr\t: {0}", info.ip_address);

                // Establish connection to the RF627 device by Service Protocol.
                bool is_connected = list[index].Connect();

                if (is_connected)
                {
                    profile_count = 0;
                    profile_lost = 0;
                    Thread receiver = new Thread(() => receive_profiles(list[index]));
                    receiver.Start();

                    while (true)
                    {
                        Thread.Sleep(1000);
                        Console.WriteLine("FPS: {0}, Lost: {1}", Program.profile_count, profile_lost);
                        profile_lost = 0;
                        profile_count = 0;
                        list[index].RebootDevice();
                    }

                }

                Console.WriteLine("{0}Press any key to end \"Profile Example\"", Environment.NewLine);
                Console.ReadKey();
            }

            // Cleanup resources allocated with sdk_init()
            RF62X.SdkCleanup();
        }
    }
}
