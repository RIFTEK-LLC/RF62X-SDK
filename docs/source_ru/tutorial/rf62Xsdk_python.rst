*******************************************************************************
Примеры для Python
*******************************************************************************
Исходный код, демонстрирующщий работу со сканером, находится в файле demo.py 
Ниже представлено описание каждой части кода.

Импорт функций  библиотеки­ «обёртки» для rf62Xsdk.dll, которые находятся в файле PYSDK.py:


.. code-block:: python

    # enums
    from PYSDK import const_protocol, const_scanner_type  
    from PYSDK import const_parameter_name, const_old_data_type
    # PySDK classes
    from PYSDK import rf627_Error, rf627_device  
    # PySDK functions
    from PYSDK import sdk_init, get_sdk_version, search_scanners, select_scanner



.. _how_to_use_rf62x_sdk_python_for_search:

Поиск устройств RF62X
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
Ниже приведен пример поиска сканеров серии RF627Old в сети  и выбор сканера с определенным  ip-адресом.

.. code-block:: python

    # ===================== RF627 Python SDK demo ================
    # Initialize sdk library
    sdk_init()
    print('sdk version', get_sdk_version()) # Print sdk version

    # ===================== RF627_search =========================
    #

    # Search for RF627old devices over network
    list = search_scanners(protocol=const_protocol.kSERVICE, 
                            scanner_type=const_scanner_type.kRF627_OLD)
    # Print count of discovered rf627-old in network by Service Protocol
    print('Discovered: ', len(list), ' rf627-old')
    # Print info of all discovered devices in network by Service Protocol
    for i in range(len(list)):
        print('Scanner index : ', i)
        print(list[i])

    # Select device by ip. Note: device can be selected by 
    # device_name, serial_number, etc. (see select_scanner documentation)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')

Ниже приведён результат вывода приложения при успешном обнаружении сканера в сети:

.. code-block:: bash

    sdk version 1.3.7
    Discovered: 1 rf627-old
    Scanner index : 0

    ---rf627 Device info---
    device_name = ABC
    serial_number = 190171
    ip_address = 192.168.1.30
    mac_address = 00:0a:35:6e:4a:9a
    profile_port = 50001
    service_port = 50011
    firmware_version = 19.11.15
    hardware_version = 18.6.20
    z_begin = 76
    z_range = 100
    x_begin = 48
    x_end = 82
    scanner_type = 1
    protocol_type = 1

    Selected scanner by ip_address 192.168.1.30

.. _how_to_use_rf62x_sdk_python_get_profile:


Получение  информации о сканере и профиля сканера
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
После того, как сканер выбран, производится получение информации о сканере и чтение профиля со сканера серии RF627Old.

.. code-block:: python

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
        # Profile conversion from ctypes to Python dictionary
        # in py_get_profile2D_from_scanner() function.

        prof = current_scanner.get_profile2D_from_scanner()

        if prof:
            datatype = prof['header']['data_type']
            print('Profile information: ')
            print('* DataType\t: ', const_old_data_type(datatype))

            if 'pixels_count' in prof:
                # pixels_format
                print('* Count\t: ', prof['pixels_count'])

            if 'points_count' in prof:
                # profile_format
                print('* Count\t: ', prof['points_count'])

            if 'intensity_count' in prof:
                # intensity
                print('* DataType\t: Intensity')
                print('* Count\t: ', prof['intensity_count'])
            print('Profile was successfully received!')
        else:
            print('Profile was not received!')


Ниже приведён результат вывода приложения при успешном получении  информации о сканере и чтении профиля со сканера:


.. code-block:: bash

    Current scanner info
    Device information fields:
    * Name          :  ABC
    * Serial        :  190171
    * IP Addr       :  192.168.1.30
    * MAC Addr      :  00:0a:35:6e:4a:9a

    Working ranges:
    * Zsmr, mm      :  76
    * Zmr , mm      :  100
    * Xsmr, mm      :  48
    * Xemr, mm      :  82

    Versions:
    * Firmware      :  19.11.15
    * Hardware      :  18.6.20


    Profile information:
    * DataType      :  CONST_rf627_old_data_type_t.DTY_ProfileNormal
    * Count         :  648

    * DataType      : Intensity
    * Count         :  648

    Profile was successfully received!

.. _how_to_use_rf62x_sdk_python_get_set_params:

Получение и установка параметров
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример получения и изменения имени сканера, установки IP адреса, смены 
состояния лазера (включение или отключение) двумя способами:

.. code-block:: python

    # =====================RF627_params=========================
    #  Read params from RF627 device by Service Protocol.
    current_scanner.read_params_from_scanner()

    device_name = current_scanner.get_parameter(
                            const_parameter_name.USER_GENERAL_DEVICENAME)
    if device_name:
        print('Old Device Name is \t:', device_name['value'])
        #  Add '_TEST' to the ending of the current name
        device_name['value']+='_TEST'
        #  Change Device Name, Method 1: update 'value' field of get_parameter() 
        #  result and pass it to set_parameter 
        current_scanner.set_parameter(device_name)
        device_name_new1 = current_scanner.get_parameter(
                            const_parameter_name.USER_GENERAL_DEVICENAME)
        print('Method 1: New Device Name is \t:', device_name_new1['value'])
        #  Add '_TEST2' to the ending of the current name
        new_name=device_name['value']+"2"
        #  Change Device Name, Method 2: set new value and pass it  
        #  to set_parameter together with parameter name
        current_scanner.set_parameter(
                        new_name,const_parameter_name.USER_GENERAL_DEVICENAME)
        device_name_new2 = current_scanner.get_parameter(
                            const_parameter_name.USER_GENERAL_DEVICENAME)
        print('Method 2: New Device Name2 is \t:', device_name_new2['value'])

    #  Get parameter of Device IP Addr.
    ip = current_scanner.get_parameter(const_parameter_name.USER_NETWORK_IP)
    if ip:
        print('Current Device IP \t:', ip['value'])
        #  Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
        ip['value'][3] = 31
        #  Method 1
        current_scanner.set_parameter(
                            ip['value'],const_parameter_name.USER_NETWORK_IP)
        ip_new1 = current_scanner.get_parameter(
                                    const_parameter_name.USER_NETWORK_IP)
        print('Method 1: New Device IP \t:', ip_new1['value'])
        #  Method 2
        current_scanner.set_parameter(ip)
        ip_new2 = current_scanner.get_parameter(
                                    const_parameter_name.USER_NETWORK_IP)
        print('Method 2: New Device IP \t:', ip_new2['value'])

    # Get parameter of Laser Enabled
    is_laser_enabled = current_scanner.get_parameter(
                                    const_parameter_name.USER_LASER_ENABLED)
    if is_laser_enabled:
        print('Current Laser State\t: ', is_laser_enabled['value'])
        # switch Laser Enabled
        is_laser_enabled['value'] = not is_laser_enabled['value']
        current_scanner.set_parameter(is_laser_enabled)
        is_laser_enabled_new = current_scanner.get_parameter(
                                    const_parameter_name.USER_LASER_ENABLED)
        print('New Laser State\t: ', is_laser_enabled_new['value'])

        # Write current parameters to device's memory
        # current_scanner.write_params_to_scanner()  #commented out in demo
    else:
        print('Could not read scanner parameters')


Ниже приведён результат вывода приложения при успешной установке новых параметров:

.. code-block:: bash

    Old Device Name is              : ABC
    Method 1: New Device Name is    : ABC_TEST
    Method 2: New Device Name2 is   : ABC_TEST2
    Current Device IP               : [192, 168, 1, 30]
    Method 1: New Device IP         : [192, 168, 1, 31]
    Method 2: New Device IP         : [192, 168, 1, 31]
    Current Laser State             :  1
    New Laser State                 :  0