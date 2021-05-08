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

            Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());

            // Search for RF627smart devices over network
            Console.WriteLine("- Start searching device");
            List<RF62X.RF627smart> Scanners = RF62X.RF627smart.Search();
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
                while (true)
                {
                    RF62X.Profile2D profile = Scanners[i].GetProfile();
                    if (profile.header != null)
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
                                Console.WriteLine("* DataType\t: PIXELS");
                                Console.WriteLine("* Count\t: {0}", profile.pixels.Count);
                                break;
                            case RF62X.PROFILE_DATA_TYPES.PROFILE_INTRP:
                                Console.WriteLine("* DataType\t: PROFILE");
                                Console.WriteLine("* Size\t: {0}", profile.points.Count);
                                break;
                            default:
                                break;
                        }
                        Console.WriteLine("Profile was successfully received!");
                        Console.WriteLine("-----------------------------------------");
                    }
                    else
                    {
                        Console.WriteLine("Profile was not received!");
                        Console.WriteLine("-----------------------------------------");
                    }
                }

                // Disconnect from scanner.
                Scanners[i].Disconnect();

            }

            Console.WriteLine("{0}Press any key to end \"Search-test\"", Environment.NewLine);
            Console.ReadKey();

            // Cleanup resources allocated with sdk_init()
            RF62X.SdkCleanup();
        }
    }
}
