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
        print("-----------------------------------------")

        # Establish connection to the RF627 device by Service Protocol.
        is_connected = connect(scanner)
        # read params from RF627 device by Service Protocol.
        is_read=read_params(scanner)

        if (is_connected and is_read):
            # Example of working with the parameter type:
            # string
            #
            # Get parameter of Device Name (first way to get parameter by string name)
            name = get_param(scanner, "user_general_deviceName")
            print("Current Device Name \t: ", name["value"])

            # Add "_TEST" to the ending of the current name
            name["value"]+="_TEST"
            set_param(scanner, name)

            str_name_new = get_param(scanner, "user_general_deviceName")
            print("New Device Name \t: ", str_name_new["value"])
            print("-------------------------------------")


            # Restore previous scanner state
            read_params(scanner)

            # Example of working with the parameter type:
            # uint32_t
            # Laser Blink
            isEnabled= get_param(scanner, USER_LASER_ENABLED)
            print("Current Laser State\t: ", ("OFF","ON")[isEnabled["value"]])

            # Change the current state to the opposite
            isEnabled["value"]=not isEnabled["value"]
            set_param(scanner, isEnabled)
            # Apply changed parameters to the device
            write_params(scanner) 

            print("Current Laser State\t: ", ("OFF","ON")[get_param(scanner, USER_LASER_ENABLED)["value"]])

            from time import sleep
            sleep(1)

            # Restore original Laser State
            isEnabled= get_param(scanner, USER_LASER_ENABLED)
            isEnabled["value"]=not isEnabled["value"]
            set_param(scanner, isEnabled)
            write_params(scanner) 
            print("Current Laser State\t: ", ("OFF","ON")[get_param(scanner, USER_LASER_ENABLED)["value"]])
            print("-------------------------------------")

            # Example of working with the parameter type:
            # array
            # Get parameter of Device IP Addr (second way to get a parameter by keys)
            ip_addr= get_param(scanner, USER_NETWORK_IP)
            print("Current Device IP\t: ",ip_addr["value"])
            #  Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
            ip_addr['value'][3] = 31
            set_param(scanner, ip_addr)

            ip_addr= get_param(scanner, USER_NETWORK_IP)
            print( "New Device IP    \t: ", ip_addr["value"])
            # write_params(scanner)  #Commented out in demo

            # Restore previous scanner state
            read_params(scanner)
            
            #  Example of working with parameters using an Enum
            #  Get parameter of Streams Format
            streams_format=get_param(scanner, USER_STREAMS_FORMAT)
            if streams_format:
                current_format=streams_format['value']
                if current_format==streams_format['enumValues']['DATA_FORMAT_RAW_PROFILE']:
                    current_format_name=streams_format['enumLabels']['DATA_FORMAT_RAW_PROFILE']
                    print("Current Streams Format\t:",current_format_name)
                    # Change the current format to the opposite
                    streams_format['value']=streams_format['enumValues']['DATA_FORMAT_PROFILE']
                    new_format_name = streams_format['enumLabels']['DATA_FORMAT_PROFILE']
                    print("New Streams Format\t: ", new_format_name)
                elif current_format==streams_format['enumValues']['DATA_FORMAT_PROFILE']:
                    current_format_name=streams_format['enumLabels']['DATA_FORMAT_PROFILE']
                    print("Current Streams Format\t:",current_format_name)
                    # Change the current format to the opposite
                    streams_format['value']=streams_format['enumValues']['DATA_FORMAT_RAW_PROFILE']
                    new_format_name = streams_format['enumLabels']['DATA_FORMAT_RAW_PROFILE']
                    print("New Streams Format\t: ", new_format_name)
                print("-------------------------------------")
                set_param(scanner, streams_format)
                write_params(scanner) 

                # Save changes to the device's memory
                # save_params(scanner) #--commented out in demo

      
        # Disconnect from scanner.
        disconnect(scanner)

    # Cleanup resources allocated with sdk_init()
    sdk_cleanup()




 