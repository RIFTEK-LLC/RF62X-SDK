using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Net.NetworkInformation;
using System.Linq;
using System.ComponentModel.Design;


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
            private struct input_t
            {
                public ushort size;
                public byte* payload;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct output_t
            {
                public ushort size;
                public byte* payload;
            };

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct command2_t
            {
                public byte* name;
                public input_t input;
                public output_t output;
            };

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
            private unsafe struct v1_0_standart_t
            {
                public ushort zmr;
                public ushort xemr;
                public ushort discrete_value;
                public fixed byte reserved_0[10];
            }

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private unsafe struct v1_1_standart_t
            {
                public ushort zmr;
                public ushort xemr;
                public ushort discrete_value;
                public fixed byte reserved_0[10];
            }

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private unsafe struct v1_1_polynomial_t
            {
                public ushort zmr;
                public ushort xemr;
                public float scaling_factor;
                public fixed byte reserved_0[8];
            }

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private unsafe struct v1_2_standart_t
            {
                public ushort zmr;
                public ushort xemr;
                public ushort discrete_value;
                public ushort alignment_with_sensor;
                public fixed byte reserved_0[8];
            }

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private unsafe struct v1_2_polynomial_t
            {
                public ushort zmr;
                public ushort xemr;
                public float scaling_factor;
                public fixed byte reserved_0[8];
            }

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private unsafe struct v1_3_standart_t
            {
                public ushort zmr;
                public ushort xemr;
                public uint pixels_divider;
                public ushort alignment_with_sensor;
                public fixed byte reserved_0[6];
            }

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private unsafe struct v1_3_polynomial_t
            {
                public ushort zmr;
                public ushort xemr;
                public float scaling_factor;
                public fixed byte reserved_0[8];
            }

            [StructLayout(LayoutKind.Explicit, Pack = _pack, Size = 16)]
            private unsafe struct profile_header_union_t
            {
                [FieldOffset(0)] public v1_0_standart_t v1_0_standart;
                [FieldOffset(0)] public v1_1_standart_t v1_1_standart;
                [FieldOffset(0)] public v1_1_polynomial_t v1_1_polynomial;
                [FieldOffset(0)] public v1_2_standart_t v1_2_standart;
                [FieldOffset(0)] public v1_2_polynomial_t v1_2_polynomial;
                [FieldOffset(0)] public v1_3_standart_t v1_3_standart;
                [FieldOffset(0)] public v1_3_polynomial_t v1_3_polynomial;
            }

            //[StructLayout(LayoutKind.Sequential, Pack = _pack)]
            //private struct profile_header
            //{
            //    public byte data_type;
            //    public byte flags;
            //    public ushort device_type;
            //    public uint serial_number;
            //    public ulong system_time;

            //    public byte proto_version_major;
            //    public byte proto_version_minor;
            //    public byte hardware_params_offset;
            //    public byte data_offset;
            //    public uint packet_count;
            //    public uint measure_count;

            //    public ushort zmr;
            //    public ushort xemr;
            //    public ushort discrete_value;
            //    public fixed byte reserved_0[10];
            //    public uint license_hash;

            //    public uint exposure_time;
            //    public uint laser_value;
            //    public uint step_count;
            //    public byte dir;
            //    public ushort payload_size;
            //    public byte bytes_per_point;
            //};

            [StructLayout(LayoutKind.Explicit, Pack = _pack, Size = 72)]
            private unsafe struct profile_header
            {
                [FieldOffset(0)] public byte data_type;
                [FieldOffset(1)] public byte flags;
                [FieldOffset(2)] public ushort device_type;
                [FieldOffset(4)] public uint serial_number;
                [FieldOffset(8)] public ulong system_time;

                [FieldOffset(16)] public byte proto_version_major;
                [FieldOffset(17)] public byte proto_version_minor;
                [FieldOffset(18)] public byte hardware_params_offset;
                [FieldOffset(19)] public byte data_offset;
                [FieldOffset(20)] public uint packet_count;
                [FieldOffset(24)] public uint measure_count;

                [FieldOffset(28)] public profile_header_union_t u;

                [FieldOffset(44)] public uint license_hash;

                [FieldOffset(48)] public uint exposure_time;
                [FieldOffset(52)] public uint laser_value;
                [FieldOffset(56)] public uint step_count;

                [FieldOffset(60)] public byte dir;
                [FieldOffset(62)] public ushort payload_size;
                [FieldOffset(64)] public byte bytes_per_point;
            }

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

            [StructLayout(LayoutKind.Sequential, Pack = _pack)]
            private struct pixels_v1_3_format
            {
                public uint* pixels;
                public uint pixels_count;
            }



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
                public pixels_v1_3_format pixelsV13Format;
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
                public uint frame_width;
                public uint frame_height;
                public byte pixel_size;

                public byte user_roi_active;
                public byte user_roi_enabled;
                public uint user_roi_pos;
                public uint user_roi_size;
                public uint fact_sensor_width;
                public uint fact_sensor_height;
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
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte WinSockInit();
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern void WinSockDeinit();
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte EnumAdapterAddresses();
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern void FreeAdapterAddresses();

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte* GetAdapterAddress(int index);
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte* GetAdapterMasks(int index);
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern int GetAdaptersCount();

            // rf62Xcore.h
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte core_init();

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte* sdk_version();

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern void platform_free(void* data);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern void* platform_calloc(UIntPtr num, UIntPtr size);


            // rf62X_sdk.h
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern void set_platform_adapter_settings(uint subnet_mask, uint host_ip_addr);


            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte search_scanners(vector_t* list, SCANNER_TYPES model, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern hello_information get_info_about_scanner(scanner_base_t* device, PROTOCOL_TYPES protocol);


            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte connect_to_scanner(scanner_base_t* device, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte check_connection_to_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte disconnect_from_scanner(scanner_base_t* device, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern void free_scanner(scanner_base_t* device);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern rf627_profile2D_t* get_profile2D_from_scanner(scanner_base_t* device, bool zero_points, bool realtime, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte send_profile2D_request_to_scanner(scanner_base_t* device, uint count, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern void free_profile2D(rf627_profile2D_t* profile);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern rf627_frame_t* get_frame_from_scanner(
                scanner_base_t* device,
                bool confirm_enabled,
                uint waiting_time,
                PROTOCOL_TYPES protocol);


            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte read_params_from_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte write_params_to_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte save_params_to_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte load_recovery_params_from_scanner(scanner_base_t* device, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern parameter_t* get_parameter(scanner_base_t* device, byte* param_name);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte set_parameter(scanner_base_t* device, parameter_t* param);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern parameter_t* create_parameter_from_type(byte* type);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern void free_parameter(parameter_t* param, SCANNER_TYPES type);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte get_dumps_profiles_from_scanner(
                scanner_base_t* device, uint index, uint count, uint timeout, 
                PROTOCOL_TYPES protocol, rf627_profile2D_t** dump, uint* dump_size, uint dump_unit_size);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte get_authorization_token_from_scanner(
                scanner_base_t* device, byte** token, uint* token_size, uint timeout, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte set_authorization_key_to_scanner(
                scanner_base_t* device, byte* key, uint key_size, uint timeout, PROTOCOL_TYPES protocol);

            // TODO: calibration_table

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte send_reboot_device_request_to_scanner(scanner_base_t* device, PROTOCOL_TYPES protocol);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte send_command2(scanner_base_t* device, command2_t* command);

            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte send_custom_command_to_scanner(
                scanner_base_t* device, byte* cmd_name, byte* data_type, byte* input, uint in_size, byte** output, uint* out_size);


            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern void vector_init(vector_t** vec);
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
            private static extern UIntPtr vector_count(vector_t* vec);
            [DllImport("libRF62X-SDK", CallingConvention = CallingConvention.Cdecl)]
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
                PROFILE_INTRP = 0x13,

                PROFILE_POLYNOMIAL = 0x20
            };

            public enum COUNT_TYPES
            {
                STEP = 1,
                MEASURE = 2,
                PACKET = 3
            };

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

                    public uint license_hash { get; private set; }
                    public uint exposure_time { get; private set; }
                    public uint laser_value { get; private set; }
                    public uint step_count { get; private set; }
                    public byte dir { get; private set; }
                    public ushort payload_size { get; private set; }
                    public byte bytes_per_point { get; private set; }

                    public float scaling_factor { get; private set; }
                    public uint pixels_divider { get; private set; }
                    public ushort alignment_with_sensor { get; private set; }

                    public Header(void* profile2D, SCANNER_TYPES type)
                    {
                        profile_header* h = null;

                        switch (type)
                        {
                            case SCANNER_TYPES.RF627_OLD:
                                h = &((rf627_old_profile2D_t*)profile2D)->header;
                                break;

                            case SCANNER_TYPES.RF62X_SMART:
                                h = &((rf627_smart_profile2D_t*)profile2D)->header;
                                break;
                        }

                        if (h == null) return;

                        data_type = (PROFILE_DATA_TYPES)h->data_type;

                        flags = h->flags;
                        device_type = h->device_type;
                        serial_number = h->serial_number;
                        system_time = h->system_time;

                        version_major = h->proto_version_major;
                        version_minor = h->proto_version_minor;
                        hardware_params_offset = h->hardware_params_offset;
                        data_offset = h->data_offset;
                        packet_count = h->packet_count;
                        measure_count = h->measure_count;

                        // default
                        zmr = 0;
                        xemr = 0;
                        discrete_value = 0;
                        scaling_factor = 0.0f;
                        pixels_divider = 0;
                        alignment_with_sensor = 0;

                        bool isPoly = (data_type == PROFILE_DATA_TYPES.PROFILE_POLYNOMIAL);

                        if (version_major == 1 && version_minor == 0)
                        {
                            zmr = h->u.v1_0_standart.zmr;
                            xemr = h->u.v1_0_standart.xemr;
                            discrete_value = h->u.v1_0_standart.discrete_value;
                        }
                        else if (version_major == 1 && version_minor == 1)
                        {
                            if (isPoly)
                            {
                                zmr = h->u.v1_1_polynomial.zmr;
                                xemr = h->u.v1_1_polynomial.xemr;
                                scaling_factor = h->u.v1_1_polynomial.scaling_factor;
                            }
                            else
                            {
                                zmr = h->u.v1_1_standart.zmr;
                                xemr = h->u.v1_1_standart.xemr;
                                discrete_value = h->u.v1_1_standart.discrete_value;
                            }
                        }
                        else if (version_major == 1 && version_minor == 2)
                        {
                            if (isPoly)
                            {
                                zmr = h->u.v1_2_polynomial.zmr;
                                xemr = h->u.v1_2_polynomial.xemr;
                                scaling_factor = h->u.v1_2_polynomial.scaling_factor;
                            }
                            else
                            {
                                zmr = h->u.v1_2_standart.zmr;
                                xemr = h->u.v1_2_standart.xemr;
                                discrete_value = h->u.v1_2_standart.discrete_value;
                                alignment_with_sensor = h->u.v1_2_standart.alignment_with_sensor;
                            }
                        }
                        else if (version_major == 1 && version_minor == 3)
                        {
                            if (isPoly)
                            {
                                zmr = h->u.v1_3_polynomial.zmr;
                                xemr = h->u.v1_3_polynomial.xemr;
                                scaling_factor = h->u.v1_3_polynomial.scaling_factor;
                            }
                            else
                            {
                                zmr = h->u.v1_3_standart.zmr;
                                xemr = h->u.v1_3_standart.xemr;
                                pixels_divider = h->u.v1_3_standart.pixels_divider;
                                alignment_with_sensor = h->u.v1_3_standart.alignment_with_sensor;
                            }
                        }

                        license_hash = h->license_hash;

                        exposure_time = h->exposure_time;
                        laser_value = h->laser_value;
                        step_count = h->step_count;
                        dir = h->dir;
                        payload_size = h->payload_size;
                        bytes_per_point = h->bytes_per_point;
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
                                                    uint pixels_count = ((rf627_profile2D_t*)_base)->rf627old_profile2D->pixelsFormat.pixels_count;
                                                    pixels = new List<uint>((int)pixels_count);
                                                    for (int i = 0; i < pixels_count; i++)
                                                    {
                                                        pixels.Add(((rf627_profile2D_t*)_base)->rf627old_profile2D->pixelsFormat.pixels[i]);
                                                    }

                                                    if (((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity_count > 0)
                                                    {
                                                        uint intensity_count = ((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity_count;
                                                        intensities = new List<byte>((int)intensity_count);
                                                        for (int i = 0; i < intensity_count; i++)
                                                            intensities.Add(((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity[i]);
                                                    }
                                                    break;
                                                }
                                            case PROFILE_DATA_TYPES.PROFILE:
                                            case PROFILE_DATA_TYPES.PROFILE_INTRP:
                                                {
                                                    uint points_count = ((rf627_profile2D_t*)_base)->rf627old_profile2D->profileFormat.points_count;
                                                    points = new List<Point2D>((int)points_count);
                                                    for (int i = 0; i < points_count; i++)
                                                    {
                                                        Point2D point = new Point2D(
                                                            ((rf627_profile2D_t*)_base)->rf627old_profile2D->profileFormat.points[i].x,
                                                            ((rf627_profile2D_t*)_base)->rf627old_profile2D->profileFormat.points[i].z);
                                                        points.Add(point);
                                                    }

                                                    if (((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity_count > 0)
                                                    {
                                                        uint intensity_count = ((rf627_profile2D_t*)_base)->rf627old_profile2D->intensity_count;
                                                        intensities = new List<byte>((int)intensity_count);
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
                                                    // v1.3 -> pixelsV13Format (uint32)
                                                    if (header.version_major == 1 && header.version_minor == 3)
                                                    {
                                                        uint cnt = ((rf627_profile2D_t*)_base)->rf627smart_profile2D->pixelsV13Format.pixels_count;
                                                        pixels = new List<uint>((int)cnt);
                                                        for (int i = 0; i < cnt; i++)
                                                            pixels.Add(((rf627_profile2D_t*)_base)->rf627smart_profile2D->pixelsV13Format.pixels[i]);
                                                    }
                                                    else
                                                    {
                                                        // v1.0..v1.2 -> pixelsFormat (uint16) => кастим в uint32
                                                        uint cnt = ((rf627_profile2D_t*)_base)->rf627smart_profile2D->pixelsFormat.pixels_count;
                                                        pixels = new List<uint>((int)cnt);
                                                        for (int i = 0; i < cnt; i++)
                                                            pixels.Add((uint)((rf627_profile2D_t*)_base)->rf627smart_profile2D->pixelsFormat.pixels[i]);
                                                    }

                                                    if (((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity_count > 0)
                                                    {
                                                        uint icnt = ((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity_count;
                                                        intensities = new List<byte>((int)icnt);
                                                        for (int i = 0; i < icnt; i++)
                                                            intensities.Add(((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity[i]);
                                                    }
                                                    break;
                                                }

                                            case PROFILE_DATA_TYPES.PROFILE:
                                            case PROFILE_DATA_TYPES.PROFILE_INTRP:
                                            case PROFILE_DATA_TYPES.PROFILE_POLYNOMIAL:
                                                {
                                                    uint points_count = ((rf627_profile2D_t*)_base)->rf627smart_profile2D->profileFormat.points_count;
                                                    points = new List<Point2D>((int)points_count);
                                                    for (int i = 0; i < points_count; i++)
                                                    {
                                                        points.Add(new Point2D(
                                                            ((rf627_profile2D_t*)_base)->rf627smart_profile2D->profileFormat.points[i].x,
                                                            ((rf627_profile2D_t*)_base)->rf627smart_profile2D->profileFormat.points[i].z));
                                                    }

                                                    if (((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity_count > 0)
                                                    {
                                                        uint icnt = ((rf627_profile2D_t*)_base)->rf627smart_profile2D->intensity_count;
                                                        intensities = new List<byte>((int)icnt);
                                                        for (int i = 0; i < icnt; i++)
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
                public List<uint> pixels { get; }

                public uint[] getPixelsArray()
                {
                    return pixels?.ToArray() ?? Array.Empty<uint>();
                }

                public Point2D[] getPointsArray()
                {
                    return points?.ToArray() ?? Array.Empty<Point2D>();
                }

                public float[] getPointsXArray()
                {
                    if (points == null || points.Count == 0)
                        return Array.Empty<float>();

                    float[] x = new float[points.Count];
                    for (int i = 0; i < points.Count; i++)
                        x[i] = points[i].X;

                    return x;
                }

                public float[] getPointsZArray()
                {
                    if (points == null || points.Count == 0)
                        return Array.Empty<float>();

                    float[] z = new float[points.Count];
                    for (int i = 0; i < points.Count; i++)
                        z[i] = points[i].Z;

                    return z;
                }


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
                                    SensorWidth = _frame->rf627old_frame->width;
                                    SensorHeight = _frame->rf627old_frame->height;

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
                                    FrameWidth = _frame->rf627smart_frame->frame_width;
                                    FrameHeight = _frame->rf627smart_frame->frame_height;
                                    SensorWidth = _frame->rf627smart_frame->fact_sensor_width;
                                    SensorHeight = _frame->rf627smart_frame->fact_sensor_height;

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
                                    platform_free(_frame->rf627old_frame);
                                    break;
                                }
                            case SCANNER_TYPES.RF62X_SMART:
                                {
                                    if (_frame->rf627smart_frame->data != null)
                                        platform_free(_frame->rf627smart_frame->data);
                                    platform_free(_frame->rf627smart_frame);
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
                public uint SensorWidth { get; }
                public uint SensorHeight { get; }

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
                                        host_ip_address = Marshal.PtrToStringAnsi((IntPtr)(((rf627_smart_hello_info_by_service_protocol*)info)->user_network_hostIP));
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
                public string host_ip_address { get; }
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
