using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Net.NetworkInformation;
using System.Linq;

namespace SDK
{
    namespace SCANNERS
    {
        public unsafe partial class RF62X
        {
    
            /// <summary>
            /// SdkVersion - Return info about SDK version
            /// </summary>
            /// <returns>SDK version</returns>
            public static string SdkVersion()
            {
                return Marshal.PtrToStringAnsi((IntPtr)(sdk_version()));
            }

            /// <summary>
            /// SdkInit - Initialize sdk library
            /// </summary>
            /// <remarks>
            /// Must be called once before further calls to any library functions
            /// </remarks> 
            /// <returns>true if success.</returns>
            public static bool SdkInit()
            {
                byte result = core_init();
                bool isInit = (result & 0x01) == 1;
                return isInit;
            }

            /// <summary>
            /// SdkCleanup - Cleanup resources allocated with sdk_init() function
            /// </summary>
            public static void SdkCleanup()
            {

            }

            /// <summary>
            /// RF627old - This class is the main interface for working with RF627-old series scanners.
            /// </summary>
            public unsafe class RF627old
            {
                private void* scannerBase { get; set; }
                private bool isConnected { get; set; }
                private PROTOCOL_TYPES currentProtocol { get; set; }
                private System.Threading.Mutex paramMutex { get; set; }
                private System.Threading.Mutex profileMutex { get; set; }

                public RF627old(void* Base)
                {
                    scannerBase = Base;
                    isConnected = false;
                    currentProtocol = PROTOCOL_TYPES.SERVICE;
                    paramMutex = new System.Threading.Mutex();
                    profileMutex = new System.Threading.Mutex();
                }

                ~RF627old()
                {
                    scanner_base_t* _base = (scanner_base_t*)this.scannerBase;
                    free_scanner(_base);
                }

                /// <summary>
                /// Search for RF627old devices over network
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>List of RF627old devices</returns>
                public static List<RF627old> Search(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    List<RF627old> result = new List<RF627old>();

                    switch (protocol)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                vector_t* scanners = stackalloc vector_t[1];
                                vector_init(&scanners);

                                NetworkInterface[] networkInterfaces = NetworkInterface.GetAllNetworkInterfaces();
                                foreach (NetworkInterface adapter in networkInterfaces)
                                {
                                    if (adapter.OperationalStatus == OperationalStatus.Up && (adapter.NetworkInterfaceType == NetworkInterfaceType.Wireless80211 || adapter.NetworkInterfaceType == NetworkInterfaceType.Ethernet))
                                    {
                                        //Console.WriteLine("Choose \"{0}\" Network Interface", adapter.Name.ToString());
                                        foreach (UnicastIPAddressInformation ip in adapter.GetIPProperties().UnicastAddresses)
                                        {
                                            if (ip.Address.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork)
                                            {
                                                byte[] MaskBytes = ip.IPv4Mask.GetAddressBytes();
                                                byte[] IPBytes = ip.Address.GetAddressBytes();
                                                if (BitConverter.IsLittleEndian)
                                                {
                                                    Array.Reverse(MaskBytes);
                                                    Array.Reverse(IPBytes);
                                                }

                                                uint IPv4Mask = BitConverter.ToUInt32(MaskBytes, 0);
                                                uint IPv4Address = BitConverter.ToUInt32(IPBytes, 0);
                                                set_platform_adapter_settings(IPv4Mask, IPv4Address);

                                                search_scanners(scanners, SCANNER_TYPES.RF627_OLD, 1000, PROTOCOL_TYPES.SERVICE);
                                                //Console.WriteLine("Send hello packet from {0} IP Address", ip.Address.ToString());
                                            }
                                        }

                                    }
                                }





                                for (int i = 0; i < vector_count(scanners).ToUInt32(); i++)
                                {
                                    scanner_base_t* t = ((scanner_base_t*)vector_get(scanners, (UIntPtr)i));

                                    if (t->type == SCANNER_TYPES.RF627_OLD)
                                    {
                                        result.Add(new RF627old(t));
                                    }

                                }

                                break;
                            }
                    }

                    return result;

                }

                /// <summary>
                /// Get information about scanner from hello packet
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>Hello_info on success</returns>
                public HelloInfo GetInfo(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                hello_information info = get_info_about_scanner(((scanner_base_t*)this.scannerBase), p);
                                return new HelloInfo((void*)info.rf627old_hello_info_service_protocol, SCANNER_TYPES.RF627_OLD, protocol);
                            }
                        default:
                            HelloInfo hello_info = new HelloInfo(null, SCANNER_TYPES.RF627_OLD, protocol);
                            return hello_info;
                    }
                }

                /// <summary>
                /// Establish connection to the RF627old device
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>true on success</returns>
                public bool Connect(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                if (isConnected == false)
                                {
                                    result = connect_to_scanner(
                                            ((scanner_base_t*)scannerBase), PROTOCOL_TYPES.SERVICE);
                                    isConnected = result == 1 ? true : false;
                                    return isConnected;
                                }
                                else
                                {
                                    return isConnected;
                                }
                            }
                    }
                    return false;
                }

                /// <summary>
                /// Close connection to the device
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>true on success</returns>
                public bool Disconnect(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                if (isConnected)
                                {
                                    result = disconnect_from_scanner(
                                            ((scanner_base_t*)this.scannerBase), PROTOCOL_TYPES.SERVICE);
                                    isConnected = result == 1 ? false : true;
                                    return isConnected;
                                }
                                else
                                {
                                    isConnected = false;
                                    return isConnected;
                                }
                            }
                    }
                    return false;
                }

                /// <summary>
                /// Get 2D measurement from scanner’s data stream
                /// </summary>
                /// <param name="zero_points">include zero points in return Profile</param>
                /// <param name="realtime">Enable getting profile in real time (buffering is disabled)</param>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>Profile</returns>
                public Profile2D GetProfile(bool zero_points = true, bool realtime = true, PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    this.profileMutex.WaitOne();

                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    if (isConnected)
                    {
                        switch (p)
                        {
                            case PROTOCOL_TYPES.SERVICE:
                                {
                                    // Get profile from scanner's data stream by Service Protocol.
                                    rf627_profile2D_t* profile_from_scanner = get_profile2D_from_scanner(
                                                (scanner_base_t*)scannerBase, zero_points, realtime, PROTOCOL_TYPES.SERVICE);

                                    if (profile_from_scanner != null)
                                    {
                                        Profile2D result = new Profile2D(profile_from_scanner);
                                        this.profileMutex.ReleaseMutex();
                                        return result;
                                    }
                                    platform_free(profile_from_scanner);
                                    break;
                                }
                            default:
                                break;
                        }
                    }

                    this.profileMutex.ReleaseMutex();
                    return null;

                }

                /// <summary>
                /// Read parameters from device to internal structure. This structure is accessible via GetParam() functions
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>true on success</returns>
                public bool ReadParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                this.paramMutex.WaitOne();

                                result = read_params_from_scanner(
                                            (scanner_base_t*)scannerBase, 3000, PROTOCOL_TYPES.SERVICE);

                                this.paramMutex.ReleaseMutex();
                                return result == 1 ? true : false;
                            }
                    }
                    return false;
                }


                /// <summary>
                /// Write current parameters to device’s memory
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>true on success</returns>
                public bool WriteParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                this.paramMutex.WaitOne();

                                result = write_params_to_scanner(
                                            (scanner_base_t*)scannerBase, 3000, PROTOCOL_TYPES.SERVICE);

                                this.paramMutex.ReleaseMutex();
                                return result == 1 ? true : false;
                            }
                    }
                    return false;
                }

                /// <summary>
                /// Search parameters by his info
                /// </summary>
                /// <param name="paramInfo">info of parameter</param>
                /// <returns>param on success, else - null</returns>
                public dynamic GetParam(PARAMS.Description paramInfo)
                {
                    return GetParam(paramInfo.Key);
                }

                /// <summary>
                /// Search parameters by his name
                /// </summary>
                /// <param name="nameKey">name of parameter</param>
                /// <returns>param on success, else - null</returns>
                public dynamic GetParam(string nameKey)
                {
                    this.paramMutex.WaitOne();

                    byte[] bytes = Encoding.ASCII.GetBytes(nameKey);
                    IntPtr unmanagedPointer = Marshal.AllocHGlobal(bytes.Length);
                    Marshal.Copy(bytes, 0, unmanagedPointer, bytes.Length);

                    parameter_t* param = get_parameter((scanner_base_t*)scannerBase, (byte*)unmanagedPointer);
                    if (param != null)
                        switch (Marshal.PtrToStringAnsi((IntPtr)param->_base.type))
                        {
                            case "unkn_t":
                                {
                                    this.paramMutex.ReleaseMutex();
                                    break;
                                }
                            case "uint32_t":
                                {
                                    List<Parameter<uint>.ValuesEnum> valEnum = new List<Parameter<uint>.ValuesEnum>();
                                    if (param->val_uint->enumValues != null)
                                        for (int i = 0; i < param->val_uint->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Parameter<uint>.ValuesEnum(
                                                    (uint)param->val_uint->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.label),
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.key)));

                                    Parameter<uint> result = new Parameter<uint>(
                                        param,
                                        param->val_uint->min,
                                        param->val_uint->max,
                                        1,
                                        1,
                                        param->val_uint->defValue,
                                        valEnum,
                                        param->val_uint->step,
                                        param->val_uint->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "uint64_t":
                                {
                                    List<Parameter<ulong>.ValuesEnum> valEnum = new List<Parameter<ulong>.ValuesEnum>();
                                    if (param->val_uint64->enumValues != null)
                                        for (int i = 0; i < param->val_uint64->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Parameter<ulong>.ValuesEnum(
                                                    (ulong)param->val_uint->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.label),
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.key)));

                                    Parameter<ulong> result = new Parameter<ulong>(
                                        param,
                                        param->val_uint64->min,
                                        param->val_uint64->max,
                                        1,
                                        1,
                                        param->val_uint64->defValue,
                                        valEnum,
                                        param->val_uint64->step,
                                        param->val_uint64->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "int32_t":
                                {
                                    List<Parameter<int>.ValuesEnum> valEnum = new List<Parameter<int>.ValuesEnum>();
                                    if (param->val_int->enumValues != null)
                                        for (int i = 0; i < param->val_int->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Parameter<int>.ValuesEnum(
                                                    (int)param->val_uint->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.label),
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.key)));

                                    Parameter<int> result = new Parameter<int>(
                                        param,
                                        param->val_int->min,
                                        param->val_int->max,
                                        1,
                                        1,
                                        param->val_int->defValue,
                                        valEnum,
                                        param->val_int->step,
                                        param->val_int->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "int64_t":
                                {
                                    List<Parameter<long>.ValuesEnum> valEnum = new List<Parameter<long>.ValuesEnum>();
                                    if (param->val_int64->enumValues != null)
                                        for (int i = 0; i < param->val_int64->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Parameter<long>.ValuesEnum(
                                                    (long)param->val_uint->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.label),
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.key)));

                                    Parameter<long> result = new Parameter<long>(
                                        param,
                                        param->val_int64->min,
                                        param->val_int64->max,
                                        1,
                                        1,
                                        param->val_int64->defValue,
                                        valEnum,
                                        param->val_int64->step,
                                        param->val_int64->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "float_t":
                                {
                                    Parameter<float> result = new Parameter<float>(
                                        param,
                                        param->val_flt->min,
                                        param->val_flt->max,
                                        1,
                                        1,
                                        param->val_flt->defValue,
                                        null,
                                        param->val_flt->step,
                                        param->val_flt->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "double_t":
                                {
                                    Parameter<double> result = new Parameter<double>(
                                        param,
                                        param->val_dbl->min,
                                        param->val_dbl->max,
                                        1,
                                        1,
                                        param->val_dbl->defValue,
                                        null,
                                        param->val_dbl->step,
                                        param->val_dbl->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "u32_arr_t":
                                {
                                    List<uint> defValue = new List<uint>();
                                    for (int i = 0; i < param->arr_uint->defCount; i++)
                                    {
                                        defValue.Add(param->arr_uint->defValue[i]);
                                    }
                                    List<uint> value = new List<uint>();
                                    for (int i = 0; i < param->arr_uint->count; i++)
                                    {
                                        value.Add(param->arr_uint->value[i]);
                                    }
                                    Parameter<List<uint>> result = new Parameter<List<uint>>(
                                       param,
                                       param->arr_uint->min,
                                       param->arr_uint->max,
                                       param->arr_uint->maxCount,
                                       param->arr_uint->defCount,
                                       defValue,
                                       null,
                                       param->arr_uint->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "u64_arr_t":
                                {
                                    List<ulong> defValue = new List<ulong>();
                                    for (int i = 0; i < param->arr_uint64->defCount; i++)
                                    {
                                        defValue.Add(param->arr_uint64->defValue[i]);
                                    }
                                    List<ulong> value = new List<ulong>();
                                    for (int i = 0; i < param->arr_uint64->count; i++)
                                    {
                                        value.Add(param->arr_uint64->value[i]);
                                    }
                                    Parameter<List<ulong>> result = new Parameter<List<ulong>>(
                                       param,
                                       param->arr_uint64->min,
                                       param->arr_uint64->max,
                                       param->arr_uint64->maxCount,
                                       param->arr_uint64->defCount,
                                       defValue,
                                       null,
                                       param->arr_uint64->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "i32_arr_t":
                                {
                                    List<int> defValue = new List<int>();
                                    for (int i = 0; i < param->arr_int->defCount; i++)
                                    {
                                        defValue.Add(param->arr_int->defValue[i]);
                                    }
                                    List<int> value = new List<int>();
                                    for (int i = 0; i < param->arr_int->count; i++)
                                    {
                                        value.Add(param->arr_int->value[i]);
                                    }
                                    Parameter<List<int>> result = new Parameter<List<int>>(
                                       param,
                                       param->arr_int->min,
                                       param->arr_int->max,
                                       param->arr_int->maxCount,
                                       param->arr_int->defCount,
                                       defValue,
                                       null,
                                       param->arr_int->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "i64_arr_t":
                                {
                                    List<long> defValue = new List<long>();
                                    for (int i = 0; i < param->arr_int64->defCount; i++)
                                    {
                                        defValue.Add(param->arr_int64->defValue[i]);
                                    }
                                    List<long> value = new List<long>();
                                    for (int i = 0; i < param->arr_int64->count; i++)
                                    {
                                        value.Add(param->arr_int64->value[i]);
                                    }
                                    Parameter<List<long>> result = new Parameter<List<long>>(
                                       param,
                                       param->arr_int64->min,
                                       param->arr_int64->max,
                                       param->arr_int64->maxCount,
                                       param->arr_int64->defCount,
                                       defValue,
                                       null,
                                       param->arr_int64->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "flt_array_t":
                                {
                                    List<float> defValue = new List<float>();
                                    for (int i = 0; i < param->arr_flt->defCount; i++)
                                    {
                                        defValue.Add(param->arr_flt->defValue[i]);
                                    }
                                    List<float> value = new List<float>();
                                    for (int i = 0; i < param->arr_flt->count; i++)
                                    {
                                        value.Add(param->arr_flt->value[i]);
                                    }
                                    Parameter<List<float>> result = new Parameter<List<float>>(
                                       param,
                                       param->arr_flt->min,
                                       param->arr_flt->max,
                                       param->arr_flt->maxCount,
                                       param->arr_flt->defCount,
                                       defValue,
                                       null,
                                       param->arr_flt->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "dbl_array_t":
                                {
                                    List<double> defValue = new List<double>();
                                    for (int i = 0; i < param->arr_dbl->defCount; i++)
                                    {
                                        defValue.Add(param->arr_dbl->defValue[i]);
                                    }
                                    List<double> value = new List<double>();
                                    for (int i = 0; i < param->arr_dbl->count; i++)
                                    {
                                        value.Add(param->arr_dbl->value[i]);
                                    }
                                    Parameter<List<double>> result = new Parameter<List<double>>(
                                       param,
                                       param->arr_dbl->min,
                                       param->arr_dbl->max,
                                       param->arr_dbl->maxCount,
                                       param->arr_dbl->defCount,
                                       defValue,
                                       null,
                                       param->arr_dbl->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "string_t":
                                {
                                    Parameter<string> result = new Parameter<string>(
                                        param,
                                        "0",
                                        param->val_str->maxLen.ToString(),
                                        1,
                                        1,
                                        Marshal.PtrToStringAnsi((IntPtr)(param->val_str->defValue)),
                                        null,
                                        "",
                                        Marshal.PtrToStringAnsi((IntPtr)(param->val_str->value)));
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            default:
                                {
                                    this.paramMutex.ReleaseMutex();
                                    return null;
                                }
                        }

                    this.paramMutex.ReleaseMutex();
                    return null;

                }

                /// <summary>
                /// Update parameter in internal structure
                /// </summary>
                /// <param name="param">Updated parameter</param>
                /// <returns>true on success, else - false</returns>
                public bool SetParam(dynamic param)
                {
                    int a = sizeof(value_base_t);

                    byte[] name = Encoding.ASCII.GetBytes(param.name);
                    IntPtr name_ptr = Marshal.AllocHGlobal(name.Length);
                    Marshal.Copy(name, 0, name_ptr, name.Length);

                    byte[] type = Encoding.ASCII.GetBytes(param.type);
                    IntPtr type_ptr = Marshal.AllocHGlobal(type.Length);
                    Marshal.Copy(type, 0, type_ptr, type.Length);

                    byte[] access = Encoding.ASCII.GetBytes(param.access);
                    IntPtr access_ptr = Marshal.AllocHGlobal(access.Length);
                    Marshal.Copy(access, 0, access_ptr, access.Length);

                    byte[] units = Encoding.ASCII.GetBytes(param.units);
                    IntPtr units_ptr = Marshal.AllocHGlobal(units.Length);
                    Marshal.Copy(units, 0, units_ptr, units.Length);

                    parameter_t* p = create_parameter_from_type((byte*)type_ptr);

                    if (p != null)
                    {
                        p->_base.name = (byte*)name_ptr;
                        p->_base.type = (byte*)type_ptr;
                        p->_base.access = (byte*)access_ptr;
                        p->_base.units = (byte*)units_ptr;
                        if (param.type == "string_t")
                        {
                            byte[] value = Encoding.ASCII.GetBytes(param.GetValue() + '\0');
                            IntPtr value_ptr = Marshal.AllocHGlobal(value.Length);
                            Marshal.Copy(value, 0, value_ptr, value.Length);
                            p->val_str->value = (byte*)value_ptr;
                            p->_base.size = (uint)value.Length + 1;
                        }
                        else if (param.type == "int32_t")
                        {
                            p->val_int->value = param.GetValue();
                        }
                        else if (param.type == "int64_t")
                        {
                            p->val_int64->value = param.GetValue();
                        }
                        else if (param.type == "uint32_t")
                        {
                            p->val_uint->value = param.GetValue();
                        }
                        else if (param.type == "uint64_t")
                        {
                            p->val_uint64->value = param.GetValue();
                        }
                        else if (param.type == "float_t")
                        {
                            p->val_flt->value = param.GetValue();
                        }
                        else if (param.type == "double_t")
                        {
                            p->val_dbl->value = param.GetValue();
                        }
                        else if (param.type == "u32_arr_t")
                        {
                            List<uint> list = param.GetValue();
                            int[] value = new int[list.Count];
                            for (int j = 0; j < list.Count; j++)
                                value[j] = Convert.ToInt32(list[j]);
                            IntPtr value_ptr = Marshal.AllocHGlobal(value.Length * sizeof(uint));
                            Marshal.Copy(value, 0, value_ptr, value.Length);
                            p->arr_uint->value = (uint*)(void*)(Marshal.AllocHGlobal(value.Length * sizeof(uint)));
                            for (int j = 0; j < list.Count; j++)
                                p->arr_uint->value[j] = Convert.ToUInt32(((uint*)(value_ptr))[j]);
                            p->_base.size = Convert.ToUInt32(list.Count * sizeof(uint));
                        }
                        this.paramMutex.WaitOne();
                        set_parameter((scanner_base_t*)scannerBase, p);
                        this.paramMutex.ReleaseMutex();
                        return true;
                    }
                    return false;
                }

            }

            /// <summary>
            /// RF627smart - This class is the main interface for working with RF62X-smart series scanners.
            /// </summary>
            public unsafe class RF627smart
            {
                /// <summary>
                /// Search for RF627smart devices over network
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>List of RF627smart devices</returns>
                public static List<RF627smart> Search(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    List<RF627smart> result = new List<RF627smart>();

                    switch (protocol)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                vector_t* scanners;// = stackalloc vector_t[1];
                                vector_init(&scanners);

                                NetworkInterface[] networkInterfaces = NetworkInterface.GetAllNetworkInterfaces();
                                foreach (NetworkInterface adapter in networkInterfaces)
                                {
                                    if (adapter.OperationalStatus == OperationalStatus.Up && (adapter.NetworkInterfaceType == NetworkInterfaceType.Wireless80211 || adapter.NetworkInterfaceType == NetworkInterfaceType.Ethernet))
                                    {
                                        //Console.WriteLine("Choose \"{0}\" Network Interface", adapter.Name.ToString());
                                        foreach (UnicastIPAddressInformation ip in adapter.GetIPProperties().UnicastAddresses)
                                        {
                                            if (ip.Address.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork)
                                            {
                                                byte[] MaskBytes = ip.IPv4Mask.GetAddressBytes();
                                                byte[] IPBytes = ip.Address.GetAddressBytes();
                                                if (BitConverter.IsLittleEndian)
                                                {
                                                    Array.Reverse(MaskBytes);
                                                    Array.Reverse(IPBytes);
                                                }

                                                uint IPv4Mask = BitConverter.ToUInt32(MaskBytes, 0);                                                
                                                uint IPv4Address = BitConverter.ToUInt32(IPBytes, 0);
                                                set_platform_adapter_settings(IPv4Mask, IPv4Address);

                                                search_scanners(scanners, SCANNER_TYPES.RF62X_SMART, 1000, PROTOCOL_TYPES.SERVICE);
                                                
                                                Console.WriteLine("Send hello packet from {0} IP Address", ip.Address.ToString());
                                            }
                                        }

                                    }
                                }


                                for (int i = 0; i < vector_count(scanners).ToUInt32(); i++)
                                {
                                    scanner_base_t* t = ((scanner_base_t*)vector_get(scanners, (UIntPtr)i));

                                    if (t->type == SCANNER_TYPES.RF62X_SMART)
                                    {
                                        result.Add(new RF627smart(t));
                                    }

                                }

                                break;
                            }
                    }

                    return result;
                }

                /// <summary>
                /// Get information about scanner from hello packet
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>Hello_info on success</returns>
                public HelloInfo GetInfo(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                hello_information info = get_info_about_scanner(((scanner_base_t*)this.scannerBase), p);
                                return new HelloInfo((void*)info.RF627smart_hello_info_service_protocol, SCANNER_TYPES.RF62X_SMART, protocol);
                            }
                        default:
                            HelloInfo hello_info = new HelloInfo(null, SCANNER_TYPES.RF62X_SMART, protocol);
                            return hello_info;
                    }
                }

                /// <summary>
                /// Establish connection to the RF627smart device
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>true on success</returns>
                public bool Connect(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                if (isConnected == false)
                                {
                                    result = connect_to_scanner(
                                            ((scanner_base_t*)scannerBase), PROTOCOL_TYPES.SERVICE);
                                    isConnected = result == 1 ? true : false;
                                    return isConnected;
                                }
                                else
                                {
                                    return isConnected;
                                }
                            }
                    }
                    return false;
                }

                /// <summary>
                /// Check connection with RF627smart device
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>true on success</returns>
                public bool CheckConnection(uint timeout, PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                if (isConnected)
                                {
                                    result = check_connection_to_scanner(
                                            ((scanner_base_t*)this.scannerBase), timeout, PROTOCOL_TYPES.SERVICE);
                                    isConnected = result == 1 ? true : false;
                                    return isConnected;
                                }
                                else
                                {
                                    return isConnected;
                                }
                            }
                    }
                    return false;
                }

                /// <summary>
                /// Close connection to the device
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>true on success</returns>
                public bool Disconnect(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                if (isConnected)
                                {
                                    result = disconnect_from_scanner(
                                            ((scanner_base_t*)this.scannerBase), PROTOCOL_TYPES.SERVICE);
                                    isConnected = result == 1 ? false : true;
                                    return isConnected;
                                }
                                else
                                {
                                    isConnected = false;
                                    return isConnected;
                                }
                            }
                    }
                    return false;
                }

                /// <summary>
                /// Get 2D measurement from scanner’s data stream
                /// </summary>
                /// <param name="zero_points">include zero points in return Profile</param>
                /// <param name="realtime">Enable getting profile in real time (buffering is disabled)</param>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>Profile</returns>
                public Profile2D GetProfile(
                    bool zero_points = true, bool realtime = true, 
                    PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    this.profileMutex.WaitOne();

                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    if (isConnected)
                    {
                        switch (p)
                        {
                            case PROTOCOL_TYPES.SERVICE:
                                {
                                    // Get profile from scanner's data stream by Service Protocol.
                                    rf627_profile2D_t* profile_from_scanner = get_profile2D_from_scanner(
                                                (scanner_base_t*)scannerBase, zero_points, realtime, PROTOCOL_TYPES.SERVICE);

                                    if (profile_from_scanner != null)
                                    {
                                        Profile2D result = new Profile2D(profile_from_scanner);
                                        this.profileMutex.ReleaseMutex();
                                        return result;
                                    }
                                    platform_free(profile_from_scanner);
                                    break;
                                }
                            default:
                                break;
                        }
                    }

                    this.profileMutex.ReleaseMutex();
                    return null;
                }

                /// <summary>
                /// Read parameters from device to internal structure. This structure is accessible via GetParam() functions
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>true on success</returns>
                public bool ReadParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                this.paramMutex.WaitOne();

                                result = read_params_from_scanner(
                                            (scanner_base_t*)scannerBase, 3000, PROTOCOL_TYPES.SERVICE);

                                this.paramMutex.ReleaseMutex();
                                return result == 1 ? true : false;
                            }
                    }
                    return false;
                }

                /// <summary>
                /// Write current parameters to device’s memory
                /// </summary>
                /// <param name="protocol">protocol’s type (Service Protocol, ENIP, Modbus-TCP)</param>
                /// <returns>true on success</returns>
                public bool WriteParams(PROTOCOL_TYPES protocol = PROTOCOL_TYPES.SERVICE)
                {
                    PROTOCOL_TYPES p;
                    if (protocol == PROTOCOL_TYPES.CURRENT)
                        p = this.currentProtocol;
                    else
                        p = protocol;

                    switch (p)
                    {
                        case PROTOCOL_TYPES.SERVICE:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                this.paramMutex.WaitOne();

                                result = write_params_to_scanner(
                                            (scanner_base_t*)scannerBase, 3000, PROTOCOL_TYPES.SERVICE);

                                this.paramMutex.ReleaseMutex();
                                return result == 1 ? true : false;
                            }
                    }
                    return false;
                }

                /// <summary>
                /// Search parameters by his info
                /// </summary>
                /// <param name="paramInfo">info of parameter</param>
                /// <returns>param on success, else - null</returns>
                public dynamic GetParam(PARAMS.Description paramInfo)
                {
                    return GetParam(paramInfo.Key);
                }

                /// <summary>
                /// Search parameters by his name
                /// </summary>
                /// <param name="nameKey">name of parameter</param>
                /// <returns>param on success, else - null</returns>
                public dynamic GetParam(string nameKey)
                {
                    this.paramMutex.WaitOne();

                    byte[] bytes = Encoding.ASCII.GetBytes(nameKey);
                    IntPtr unmanagedPointer = Marshal.AllocHGlobal(bytes.Length);
                    Marshal.Copy(bytes, 0, unmanagedPointer, bytes.Length);

                    parameter_t* param = get_parameter((scanner_base_t*)scannerBase, (byte*)unmanagedPointer);
                    if (param != null)
                        switch (Marshal.PtrToStringAnsi((IntPtr)param->_base.type))
                        {
                            case "unkn_t":
                                {
                                    this.paramMutex.ReleaseMutex();
                                    break;
                                }
                            case "uint32_t":
                                {
                                    List<Parameter<uint>.ValuesEnum> valEnum = new List<Parameter<uint>.ValuesEnum>();
                                    if (param->val_uint->enumValues != null)
                                        for (int i = 0; i < param->val_uint->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Parameter<uint>.ValuesEnum(
                                                    (uint)param->val_uint->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.label),
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.key)));

                                    Parameter<uint> result = new Parameter<uint>(
                                        param,
                                        param->val_uint->min,
                                        param->val_uint->max,
                                        1,
                                        1,
                                        param->val_uint->defValue,
                                        valEnum,
                                        param->val_uint->step,
                                        param->val_uint->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "uint64_t":
                                {
                                    List<Parameter<ulong>.ValuesEnum> valEnum = new List<Parameter<ulong>.ValuesEnum>();
                                    if (param->val_uint64->enumValues != null)
                                        for (int i = 0; i < param->val_uint64->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Parameter<ulong>.ValuesEnum(
                                                    (ulong)param->val_uint->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.label),
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.key)));

                                    Parameter<ulong> result = new Parameter<ulong>(
                                        param,
                                        param->val_uint64->min,
                                        param->val_uint64->max,
                                        1,
                                        1,
                                        param->val_uint64->defValue,
                                        valEnum,
                                        param->val_uint64->step,
                                        param->val_uint64->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "int32_t":
                                {
                                    List<Parameter<int>.ValuesEnum> valEnum = new List<Parameter<int>.ValuesEnum>();
                                    if (param->val_int->enumValues != null)
                                        for (int i = 0; i < param->val_int->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Parameter<int>.ValuesEnum(
                                                    (int)param->val_uint->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.label),
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.key)));

                                    Parameter<int> result = new Parameter<int>(
                                        param,
                                        param->val_int->min,
                                        param->val_int->max,
                                        1,
                                        1,
                                        param->val_int->defValue,
                                        valEnum,
                                        param->val_int->step,
                                        param->val_int->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "int64_t":
                                {
                                    List<Parameter<long>.ValuesEnum> valEnum = new List<Parameter<long>.ValuesEnum>();
                                    if (param->val_int64->enumValues != null)
                                        for (int i = 0; i < param->val_int64->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Parameter<long>.ValuesEnum(
                                                    (long)param->val_uint->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.label),
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.key)));

                                    Parameter<long> result = new Parameter<long>(
                                        param,
                                        param->val_int64->min,
                                        param->val_int64->max,
                                        1,
                                        1,
                                        param->val_int64->defValue,
                                        valEnum,
                                        param->val_int64->step,
                                        param->val_int64->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "float_t":
                                {
                                    Parameter<float> result = new Parameter<float>(
                                        param,
                                        param->val_flt->min,
                                        param->val_flt->max,
                                        1,
                                        1,
                                        param->val_flt->defValue,
                                        null,
                                        param->val_flt->step,
                                        param->val_flt->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "double_t":
                                {
                                    Parameter<double> result = new Parameter<double>(
                                        param,
                                        param->val_dbl->min,
                                        param->val_dbl->max,
                                        1,
                                        1,
                                        param->val_dbl->defValue,
                                        null,
                                        param->val_dbl->step,
                                        param->val_dbl->value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "u32_arr_t":
                                {
                                    List<uint> defValue = new List<uint>();
                                    for (int i = 0; i < param->arr_uint->defCount; i++)
                                    {
                                        defValue.Add(param->arr_uint->defValue[i]);
                                    }
                                    List<uint> value = new List<uint>();
                                    for (int i = 0; i < param->arr_uint->count; i++)
                                    {
                                        value.Add(param->arr_uint->value[i]);
                                    }
                                    Parameter<List<uint>> result = new Parameter<List<uint>>(
                                       param,
                                       param->arr_uint->min,
                                       param->arr_uint->max,
                                       param->arr_uint->maxCount,
                                       param->arr_uint->defCount,
                                       defValue,
                                       null,
                                       param->arr_uint->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "u64_arr_t":
                                {
                                    List<ulong> defValue = new List<ulong>();
                                    for (int i = 0; i < param->arr_uint64->defCount; i++)
                                    {
                                        defValue.Add(param->arr_uint64->defValue[i]);
                                    }
                                    List<ulong> value = new List<ulong>();
                                    for (int i = 0; i < param->arr_uint64->count; i++)
                                    {
                                        value.Add(param->arr_uint64->value[i]);
                                    }
                                    Parameter<List<ulong>> result = new Parameter<List<ulong>>(
                                       param,
                                       param->arr_uint64->min,
                                       param->arr_uint64->max,
                                       param->arr_uint64->maxCount,
                                       param->arr_uint64->defCount,
                                       defValue,
                                       null,
                                       param->arr_uint64->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "i32_arr_t":
                                {
                                    List<int> defValue = new List<int>();
                                    for (int i = 0; i < param->arr_int->defCount; i++)
                                    {
                                        defValue.Add(param->arr_int->defValue[i]);
                                    }
                                    List<int> value = new List<int>();
                                    for (int i = 0; i < param->arr_int->count; i++)
                                    {
                                        value.Add(param->arr_int->value[i]);
                                    }
                                    Parameter<List<int>> result = new Parameter<List<int>>(
                                       param,
                                       param->arr_int->min,
                                       param->arr_int->max,
                                       param->arr_int->maxCount,
                                       param->arr_int->defCount,
                                       defValue,
                                       null,
                                       param->arr_int->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "i64_arr_t":
                                {
                                    List<long> defValue = new List<long>();
                                    for (int i = 0; i < param->arr_int64->defCount; i++)
                                    {
                                        defValue.Add(param->arr_int64->defValue[i]);
                                    }
                                    List<long> value = new List<long>();
                                    for (int i = 0; i < param->arr_int64->count; i++)
                                    {
                                        value.Add(param->arr_int64->value[i]);
                                    }
                                    Parameter<List<long>> result = new Parameter<List<long>>(
                                       param,
                                       param->arr_int64->min,
                                       param->arr_int64->max,
                                       param->arr_int64->maxCount,
                                       param->arr_int64->defCount,
                                       defValue,
                                       null,
                                       param->arr_int64->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "flt_array_t":
                                {
                                    List<float> defValue = new List<float>();
                                    for (int i = 0; i < param->arr_flt->defCount; i++)
                                    {
                                        defValue.Add(param->arr_flt->defValue[i]);
                                    }
                                    List<float> value = new List<float>();
                                    for (int i = 0; i < param->arr_flt->count; i++)
                                    {
                                        value.Add(param->arr_flt->value[i]);
                                    }
                                    Parameter<List<float>> result = new Parameter<List<float>>(
                                       param,
                                       param->arr_flt->min,
                                       param->arr_flt->max,
                                       param->arr_flt->maxCount,
                                       param->arr_flt->defCount,
                                       defValue,
                                       null,
                                       param->arr_flt->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "dbl_array_t":
                                {
                                    List<double> defValue = new List<double>();
                                    for (int i = 0; i < param->arr_dbl->defCount; i++)
                                    {
                                        defValue.Add(param->arr_dbl->defValue[i]);
                                    }
                                    List<double> value = new List<double>();
                                    for (int i = 0; i < param->arr_dbl->count; i++)
                                    {
                                        value.Add(param->arr_dbl->value[i]);
                                    }
                                    Parameter<List<double>> result = new Parameter<List<double>>(
                                       param,
                                       param->arr_dbl->min,
                                       param->arr_dbl->max,
                                       param->arr_dbl->maxCount,
                                       param->arr_dbl->defCount,
                                       defValue,
                                       null,
                                       param->arr_dbl->step,
                                       value);
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            case "string_t":
                                {
                                    Parameter<string> result = new Parameter<string>(
                                        param,
                                        "0",
                                        param->val_str->maxLen.ToString(),
                                        1,
                                        1,
                                        Marshal.PtrToStringAnsi((IntPtr)(param->val_str->defValue)),
                                        null,
                                        "",
                                        Marshal.PtrToStringAnsi((IntPtr)(param->val_str->value)));
                                    this.paramMutex.ReleaseMutex();
                                    return result;
                                }
                            default:
                                {
                                    this.paramMutex.ReleaseMutex();
                                    return null;
                                }
                        }

                    this.paramMutex.ReleaseMutex();
                    return null;

                }

                /// <summary>
                /// Update parameter in internal structure
                /// </summary>
                /// <param name="param">Updated parameter</param>
                /// <returns>true on success, else - false</returns>
                public bool SetParam(dynamic param)
                {
                    int a = sizeof(value_base_t);

                    byte[] name = Encoding.ASCII.GetBytes(param.name);
                    IntPtr name_ptr = Marshal.AllocHGlobal(name.Length);
                    Marshal.Copy(name, 0, name_ptr, name.Length);

                    byte[] type = Encoding.ASCII.GetBytes(param.type);
                    IntPtr type_ptr = Marshal.AllocHGlobal(type.Length);
                    Marshal.Copy(type, 0, type_ptr, type.Length);

                    byte[] access = Encoding.ASCII.GetBytes(param.access);
                    IntPtr access_ptr = Marshal.AllocHGlobal(access.Length);
                    Marshal.Copy(access, 0, access_ptr, access.Length);

                    byte[] units = Encoding.ASCII.GetBytes(param.units);
                    IntPtr units_ptr = Marshal.AllocHGlobal(units.Length);
                    Marshal.Copy(units, 0, units_ptr, units.Length);

                    parameter_t* p = create_parameter_from_type((byte*)type_ptr);

                    if (p != null)
                    {
                        p->_base.name = (byte*)name_ptr;
                        p->_base.type = (byte*)type_ptr;
                        p->_base.access = (byte*)access_ptr;
                        p->_base.units = (byte*)units_ptr;
                        if (param.type == "string_t")
                        {
                            byte[] value = Encoding.ASCII.GetBytes(param.GetValue() + '\0');
                            IntPtr value_ptr = Marshal.AllocHGlobal(value.Length);
                            Marshal.Copy(value, 0, value_ptr, value.Length);
                            p->val_str->value = (byte*)value_ptr;
                            p->_base.size = (uint)value.Length + 1;
                        }
                        else if (param.type == "int32_t")
                        {
                            p->val_int->value = param.GetValue();
                        }
                        else if (param.type == "int64_t")
                        {
                            p->val_int64->value = param.GetValue();
                        }
                        else if (param.type == "uint32_t")
                        {
                            p->val_uint->value = param.GetValue();
                        }
                        else if (param.type == "uint64_t")
                        {
                            p->val_uint64->value = param.GetValue();
                        }
                        else if (param.type == "float_t")
                        {
                            p->val_flt->value = param.GetValue();
                        }
                        else if (param.type == "double_t")
                        {
                            p->val_dbl->value = param.GetValue();
                        }
                        else if (param.type == "u32_arr_t")
                        {
                            List<uint> list = param.GetValue();
                            int[] value = new int[list.Count];
                            for (int j = 0; j < list.Count; j++)
                                value[j] = Convert.ToInt32(list[j]);
                            IntPtr value_ptr = Marshal.AllocHGlobal(value.Length * sizeof(uint));
                            Marshal.Copy(value, 0, value_ptr, value.Length);
                            p->arr_uint->value = (uint*)(void*)(Marshal.AllocHGlobal(value.Length * sizeof(uint)));
                            for (int j = 0; j < list.Count; j++)
                                p->arr_uint->value[j] = Convert.ToUInt32(((uint*)(value_ptr))[j]);
                            p->_base.size = Convert.ToUInt32(list.Count * sizeof(uint));
                        }
                        this.paramMutex.WaitOne();
                        set_parameter((scanner_base_t*)scannerBase, p);
                        this.paramMutex.ReleaseMutex();
                        return true;
                    }
                    return false;
                }

                private void* scannerBase { get; set; }
                private bool isConnected { get; set; }
                private PROTOCOL_TYPES currentProtocol { get; set; }
                private System.Threading.Mutex paramMutex { get; set; }
                private System.Threading.Mutex profileMutex { get; set; }

                public RF627smart(void* Base)
                {
                    scannerBase = Base;
                    isConnected = false;
                    currentProtocol = PROTOCOL_TYPES.SERVICE;
                    paramMutex = new System.Threading.Mutex();
                    profileMutex = new System.Threading.Mutex();
                }
                ~RF627smart()
                {
                    free_scanner(((scanner_base_t*)this.scannerBase));
                }


            }
        }
    }
}
