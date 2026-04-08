//using System;
//using System.Collections.Generic;
//using System.Threading;
//using SDK.SCANNERS;

//namespace PROFILE_EXAMPLE
//{
//    class Program
//    {
//        public static uint profileСount;
//        public static uint profileLost;
//        public static bool isReceiveRun = true;
//        public static void receive_profiles(RF62X.RF627smart scanner)
//        {
//            // Get profile from scanner's data stream by Service Protocol.
//            RF62X.Profile2D profile = null;
//            bool zero_points = true;
//            bool realtime = false;

//            uint last_index = 0;
//            bool first_profile = true;
//            while (isReceiveRun)
//                if ((profile = scanner.GetProfile(zero_points, realtime)) != null)
//                {
//                    if (first_profile)
//                    {
//                        last_index = profile.header.measure_count;
//                        first_profile = false;
//                    }
//                    else
//                    {
//                        profileСount++;
//                        if (profile.header.measure_count - last_index > 1)
//                            profileLost+=(profile.header.measure_count - last_index);
//                        last_index = profile.header.measure_count;
//                    }
//                }
//                else
//                {
//                    Console.WriteLine("Profile was not received!");
//                    Console.WriteLine("-----------------------------------------");
//                }
//        }

//        static void Main(string[] args)
//        {
//            Console.WriteLine("#########################################");
//            Console.WriteLine("#                                       #");
//            Console.WriteLine("#         Profile Example v2.x.x        #");
//            Console.WriteLine("#                                       #");
//            Console.WriteLine("#########################################");

//            // Initialize sdk library
//            RF62X.SdkInit();

//            // Print return rf62X sdk version
//            Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
//            Console.WriteLine("=========================================");

//            // Search for RF627smart devices over network
//            List<RF62X.RF627smart> list = RF62X.RF627smart.Search(500);

//            // Print count of discovered rf627smart in network
//            Console.WriteLine("Was found\t: {0} RF627 v2.x.x", list.Count);
//            Console.WriteLine("=========================================");

//            int index = -1;
//            if (list.Count > 1)
//            {
//                Console.WriteLine("Select scanner for test: ");
//                for (int i = 0; i < list.Count; i++)
//                    Console.WriteLine("{0}. Serial: {1}", i, 
//                                      list[i].GetInfo().serial_number);
//                index = Convert.ToInt32(Console.ReadLine());
//            }
//            else if (list.Count == 1)
//                index = 0;

//            if (index == -1)
//                return;

//            RF62X.HelloInfo info = list[index].GetInfo();

//            Console.WriteLine("-----------------------------------------");
//            Console.WriteLine("Device information: ");
//            Console.WriteLine("* Name  \t: {0}", info.device_name);
//            Console.WriteLine("* Serial\t: {0}", info.serial_number);
//            Console.WriteLine("* IP Addr\t: {0}", info.ip_address);
//            Console.WriteLine("-----------------------------------------");

//            // Establish connection to the RF627 device by Service Protocol.
//            bool is_connected = list[index].Connect();

//            if (is_connected)
//            {
//                Thread receiver = new Thread(() => receive_profiles(list[index]));
//                isReceiveRun = true;
//                receiver.Start();

//                Console.WriteLine("Thread of receiving profiles started");
//                Console.WriteLine("For interrupt receiving press \"Ctrl+C\"");

//                bool isRun = true;
//                Console.CancelKeyPress += delegate 
//                    (object sender, ConsoleCancelEventArgs consoleArgs) {
//                    consoleArgs.Cancel = true;
//                    isRun = false;
//                    isReceiveRun = false;
//                };

//                while (isRun)
//                {
//                    Thread.Sleep(1000);
//                    Console.WriteLine("FPS: {0}, Lost: {1}", 
//                                      Program.profileСount, profileLost);
//                    profileLost = 0;
//                    profileСount = 0;
//                }

//                receiver.Join();
//                Console.WriteLine("Thread of receiving profiles interrupted");
//                Console.WriteLine("-----------------------------------------");
//            }

//            // Cleanup resources allocated with sdk_init()
//            RF62X.SdkCleanup();

//            Console.WriteLine("Press any key to close this window...");
//            Console.ReadKey();
//        }
//    }
//}


using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace PROFILE_ONESHOT_ALL
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
