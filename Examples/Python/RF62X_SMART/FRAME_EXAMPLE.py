import sys
sys.path.append("../../../RF62X-Wrappers/Python/")
from PYSDK_SMART import *


if __name__ == '__main__':

    print("#########################################")
    print("#                                       #")
    print("#          Frame Example v2.x.x          #")
    print("#                                       #")
    print("#########################################")
    
    # Initialize sdk library
    sdk_init()

    # Print return rf627 sdk version
    print('SDK version', sdk_version())
    print("=========================================")

    # Create value for scanners vector's type
    list_scanners=search()
    print("Was found\t:", len(list_scanners), "RF627-Smart")
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
        if (is_connected):
            frame=get_frame(scanner, kSERVICE)

        if (is_connected and frame is not None):
            print("Frame information: ")
            print("* Data Size\t: ",frame['data_size'])
            print("* Frame Height\t: ",frame['height'])
            print("* Frame Width\t: ",frame['width'])
            print("Frame was successfully received!")
            print("-----------------------------------------")
        else:
            print("Frame was not received!")
            print("-----------------------------------------")


      
        # Disconnect from scanner.
        disconnect(scanner)

    # Cleanup resources allocated with sdk_init()
    sdk_cleanup()




 