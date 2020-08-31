from PYSDK import const_protocol, const_scanner_type, const_parameter_name, const_old_data_type  # enums
from PYSDK import rf627_Error, rf627_device  # PySDK classes
from PYSDK import sdk_init, get_sdk_version, search_scanners, select_scanner  # PySDK functions

# ===================== RF627 Python SDK demo ================
# Initialize sdk library
sdk_init()
print('sdk version', get_sdk_version()) # Print sdk version

# ===================== RF627_search =========================
#

# Search for RF627old devices over network
list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
# Print count of discovered rf627-old in network by Service Protocol
print('Discovered: ', len(list), ' rf627-old')
# Print info of all discovered devices in network by Service Protocol
for i in range(len(list)):
    print('Scanner index : ', i)
    print(list[i])

# Select device by ip. Note: device can be selected by device_name, serial_number, etc. (see select_scanner documentation)
current_scanner=select_scanner(list, ip_address='192.168.1.30')

if current_scanner:
    # Print current_scanner device info
    print('Current scanner info')
    hello = current_scanner.get_info_about_scanner()
    print('Device information fields: ')
    print('* Name\t: ', hello['device_name'])
    print('* Serial\t: ', hello['serial_number'])
    print('* IP Addr\t: ', hello['ip_address'])
    print('* MAC Addr\t: ', hello['mac_address'])
    print('\nWorking ranges:')
    print('* Zsmr, mm\t: ', hello['z_begin'])
    print('* Zmr , mm\t: ', hello['z_range'])
    print('* Xsmr, mm\t: ', hello['x_begin'])
    print('* Xemr, mm\t: ', hello['x_end'])
    print('\nVersions: ')
    print('* Firmware\t: ', hello['firmware_version'])
    print('* Hardware\t: ', hello['hardware_version'])
    print('\n')

    # =====================RF627_profile=========================
    # Get profile from scanner's data stream by Service Protocol.
    # Profile conversion from ctypes to Python dictionary in py_get_profile2D_from_scanner() function.

    prof = current_scanner.get_profile2D_from_scanner()

    if prof:
        datatype = prof['header']['data_type']
        print('Profile information: ')
        print('* DataType\t: ', const_old_data_type(datatype))

        if 'pixels_count' in prof:
            # pixels_format
            print('* Count\t: ', prof['pixels_count'])
            for j in range(5):
                print('-pixel [', j, ']\t', 'intensity=', prof['pixels'][j])

        if 'points_count' in prof:
            # profile_format
            print('* Count\t: ', prof['points_count'])
            for j in range(5):
                print('-point [', j, ']\t x=', prof['points'][j].x, '\t z=', prof['points'][j].z)

        if 'intensity_count' in prof:
            # intensity
            print('* DataType\t: Intensity')
            print('* Count\t: ', prof['intensity_count'])
            for j in range(5):
                print('-intensity [', j, ']\t', '=', prof['intensity'][j])
        print('Profile was successfully received!')
    else:
        print('Profile was not received! Probably, *Host IP address* in scanners'' configuration should be changed.')

    # =====================RF627_params=========================
    #  Read params from RF627 device by Service Protocol.
    current_scanner.read_params_from_scanner()

    device_name = current_scanner.get_parameter(const_parameter_name.USER_GENERAL_DEVICENAME)
    if device_name:
        print('Old Device Name is \t:', device_name['value'])
        #  Add '_TEST' to the ending of the current name
        device_name['value']+='_TEST'
        #  Change Device Name, Method 1: update 'value' field of get_parameter() result and pass it to set_parameter 
        current_scanner.set_parameter(device_name)
        device_name_new1 = current_scanner.get_parameter(const_parameter_name.USER_GENERAL_DEVICENAME)
        print('Method 1: New Device Name is \t:', device_name_new1['value'])
        #  Add '_TEST2' to the ending of the current name
        new_name=device_name['value']+"2"
        #  Change Device Name, Method 2: set new value and pass it to set_parameter together with parameter name
        current_scanner.set_parameter(new_name,const_parameter_name.USER_GENERAL_DEVICENAME)
        device_name_new2 = current_scanner.get_parameter(const_parameter_name.USER_GENERAL_DEVICENAME)
        print('Method 2: New Device Name2 is \t:', device_name_new2['value'])

    #  Get parameter of Device IP Addr.
    ip = current_scanner.get_parameter(const_parameter_name.USER_NETWORK_IP)
    if ip:
        print('Current Device IP \t:', ip['value'])
        #  Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
        ip['value'][3] = 31
        #  Method 1
        current_scanner.set_parameter(ip['value'],const_parameter_name.USER_NETWORK_IP)
        ip_new1 = current_scanner.get_parameter(const_parameter_name.USER_NETWORK_IP)
        print('Method 1: New Device IP \t:', ip_new1['value'])
        #  Method 2
        current_scanner.set_parameter(ip)
        ip_new2 = current_scanner.get_parameter(const_parameter_name.USER_NETWORK_IP)
        print('Method 2: New Device IP \t:', ip_new2['value'])

    # Get parameter of Laser Enabled
    is_laser_enabled = current_scanner.get_parameter(const_parameter_name.USER_LASER_ENABLED)
    if is_laser_enabled:
        print('Current Laser State\t: ', is_laser_enabled['value'])
        is_laser_enabled['value'] = not is_laser_enabled['value']  # switch Laser Enabled
        current_scanner.set_parameter(is_laser_enabled)
        is_laser_enabled_new = current_scanner.get_parameter(const_parameter_name.USER_LASER_ENABLED)
        print('New Laser State\t: ', is_laser_enabled_new['value'])

        # Write current parameters to device's memory
        # current_scanner.write_params_to_scanner()  #commented out in demo
    else:
        print('Could not read scanner parameters')

else:
    print('Scanner was not selected')
