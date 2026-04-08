using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace PROFILE_EXAMPLE
{
    internal class Program
    {
        static void Main()
        {
            Console.WriteLine("#########################################");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#         Profile Example v2.x.x        #");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#########################################\n");

            RF62X.SdkInit();
            try
            {
                Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
                Console.WriteLine("=========================================");

                List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

                Console.WriteLine("Was found\t: {0} RF627 v2.x.x", list.Count);
                Console.WriteLine("=========================================");

                for (int i = 0; i < list.Count; i++)
                {
                    var scanner = list[i];
                    RF62X.HelloInfo info = scanner.GetInfo();

                    Console.WriteLine("\n\nID scanner's list: {0}", i);
                    Console.WriteLine("-----------------------------------------");
                    Console.WriteLine("Device information:");
                    Console.WriteLine("* Name  \t: {0}", info.device_name);
                    Console.WriteLine("* Serial\t: {0}", info.serial_number);
                    Console.WriteLine("* IP Addr\t: {0}", info.ip_address);

                    if (!scanner.Connect())
                        continue;

                    try
                    {
                        bool zeroPoints = true;
                        bool realtime = true;

                        RF62X.Profile2D profile = scanner.GetProfile(zeroPoints, realtime);

                        if (profile != null)
                        {
                            var h = profile.header;

                            Console.WriteLine("Profile information:");
                            Console.WriteLine("* Version\t: v{0}.{1}", h.version_major, h.version_minor);

                            switch (h.data_type)
                            {
                                case RF62X.PROFILE_DATA_TYPES.PIXELS:
                                    Console.WriteLine("* DataType\t: PIXELS");
                                    Console.WriteLine("* Count\t\t: {0}", profile.pixels != null ? profile.pixels.Count : 0);
                                    Console.WriteLine("* Step \t\t: {0}", h.step_count);
                                    break;

                                case RF62X.PROFILE_DATA_TYPES.PIXELS_INTRP:
                                    Console.WriteLine("* DataType\t: PIXELS_INTRP");
                                    Console.WriteLine("* Count\t\t: {0}", profile.pixels != null ? profile.pixels.Count : 0);
                                    Console.WriteLine("* Step \t\t: {0}", h.step_count);
                                    break;

                                case RF62X.PROFILE_DATA_TYPES.PROFILE:
                                    Console.WriteLine("* DataType\t: PROFILE");
                                    Console.WriteLine("* Size\t\t: {0}", profile.points != null ? profile.points.Count : 0);
                                    Console.WriteLine("* Step \t\t: {0}", h.step_count);
                                    break;

                                case RF62X.PROFILE_DATA_TYPES.PROFILE_INTRP:
                                    Console.WriteLine("* DataType\t: PROFILE_INTRP");
                                    Console.WriteLine("* Size\t\t: {0}", profile.points != null ? profile.points.Count : 0);
                                    Console.WriteLine("* Step \t\t: {0}", h.step_count);
                                    break;

                                case RF62X.PROFILE_DATA_TYPES.PROFILE_POLYNOMIAL:
                                    Console.WriteLine("* DataType\t: PROFILE_POLYNOMIAL");
                                    Console.WriteLine("* Size\t\t: {0}", profile.points != null ? profile.points.Count : 0);
                                    Console.WriteLine("* Step \t\t: {0}", h.step_count);
                                    break;

                                default:
                                    Console.WriteLine("* DataType\t: {0}", h.data_type);
                                    Console.WriteLine("* Step \t\t: {0}", h.step_count);
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
                    finally
                    {
                        scanner.Disconnect();
                    }
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
