using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace PARAMETER_EXAMPLE
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("#########################################");
            Console.WriteLine("#                                       #");
            Console.WriteLine("#       Parameter Example v2.x.x        #");
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

                // Establish connection to the RF627 device by Service Protocol.
                bool isConnected = list[i].Connect();

                // read params from RF627 device by Service Protocol.
                bool isRead = list[i].ReadParams();

                if (isConnected && isRead)
                {
                    //
                    // Example of working with the parameter type:
                    // std::string
                    //
                    // Get parameter of Device Name (first way to get parameter by string name)
                    // Get parameter of user_dump_capacity
                    RF62X.Parameter<string> name = list[i].GetParam("user_general_deviceName");
                    if (name != null && name.type == "string_t")
                    {
                        string str_name = name.GetValue();
                        Console.WriteLine("Current Device Name \t: {0}", str_name);

                        // Add "_TEST" to the ending of the current name
                        str_name += "_TEST";
                        name.SetValue(str_name);
                        Console.WriteLine("New Device Name \t: {0}", str_name);
                        Console.WriteLine("-------------------------------------");

                        list[i].SetParam(name);
                    }

                    //
                    // Example of working with the parameter type:
                    // uint32_t
                    //
                    // Get parameter of Laser Enabled
                    RF62X.Parameter<uint> laserEnabled = list[i].GetParam("user_laser_enabled");
                    if (laserEnabled != null && laserEnabled.type == "uint32_t")
                    {
                        bool isEnabled = Convert.ToBoolean(laserEnabled.GetValue());
                        Console.WriteLine("Current Laser State\t: {0}", isEnabled ? "ON" : "OFF");

                        // Change the current state to the opposite
                        isEnabled = !isEnabled;
                        laserEnabled.SetValue((uint)(Convert.ToUInt32(isEnabled)));
                        Console.WriteLine("New Laser State\t\t: {0}", isEnabled ? "ON" : "OFF");
                        Console.WriteLine("-----------------------------------------");

                        list[i].SetParam(laserEnabled);
                    }



                    //
                    // Example of working with the parameter type:
                    // std::vector<uint32_t>
                    //
                    // Get parameter of Device IP Addr (second way to get a parameter by keys)
                    RF62X.Parameter<List<uint>> ipAddr = list[i].GetParam("user_network_ip");
                    if (ipAddr != null && ipAddr.type == "u32_arr_t")
                    {
                        List<uint> ip = ipAddr.GetValue();
                        Console.WriteLine("Current Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);

                        // Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
                        ip[3]++;
                        ipAddr.SetValue(ip);
                        Console.WriteLine("New Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);
                        Console.WriteLine("-----------------------------------------");

                        list[i].SetParam(ipAddr);
                    }



                    //
                    // Example of working with parameters using an Enum
                    //
                    // Get parameter of Streams Format
                    RF62X.Parameter<uint> streamsFormat = list[i].GetParam("user_streams_format");
                    if (streamsFormat != null && streamsFormat.type == "uint32_t")
                    {
                        uint currentFormat = streamsFormat.GetValue();
                        
                        var RAW_PROFILE = streamsFormat.valuesEnum.Find(
                            delegate (RF62X.Parameter<uint>.ValuesEnum v) {
                                return v.GetKey() == "DATA_FORMAT_RAW_PROFILE"; 
                            });
                        if (currentFormat == RAW_PROFILE.GetValue())
                        {
                            Console.WriteLine("Current Streams Format\t: RAW_PROFILE");
                            // Change the current format to the opposite
                            var newFormat = streamsFormat.valuesEnum.Find(
                                delegate (RF62X.Parameter<uint>.ValuesEnum v) {
                                    return v.GetKey() == "DATA_FORMAT_PROFILE";
                                });
                            streamsFormat.SetValue(newFormat.GetValue());
                            Console.WriteLine("New Streams Format\t: FORMAT_PROFILE");
                        }
                        else
                        {
                            Console.WriteLine("Current Streams Format\t: FORMAT_PROFILE");
                            // Change the current format to the opposite
                            var newFormat = streamsFormat.valuesEnum.Find(
                                delegate (RF62X.Parameter<uint>.ValuesEnum v) {
                                    return v.GetKey() == "DATA_FORMAT_RAW_PROFILE";
                                });
                            streamsFormat.SetValue(newFormat.GetValue());
                            Console.WriteLine("New Streams Format\t: RAW_PROFILE");
                        }

                        Console.WriteLine("-----------------------------------------");
                        list[i].SetParam(streamsFormat);
                    }


                    //
                    // Example of working with parameters using an Enum
                    //
                    // Get/Set parameter of Sync Source
                    RF62X.Parameter<uint> syncSource = list[i].GetParam("user_sensor_syncSource");
                    if (syncSource != null)
                    {
                        // Set syncSource to SYNC_INTERNAL (or SYNC_EXTERNAL)
                        var newSource = syncSource.valuesEnum.Find(
                                delegate (RF62X.Parameter<uint>.ValuesEnum v) {
                                    return v.GetKey() == "SYNC_INTERNAL";
                                });
                        syncSource.SetValue(newSource.GetValue());
                        Console.WriteLine("New Sync Source\t: {0}", newSource.GetLabel());

                        Console.WriteLine("-----------------------------------------");
                        list[i].SetParam(syncSource);
                    }

                    // Apply changed parameters to the device
                    char answer = 'n';
                    Console.Write("Apply changed params to the device? (y/n):");
                    answer = Console.ReadLine()[0];
                    if (answer == 'y' || answer == 'Y')
                    {
                        list[i].WriteParams();
                        // Save changes to the device's memory
                        Console.Write("Save changes to device's memory? (y/n): ");
                        answer = Console.ReadLine()[0];
                        if (answer == 'y' || answer == 'Y')
                            list[i].SaveParams();
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
