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
            /// @cond

            #region dll-types

#if WIN64
            const int _pack = 8;
#else
            const int _pack = 4;
#endif

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct vector_t
            {
                public void** data;
                public UIntPtr size;
                public UIntPtr count;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct enumRec_t
            {
                public int value;
                public byte* label;
                public byte* key;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct valuesEnum_t
            {
                public int recCount;
                public enumRec_t* rec;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct value_base_t
            {
                public byte* name;
                public byte* type;
                public byte* access;
                public ushort index;
                public uint offset;
                public uint size;
                public byte* units;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct value_uint32_t
            {
                public uint min;
                public uint max;
                public uint step;
                public uint defValue;
                public valuesEnum_t* enumValues;
                public uint value;

            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct value_uint64_t
            {
                public ulong min;
                public ulong max;
                public ulong step;
                public ulong defValue;
                public valuesEnum_t* enumValues;
                public ulong value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct value_int32_t
            {
                public int min;
                public int max;
                public int step;
                public int defValue;
                public valuesEnum_t* enumValues;
                public int value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct value_int64_t
            {
                public long min;
                public long max;
                public long step;
                public long defValue;
                public valuesEnum_t* enumValues;
                public long value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct value_flt_t
            {
                public float min;
                public float max;
                public float step;
                public float defValue;
                public float value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct value_dbl_t
            {
                public double min;
                public double max;
                public double step;
                public double defValue;
                public double value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct array_uint32_t
            {
                public uint min;
                public uint max;
                public uint step;
                public uint maxCount;
                public uint defCount;
                public uint* defValue;
                public uint count;
                public uint* value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct array_uint64_t
            {
                public ulong min;
                public ulong max;
                public ulong step;
                public uint maxCount;
                public uint defCount;
                public ulong* defValue;
                public uint count;
                public ulong* value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct array_int32_t
            {
                public int min;
                public int max;
                public int step;
                public uint maxCount;
                public uint defCount;
                public int* defValue;
                public uint count;
                public int* value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct array_int64_t
            {
                public long min;
                public long max;
                public long step;
                public uint maxCount;
                public uint defCount;
                public long* defValue;
                public uint count;
                public long* value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct array_flt_t
            {
                public float min;
                public float max;
                public float step;
                public uint maxCount;
                public uint defCount;
                public float* defValue;
                public uint count;
                public float* value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct array_dbl_t
            {
                public double min;
                public double max;
                public double step;
                public uint maxCount;
                public uint defCount;
                public double* defValue;
                public uint count;
                public double* value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct value_str_t
            {
                public ushort maxLen;
                public byte* defValue;
                public byte* value;
            };



#if WIN64
            [StructLayout(LayoutKind.Explicit, Pack = _pack)]
            private struct parameter_t
            {
                [FieldOffset(0)]
                public value_base_t _base;
                [FieldOffset(48)]
                public void* rawData;
                [FieldOffset(48)]
                public value_uint32_t* val_uint;
                [FieldOffset(48)]
                public value_uint64_t* val_uint64;
                [FieldOffset(48)]
                public value_int32_t* val_int;
                [FieldOffset(48)]
                public value_int64_t* val_int64;
                [FieldOffset(48)]
                public value_flt_t* val_flt;
                [FieldOffset(48)]
                public value_dbl_t* val_dbl;
                [FieldOffset(48)]
                public array_uint32_t* arr_uint;
                [FieldOffset(48)]
                public array_uint64_t* arr_uint64;
                [FieldOffset(48)]
                public array_int32_t* arr_int;
                [FieldOffset(48)]
                public array_int64_t* arr_int64;
                [FieldOffset(48)]
                public array_flt_t* arr_flt;
                [FieldOffset(48)]
                public array_dbl_t* arr_dbl;
                [FieldOffset(48)]
                public value_str_t* val_str;

            };
#else
            [StructLayout(LayoutKind.Explicit, Pack = _pack)]
            private struct parameter_t
            {
                [FieldOffset(0)]
                public value_base_t _base;
                [FieldOffset(28)]
                public void* rawData;
                [FieldOffset(28)]
                public value_uint32_t* val_uint;
                [FieldOffset(28)]
                public value_uint64_t* val_uint64;
                [FieldOffset(28)]
                public value_int32_t* val_int;
                [FieldOffset(28)]
                public value_int64_t* val_int64;
                [FieldOffset(28)]
                public value_flt_t* val_flt;
                [FieldOffset(28)]
                public value_dbl_t* val_dbl;
                [FieldOffset(28)]
                public array_uint32_t* arr_uint;
                [FieldOffset(28)]
                public array_uint64_t* arr_uint64;
                [FieldOffset(28)]
                public array_int32_t* arr_int;
                [FieldOffset(28)]
                public array_int64_t* arr_int64;
                [FieldOffset(28)]
                public array_flt_t* arr_flt;
                [FieldOffset(28)]
                public array_dbl_t* arr_dbl;
                [FieldOffset(28)]
                public value_str_t* val_str;

            };
#endif

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct profile_header
            {
                public byte data_type;
                public byte flags;
                public ushort device_type;
                public uint serial_number;
                public ulong system_time;

                public byte proto_version_major;
                public byte proto_version_minor;
                public byte hardware_params_offset;
                public byte data_offset;
                public uint packet_count;
                public uint measure_count;

                public ushort zmr;
                public ushort xemr;
                public ushort discrete_value;
                public fixed byte reserved_0[14];

                public uint exposure_time;
                public uint laser_value;
                public uint step_count;
                public byte dir;
                public ushort payload_size;
                public byte bytes_per_point;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct pixels_format
            {
                public ushort* pixels;
                public uint pixels_count;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct rf62X_point_t
            {
                public float x;
                public float z;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct profile_format
            {
                public rf62X_point_t* points;
                public uint points_count;
            };



            #region rf62Xold

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct rf627_old_hello_info_by_service_protocol
            {
                public byte* device_name;
                public uint serial_number;
                public fixed byte ip_address[4];
                public fixed byte mac_address[6];
                public ushort profile_port;
                public ushort service_port;
                public uint firmware_version;
                public uint hardware_version;
                public uint z_begin;
                public uint z_range;
                public uint x_begin;
                public uint x_end;
            };


            [StructLayout(LayoutKind.Explicit, Pack = _pack)]
            private struct rf627_old_profile2D_t
            {
                [FieldOffset(0)]
                public profile_header header;
                [FieldOffset(72)]
                public pixels_format pixelsFormat;
                [FieldOffset(72)]
                public profile_format profileFormat;
                [FieldOffset(72 + 2 * _pack)]
                public byte* intensity;
                [FieldOffset(72 + 3 * _pack)]
                public uint intensity_count;
            }


            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct rf627_old_frame_t
            {
                public byte* data;
                public uint data_size;
                public uint width;
                public uint height;
                public byte pixel_size;

                public byte user_roi_active;
                public byte user_roi_enabled;
                public uint user_roi_pos;
                public uint user_roi_size;
            };


            #endregion

            #region RF627smart

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct rf627_smart_hello_info_by_service_protocol
            {
                public fixed uint fact_general_firmwareVer[3];
                public uint fact_general_hardwareVer;

                public uint fact_general_mr;
                public uint fact_general_smr;
                public uint fact_general_xsmr;

                public uint fact_laser_waveLength;

                public byte* user_general_deviceName;
                public uint fact_general_productCode;
                public uint fact_general_serial;

                public byte* user_network_ip;
                public byte* user_network_mask;
                public byte* user_network_gateway;
                public byte* user_network_hostIP;
                public byte* fact_network_macAddr;

                public uint user_network_hostPort;
                public uint user_network_servicePort;
                public uint user_network_webPort;

                public uint user_network_speed;
                public byte user_network_autoNeg;

                public uint user_streams_udpEnabled;
                public uint user_streams_format;

                public uint fact_general_xemr;
            };

            [StructLayout(LayoutKind.Explicit, Pack = _pack)]
            private struct rf627_smart_profile2D_t
            {
                [FieldOffset(0)]
                public profile_header header;
                [FieldOffset(72)]
                public pixels_format pixelsFormat;
                [FieldOffset(72)]
                public profile_format profileFormat;
                [FieldOffset(72 + 2 * _pack)]
                public byte* intensity;
                [FieldOffset(72 + 3 * _pack)]
                public uint intensity_count;
            }

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct rf627_smart_frame_t
            {
                public byte* data;
                public uint data_size;
                public uint width;
                public uint height;
                public byte pixel_size;

                public byte user_roi_active;
                public byte user_roi_enabled;
                public uint user_roi_pos;
                public uint user_roi_size;
            };

            #endregion



            [StructLayout(LayoutKind.Explicit, Pack = _pack)]
            private struct rf627_profile2D_t
            {
                [FieldOffset(0)]
                public SCANNER_TYPES type;
                [FieldOffset(_pack)]
                public rf627_old_profile2D_t* rf627old_profile2D;
                [FieldOffset(_pack)]
                public rf627_smart_profile2D_t* rf627smart_profile2D;
            };

            [StructLayout(LayoutKind.Explicit)]
            private struct scanner_base_t
            {
                [FieldOffset(0)]
                public SCANNER_TYPES type;
                [FieldOffset(_pack)]
                public void* rf627_old;
                [FieldOffset(_pack)]
                public void* rf627_smart;
            };

            [StructLayout(LayoutKind.Explicit, Pack = _pack)]
            private struct rf627_frame_t
            {
                [FieldOffset(0)]
                public SCANNER_TYPES type;
                [FieldOffset(_pack)]
                public rf627_old_frame_t* rf627old_frame;
                [FieldOffset(_pack)]
                public rf627_smart_frame_t* rf627smart_frame;
            };

            [StructLayout(LayoutKind.Explicit, Pack = _pack)]
            private struct hello_information
            {
                [FieldOffset(0)]
                public SCANNER_TYPES scanner_type;
                [FieldOffset(4)]
                public PROTOCOL_TYPES protocol_type;
                [FieldOffset(8)]
                public rf627_old_hello_info_by_service_protocol* rf627old_hello_info_service_protocol;
                [FieldOffset(8)]
                public rf627_smart_hello_info_by_service_protocol* RF627smart_hello_info_service_protocol;
            };

            #endregion

            #region dll-methods

            // network.h
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte WinSockInit();
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void WinSockDeinit();
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte EnumAdapterAddresses();
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void FreeAdapterAddresses();

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte* GetAdapterAddress(int index);
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte* GetAdapterMasks(int index);
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern int GetAdaptersCount();

            // rf62Xcore.h
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte core_init();

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte* sdk_version();

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void platform_free(void* data);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void* platform_calloc(UIntPtr num, UIntPtr size);


            // rf62X_sdk.h
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void set_platform_adapter_settings(uint subnet_mask, uint host_ip_addr);


            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte search_scanners(vector_t* list, SCANNER_TYPES model, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern hello_information get_info_about_scanner(scanner_base_t* device, PROTOCOL_TYPES protocol);


            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte connect_to_scanner(scanner_base_t* device, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte check_connection_to_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte disconnect_from_scanner(scanner_base_t* device, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void free_scanner(scanner_base_t* device);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern rf627_profile2D_t* get_profile2D_from_scanner(scanner_base_t* device, bool zero_points, bool realtime, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte send_profile2D_request_to_scanner(scanner_base_t* device, uint count, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void free_profile2D(rf627_profile2D_t* profile);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern rf627_frame_t* get_frame_from_scanner(scanner_base_t* device, PROTOCOL_TYPES protocol);


            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte read_params_from_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte write_params_to_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte save_params_to_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte load_recovery_params_from_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern parameter_t* get_parameter(scanner_base_t* device, byte* param_name);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte set_parameter(scanner_base_t* device, parameter_t* param);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern parameter_t* create_parameter_from_type(byte* type);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void free_parameter(parameter_t* param, SCANNER_TYPES type);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte get_dumps_profiles_from_scanner(
                scanner_base_t* device, uint index, uint count, uint timeout, 
                PROTOCOL_TYPES protocol, rf627_profile2D_t** dump, uint* dump_size, uint dump_unit_size);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte get_authorization_token_from_scanner(
                scanner_base_t* device, byte** token, uint* token_size, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte set_authorization_key_to_scanner(
                scanner_base_t* device, byte* key, uint key_size, uint timeout, PROTOCOL_TYPES protocol);

            // TODO: calibration_table

            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte send_reboot_device_request_to_scanner(scanner_base_t* device, PROTOCOL_TYPES protocol);


            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void vector_init(vector_t** vec);
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern UIntPtr vector_count(vector_t* vec);
            [DllImport("libRF62X-SDK.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void* vector_get(vector_t* vec, UIntPtr index);


            #endregion

            /// @endcond


            public enum SCANNER_TYPES
            {
                RF627_OLD = 1,
                RF62X_SMART = 2
            };
            public enum PROTOCOL_TYPES
            {
                CURRENT = 0,
                SERVICE = 1,
                ETHERNET_IP = 2,
                MODBUS_TCP = 3,
            };
            public enum PROFILE_DATA_TYPES
            {
                PIXELS = 0x10,
                PROFILE = 0x11,
                PIXELS_INTRP = 0x12,
                PROFILE_INTRP = 0x13
            };

            public enum COUNT_TYPES
            {
                STEP = 1,
                MEASURE = 2,
                PACKET = 3
            };

            public static class PARAMS
            {

                public class Description
                {
                    public string Key;
                    public string Type;
                    public Type GetParamType()
                    {
                        switch (Type)
                        {
                            case "unkn_t":
                                {
                                    return null;
                                }
                            case "uint32_t":
                                {
                                    return typeof(uint);
                                }
                            case "uint64_t":
                                {
                                    return typeof(ulong);
                                }
                            case "int32_t":
                                {
                                    return typeof(int);
                                }
                            case "int64_t":
                                {
                                    return typeof(long);
                                }
                            case "float_t":
                                {
                                    return typeof(float);
                                }
                            case "double_t":
                                {
                                    return typeof(double);
                                }
                            case "u32_arr_t":
                                {
                                    return typeof(uint[]);
                                }
                            case "u64_arr_t":
                                {
                                    return typeof(ulong[]);
                                }
                            case "i32_arr_t":
                                {
                                    return typeof(int[]);
                                }
                            case "i64_arr_t":
                                {
                                    return typeof(long[]);
                                }
                            case "flt_array_t":
                                {
                                    return typeof(float[]);
                                }
                            case "dbl_array_t":
                                {
                                    return typeof(double[]);
                                }
                            case "string_t":
                                {
                                    return typeof(string);
                                }
                            default:
                                {
                                    return null;
                                }
                        }
                    }
                }
                public static class User
                {
                    public static class General
                    {
                        public static Description deviceState { get; } = new Description()
                        {
                            Key = "user_general_deviceState",
                            Type = "uint32_t"
                        };
                        public static Description deviceName { get; } = new Description()
                        {
                            Key = "user_general_deviceName",
                            Type = "string_t"
                        };
                        public static Description saveLog { get; } = new Description()
                        {
                            Key = "user_general_saveLog",
                            Type = "uint32_t"
                        };
                    }

                    public static class SysMon
                    {
                        public static Description fpgaTemp { get; } = new Description()
                        {
                            Key = "user_sysMon_fpgaTemp",
                            Type = "float_t"
                        };
                        public static Description paramsChanged { get; } = new Description()
                        {
                            Key = "user_sysMon_paramsChanged",
                            Type = "uint32_t"
                        };
                        public static Description tempSens00 { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens00",
                            Type = "float_t"
                        };
                        public static Description tempSens00Max { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens00Max",
                            Type = "float_t"
                        };
                        public static Description tempSens00Min { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens00Min",
                            Type = "float_t"
                        };
                        public static Description tempSens01 { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens01",
                            Type = "float_t"
                        };
                        public static Description tempSens01Max { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens01Max",
                            Type = "float_t"
                        };
                        public static Description tempSens01Min { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens01Min",
                            Type = "float_t"
                        };
                        public static Description tempSens10 { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens10",
                            Type = "float_t"
                        };
                        public static Description tempSens10Max { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens10Max",
                            Type = "float_t"
                        };
                        public static Description tempSens10Min { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens10Min",
                            Type = "float_t"
                        };
                        public static Description tempSens11 { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens11",
                            Type = "float_t"
                        };
                        public static Description tempSens11Max { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens11Max",
                            Type = "float_t"
                        };
                        public static Description tempSens11Min { get; } = new Description()
                        {
                            Key = "user_sysMon_tempSens11Min",
                            Type = "float_t"
                        };
                    }

                    public static class Sensor
                    {
                        public static Description syncSource { get; } = new Description()
                        {
                            Key = "user_sensor_syncSource",
                            Type = "uint32_t"
                        };
                        public static Description framerate { get; } = new Description()
                        {
                            Key = "user_sensor_framerate",
                            Type = "uint32_t"
                        };
                        public static Description maxFramerate { get; } = new Description()
                        {
                            Key = "user_sensor_maxFramerate",
                            Type = "uint32_t"
                        };
                        public static Description exposureControl { get; } = new Description()
                        {
                            Key = "user_sensor_exposureControl",
                            Type = "uint32_t"
                        };
                        public static Description exposure1 { get; } = new Description()
                        {
                            Key = "user_sensor_exposure1",
                            Type = "uint32_t"
                        };
                        public static Description exposure2 { get; } = new Description()
                        {
                            Key = "user_sensor_exposure2",
                            Type = "uint32_t"
                        };
                        public static Description exposure3 { get; } = new Description()
                        {
                            Key = "user_sensor_exposure3",
                            Type = "uint32_t"
                        };
                        public static Description exposure4 { get; } = new Description()
                        {
                            Key = "user_sensor_exposure4",
                            Type = "uint32_t"
                        };
                        public static Description maxExposure { get; } = new Description()
                        {
                            Key = "user_sensor_maxExposure",
                            Type = "uint32_t"
                        };
                        public static Description doubleSpeedEnabled { get; } = new Description()
                        {
                            Key = "user_sensor_doubleSpeedEnabled",
                            Type = "uint32_t"
                        };
                        public static Description edrType { get; } = new Description()
                        {
                            Key = "user_sensor_edrType",
                            Type = "uint32_t"
                        };
                        public static Description edrColumnDivider { get; } = new Description()
                        {
                            Key = "user_sensor_edrColumnDivider",
                            Type = "uint32_t"
                        };
                        //public static Description edrType1Enabled { get; } = new Description()
                        //{
                        //    Key = "user_sensor_edrType1Enabled",
                        //    Type = "uint32_t"
                        //};
                        //public static Description edrType2Enabled { get; } = new Description()
                        //{
                        //    Key = "user_sensor_edrType2Enabled",
                        //    Type = "uint32_t"
                        //};
                        //public static Description edrType2Divider { get; } = new Description()
                        //{
                        //    Key = "user_sensor_edrType2Divider",
                        //    Type = "uint32_t"
                        //};
                        //public static Description edrType2MaxDivider { get; } = new Description()
                        //{
                        //    Key = "user_sensor_edrType2MaxDivider",
                        //    Type = "uint32_t"
                        //};
                        //public static Description autoExposureEnabled { get; } = new Description()
                        //{
                        //    Key = "user_sensor_autoExposureEnabled",
                        //    Type = "uint32_t"
                        //};
                    }

                    public static class Roi
                    {
                        public static Description enable { get; } = new Description()
                        {
                            Key = "user_roi_enabled",
                            Type = "uint32_t"
                        };
                        public static Description active { get; } = new Description()
                        {
                            Key = "user_roi_active",
                            Type = "uint32_t"
                        };
                        public static Description posMode { get; } = new Description()
                        {
                            Key = "user_roi_posMode",
                            Type = "uint32_t"
                        };
                        public static Description pos { get; } = new Description()
                        {
                            Key = "user_roi_pos",
                            Type = "uint32_t"
                        };
                        public static Description maxPos { get; } = new Description()
                        {
                            Key = "user_roi_maxPos",
                            Type = "uint32_t"
                        };
                        public static Description reqProfSize { get; } = new Description()
                        {
                            Key = "user_roi_reqProfSize",
                            Type = "uint32_t"
                        };
                        public static Description size { get; } = new Description()
                        {
                            Key = "user_roi_size",
                            Type = "uint32_t"
                        };
                    }

                    public static class NetWork
                    {
                        public static Description speed { get; } = new Description()
                        {
                            Key = "user_network_speed",
                            Type = "uint32_t"
                        };
                        public static Description requiredSpeed { get; } = new Description()
                        {
                            Key = "user_network_requiredSpeed",
                            Type = "uint32_t"
                        };
                        public static Description autoNeg { get; } = new Description()
                        {
                            Key = "user_network_autoNeg",
                            Type = "uint32_t"
                        };
                        public static Description ip { get; } = new Description()
                        {
                            Key = "user_network_ip",
                            Type = "u32_arr_t"
                        };
                        public static Description mask { get; } = new Description()
                        {
                            Key = "user_network_mask",
                            Type = "u32_arr_t"
                        };
                        public static Description gateway { get; } = new Description()
                        {
                            Key = "user_network_gateway",
                            Type = "u32_arr_t"
                        };
                        public static Description hostIP { get; } = new Description()
                        {
                            Key = "user_network_hostIP",
                            Type = "u32_arr_t"
                        };
                        public static Description hostPort { get; } = new Description()
                        {
                            Key = "user_network_hostPort",
                            Type = "uint32_t"
                        };
                        public static Description webPort { get; } = new Description()
                        {
                            Key = "user_network_webPort",
                            Type = "uint32_t"
                        };
                        public static Description servicePort { get; } = new Description()
                        {
                            Key = "user_network_servicePort",
                            Type = "uint32_t"
                        };
                    }

                    public static class Streams
                    {
                        public static Description udpEnable { get; } = new Description()
                        {
                            Key = "user_streams_udpEnabled",
                            Type = "uint32_t"
                        };
                        public static Description format { get; } = new Description()
                        {
                            Key = "user_streams_format",
                            Type = "uint32_t"
                        };
                        public static Description includeIntensity { get; } = new Description()
                        {
                            Key = "user_streams_includeIntensity",
                            Type = "uint32_t"
                        };
                        public static Description pointsCount { get; } = new Description()
                        {
                            Key = "user_streams_pointsCount",
                            Type = "uint32_t"
                        };
                    }

                    public static class Processing
                    {
                        public static Description threshold { get; } = new Description()
                        {
                            Key = "user_processing_threshold",
                            Type = "uint32_t"
                        };

                        public static Description profPerSec { get; } = new Description()
                        {
                            Key = "user_processing_profPerSec",
                            Type = "uint32_t"
                        };
                        public static Description medianMode { get; } = new Description()
                        {
                            Key = "user_processing_medianMode",
                            Type = "uint32_t"
                        };
                        public static Description bilateralMode { get; } = new Description()
                        {
                            Key = "user_processing_bilateralMode",
                            Type = "uint32_t"
                        };
                        public static Description peakMode { get; } = new Description()
                        {
                            Key = "user_processing_peakMode",
                            Type = "uint32_t"
                        };
                        public static Description flip { get; } = new Description()
                        {
                            Key = "user_processing_flip",
                            Type = "uint32_t"
                        };

                        //public static Description mode { get; } = new Description()
                        //{
                        //    Key = "user_processing_mode",
                        //    Type = "uint32_t"
                        //};
                    }

                    public static class Laser
                    {
                        public static Description enabled { get; } = new Description()
                        {
                            Key = "user_laser_enabled",
                            Type = "uint32_t"
                        };
                        //public static Description mode { get; } = new Description()
                        //{
                        //    Key = "user_laser_mode",
                        //    Type = "uint32_t"
                        //};
                        public static Description value { get; } = new Description()
                        {
                            Key = "user_laser_value",
                            Type = "uint32_t"
                        };
                    }

                    public static class Trigger
                    {
                        public static class Sync
                        {
                            public static Description source { get; } = new Description()
                            {
                                Key = "user_trigger_sync_source",
                                Type = "uint32_t"
                            };
                            public static Description strictEnabled { get; } = new Description()
                            {
                                Key = "user_trigger_sync_strictEnabled",
                                Type = "uint32_t"
                            };
                            public static Description divider { get; } = new Description()
                            {
                                Key = "user_trigger_sync_divider",
                                Type = "uint32_t"
                            };
                            public static Description delay { get; } = new Description()
                            {
                                Key = "user_trigger_sync_delay",
                                Type = "uint32_t"
                            };
                        }
                        public static class Counter
                        {
                            public static Description type { get; } = new Description()
                            {
                                Key = "user_trigger_counter_type",
                                Type = "uint32_t"
                            };
                            public static Description maxValueEnabled { get; } = new Description()
                            {
                                Key = "user_trigger_counter_maxValueEnabled",
                                Type = "uint32_t"
                            };
                            public static Description maxValue { get; } = new Description()
                            {
                                Key = "user_trigger_counter_maxValue",
                                Type = "uint32_t"
                            };
                            public static Description resetTimerEnabled { get; } = new Description()
                            {
                                Key = "user_trigger_counter_resetTimerEnabled",
                                Type = "uint32_t"
                            };
                            public static Description resetTimerValue { get; } = new Description()
                            {
                                Key = "user_trigger_counter_resetTimerValue",
                                Type = "uint32_t"
                            };
                            public static Description value { get; } = new Description()
                            {
                                Key = "user_trigger_counter_value",
                                Type = "uint32_t"
                            };
                        }
                    }

                    public static class Inputs1
                    {
                        public static Description enabled { get; } = new Description()
                        {
                            Key = "user_input1_enabled",
                            Type = "uint32_t"
                        };
                        //public static Description occasion { get; } = new Description()
                        //{
                        //    Key = "user_inputs_1_event",
                        //    Type = "uint32_t"
                        //};
                        public static Description mode { get; } = new Description()
                        {
                            Key = "user_input1_mode",
                            Type = "uint32_t"
                        };
                        public static Description samples { get; } = new Description()
                        {
                            Key = "user_input1_samples",
                            Type = "uint32_t"
                        };

                        //public static Description delay { get; } = new Description()
                        //{
                        //    Key = "user_inputs_1_delay",
                        //    Type = "uint32_t"
                        //};
                        //public static Description divider { get; } = new Description()
                        //{
                        //    Key = "user_inputs_1_divider",
                        //    Type = "uint32_t"
                        //};
                    }

                    public static class Inputs2
                    {
                        public static Description enabled { get; } = new Description()
                        {
                            Key = "user_inputs2_enabled",
                            Type = "uint32_t"
                        };
                        public static Description mode { get; } = new Description()
                        {
                            Key = "user_inputs2_mode",
                            Type = "uint32_t"
                        };
                        public static Description samples { get; } = new Description()
                        {
                            Key = "user_input2_samples",
                            Type = "uint32_t"
                        };
                        //public static Description inverse { get; } = new Description()
                        //{
                        //    Key = "user_inputs_2_inverse",
                        //    Type = "uint32_t"
                        //};
                    }

                    public static class Inputs3
                    {
                        public static Description enabled { get; } = new Description()
                        {
                            Key = "user_inputs3_enabled",
                            Type = "uint32_t"
                        };
                        public static Description mode { get; } = new Description()
                        {
                            Key = "user_inputs3_mode",
                            Type = "uint32_t"
                        };
                        public static Description samples { get; } = new Description()
                        {
                            Key = "user_input3_samples",
                            Type = "uint32_t"
                        };
                    }

                    public static class Outputs1
                    {
                        public static Description enabled { get; } = new Description()
                        {
                            Key = "user_outputs1_enabled",
                            Type = "uint32_t"
                        };
                        public static Description mode { get; } = new Description()
                        {
                            Key = "user_outputs1_mode",
                            Type = "uint32_t"
                        };
                        //public static Description delay { get; } = new Description()
                        //{
                        //    Key = "user_outputs_1_delay",
                        //    Type = "uint32_t"
                        //};
                        public static Description pulseWidth { get; } = new Description()
                        {
                            Key = "user_outputs1_pulseWidth",
                            Type = "uint32_t"
                        };
                        //public static Description inverse { get; } = new Description()
                        //{
                        //    Key = "user_outputs_1_inverse",
                        //    Type = "uint32_t"
                        //};
                    }

                    public static class Outputs2
                    {
                        public static Description enabled { get; } = new Description()
                        {
                            Key = "user_outputs2_enabled",
                            Type = "uint32_t"
                        };
                        public static Description mode { get; } = new Description()
                        {
                            Key = "user_outputs2_mode",
                            Type = "uint32_t"
                        };
                        //public static Description delay { get; } = new Description()
                        //{
                        //    Key = "user_outputs_2_delay",
                        //    Type = "uint32_t"
                        //};
                        public static Description pulseWidth { get; } = new Description()
                        {
                            Key = "user_outputs2_pulseWidth",
                            Type = "uint32_t"
                        };
                        //public static Description inverse { get; } = new Description()
                        //{
                        //    Key = "user_outputs_2_inverse",
                        //    Type = "uint32_t"
                        //};
                    }

                    public static class Dump
                    {
                        public static Description enabled { get; } = new Description()
                        {
                            Key = "user_dump_enabled",
                            Type = "uint32_t"
                        };
                        public static Description capacity { get; } = new Description()
                        {
                            Key = "user_dump_capacity",
                            Type = "uint32_t"
                        };
                        public static Description size { get; } = new Description()
                        {
                            Key = "user_dump_size",
                            Type = "uint32_t"
                        };
                        public static Description timeStamp { get; } = new Description()
                        {
                            Key = "user_dump_timeStamp",
                            Type = "uint32_t"
                        };

                        public static class View3D
                        {
                            public static Description motionType { get; } = new Description()
                            {
                                Key = "user_view3d_motionType",
                                Type = "uint32_t"
                            };
                            public static Description ySource { get; } = new Description()
                            {
                                Key = "user_view3d_ySource",
                                Type = "uint32_t"
                            };
                            public static Description yStep { get; } = new Description()
                            {
                                Key = "user_view3d_yStep",
                                Type = "float_t"
                            };
                            public static Description paintMode { get; } = new Description()
                            {
                                Key = "user_view3d_paintMode",
                                Type = "uint32_t"
                            };
                            public static Description decimation { get; } = new Description()
                            {
                                Key = "user_view3d_decimation",
                                Type = "uint32_t"
                            };
                        }

                    }


                    public static class Eip
                    {
                        public static Description tcpPort { get; } = new Description()
                        {
                            Key = "user_eip_tcpPort",
                            Type = "uint32_t"
                        };
                        public static Description udpPort { get; } = new Description()
                        {
                            Key = "user_eip_udpPort",
                            Type = "uint32_t"
                        };
                        public static Description tcpTTL { get; } = new Description()
                        {
                            Key = "user_eip_tcp_ttl",
                            Type = "uint32_t"
                        };
                        public static Description tcpTimeout { get; } = new Description()
                        {
                            Key = "user_eip_tcp_timeout",
                            Type = "uint32_t"
                        };
                        public static Description multicastAlloc { get; } = new Description()
                        {
                            Key = "user_eip_tcp_multiCast_alloc",
                            Type = "uint32_t"
                        };
                        public static Description multicastNum { get; } = new Description()
                        {
                            Key = "user_eip_tcp_multiCast_num",
                            Type = "uint32_t"
                        };
                        public static Description multicastAddr { get; } = new Description()
                        {
                            Key = "user_eip_tcp_multiCast_addr",
                            Type = "u32_arr_t"
                        };
                    }

                    public static class Compatibility
                    {
                        public static Description rf625Enabled { get; } = new Description()
                        {
                            Key = "user_compatibility_rf625Enabled",
                            Type = "uint32_t"
                        };
                        public static Description rf625TCPPort { get; } = new Description()
                        {
                            Key = "user_compatibility_rf625TCPPort",
                            Type = "uint32_t"
                        };
                    }
                }

                public static List<Description> GetParamsDescriptionList()
                {
                    List<Description> list = new List<Description>();

                    list.Add(User.General.deviceName);
                    list.Add(User.General.deviceState);
                    list.Add(User.General.saveLog);

                    list.Add(User.SysMon.fpgaTemp);
                    list.Add(User.SysMon.paramsChanged);
                    list.Add(User.SysMon.tempSens00);
                    list.Add(User.SysMon.tempSens00Max);
                    list.Add(User.SysMon.tempSens00Min);
                    list.Add(User.SysMon.tempSens01);
                    list.Add(User.SysMon.tempSens01Max);
                    list.Add(User.SysMon.tempSens01Min);
                    list.Add(User.SysMon.tempSens10);
                    list.Add(User.SysMon.tempSens10Max);
                    list.Add(User.SysMon.tempSens10Min);
                    list.Add(User.SysMon.tempSens11);
                    list.Add(User.SysMon.tempSens11Max);
                    list.Add(User.SysMon.tempSens11Min);

                    list.Add(User.Sensor.doubleSpeedEnabled);
                    list.Add(User.Sensor.edrColumnDivider);
                    list.Add(User.Sensor.edrType);
                    list.Add(User.Sensor.exposureControl);
                    list.Add(User.Sensor.framerate);
                    list.Add(User.Sensor.maxExposure);
                    list.Add(User.Sensor.maxFramerate);
                    list.Add(User.Sensor.syncSource);
                    list.Add(User.Sensor.exposure1);
                    list.Add(User.Sensor.exposure2);
                    list.Add(User.Sensor.exposure3);
                    list.Add(User.Sensor.exposure4);

                    list.Add(User.Roi.active);
                    list.Add(User.Roi.enable);
                    list.Add(User.Roi.maxPos);
                    list.Add(User.Roi.pos);
                    list.Add(User.Roi.posMode);
                    list.Add(User.Roi.reqProfSize);
                    list.Add(User.Roi.size);

                    list.Add(User.NetWork.autoNeg);
                    list.Add(User.NetWork.gateway);
                    list.Add(User.NetWork.hostIP);
                    list.Add(User.NetWork.hostPort);
                    list.Add(User.NetWork.ip);
                    list.Add(User.NetWork.mask);
                    list.Add(User.NetWork.requiredSpeed);

                    list.Add(User.Streams.format);
                    list.Add(User.Streams.includeIntensity);
                    list.Add(User.Streams.pointsCount);
                    list.Add(User.Streams.udpEnable);

                    list.Add(User.Processing.bilateralMode);
                    list.Add(User.Processing.flip);
                    list.Add(User.Processing.medianMode);
                    list.Add(User.Processing.peakMode);
                    list.Add(User.Processing.profPerSec);
                    list.Add(User.Processing.threshold);

                    list.Add(User.Laser.enabled);
                    list.Add(User.Laser.value);

                    list.Add(User.Trigger.Counter.maxValue);
                    list.Add(User.Trigger.Counter.maxValueEnabled);
                    list.Add(User.Trigger.Counter.resetTimerEnabled);
                    list.Add(User.Trigger.Counter.resetTimerValue);
                    list.Add(User.Trigger.Counter.type);
                    list.Add(User.Trigger.Counter.value);

                    list.Add(User.Trigger.Sync.delay);
                    list.Add(User.Trigger.Sync.divider);
                    list.Add(User.Trigger.Sync.source);
                    list.Add(User.Trigger.Sync.strictEnabled);

                    list.Add(User.Inputs1.enabled);
                    list.Add(User.Inputs1.mode);
                    list.Add(User.Inputs1.samples);

                    list.Add(User.Inputs2.enabled);
                    list.Add(User.Inputs2.mode);
                    list.Add(User.Inputs2.samples);

                    list.Add(User.Inputs3.enabled);
                    list.Add(User.Inputs3.mode);
                    list.Add(User.Inputs3.samples);

                    list.Add(User.Outputs1.enabled);
                    list.Add(User.Outputs1.mode);
                    list.Add(User.Outputs1.pulseWidth);

                    list.Add(User.Outputs2.enabled);
                    list.Add(User.Outputs2.mode);
                    list.Add(User.Outputs2.pulseWidth);

                    list.Add(User.Dump.capacity);
                    list.Add(User.Dump.enabled);
                    list.Add(User.Dump.size);
                    list.Add(User.Dump.timeStamp);

                    list.Add(User.Dump.View3D.decimation);
                    list.Add(User.Dump.View3D.motionType);
                    list.Add(User.Dump.View3D.paintMode);
                    list.Add(User.Dump.View3D.ySource);
                    list.Add(User.Dump.View3D.yStep);

                    list.Add(User.Compatibility.rf625Enabled);
                    list.Add(User.Compatibility.rf625TCPPort);

                    return list;

                }

            }

            public class Parameter<T>
            {
                public Parameter(void* _base, dynamic Min, dynamic Max, uint MaxCount, uint DefCount, dynamic DefValue, List<ValuesEnum> ValuesEnum, dynamic Step, T Value)
                {
                    name = Marshal.PtrToStringAnsi((IntPtr)((parameter_t*)_base)->_base.name);
                    index = ((parameter_t*)_base)->_base.index;
                    offset = ((parameter_t*)_base)->_base.offset;
                    size = ((parameter_t*)_base)->_base.size;
                    type = Marshal.PtrToStringAnsi((IntPtr)((parameter_t*)_base)->_base.type);
                    access = Marshal.PtrToStringAnsi((IntPtr)((parameter_t*)_base)->_base.access);
                    units = Marshal.PtrToStringAnsi((IntPtr)((parameter_t*)_base)->_base.units);

                    min = Min;
                    max = Max;
                    maxCount = MaxCount;
                    defCount = DefCount;
                    valuesEnum = ValuesEnum;
                    step = Step;
                    value = Value;

                }
                public string name { get; }
                public string type { get; }
                public string access { get; }
                public ushort index { get; }
                public uint offset { get; }
                public uint size { get; }
                public string units { get; }

                public dynamic min { get; }
                public dynamic max { get; }
                public uint maxCount { get; }
                public uint defCount { get; }
                public dynamic defValue { get; }

                public class ValuesEnum
                {
                    private dynamic _value;
                    private string _label;
                    private string _key;
                    public dynamic GetValue()
                    {
                        return _value;
                    }
                    public string GetLabel()
                    {
                        return _label;
                    }
                    public string GetKey()
                    {
                        return _key;
                    }
                    public ValuesEnum(T value, string label, string key)
                    {
                        _value = value;
                        _label = label;
                        _key = key;
                    }

                }
                public List<ValuesEnum> valuesEnum { get; }

                private dynamic step;
                private T value;


                public T GetValue()
                {
                    return value;
                }
                public void SetValue(T newValue)
                {
                    value = newValue;
                }
            }

            public class Point2D
            {
                public Point2D(float x, float z)
                {
                    X = x;
                    Z = z;
                }
                public float X;
                public float Z;
            }

            public unsafe class Profile2D
            {
                public class Header
                {
                    public PROFILE_DATA_TYPES data_type { get; private set; }
                    public byte flags { get; private set; }
                    public ushort device_type { get; private set; }
                    public uint serial_number { get; private set; }
                    public ulong system_time { get; private set; }

                    public byte version_major { get; private set; }
                    public byte version_minor { get; private set; }
                    public byte hardware_params_offset { get; private set; }
                    public byte data_offset { get; private set; }
                    public uint packet_count { get; private set; }
                    public uint measure_count { get; private set; }

                    public ushort zmr { get; private set; }
                    public ushort xemr { get; private set; }
                    public ushort discrete_value { get; private set; }

                    public uint exposure_time { get; private set; }
                    public uint laser_value { get; private set; }
                    public uint step_count { get; private set; }
                    public byte dir { get; private set; }
                    public ushort payload_size { get; private set; }
                    public byte bytes_per_point { get; private set; }

                    public Header(void* profile2D, SCANNER_TYPES type)
                    {
                        switch (type)
                        {
                            case SCANNER_TYPES.RF627_OLD:
                                {
                                    data_type = (PROFILE_DATA_TYPES)((rf627_old_profile2D_t*)profile2D)->header.data_type;

                                    data_offset = ((rf627_old_profile2D_t*)profile2D)->header.data_offset;
                                    flags = ((rf627_old_profile2D_t*)profile2D)->header.flags;
                                    device_type = ((rf627_old_profile2D_t*)profile2D)->header.device_type;
                                    serial_number = ((rf627_old_profile2D_t*)profile2D)->header.serial_number;
                                    system_time = ((rf627_old_profile2D_t*)profile2D)->header.system_time;

                                    version_major = ((rf627_old_profile2D_t*)profile2D)->header.proto_version_major;
                                    version_minor = ((rf627_old_profile2D_t*)profile2D)->header.proto_version_minor;
                                    hardware_params_offset = ((rf627_old_profile2D_t*)profile2D)->header.hardware_params_offset;
                                    data_offset = ((rf627_old_profile2D_t*)profile2D)->header.data_offset;
                                    packet_count = ((rf627_old_profile2D_t*)profile2D)->header.packet_count;
                                    measure_count = ((rf627_old_profile2D_t*)profile2D)->header.measure_count;

                                    zmr = ((rf627_old_profile2D_t*)profile2D)->header.zmr;
                                    xemr = ((rf627_old_profile2D_t*)profile2D)->header.xemr;
                                    discrete_value = ((rf627_old_profile2D_t*)profile2D)->header.discrete_value;

                                    exposure_time = ((rf627_old_profile2D_t*)profile2D)->header.exposure_time;
                                    laser_value = ((rf627_old_profile2D_t*)profile2D)->header.laser_value;
                                    step_count = ((rf627_old_profile2D_t*)profile2D)->header.step_count;
                                    dir = ((rf627_old_profile2D_t*)profile2D)->header.dir;
                                    break;
                                }
                            case SCANNER_TYPES.RF62X_SMART:
                                {
                                    rf627_smart_profile2D_t* a = (rf627_smart_profile2D_t*)profile2D;
                                    data_type = (PROFILE_DATA_TYPES)((rf627_smart_profile2D_t*)profile2D)->header.data_type;

                                    data_offset = ((rf627_smart_profile2D_t*)profile2D)->header.data_offset;
                                    flags = ((rf627_smart_profile2D_t*)profile2D)->header.flags;
                                    device_type = ((rf627_smart_profile2D_t*)profile2D)->header.device_type;
                                    serial_number = ((rf627_smart_profile2D_t*)profile2D)->header.serial_number;
                                    system_time = ((rf627_smart_profile2D_t*)profile2D)->header.system_time;

                                    version_major = ((rf627_smart_profile2D_t*)profile2D)->header.proto_version_major;
                                    version_minor = ((rf627_smart_profile2D_t*)profile2D)->header.proto_version_minor;
                                    hardware_params_offset = ((rf627_smart_profile2D_t*)profile2D)->header.hardware_params_offset;
                                    data_offset = ((rf627_smart_profile2D_t*)profile2D)->header.data_offset;
                                    packet_count = ((rf627_smart_profile2D_t*)profile2D)->header.packet_count;
                                    measure_count = ((rf627_smart_profile2D_t*)profile2D)->header.measure_count;

                                    zmr = ((rf627_smart_profile2D_t*)profile2D)->header.zmr;
                                    xemr = ((rf627_smart_profile2D_t*)profile2D)->header.xemr;
                                    discrete_value = ((rf627_smart_profile2D_t*)profile2D)->header.discrete_value;

                                    exposure_time = ((rf627_smart_profile2D_t*)profile2D)->header.exposure_time;
                                    laser_value = ((rf627_smart_profile2D_t*)profile2D)->header.laser_value;
                                    step_count = ((rf627_smart_profile2D_t*)profile2D)->header.step_count;
                                    dir = ((rf627_smart_profile2D_t*)profile2D)->header.dir;
                                    break;
                                }
                        }
                    }

                }

                public Profile2D(void* _base)
                {
                    m_ProfileBase = _base;
                    rf627_profile2D_t* profile_from_scanner = (rf627_profile2D_t*)m_ProfileBase;
                    if (profile_from_scanner != null)
                    {
                        switch (profile_from_scanner->type)
                        {
                            case SCANNER_TYPES.RF627_OLD:
                                {
                                    if (profile_from_scanner->rf627old_profile2D != null)
                                    {
                                        header = new Header(profile_from_scanner->rf627old_profile2D, SCANNER_TYPES.RF627_OLD);
                                        switch (header.data_type)
                                        {
                                            case PROFILE_DATA_TYPES.PIXELS:
                                            case PROFILE_DATA_TYPES.PIXELS_INTRP:
                                                {
                                                    pixels = new List<ushort>();
                                                    uint pixels_count = ((rf627_profile2D_t*)_base)->rf627old_profile2D->pixelsFormat.pixels_count;
                                                    for (int i = 0; i < pixels_count; i++)
                                                    {
                                                        pixels.Add(((rf627_profile2D_t*)_base)->rf627old_profile2D->pixelsFormat.pixels[i]);
                                                    }

                                                    if (((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity_count > 0)
                                                    {
                                                        intensities = new List<byte>();
                                                        uint intensity_count = ((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity_count;
                                                        for (int i = 0; i < intensity_count; i++)
                                                            intensities.Add(((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity[i]);
                                                    }
                                                    break;
                                                }
                                            case PROFILE_DATA_TYPES.PROFILE:
                                            case PROFILE_DATA_TYPES.PROFILE_INTRP:
                                                {
                                                    points = new List<Point2D>();
                                                    uint points_count = ((rf627_profile2D_t*)_base)->rf627old_profile2D->profileFormat.points_count;
                                                    for (int i = 0; i < points_count; i++)
                                                    {
                                                        Point2D point = new Point2D(
                                                            ((rf627_profile2D_t*)_base)->rf627old_profile2D->profileFormat.points[i].x,
                                                            ((rf627_profile2D_t*)_base)->rf627old_profile2D->profileFormat.points[i].z);
                                                        points.Add(point);
                                                    }

                                                    if (((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity_count > 0)
                                                    {
                                                        intensities = new List<byte>();
                                                        uint intensity_count = ((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity_count;
                                                        for (int i = 0; i < intensity_count; i++)
                                                            intensities.Add(((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity[i]);
                                                    }
                                                    break;
                                                }
                                            default:
                                                break;
                                        }

                                    }
                                    break;
                                }
                            case SCANNER_TYPES.RF62X_SMART:
                                {
                                    if (profile_from_scanner->rf627smart_profile2D != null)
                                    {
                                        header = new Header(profile_from_scanner->rf627smart_profile2D, SCANNER_TYPES.RF62X_SMART);
                                        switch (header.data_type)
                                        {
                                            case PROFILE_DATA_TYPES.PIXELS:
                                            case PROFILE_DATA_TYPES.PIXELS_INTRP:
                                                {
                                                    pixels = new List<ushort>();
                                                    uint pixels_count = ((rf627_profile2D_t*)_base)->rf627smart_profile2D->pixelsFormat.pixels_count;
                                                    for (int i = 0; i < pixels_count; i++)
                                                    {
                                                        pixels.Add(((rf627_profile2D_t*)_base)->rf627smart_profile2D->pixelsFormat.pixels[i]);
                                                    }

                                                    if (((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity_count > 0)
                                                    {
                                                        intensities = new List<byte>();
                                                        uint intensity_count = ((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity_count;
                                                        for (int i = 0; i < intensity_count; i++)
                                                            intensities.Add(((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity[i]);
                                                    }
                                                    break;
                                                }
                                            case PROFILE_DATA_TYPES.PROFILE:
                                            case PROFILE_DATA_TYPES.PROFILE_INTRP:
                                                {
                                                    points = new List<Point2D>();
                                                    uint points_count = ((rf627_profile2D_t*)_base)->rf627smart_profile2D->profileFormat.points_count;
                                                    for (int i = 0; i < points_count; i++)
                                                    {
                                                        Point2D point = new Point2D(
                                                            ((rf627_profile2D_t*)_base)->rf627smart_profile2D->profileFormat.points[i].x,
                                                            ((rf627_profile2D_t*)_base)->rf627smart_profile2D->profileFormat.points[i].z);
                                                        points.Add(point);
                                                    }

                                                    if (((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity_count > 0)
                                                    {
                                                        intensities = new List<byte>();
                                                        uint intensity_count = ((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity_count;
                                                        for (int i = 0; i < intensity_count; i++)
                                                            intensities.Add(((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity[i]);
                                                    }
                                                    break;
                                                }
                                            default:
                                                break;
                                        }

                                    }
                                    break;
                                }
                        }

                    }


                }
                ~Profile2D()
                {
                    rf627_profile2D_t* _profile = (rf627_profile2D_t*)m_ProfileBase;
                    free_profile2D(_profile);
                    /*if (_profile != null)
                    {
                        switch (_profile->type)
                        {
                            case SCANNER_TYPES.RF627_OLD:
                                {
                                    if (_profile->rf627old_profile2D != null)
                                    {
                                        platform_free(_profile->rf627old_profile2D->intensity);
                                        _profile->rf627old_profile2D->intensity = null;
                                        platform_free(_profile->rf627old_profile2D->pixelsFormat.pixels);
                                        _profile->rf627old_profile2D->pixelsFormat.pixels = null;
                                        platform_free(_profile->rf627old_profile2D);
                                        _profile->rf627old_profile2D = null;
                                    }
                                    break;
                                }
                            case SCANNER_TYPES.RF62X_SMART:
                                {
                                    if (_profile->rf627smart_profile2D != null)
                                    {
                                        platform_free(_profile->rf627smart_profile2D->intensity);
                                        _profile->rf627smart_profile2D->intensity = null;
                                        platform_free(_profile->rf627smart_profile2D->pixelsFormat.pixels);
                                        _profile->rf627smart_profile2D->pixelsFormat.pixels = null;
                                        platform_free(_profile->rf627smart_profile2D);
                                        _profile->rf627smart_profile2D = null;
                                    }
                                    break;
                                }
                        }
                        platform_free(_profile);
                    }*/
                }

                public Header header { get; private set; }
                public List<byte> intensities { get; }
                public List<Point2D> points { get; }
                public List<ushort> pixels { get; }

                private void* m_ProfileBase;

            }

            public unsafe class Frame
            {
                public Frame(void* frame_base)
                {
                    m_FrameBase = frame_base;
                    rf627_frame_t* _frame = (rf627_frame_t*)m_FrameBase;
                    if (_frame != null)
                    {
                        switch (_frame->type)
                        {
                            case SCANNER_TYPES.RF627_OLD:
                                {
                                    Data = new List<byte>();
                                    for (int i = 0; i < _frame->rf627old_frame->data_size; i++)
                                        Data.Add(_frame->rf627old_frame->data[i]);
                                    DataSize = _frame->rf627old_frame->data_size;
                                    PixelSize = _frame->rf627old_frame->pixel_size;
                                    FrameWidth = _frame->rf627old_frame->width;
                                    FrameHeight = _frame->rf627old_frame->height;

                                    RoiActive = _frame->rf627old_frame->user_roi_active == 1 ? true : false;
                                    RoiEnabled = _frame->rf627old_frame->user_roi_enabled == 1 ? true : false;
                                    RoiPos = _frame->rf627old_frame->user_roi_pos;
                                    RoiSize = _frame->rf627old_frame->user_roi_size;
                                    break;
                                }
                            case SCANNER_TYPES.RF62X_SMART:
                                {
                                    Data = new List<byte>();
                                    for (int i = 0; i < _frame->rf627smart_frame->data_size; i++)
                                        Data.Add(_frame->rf627smart_frame->data[i]);
                                    DataSize = _frame->rf627smart_frame->data_size;
                                    PixelSize = _frame->rf627smart_frame->pixel_size;
                                    FrameWidth = _frame->rf627smart_frame->width;
                                    FrameHeight = _frame->rf627smart_frame->height;

                                    RoiActive = _frame->rf627smart_frame->user_roi_active == 1 ? true : false;
                                    RoiEnabled = _frame->rf627smart_frame->user_roi_enabled == 1 ? true : false;
                                    RoiPos = _frame->rf627smart_frame->user_roi_pos;
                                    RoiSize = _frame->rf627smart_frame->user_roi_size;
                                    break;
                                }
                        }

                    }


                }
                ~Frame()
                {
                    rf627_frame_t* _frame = (rf627_frame_t*)m_FrameBase;
                    if (_frame != null)
                    {
                        switch (_frame->type)
                        {
                            case SCANNER_TYPES.RF627_OLD:
                                {
                                    if (_frame->rf627old_frame->data != null)
                                        platform_free(_frame->rf627old_frame->data);
                                    break;
                                }
                            case SCANNER_TYPES.RF62X_SMART:
                                {
                                    if (_frame->rf627smart_frame->data != null)
                                        platform_free(_frame->rf627smart_frame->data);
                                    break;
                                }
                        }
                        platform_free(_frame);
                    }
                }

                public List<byte> Data { get; }
                public uint DataSize { get; }
                public uint PixelSize { get; }
                public uint FrameWidth { get; }
                public uint FrameHeight { get; }

                public bool RoiActive { get; }
                public bool RoiEnabled { get; }
                public uint RoiPos { get; }
                public uint RoiSize { get; }

                private void* m_FrameBase;
            }

            public unsafe class HelloInfo
            {
                public HelloInfo(void* info, SCANNER_TYPES type, PROTOCOL_TYPES protocol)
                {
                    switch (type)
                    {
                        case SCANNER_TYPES.RF627_OLD:
                            {
                                switch (protocol)
                                {
                                    case PROTOCOL_TYPES.SERVICE:
                                        device_name = Marshal.PtrToStringAnsi((IntPtr)(((rf627_old_hello_info_by_service_protocol*)info)->device_name));
                                        serial_number = ((rf627_old_hello_info_by_service_protocol*)info)->serial_number;

                                        ip_address = ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[0] + "."
                                            + ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[1] + "."
                                            + ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[2] + "."
                                            + ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[3] + ".";
                                        byte[] mac_arr = new byte[6];
                                        Marshal.Copy((IntPtr)((rf627_old_hello_info_by_service_protocol*)info)->mac_address, mac_arr, 0, 6);
                                        mac_address = BitConverter.ToString(mac_arr).Replace("-", ":");

                                        profile_port = ((rf627_old_hello_info_by_service_protocol*)info)->profile_port;
                                        service_port = ((rf627_old_hello_info_by_service_protocol*)info)->service_port;

                                        byte[] firmware_arr = BitConverter.GetBytes(((rf627_old_hello_info_by_service_protocol*)info)->firmware_version);
                                        firmware_version = firmware_arr[3] + "." + firmware_arr[2] + "." + firmware_arr[1];
                                        byte[] hardware_arr = BitConverter.GetBytes(((rf627_old_hello_info_by_service_protocol*)info)->hardware_version);
                                        hardware_version = firmware_arr[3] + "." + firmware_arr[2] + "." + firmware_arr[1];

                                        z_smr = ((rf627_old_hello_info_by_service_protocol*)info)->z_begin;
                                        z_mr = ((rf627_old_hello_info_by_service_protocol*)info)->z_range;
                                        x_smr = ((rf627_old_hello_info_by_service_protocol*)info)->x_begin;
                                        x_emr = ((rf627_old_hello_info_by_service_protocol*)info)->x_end;
                                        break;
                                    case PROTOCOL_TYPES.ETHERNET_IP:
                                        break;
                                    case PROTOCOL_TYPES.MODBUS_TCP:
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            }

                        case SCANNER_TYPES.RF62X_SMART:
                            {
                                switch (protocol)
                                {
                                    case PROTOCOL_TYPES.SERVICE:
                                        device_name = Marshal.PtrToStringAnsi((IntPtr)(((rf627_smart_hello_info_by_service_protocol*)info)->user_general_deviceName));
                                        serial_number = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_serial;

                                        ip_address = Marshal.PtrToStringAnsi((IntPtr)(((rf627_smart_hello_info_by_service_protocol*)info)->user_network_ip));
                                        mac_address = Marshal.PtrToStringAnsi((IntPtr)(((rf627_smart_hello_info_by_service_protocol*)info)->fact_network_macAddr));

                                        profile_port = (ushort)((rf627_smart_hello_info_by_service_protocol*)info)->user_network_hostPort;
                                        service_port = (ushort)((rf627_smart_hello_info_by_service_protocol*)info)->user_network_servicePort;

                                        firmware_version = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_firmwareVer[0] + "."
                                                            + ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_firmwareVer[1] + "."
                                                            + ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_firmwareVer[2];
                                        byte[] hardware_arr = BitConverter.GetBytes(((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_hardwareVer);
                                        hardware_version = hardware_arr[3] + "." + hardware_arr[2] + "." + hardware_arr[1];

                                        z_smr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_smr;
                                        z_mr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_mr;
                                        x_smr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_xsmr;
                                        x_emr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_xemr;
                                        break;
                                    case PROTOCOL_TYPES.ETHERNET_IP:
                                        break;
                                    case PROTOCOL_TYPES.MODBUS_TCP:
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            }
                    }


                }
                ~HelloInfo()
                {

                }

                public string device_name { get; }
                public uint serial_number { get; }
                public string ip_address { get; }
                public string mac_address { get; }
                public ushort profile_port { get; }
                public ushort service_port { get; }
                public string firmware_version { get; }
                public string hardware_version { get; }
                public uint z_smr { get; }
                public uint z_mr { get; }
                public uint x_smr { get; }
                public uint x_emr { get; }

            }

        }
    }
}
