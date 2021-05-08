import sys
sys.path.append("../../../rf62Xwrappers/Python/")
from PYSDK_SMART import *


if __name__ == '__main__':

    lib.core_init()
    print('sdk version', lib.sdk_version()) # Print sdk version
    scanners=vector_t()
    lib.vector_init(byref(scanners))
    for i in range(lib.GetAdaptersCount()):
        host_ip_addr = inet_addr(lib.GetAdapterAddress(i).decode("utf-8"))
        host_mask= inet_addr("255.255.255.0")
        lib.set_platform_adapter_settings(host_mask, host_ip_addr)
        lib.search_scanners(scanners, kRF627_SMART, 500, kSERVICE)
    print('Discovered:', lib.vector_count(scanners), 'rf627-smart')
 
    for i in range(lib.vector_count(scanners)):
        scanner = lib.vector_get(scanners,i)
        scanner = cast(scanner, POINTER(scanner_base_t))
        
        #scanner info
        hello = lib.get_info_about_scanner(scanner, kSERVICE)
        if hello is not None:
            print('Device information fields: ')
            print('* Name\t: ', hello['user_general_deviceName'])
            print('* Serial\t: ', hello['fact_general_serial'])
            print('* IP Addr\t: ', hello['user_network_ip'])
        else:
            print('Could not get device information\n')

    
        #get profile
        is_connected = lib.connect_to_scanner(scanner, kSERVICE)
        if (is_connected):
            zero_points = True
            prof = lib.get_profile2D_from_scanner(scanner, zero_points, kSERVICE)
            if prof:
                header_data_type = prof['header']['data_type']
                print('Profile information: ')
                print('* DataType\t: ', header_data_type)

                if 'pixels' in prof:
                    # pixels_format
                    print('* Count\t: ', len(prof['pixels']))
                    for j in range(5):
                        print('-pixel [', j, ']\t', 'intensity=', prof['pixels'][j])

                if 'points' in prof:
                    # profile_format
                    print('* Count\t: ', len(prof['points']))
                    for j in range(5):
                        print('-point [', j, ']\t x=', prof['points'][j].x, '\t z=', prof['points'][j].z)

                if 'intensity' in prof:
                    # intensity
                    print('* DataType\t: Intensity')
                    print('* Count\t: ', len(prof['intensity']))
                    for j in range(5):
                        print('-intensity [', j, ']\t', '=', prof['intensity'][j])
                print("Profile was successfully received!\n");
                print("-----------------------------------------\n");
            else:
                print("Profile was not received!\n");
                print("-----------------------------------------\n");

            #laser blink

            lib.read_params_from_scanner(scanner, 500, kSERVICE)

            is_laser_enabled = get_parameter_by_name(scanner, "user_laser_enabled")
            print('Current Laser State\t: ', is_laser_enabled['value'])
            is_laser_enabled['value'] = not is_laser_enabled['value']  # switch Laser Enabled
            change_parameter(scanner, is_laser_enabled)
        
            from time import sleep
            sleep(1)

            is_laser_enabled['value'] = not is_laser_enabled['value']  # switch Laser Enabled
            change_parameter(scanner, is_laser_enabled)

            lib.disconnect_from_scanner(scanner, kSERVICE)


    print("done") 


