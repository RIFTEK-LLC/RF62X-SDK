using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace DUMP_EXAMPLE
{
    class Program
    {
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


            for (int i = 0; i < list.Count; i++)
            {
                RF62X.HelloInfo info = list[i].GetInfo();

                Console.WriteLine("\n\nID scanner's list: {0}", i);
                Console.WriteLine("-----------------------------------------");
                Console.WriteLine("Device information: ");
                Console.WriteLine("* Name\t: {0}", info.device_name);
                Console.WriteLine("* Serial\t: {0}", info.serial_number);
                Console.WriteLine("* IP Addr\t: {0}", info.ip_address);

                // Establish connection to the RF627 device by Service Protocol.
                bool is_connected = list[i].Connect();

                if (is_connected)
                {
                    uint count_of_profiles = 1000;
                    list[i].StartDumpRecording(count_of_profiles);

                    uint size = 0;
                    do
                    {
                        list[i].ReadParams();
                        size = list[i].GetParam("user_dump_size").GetValue();
                        Console.WriteLine("Current profiles in the dump: {0}", size);
                    } while (size < count_of_profiles);

                    List<RF62X.Profile2D> dump =
                            list[i].GetDumpsProfiles(0, count_of_profiles);

                    Console.WriteLine("{0} Profiles were received!", dump.Count);
                    Console.WriteLine("-----------------------------------------");
                }
                else
                {
                    Console.WriteLine("Dump was not received!");
                    Console.WriteLine("-----------------------------------------");
                }
                // Disconnect from scanner.
                list[i].Disconnect();
            }
            Console.WriteLine("{0}Press any key to end \"Profile Example\"", Environment.NewLine);
            Console.ReadKey();

            // Cleanup resources allocated with sdk_init()
            RF62X.SdkCleanup();
        }

    }
}
