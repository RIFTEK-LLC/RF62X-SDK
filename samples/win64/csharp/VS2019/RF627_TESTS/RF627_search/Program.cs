using System;
using System.Collections.Generic;
using SDK.SCANNERS;

namespace RF627_search
{
    class Program
    {
        static void Main(string[] args)
        {
            // Start initialization of the library core
            RF627.SdkInit();

            // Print return rf627 sdk version
            Console.WriteLine("Current rf627 sdk version: {0}", RF627.SdkVersion());

            // Search for RF627old devices over network
            Console.WriteLine("- Start searching device");
            List<RF627.RF627old> Scanners = RF627.RF627old.Search();
            Console.WriteLine("+ {0} scanners detected", Scanners.Count);

            Console.WriteLine("{0}Press any key to end \"Search-test\"", Environment.NewLine);
            Console.ReadKey();
        }
    }
}
