using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace PROFILE_EXAMPLE
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

                // Get profile from scanner's data stream by Service Protocol.
                RF62X.Profile2D profile = null;
                bool zero_points = true;
                bool realtime = true;
                int count = 0;
                while (true)
                {
                    if (is_connected && (profile = list[i].GetProfile(zero_points, realtime)) != null)
                    {
                        Console.WriteLine("Profile information: ");
                        switch (profile.header.data_type)
                        {
                            case RF62X.PROFILE_DATA_TYPES.PIXELS:
                                Console.WriteLine("* DataType\t: PIXELS");
                                Console.WriteLine("* Count\t: {0}", profile.pixels.Count);
                                break;
                            case RF62X.PROFILE_DATA_TYPES.PROFILE:
                                Console.WriteLine("* DataType\t: PROFILE");
                                Console.WriteLine("* Size\t: {0}", profile.points.Count);
                                break;
                            case RF62X.PROFILE_DATA_TYPES.PIXELS_INTRP:
                                Console.WriteLine("* DataType\t: PIXELS_INTRP");
                                Console.WriteLine("* Count\t: {0}", profile.pixels.Count);
                                break;
                            case RF62X.PROFILE_DATA_TYPES.PROFILE_INTRP:
                                Console.WriteLine("* DataType\t: PROFILE_INTRP");
                                Console.WriteLine("* Size\t: {0}", profile.points.Count);
                                break;
                            default:
                                break;
                        }
                        count++;
                        Console.WriteLine("Profile was successfully received: {0}", count);
                        Console.WriteLine("-----------------------------------------");
                    }
                    else
                    {
                        Console.WriteLine("Profile was not received!");
                        Console.WriteLine("-----------------------------------------");
                    }
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
