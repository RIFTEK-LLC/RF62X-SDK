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

                    Console.WriteLine("- Try to receive profile");
                    RF627.Profile profile = Scanners[i].GetProfile();
                    if (profile.header != null)
                        Console.WriteLine("+ Received profile successfully. S/n: {0}", 
                            profile.header.serial_number.ToString());
                    else 
                        Console.WriteLine("! Profile is null");
                        
                }
                else Console.WriteLine("! Connection error");
            }

            Console.WriteLine("{0}Press any key to end \"Search-test\"", Environment.NewLine);
            Console.ReadKey();
        }
    }
}
