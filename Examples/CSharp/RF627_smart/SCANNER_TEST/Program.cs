using System;
using System.Collections.Generic;
using System.Threading;
using SDK.SCANNERS;

namespace SCANNER_TEST
{
    class Program
    {

        public static uint profile_count;
        public static uint profile_lost;
        public static List<RF62X.RF627smart> list;
        public static bool isReceiveRun = true;
        public static void receive_profiles(int index)
        {
            // Get profile from scanner's data stream by Service Protocol.
            RF62X.Profile2D profile = null;
            bool zero_points = true;
            bool realtime = false;

            uint last_index = 0;
            bool first_profile = true;
            while (isReceiveRun)
                if ((profile = list[index].GetProfile(zero_points, realtime)) != null)
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

        protected static void myHandler(object sender, ConsoleCancelEventArgs args)
        {
            args.Cancel = true;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("#########################################");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#          Scanner Tests v2.x.x         #");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#########################################");

            // Initialize sdk library
            RF62X.SdkInit();

            // Print return rf62X sdk version
            Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
            Console.WriteLine("=========================================");

            bool isEnd = false;
            while(!isEnd)
            {
                int actionId = -1;
                Console.WriteLine("1 - Start searching for RF62X v2.x.x scanners");
                Console.WriteLine("2 - Exit the Scanner Tests Program...");
                Console.Write("Select an action: ");
                actionId = Convert.ToInt32(Console.ReadLine());
                Console.WriteLine("");

                switch (actionId)
                {
                    case 1:
                        {
                            Console.WriteLine("=========================================");
                            Console.WriteLine("Start searching for RF62X v2.x.x scanners");
                            Console.WriteLine("=========================================");
                            // Search for RF627smart devices over network
                            list = RF62X.RF627smart.Search(500);

                            // Print count of discovered rf627smart in network by Service Protocol
                            Console.WriteLine("Was found\t: {0} RF627-Smart", list.Count);
                            Console.WriteLine("=========================================");
                            Console.WriteLine("");

                            int index = -1;
                            if (list.Count > 1)
                            {
                                for (int i = 0; i < list.Count; i++)
                                    Console.WriteLine("{0}. Serial: {1}", i + 1, list[i].GetInfo().serial_number);
                                Console.Write("Select scanner for test: ");
                                index = Convert.ToInt32(Console.ReadLine()) - 1;
                                Console.WriteLine("-----------------------------------------");
                            }
                            else if (list.Count == 1)
                                index = 0;

                            if (index != -1)
                            {
                                RF62X.HelloInfo info = list[index].GetInfo();

                                Console.WriteLine("Device information: ");
                                Console.WriteLine("* Name\t: {0}", info.device_name);
                                Console.WriteLine("* Serial\t: {0}", info.serial_number);
                                Console.WriteLine("* IP Addr\t: {0}", info.ip_address);
                                Console.WriteLine("* Host IP Addr\t: {0}", info.host_ip_address);
                                Console.WriteLine("-----------------------------------------");

                                // Establish connection to the RF627 device by Service Protocol.
                                Console.WriteLine("- Try to connect to device...");
                                bool is_connected = list[index].Connect();
                                if (is_connected)
                                {
                                    Console.WriteLine("+ Connected successfully!");
                                    Console.WriteLine("-----------------------------------------");

                                    bool isScannerTestEnd = false;
                                    while (!isScannerTestEnd)
                                    {
                                        actionId = -1;
                                        Console.WriteLine("1 - Set Exposure Parameter");
                                        Console.WriteLine("2 - Set Sync Source Parameter");
                                        Console.WriteLine("3 - Start capturing profiles");
                                        Console.WriteLine("4 - End Cuurent scanner test");
                                        Console.Write("Select an action: ");
                                        actionId = Convert.ToInt32(Console.ReadLine());
                                        Console.WriteLine("=========================================");


                                        switch (actionId)
                                        {
                                            case 1:
                                                {
                                                    RF62X.Parameter<uint> sensorExposure1 = list[index].GetParam("user_sensor_exposure1");
                                                    if (sensorExposure1 != null && sensorExposure1.type == "uint32_t")
                                                    {
                                                        uint value = sensorExposure1.GetValue();
                                                        Console.WriteLine("Current Sensor Exposure1\t: {0}", value);

                                                        // Change the Sensor Exposure1
                                                        Console.Write("Enter a new value (multiple of 100): ");
                                                        uint newValue = Convert.ToUInt32(Console.ReadLine());
                                                        sensorExposure1.SetValue(newValue);

                                                        list[index].SetParam(sensorExposure1);
                                                        if (list[index].WriteParams())
                                                        {
                                                            Console.WriteLine("New Sensor Exposure1\t\t: {0}", newValue);
                                                            Console.WriteLine("-----------------------------------------");
                                                        }
                                                        else
                                                        {
                                                            Console.WriteLine("Failed to set the new value");
                                                            Console.WriteLine("Most likely reasons for this behavior:");
                                                            Console.WriteLine("* New value does not match parameter step.");
                                                            Console.WriteLine("* New value is out of range.");
                                                        }
                                                    }
                                                    break;
                                                }
                                            case 2:
                                                {
                                                    RF62X.Parameter<uint> syncSource = list[index].GetParam("user_sensor_syncSource");
                                                    if (syncSource != null)
                                                    {
                                                        Dictionary<int, string> syncSourceValues = new Dictionary<int, string>(4);
                                                        syncSourceValues.Add(1, "SYNC_INTERNAL");
                                                        syncSourceValues.Add(2, "SYNC_EXTERNAL");
                                                        syncSourceValues.Add(3, "SYNC_SOFTWARE_EXT");
                                                        syncSourceValues.Add(4, "SYNC_SOFTWARE");

                                                        // Set syncSource to SYNC_INTERNAL (or SYNC_EXTERNAL)
                                                        foreach (var item in syncSourceValues)
                                                        {
                                                            Console.WriteLine("{0} - {1}", item.Key, item.Value);
                                                        }
                                                        Console.Write("Select Sync Source: ");
                                                        int newValue = Convert.ToInt32(Console.ReadLine());
                                                        var newSource = syncSource.valuesEnum.Find(
                                                                delegate (RF62X.Parameter<uint>.ValuesEnum v)
                                                                {
                                                                    return v.GetKey() == syncSourceValues[newValue];
                                                                });

                                                        syncSource.SetValue(newSource.GetValue());
                                                        list[index].SetParam(syncSource);
                                                        if (list[index].WriteParams())
                                                        {
                                                            Console.WriteLine("New Sync Source\t: {0}", newSource.GetLabel());
                                                            Console.WriteLine("-----------------------------------------");
                                                        }
                                                        else
                                                        {
                                                            Console.WriteLine("Failed to set the new value");
                                                            Console.WriteLine("Most likely reasons for this behavior:");
                                                            Console.WriteLine("* New value does not match parameter step.");
                                                            Console.WriteLine("* New value is out of range.");
                                                        }
                                                    }
                                                    break;
                                                }
                                            case 3:
                                                {
                                                    profile_count = 0;
                                                    profile_lost = 0;
                                                    Thread receiver = new Thread(() => receive_profiles(index));
                                                    isReceiveRun = true;
                                                    receiver.Start();

                                                    Console.WriteLine("Thread of receiving profiles started (to interrupt press Ctrl+C))");

                                                    bool isRun = true;
                                                    Console.CancelKeyPress += delegate (object sender, ConsoleCancelEventArgs consoleArgs) {
                                                        consoleArgs.Cancel = true;
                                                        isRun = false;
                                                        isReceiveRun = false;
                                                    };

                                                    while (isRun)
                                                    {
                                                        Thread.Sleep(1000);
                                                        Console.WriteLine("FPS: {0}, Lost: {1}", Program.profile_count, profile_lost);
                                                        profile_lost = 0;
                                                        profile_count = 0;
                                                    }

                                                    receiver.Join();
                                                    Console.WriteLine("Thread of receiving profiles interrupted");
                                                    Console.WriteLine("-----------------------------------------");
                                                    break;
                                                }
                                            case 4:
                                                {
                                                    isScannerTestEnd = true;
                                                    break;
                                                }
                                            default:
                                                break;
                                        }
                                    }
                                }
                                else
                                {
                                    Console.WriteLine("Failed to connect to the scanner...." + Environment.NewLine);
                                    Console.WriteLine("Most likely reasons for this behavior:");
                                    Console.WriteLine("* Wrong Host IP Address in the scanner settings.");
                                    Console.WriteLine("* Profiles Destination Port is occupied by another application.");
                                    Console.WriteLine("-----------------------------------------");
                                }

                                Console.WriteLine("");
                            }
                            else
                            {
                                Console.WriteLine("No scanners were found...");
                            }
                            break;
                        }
                    case 2:
                        {
                            isEnd = true;
                            break;
                        }
                    default:
                        break;
                }
            }

        }
    }
}
