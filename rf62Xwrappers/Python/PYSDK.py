Àfrom PYSDK_functions import *

###################### Python SDK  functions and objects ##################################

# enums
const_protocol=CONST_protocol_types_t
const_scanner_type=CONST_scanner_types_t
const_parameter_name=CONST_parameter_name_keys_t
const_old_data_type=CONST_rf627_old_data_type_t

# # @package PySDK
# Documentation for PySDK module.
# 
# Python wrapper using ctypes over RF627 scanner SDK (rf62Xcore) written in C.

# # Error handler
# Error handler class
class rf627_Error(BaseException):
    pass

# # RF627-old series scanner class
# This class is the main interface for working with RF627-old series scanners.
class rf627_device(object):

## The constructor.
#  @param scanner_object (scanner_base_t) - scanner pointer
#  @param scanner_type (scanner_types_t) - scanner's type (RF627-old, RF627-smart)
#  @param protocol (protocol_types_t) - protocol's type (Service Protocol, ENIP, Modbus-TCP)
    def __init__(self, scanner_object, scanner_type, protocol):
        self.protocol=protocol
        self.scanner_type=scanner_type
        self.scanner_object=scanner_object
        self.connect_to_scanner()
        self.info=parse_py_get_info_about_scanner(lib.get_info_about_scanner(self.scanner_object, self.protocol)) #storing hello_information as Python dictionary
    
## Convert object properties into reader-friendly strings
# @return string
    def __str__(self):
        ret='\n\t---rf627 Device info---\n'
        for key in self.info:
            ret+='\t'+str(key).ljust(20)+'\t=\t'+str(self.info[key])+'\n' 
        return ret 

## Establish connection to the RF62X device
#  @return 0 on success
    def connect_to_scanner(self):
       return lib.connect_to_scanner(self.scanner_object,  self.protocol)

## Disconnect from the RF62X device
#  @return 0 on success
    def disconnect_from_scanner(self):
       return lib.disconnect_from_scanner(self.scanner_object,  self.protocol)
       
           
## Get measurement from scanner's data stream
# @param is_include_zero_points (bool) - include zero points in return profile2D
# @return profile (rf627_profile2D_t). 
# Result profile can be converted to Python dictionary using parse_profile2D() function
    def get_profile2D_from_scanner(self, is_include_zero_points=True):
        return lib.get_profile2D_from_scanner(self.scanner_object, is_include_zero_points, self.protocol)
    
## Get information about scanner from hello packet
# @return hello_information (dict)
    def get_info_about_scanner(self):
        return self.info

## Search parameters by its name
# @param name_as_number (int) - parameter index from const_parameter_name 
# @return param (dict) on success, else - None
    def get_parameter(self,name_as_number):
        ret=lib.get_parameter(self.scanner_object,CONST_parameter_names_array[name_as_number])
        return parse_py_get_parameter(ret) 

## Set parameter by its name
# @param name_as_number (int) - parameter index from const_parameter_name 
# @param new_value - value
# @return 0 if success
    def set_parameter(self,new_value, name_as_number=-1):
        if not isinstance(new_value, dict):
            #value was passed
            if (name_as_number>=0):
                par=self.get_parameter(name_as_number) #old value as dict
                par['value']=new_value #update value
            else:
                par=None #name_as_number was not passed
        else:
            #dict with new value was passed
            par=new_value

        if par:
            par=set_parameter_value(par) #updated (parameter_t) object according to new value
            return lib.set_parameter(self.scanner_object, par['ctypes'])
        else:
            return 1

## Read parameters from device to internal structure.
# @return 0 on success
    def read_params_from_scanner(self):
        return lib.read_params_from_scanner(self.scanner_object, self.protocol)

##  Write current parameters to device memory
# @return 0 on success
    def write_params_to_scanner(self):
        return lib.write_params_to_scanner(self.scanner_object,self.protocol )

## Initialize sdk library
# Must be called once before further calls to any library functions
def sdk_init():
    if not lib.core_init():
        raise rf627_Error('sdk_init')
 
##  Info about SDK version
#  @return info (string) - SDK version
def get_sdk_version():
    return lib.core_version().decode('utf-8')

## Search for RF627old devices over network
#  @param scanner_type (scanner_types_t) - scanner's type (RF627-old, RF627-smart)
#  @param protocol (protocol_types_t) - protocol's type (Service Protocol, ENIP, Modbus-TCP)
#  @return scannerList(list) - list of rf627_device objects
def search_scanners(scanner_type=const_scanner_type.kRF627_OLD, protocol=const_protocol.kSERVICE):
    scannerList=[]
#  Iterate over all available network adapters in the current operatings system to send "Hello" requests.
    for interface in ni.interfaces():
        try:
            iface_data = ni.ifaddresses(interface)
            for family in iface_data:
                if family != ni.AF_INET:
                    continue
                for address in iface_data[family]:
                    host_ip_addr = inet_addr(address['addr'])
                    host_mask = inet_addr('255.255.255.0')
                    # Set adapter's settings
                    lib.set_platform_adapter_settings(host_mask, host_ip_addr)
                    
                    #temporary variable
                    _scannerList = vector_t()
                    #  Search for RF627-old devices over network by Service Protocol.
                    lib.search_scanners(byref(_scannerList), scanner_type, protocol)
                    #Append device to list of rf627_device objects
                    for i in range(_scannerList.count):
                        scannerList.append( rf627_device(cast(_scannerList.data[i], POINTER(scanner_base_t)), scanner_type, protocol) )

        except ValueError:
            pass
    
    return scannerList

## Select device from scannerList
#  @param scannerList(list) - list of rf627_device objects
#  @param option (dict) - scanner's property as filter parameter. 
#  Option fileds (rf627_old_hello_info_by_service_protocol) - device_name, serial_number,ip_address, mac_address, profile_port, 
#  service_port, firmware_version, hardware_version, z_begin, z_range, x_begin, x_end
#  @return scanner(rf627_device) - first rf627_device object from scannerList with corresponding option
def select_scanner(scannerList, **option):
    if len(option.keys())!=1:
        raise rf627_Error('select_scanner: only 1 argument supported')
    key = next(iter(option))
    value = next(iter(option.values()))
    for i in range(len(scannerList)):
        info=scannerList[i].get_info_about_scanner()
        if key in info.keys():
            if value==str(info[key]):
                print('Selected scanner by', key,value)
                return scannerList[i]
    print('Scanner was not selected by', key,value)
    return None
    
