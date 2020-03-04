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
            RF627.SdkInit();

            // Search for RF627old devices over network
            Console.WriteLine("- Start searching device");
            List<RF627.RF627old> Scanners = RF627.RF627old.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);

            // foreach over an scanners list
            for (int i = 0; i < Scanners.Count; i++)
            {
                Console.WriteLine("{0}- Try to connect to {1} scanner", Environment.NewLine, i + 1);
                bool isConnect = Scanners[i].Connect();
                if (isConnect)
                {
                    Console.WriteLine("+ Successfully connected"); Console.WriteLine();

                    Console.WriteLine("- Try to read params");
                    bool isReadParam = Scanners[i].ReadParams();
                    if (isReadParam)
                    {
                        Console.WriteLine("+ Parameters read successfully"); Console.WriteLine();

                        Console.WriteLine("- Try to get scanner's name");
                        RF627.Param<string> deviceName = Scanners[i].GetParam(RF627.Params.User.General.deviceName);
                        if (deviceName != null)
                        {
                            Console.WriteLine("+ Device name is: {0}", deviceName.GetValue()); Console.WriteLine();

                            Console.WriteLine("- Try to set new scanner's name and write changed parameters to scanner");
                            string newName = "Test Name";
                            deviceName.SetValue(newName);
                            Scanners[i].SetParam(deviceName);

                            // Send command to scanner to write changed parameters
                            bool isSet = Scanners[i].WriteParams();
                            if (isSet)
                                Console.WriteLine("+ Command to change parameters send successfully");
                            else Console.WriteLine("! Error send changing command");
                        }
                        else Console.WriteLine("! Error getting device name");
                    }
                    else Console.WriteLine("! Parameters didn't read");

                    // Check that the parameter is set correctly
                    // Read again all params from RF627 device.
                    Console.WriteLine("- Try to read again params");
                    isReadParam = Scanners[i].ReadParams();
                    if (isReadParam)
                    {
                        Console.WriteLine("+ Parameters read successfully"); Console.WriteLine();

                        Console.WriteLine("- Try to get scanner's name");
                        RF627.Param<string> deviceName = Scanners[i].GetParam(RF627.Params.User.General.deviceName);
                        if (deviceName.GetValue() == "Test Name")
                            Console.WriteLine("+ Changed parameters write successfully");
                        else Console.WriteLine("! Error changing parameters");
                        Console.WriteLine();
                    }
                    else Console.WriteLine("! Parameters didn't read");
                }
                else Console.WriteLine("! Connection error");
            }

            Console.WriteLine("{0}Press any key to end \"Parameters-test\"", Environment.NewLine);
            Console.ReadKey();
        }
    }
}
