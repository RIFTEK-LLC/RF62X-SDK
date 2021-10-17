import sys
sys.path.append("../../../RF62X-Wrappers/Python/")
from PYSDK_SMART import *


if __name__ == '__main__':

    print("#########################################")
    print("#                                       #")
    print("#          Parameter Example v2.x.x     #")
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
        print("-----------------------------------------")

        # Establish connection to the RF627 device by Service Protocol.
        is_connected = connect(scanner)
        if (not is_connected):
            print("Failed to connect to scanner!")
            continue

        # read params from RF627 device by Service Protocol.
        is_read=read_params(scanner)
        if (not is_read):
            print("Failed to read scanner parameters!")
            continue


        # Example of working with the parameter type:
        # string
        #
        # Get parameter of Device Name (first way to get parameter by string name)
        name = get_param(scanner, "user_general_deviceName")
        if (name is not None):
            print("Current Device Name \t: ", name["value"])

        # Add "_TEST" to the ending of the current name
        name["value"]+="_TEST"
        set_param(scanner, name)

        str_name_new = get_param(scanner, "user_general_deviceName")
        print("New Device Name \t: ", str_name_new["value"])
        print("-------------------------------------")


        # Example of working with the parameter type:
        # uint32_t
        #
        # Get parameter of Sensor Framerate
        fps = get_param(scanner, "user_sensor_framerate")
        if fps is not None:
            print("Current FPS \t: ", fps["value"])
            #  Change the framerate to 100
            set_param(scanner, "user_sensor_framerate", 100)
            print("New FPS  \t\t: ", get_param(scanner, "user_sensor_framerate")["value"])
            print("-------------------------------------")


        # Example of working with the parameter type:
        # vector
        #
        # Get parameter of Device IP Addr
        ip_addr= get_param(scanner, "user_network_ip")
        if ip_addr is not None:
            print("Current Device IP\t: ",ip_addr["value"])
            #  Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
            ip_addr['value'][3] = 31
            set_param(scanner, ip_addr)
            ip_addr= get_param(scanner, "user_network_ip")
            print( "New Device IP    \t: ", ip_addr["value"])
    
        # Example of working with using an Enum:
        # uint32_t
        # 
        # Get parameter of Sync Source

        syncSource= get_param(scanner, "user_sensor_syncSource")
        if syncSource is not None:
            current_value = syncSource["value"]
            syncEnum = syncSource["enumIndexes"]
            syncEnumLabes = syncSource["enumLabels"]
            current_key=syncEnum[current_value]
            current_label=syncEnumLabes[current_key]
            print("Current Sync Source Key\t: ",current_key)
            print("Current Sync Source Label\t: ",current_label)

        # Change the current state to SYNC_EXTERNAL (or SYNC_INTERNAL)
        if (current_key=="SYNC_INTERNAL"):
            set_param(scanner, "user_sensor_syncSource", "SYNC_EXTERNAL")
        else:
            set_param(scanner, "user_sensor_syncSource", "SYNC_INTERNAL")
        
        syncSource= get_param(scanner, "user_sensor_syncSource")
        print( "New Sync Source", syncSource["enumIndexes"][syncSource["value"]])
 
        # Restore previous scanner state
        read_params(scanner)

        # Example of working with using an Enum:
        # uint32_t
        # Get parameter of Laser Enabled
        laser= get_param(scanner, "user_laser_enabled")
        isEnabled =  laser["enumIndexes"][laser["value"]]


        if laser is not None:
            print("Current Laser State\t: ", laser["enumLabels"][laser["enumIndexes"][laser["value"]]] )
            if laser["enumIndexes"][laser["value"]]=="FALSE":
                set_param(scanner, "user_laser_enabled", "TRUE")
            else:
                set_param(scanner, "user_laser_enabled", "FALSE")

            # Apply changed parameters to the device
            write_params(scanner) 

            laser= get_param(scanner, "user_laser_enabled")
            print("New Laser State\t: ", laser["enumLabels"][laser["enumIndexes"][laser["value"]]] )

            from time import sleep
            sleep(1)

            # Restore original Laser State (Blink for 1 second)
            set_param(scanner, "user_laser_enabled", isEnabled)
            write_params(scanner) 

            laser= get_param(scanner, "user_laser_enabled")
            print("Restore Original Laser State\t: ", laser["enumLabels"][laser["enumIndexes"][laser["value"]]] )
            print("-------------------------------------")
     

       
   
        # Disconnect from scanner.
        disconnect(scanner)

# Cleanup resources allocated with sdk_init()
sdk_cleanup()




 
