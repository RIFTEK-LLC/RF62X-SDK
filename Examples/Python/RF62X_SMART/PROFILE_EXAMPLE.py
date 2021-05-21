from PYSDK_SMART import *


if __name__ == '__main__':

    print("#########################################")
    print("#                                       #")
    print("#          Profile Example v2.x.x       #")
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
# Get profile from scanner's data stream by Service Protocol.
        zero_points=True
        realtime=True
        count=0
        while(True):
            profile = get_profile2D(scanner,zero_points,realtime,kSERVICE)
            if (is_connected and profile is not None):
                profile_data_type=profile['header']['data_type']
                print("Profile information: ")
                if profile_data_type == PROFILE_DATA_TYPES.PIXELS:
                    print("* DataType\t: PIXELS")
                    print("* Count\t: ", profile['pixels_count'])
                elif profile_data_type == PROFILE_DATA_TYPES.PIXELS_INTRP:
                    print("* DataType\t: PIXELS_INTRP")
                    print("* Count\t: ", profile['pixels_count'])
                elif profile_data_type == PROFILE_DATA_TYPES.PROFILE:
                    print("* DataType\t: PROFILE")
                    print("* Count\t: ", profile['points_count'])
                elif profile_data_type == PROFILE_DATA_TYPES.PROFILE_INTRP:
                    print("* DataType\t: PROFILE_INTRP")
                    print("* Count\t: ", profile['points_count'])
                    
                if 'intensity' in profile:
                    print("* DataType\t: Intensity")
                    print("* Count\t: ", profile['intensity_count'])
                
                print("First 3 values:")
                if 'pixels' in profile:
                    for j in range(3):
                        print('-pixel [', j, ']\t', 'intensity=', profile['pixels'][j])
                if 'points' in profile:
                    for j in range(3):
                         print('-point [', j, ']\t x=', profile['points'][j].x, '\t z=', profile['points'][j].z)
                if 'intensity' in profile:
                    for j in range(3):
                        print('-intensity [', j, ']\t', '=', profile['intensity'][j])
                print("Profile was successfully received: ")
                print("-----------------------------------------")
            else:
                print("Profile was not received!")
                print("-----------------------------------------")

        # Disconnect from scanner.
        disconnect(scanner)

    # Cleanup resources allocated with sdk_init()
    sdk_cleanup()




 