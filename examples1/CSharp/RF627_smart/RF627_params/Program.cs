using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace RF627_params
{
    class Program
    {
        static void Main(string[] args)
        {
            // Start initialization of the library core
            RF62X.SdkInit();

            // Search for RF627smart devices over network
            Console.WriteLine("- Start searching device");
            List<RF62X.RF627smart> Scanners = RF62X.RF627smart.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);

            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
                // Establish connection to the RF627 device by Service Protocol.
                bool isConnected = Scanners[i].Connect();

                // read params from RF627 device by Service Protocol.
                Scanners[i].ReadParams();

                // Get parameter of Device Name
                RF62X.Parameter<string> name = Scanners[i].GetParam(RF62X.PARAMS.User.General.deviceName);
                if (name != null)
                {
                    string strName = name.GetValue();
                    Console.WriteLine("\n\nCurrent Device Name \t: {0}", strName);

                    // Add "_TEST" to the ending of the current name
                    strName += "_TEST";
                    name.SetValue(strName);
                    Console.WriteLine("New Device Name \t: {0}", strName);
                    Console.WriteLine("-----------------------------------------");

                    Scanners[i].SetParam(name);

                }

                // Get parameter of Device IP Addr
                RF62X.Parameter<List<uint>> ipAddr = Scanners[i].GetParam(RF62X.PARAMS.User.NetWork.ip);
                if (ipAddr != null)
                {
                    List<uint> ip = ipAddr.GetValue();
                    Console.WriteLine("Current Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);

                    // Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
                    ip[3]++;                    
                    ipAddr.SetValue(ip);
                    Console.WriteLine("New Device IP Addr\t: {0}.{1}.{2}.{3}", ip[0], ip[1], ip[2], ip[3]);
                    Console.WriteLine("-----------------------------------------");

                    Scanners[i].SetParam(ipAddr);
                }

                // Get parameter of Laser Enabled
                RF62X.Parameter<uint> laserEnabled = Scanners[i].GetParam(RF62X.PARAMS.User.Laser.enabled);
                if (laserEnabled != null)
                {
                    bool isLaserEnabled = Convert.ToBoolean(laserEnabled.GetValue());
                    Console.WriteLine("Current Laser State\t: {0}", isLaserEnabled ? "ON" : "OFF");

                    // Change the current state to the opposite
                    isLaserEnabled = !isLaserEnabled;
                    laserEnabled.SetValue((uint)(Convert.ToUInt32(isLaserEnabled)));
                    Console.WriteLine("New Laser State\t\t: {0}", isLaserEnabled ? "ON" : "OFF");
                    Console.WriteLine("-----------------------------------------");


                    Scanners[i].SetParam(laserEnabled);
                }

                // Get parameter of exposure
                RF62X.Parameter<uint> exposure = Scanners[i].GetParam(RF62X.PARAMS.User.Sensor.exposure1);
                if (exposure != null)
                {
                    uint current_value = exposure.GetValue();
                    Console.WriteLine("Current exposure value\t: {0}", current_value);

                    // Change the current exposure value to new
                    uint new_value = 3000000;
                    exposure.SetValue(new_value);
                    Console.WriteLine("New exposure value\t: {0}", new_value);
                    Console.WriteLine("-----------------------------------------");
                    
                    Scanners[i].SetParam(exposure);
                }

                //  Write changes parameters to the device's memory
                Scanners[i].WriteParams();

                // Disconnect from scanner.
                Scanners[i].Disconnect();
            }
            Console.WriteLine("{0}Press any key to end \"Parameters-test\"", Environment.NewLine);
            Console.ReadKey();

            // Cleanup resources allocated with SdkInit()
            RF62X.SdkCleanup();
        }
    }
}
