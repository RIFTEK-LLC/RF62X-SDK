import sys
sys.path.append("../../../RF62X-Wrappers/Python/")
from PYSDK_SMART import *


if __name__ == '__main__':

    print("#########################################")
    print("#                                       #")
    print("#          Dump Example v2.x.x          #")
    print("#                                       #")
    print("#########################################")
    
    # Initialize sdk library
    sdk_init()

    # Print return rf627 sdk version
    print('SDK version', sdk_version())
    print("=========================================")

    # Create value for scanners vector's type
    list_scanners=search()
    print("Was found\t:", len(list_scanners), "RF627 v2.x.x")
    print("=========================================")


    # Iterate over all available network adapters in the current operating
    # system to send "Hello" requests.
    i=0
    for scanner in list_scanners: 
        info = get_info(scanner, kSERVICE)
        i+=1
        #  Print short information about the scanner
        print("\n\nID scanner's list:", i)
        print("-----------------------------------------")
        print("Device information:")
        print("* Name\t\t: ",   info['user_general_deviceName'])
        print("* Serial\t: ",   info['fact_general_serial']); 
        print("* IP Addr\t: ",  info['user_network_ip']); 
        # Establish connection to the RF627 device by Service Protocol.
        is_connected = connect(scanner)
        if (not is_connected):
            print("Failed to connect to scanner!")
            continue

        count_of_profiles = 1000
        start_dump_recording(scanner, count_of_profiles)
        print("Start dump recording...")
        print("-----------------------------------------")
        size = 0

        # wait dump recording
        while(size < count_of_profiles):
            read_params(scanner)
            size_param = get_param(scanner,"user_dump_size")
            if size_param is not None:
                size=size_param["value"]
                print("Current profiles in the dump: ", size)
            else:
                print("Error getting profiles in the dump")

        print("Start dump downloading...")
        list_dumps = get_dumps_profiles(scanner, 0, count_of_profiles)
        print(len(list_dumps), "Profiles in dump were downloaded!")
        print("-----------------------------------------")


        # Disconnect from scanner.
        disconnect(scanner)

    # Cleanup resources allocated with sdk_init()
    sdk_cleanup()




 
