using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Net.NetworkInformation;

namespace SDK
{
    namespace SCANNERS
    {
        public unsafe class RF62X
        {
            #region dll

            #region dll-types
            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct vector_t
            {
                public void** data;
                public UIntPtr size;
                public UIntPtr count;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct config_options_t
            {
                public uint version;
                public uint length;
                public byte validated;
                public byte reserved;
            }

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct _InitRegs
            {
                ushort Addr;
                ushort Value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct _speedDuplex
            {
                ushort speed;
                byte duplex;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct factory_params_t
            {
                /*-------Общие параметры устройства-----------------------*/
                [StructLayout(LayoutKind.Sequential, Pack = 8)]
                public unsafe struct General
                {
                    public ushort DeviceID;            //Идентификатор типа сканера
                    public uint Serial;                //Серийный номер сканера
                    public uint SerialOfPCB;       //Серийный номер электроники
                    public uint OperatingTime_H;   //Наработка сканера, часов
                    public byte OperatingTime_M;   //Наработка сканера, минут
                    public byte OperatingTime_S;   //Наработка сканера, секунд
                    public uint RunTime_H;         //Время работы после запуска, часов
                    public byte RunTime_M;         //Время работы после запуска, минут
                    public byte RunTime_S;         //Время работы после запуска, секунд
                    public uint StartUp_Counter;    //Количество запусков сканера
                    public uint FirmWareVer;       //Версия прошивки
                    public uint HardWareVer;       //Версия аппаратного обеспечения
                    public uint CustomerID;
                    public uint PL_SystemClk;      //Системная тактовая для PL - частота AXI в Гц
                    public uint BaseZ;
                    public uint RangeZ;
                    public uint RangeXStart;
                    public uint RangeXEnd;
                    public ushort PixelsDivider;
                    public ushort ProfilesDivider;
                    public uint FSBL_Version;       //Версия загрузчика
                    public fixed byte oemDeviceName[16];
                    public fixed byte Reserved[76];

                };
                public General general;
                /*-------Параметры установленной матрицы-------------------*/
                [StructLayout(LayoutKind.Sequential, Pack = 8)]
                public struct Sensor
                {
                    public fixed byte Name[32];                    //Имя матрицы - для отображения
                    public ushort Width;                       //Количество пикселов по горизонтали
                    public ushort Height;                      //Количество пикселов но вертикали
                    public uint PixelClock;                    //Пиксельная частота в Гц
                    public ushort Black_OddLines;
                    public ushort Black_EvenLines;
                    public uint FrameCycle_ConstPart;
                    public uint FrameCycle_PerLinePart;
                    public byte FrameRateORExposure;       //Селектор по чем настраивать матрицу - по частоте кадров или экспозиции: 0 - по частоте, 1 - по экспозиции
                    public uint MinExposure;               //Минимальное время экспозиции в нс.
                    public byte ImageFlipping;             //Режим отражения изображения: 0 - без отражения, 1 - по X, 2 - по Y, 3 - и по X и по Y
                    public uint MaxExposure;               //Максимальное время экспозиции, заданное при настройке сканера
                    public byte edrPoint1Value;                //Значение напряжения (в условных единицах 0..63) в 1-й точке излома прямой накопления (стр.30-31 даташита CMV300)
                    public byte edrPoint2Value;                //Значение напряжения (в условных единицах 0..63) во 2-й точке излома прямой накопления (стр.30-31 даташита CMV300)
                    public ushort edrPoint1Pos;                //Положение в 1/1000 точки относительно начала экспозиции, т.е. 0 - одновременно с началом экспозиции, 999 - сразу в конце
                    public ushort edrPoint2Pos;                //Положение в 1/1000 точки относительно начала экспозиции, т.е. 0 - одновременно с началом экспозиции, 999 - сразу в конце
                    public fixed byte Reserved[113];
                    public fixed ushort InitRegs[64 * 2];                      //Структура с параметрами инициализации регистров матрицы
                };
                public Sensor sensor;
                /*-------Параметры сетевого подключения-------------------*/
                [StructLayout(LayoutKind.Sequential, Pack = 8)]
                public struct Network
                {
                    public fixed byte MAC[6];
                    public ushort EIP_VendorID;
                    public ushort EIP_DeviceType;
                    public byte forceAutoNegTime;          //Количество секунд, через которое сканер установит автосогласование принудительно в случае отсутствия связи по Ethernet
                    public fixed byte Reserved[31];
                };
                public Network network;
                /*-------Параметры управления лазером----------------------*/
                [StructLayout(LayoutKind.Sequential, Pack = 8)]
                public struct Laser
                {
                    public ushort Wavelength;              //Длина волны в нм
                    public byte Koeff1;                    //Коээфициент крутизны регулирования отпределяется как Koeff1/128
                    public byte Koeff2;
                    public uint MinValue;              //Значение, при котором лазер зажигается
                    public uint MaxValue;              //Максимальное допустимое значение
                    public byte EnableModeChange;      //Разрешение изменения режима работы лазера: 0 - запрещено, 1 - разрешено
                    public fixed byte Reserved[31];
                };
                public Laser laser;
                /*------------Параметры входных каналов--------------------*/
                [StructLayout(LayoutKind.Sequential, Pack = 8)]
                public struct Inputs
                {
                    public ushort In1_MinDelay;            //Минимальная задержка в нс
                    public uint In1_MaxDelay;          //Максимальная задержка в нс
                    public ushort MaxDividerIn1;           //Максимальное значение делителя частоты кадров
                    public ushort MinDividerIn1;           //Минимальное значение делителя частоты кадров
                    public fixed byte Reserved[62];
                };
                public Inputs inputs;
                /*------------Параметры выходных каналов-------------------*/
                [StructLayout(LayoutKind.Sequential, Pack = 8)]
                public struct Outputs
                {
                    public ushort Out1_MinDelay;
                    public uint Out1_MaxDelay;
                    public ushort Out1_MinPulseWidth;
                    public uint Out1_MaxPulseWidth;
                    public ushort Out2_MinDelay;
                    public uint Out2_MaxDelay;
                    public ushort Out2_MinPulseWidth;
                    public uint Out2_MaxPulseWidth;
                    public fixed byte Reserved[32];
                };
                public Outputs outputs;
                /*------------Параметры обработки профилей-----------------*/
                [StructLayout(LayoutKind.Sequential, Pack = 8)]
                public struct Profiles
                {
                    public uint maxDumpSize;
                    public fixed byte Reserved[60];
                };
                public Profiles profiles;
                /*------------Параметры протокола EthernetIP---------------*/
                [StructLayout(LayoutKind.Sequential, Pack = 8)]
                public struct Eip
                {
                    [StructLayout(LayoutKind.Sequential, Pack = 8)]
                    public struct Identity
                    {
                        public ushort vendorID;                // Attribute 1: Vendor ID - идентификационный номер производителя устройства
                        public ushort deviceType;              // Attribute 2: Device Type - тип устройства, который определяет его область использования
                        public ushort productCode;         // Attribute 3: Product Code - идентифицирует номер конкретного продукта
                        [StructLayout(LayoutKind.Sequential, Pack = 8)]
                        public struct Revision
                        {
                            public byte majorRev;          // Attribute 4: Revision	USINT Major
                            public byte minorRev;          //							USINT Minor
                        };                                      // Структура, хранящая EIP-версию девайса
                        public Revision revision;
                    };
                    public Identity identity;

                    [StructLayout(LayoutKind.Sequential, Pack = 8)]
                    public struct TcpInterface
                    {
                        public uint configCapability;      // Attribute 2: Данный атрибут описывает поддержку устройством дополнительных возможностей конфигурации сети
                        [StructLayout(LayoutKind.Sequential, Pack = 8)]
                        public struct PhyLinkObject
                        {
                            public ushort pathSize;            // Path size in 16 bit words (path_size * 16 bit)
                            public ushort classId;         // Class ID of the linked object
                            public ushort instanceNumber;      // Requested Instance Number of the linked object
                            public ushort attributeNumber; // Requested Attribute Number of the linked object
                        };
                        public PhyLinkObject phyLinkObject;                                  // Attribute 4: Этот атрибут идентифицирует объект, связанный с базовым физическим интерфейсом связи (Ethernet Link Object)
                    };
                    public TcpInterface tcpInterface;

                    public byte intrfType;             //Type of rfInterface: twisted pair, fiber, rfInternal, etc
                    [StructLayout(LayoutKind.Sequential, Pack = 8)]
                    public struct IntrfCapability
                    {
                        public ushort capabilityBits;
                        public byte speedDupCount;

                        //[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
                        public fixed byte speedDuplex[16];
                    };                                  //Path to physical link object
                    public IntrfCapability intrfCapability;
                    public fixed byte Reserved[44];
                };
                public Eip eip;
                /*-------Резерв--------------------------------------------*/
                public fixed byte Reserved[167];
                /*---------------------------------------------------------*/
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct DTF_header
            {
                fixed byte Tag[4];            //<! File header tag = "DTF+"
                ushort FormatVersion;     //<! Version of header format (1)
                struct timestamp
                {
                    struct date
                    {
                        byte Day;
                        byte Month;
                        ushort Year;
                    }
                            ;
                    struct time
                    {
                        byte Hour;
                        byte Minute;
                        byte Second;
                    };
                };                                     //<! date and time of calibration
                ushort DevType;            //<! Device type (627)
                uint SerialNumber;       //<! Serial Number of Scanner
                ushort BaseZ;              //<! Z base, mm
                ushort RangeZ;             //<! Z measurement range, mm
                ushort RangeXStart;        //<! X start measurement range, mm
                ushort RangeXEnd;          //<! X end measurement range, mm
                ushort YSteps;             //<! Number of calibration steps
                ushort StartPosition;      //<! Start position
                ushort EndPosition;        //<! End position
                ushort CutXLeft;           //<! Amount of pixels to cut from left
                ushort CutXRight;          //<! Amount of pixels to cut from right
                byte PlaneType;          //<! 0 - ZPlane, 1 - TrianglesXY
                byte InvertZ;            //<! 0 - no invert, other - invert
                uint TriangleWidth;      //<! Triangle width, um
                uint TriangleHeight;     //<! Triangle height, um
                byte AveragingSize;      //<! Number of pixels profiles for averaging
                uint Exposure;           //<! Exposure time, ns (0 for Auto)
                short Temp;               //<! Temperature upon calibration, C/10
                double StepLength;         //<! Z Step Length
                uint FirmwareVer;       //<! Firmware Version
                uint HardwareVer;       //<! Hardware Version
                fixed byte Reserved[186];      //<!- Reserved
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct TBL_header
            {
                byte FormatVersion;     //<! Version of header format (1)
                ushort CRC;                //<!- CRC
                uint SerialNumber;       //<! Serial Number of Scanner
                struct timestamp
                {
                    struct date
                    {
                        ushort Year;
                        byte Month;
                        byte Day;
                    };
                    struct time
                    {
                        byte Hour;
                        byte Minute;
                        byte Second;
                    };
                };                                     //<! date and time of calibration
                fixed byte Zero[242];          //<! Must be filled with zeroes
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct general_params_t
            {
                public fixed byte name[64];
                public byte save_log_to_spi;
                public fixed byte reserved[127];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct sysmon_params_t
            {
                public short fpga_temp;
                public byte params_changed;         //Параметры были изменены, но не сохранены: 1 - factory, 2 - user, 3 - factory & user
                public short sens00_temp;
                public short sens00_max;
                public short sens00_min;
                public short sens01_temp;
                public short sens01_max;
                public short sens01_min;
                public short sens10_temp;
                public short sens10_max;
                public short sens10_min;
                public short sens11_temp;
                public short sens11_max;
                public short sens11_min;
                public fixed byte reserved[55];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct sensor_params_t
            {
                public byte dhs;
                public byte gain_analog;
                public byte gain_digital;
                public uint exposure;
                public uint max_exposure;
                public uint frame_rate;
                public uint max_frame_rate;
                public byte exposure_hdr_mode;
                public byte auto_exposure;
                public byte column_edr_mode;
                public byte column_exposure_div;
                public byte column_exposure_max_div;
                public fixed byte reserved_1[59];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct rf625compat_params_t
            {
                public byte enable;
                public ushort tcp_port;
                public fixed byte reserved[32];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct roi_params_t
            {
                public byte enable;
                public byte active;
                public ushort window_height;
                public byte position_mode;
                public ushort window_top;
                public ushort current_window_top;
                public ushort profile_size;
                public fixed byte reserved[80];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct network_params_t
            {
                public ushort speed;
                public byte autonegotiation;
                public uint ip_address;
                public uint net_mask;
                public uint gateway_ip;
                public uint host_ip;
                public ushort stream_port;
                public ushort http_port;
                public ushort service_port;
                //    ushort    eip_broadcast_port;
                //    ushort    eip_port;
                public fixed byte reserved[68];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct stream_params_t
            {
                public byte enable;
                public byte format;
                public byte ack;
                public byte include_intensivity;
                public fixed byte reserved[31];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct image_processing_params_t
            {
                public uint brightness_threshold;
                public byte filter_width;
                public byte processing_mode;
                public byte reduce_noise;
                public uint frame_rate;
                public byte median_filter_mode;
                public byte bilateral_filter_mode;
                public byte peak_select_mode;
                public byte profile_flip;
                public fixed byte reserved[56];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct laser_params_t
            {
                public byte enable;
                public byte auto_level;
                public ushort level;
                public fixed byte reserved[32];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct inputs_preset_t
            {
                public ushort params_mask;
                public byte in1_enable;
                public byte in1_mode;
                public uint in1_delay;
                public byte in1_decimation;
                public byte in2_enable;
                public byte in2_mode;
                public byte in2_invert;
                public byte in3_enable;
                public byte in3_mode;
                public fixed byte reserved[12];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct inputs_params_t
            {
                public byte preset_index;
                public inputs_preset_t Params1;
                public inputs_preset_t Params2;
                public inputs_preset_t Params3;
                public inputs_preset_t Params4;
                public inputs_preset_t Params5;
                public inputs_preset_t Params6;
                public inputs_preset_t Params7;
                public inputs_preset_t Params8;
                public inputs_preset_t Params9;
                public inputs_preset_t Params10;
                public inputs_preset_t Params11;
                public inputs_preset_t Params12;
                public fixed byte reserved[32];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct outputs_params_t
            {
                public byte out1_enable;
                public byte out1_mode;
                public uint out1_delay;
                public uint out1_pulse_width;
                public byte out1_invert;
                public byte out2_enable;
                public byte out2_mode;
                public uint out2_delay;
                public uint out2_pulse_width;
                public byte out2_invert;
                public fixed byte reserved[32];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct user_params_t
            {
                public general_params_t general;
                public sysmon_params_t sysmon;
                public rf625compat_params_t rf625compat;
                public sensor_params_t sensor;
                public roi_params_t roi;
                public network_params_t network;
                public stream_params_t stream;
                public image_processing_params_t image_processing;
                public laser_params_t laser;
                public inputs_params_t inputs;
                public outputs_params_t outputs;
                fixed byte reserved[283];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct rf627_old_hello_info_by_service_protocol
            {
                public byte* device_name;
                public uint serial_number;
                public uint ip_address;
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

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct rf627_smart_t
            {
                public void* m_svc_sock;
                public void* m_data_sock;
                public ushort msg_count;

                private vector_t* params_list;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct rf627_old_t
            {
                public config_options_t options;
                public factory_params_t factory_params;
                public user_params_t user_params;

                public void* m_svc_sock;
                public void* m_data_sock;
                public ushort msg_count;

                public vector_t* params_list;

                public rf627_old_hello_info_by_service_protocol info_by_service_protocol;
            };

            [StructLayout(LayoutKind.Explicit)]
            private struct scanner_base_t
            {
                [FieldOffset(0)]
                public SCANNERS_TYPES type;
                [FieldOffset(8)]
                public rf627_old_t* rf627_old;
                [FieldOffset(8)]
                public rf627_smart_t* rf627_smart;
            };



            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct enumRec_t
            {
                public int value;
                public byte* key;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct valuesEnum_t
            {
                public int recCount;
                public enumRec_t rec;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
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

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct value_uint32_t
            {
                public uint min;
                public uint max;
                public uint step;
                public uint defValue;
                public valuesEnum_t* enumValues;
                public uint value;

            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct value_uint64_t
            {
                public ulong min;
                public ulong max;
                public ulong step;
                public ulong defValue;
                public valuesEnum_t* enumValues;
                public ulong value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct value_int32_t
            {
                public int min;
                public int max;
                public int step;
                public int defValue;
                public valuesEnum_t* enumValues;
                public int value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct value_int64_t
            {
                public long min;
                public long max;
                public long step;
                public long defValue;
                public valuesEnum_t* enumValues;
                public long value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct value_flt_t
            {
                public float min;
                public float max;
                public float step;
                public float defValue;
                public float value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct value_dbl_t
            {
                public double min;
                public double max;
                public double step;
                public double defValue;
                public double value;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
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

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
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

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
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

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
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

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
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

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
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

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct value_str_t
            {
                public ushort maxLen;
                public byte* defValue;
                public byte* value;
            };

            [StructLayout(LayoutKind.Explicit, Pack = 8)]
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


            [StructLayout(LayoutKind.Sequential, Pack = 8)]
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
                public fixed byte reserved_1[3];
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct pixels_format
            {
                public ushort* pixels;
                public uint pixels_count;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct rf627_old_point_t
            {
                public float x;
                public float z;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 8)]
            private struct profile_format
            {
                public rf627_old_point_t* points;
                public uint points_count;
            };

            [StructLayout(LayoutKind.Explicit, Pack = 8)]
            private struct rf627_old_profile_t
            {
                [FieldOffset(0)]
                public profile_header header;
                [FieldOffset(64)]
                public pixels_format pixelsFormat;
                [FieldOffset(64)]
                public profile_format profileFormat;
                [FieldOffset(80)]
                public byte* intensity;
                [FieldOffset(88)]
                public uint intensity_count;
            }
            [StructLayout(LayoutKind.Explicit, Pack = 8)]
            private struct rf627_profile_t
            {
                [FieldOffset(0)]
                public SCANNERS_TYPES type;
                [FieldOffset(8)]
                public rf627_old_profile_t* rf627_profile;
            };



            #endregion

            #region dll-methods

            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte search_scanners(vector_t* list, SCANNERS_TYPES model, PROTOCOLS_TYPES protocol);

            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void vector_init(vector_t** vec);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern UIntPtr vector_count(vector_t* vec);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void* vector_get(vector_t* vec, UIntPtr index);

            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte read_params_from_scanner(scanner_base_t* device, PROTOCOLS_TYPES protocol);

            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern parameter_t* get_parameter(scanner_base_t* device, byte* param_name);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte connect_to_scanner(scanner_base_t* device, PROTOCOLS_TYPES protocol);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte disconnect_from_scanner(scanner_base_t* device, PROTOCOLS_TYPES protocol);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern rf627_profile_t* get_profile2D_from_scanner(scanner_base_t* device, bool zero_points, PROTOCOLS_TYPES protocol);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern rf627_old_profile_t* rf627_old_get_profile(rf627_old_t* scanner);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern parameter_t* create_parameter_from_type(byte* type);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte set_parameter(scanner_base_t* device, parameter_t* param);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte write_params_to_scanner(scanner_base_t* device, PROTOCOLS_TYPES protocol);
            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void set_platform_adapter_settings(uint host_mask, uint host_ip_addr);


            #endregion

            #endregion


            public static class Params
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
                                    break;
                                }
                            case "uint32_t":
                                {
                                    return typeof(uint);
                                    break;
                                }
                            case "uint64_t":
                                {
                                    return typeof(ulong);
                                    break;
                                }
                            case "int32_t":
                                {
                                    return typeof(int);
                                    break;
                                }
                            case "int64_t":
                                {
                                    return typeof(long);
                                    break;
                                }
                            case "float_t":
                                {
                                    return typeof(float);
                                    break;
                                }
                            case "double_t":
                                {
                                    return typeof(double);
                                    break;
                                }
                            case "u32_arr_t":
                                {
                                    return typeof(uint[]);
                                    break;
                                }
                            case "u64_arr_t":
                                {
                                    return typeof(ulong[]);
                                    break;
                                }
                            case "i32_arr_t":
                                {
                                    return typeof(int[]);
                                    break;
                                }
                            case "i64_arr_t":
                                {
                                    return typeof(long[]);
                                    break;
                                }
                            case "flt_array_t":
                                {
                                    return typeof(float[]);
                                    break;
                                }
                            case "dbl_array_t":
                                {
                                    return typeof(double[]);
                                    break;
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
                        public static Description user_sensor_exposure1 { get; } = new Description()
                        {
                            Key = "user_sensor_exposure1",
                            Type = "uint32_t"
                        };
                        public static Description user_sensor_exposure2 { get; } = new Description()
                        {
                            Key = "user_sensor_exposure2",
                            Type = "uint32_t"
                        };
                        public static Description user_sensor_exposure3 { get; } = new Description()
                        {
                            Key = "user_sensor_exposure3",
                            Type = "uint32_t"
                        };
                        public static Description user_sensor_exposure4 { get; } = new Description()
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
                            Type = "uint32_t"
                        };
                        public static Description mask { get; } = new Description()
                        {
                            Key = "user_network_mask",
                            Type = "uint32_t"
                        };
                        public static Description gateway { get; } = new Description()
                        {
                            Key = "user_network_gateway",
                            Type = "uint32_t"
                        };
                        public static Description hostIP { get; } = new Description()
                        {
                            Key = "user_network_hostIP",
                            Type = "uint32_t"
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
                        public static Description preset { get; } = new Description()
                        {
                            Key = "user_inputs_preset",
                            Type = "uint32_t"
                        };
                        public static Description params_mask { get; } = new Description()
                        {
                            Key = "user_inputs_params_mask",
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
                    list.Add(User.Sensor.user_sensor_exposure1);
                    list.Add(User.Sensor.user_sensor_exposure2);
                    list.Add(User.Sensor.user_sensor_exposure3);
                    list.Add(User.Sensor.user_sensor_exposure4);

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
                    list.Add(User.Laser.params_mask);
                    list.Add(User.Laser.preset);
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

            public enum SCANNERS_TYPES
            {
                RF627_OLD = 1,
                RF627_SMART = 2
            };
            public enum PROTOCOLS_TYPES
            {
                SERVICE_PROTOKOL = 1,
                ETHERNET_IP = 2,
                MODBUS_TCP = 3,
            };
            public enum PROFILE_TYPE
            {
                PIXELS_NORMAL = 0x10,
                PROFILE_NORMAL = 0x11,
                PIXELS_INTERPOLATED = 0x12,
                PROFILE_INTERPOLATED = 0x13
            };

            public class Param<T>
            {
                public Param(void* _base, T Min, T Max, uint MaxCount, uint DefCount, T DefValue, List<ValuesEnum> ValuesEnum, T Step, T Value)
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

                public T min { get; }
                public T max { get; }
                public uint maxCount { get; }
                public uint defCount { get; }
                public T defValue { get; }

                public class ValuesEnum
                {
                    private T _value;
                    private string _key;
                    public T GetValue()
                    {
                        return _value;
                    }
                    public string GetKey()
                    {
                        return _key;
                    }
                    public ValuesEnum(T value, string key)
                    {
                        _value = value;
                        _key = key;
                    }

                }
                public List<ValuesEnum> valuesEnum { get; }

                private T step;
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
            public unsafe class Profile
            {
                public class Header
                {
                    public PROFILE_TYPE data_type { get; private set; }
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

                    public Header(void* _base)
                    {
                        data_type = (PROFILE_TYPE)((rf627_profile_t*)_base)->rf627_profile->header.data_type;

                        data_offset = ((rf627_profile_t*)_base)->rf627_profile->header.data_offset;
                        flags = ((rf627_profile_t*)_base)->rf627_profile->header.flags;
                        device_type = ((rf627_profile_t*)_base)->rf627_profile->header.device_type;
                        serial_number = ((rf627_profile_t*)_base)->rf627_profile->header.serial_number;
                        system_time = ((rf627_profile_t*)_base)->rf627_profile->header.system_time;

                        version_major = ((rf627_profile_t*)_base)->rf627_profile->header.proto_version_major;
                        version_minor = ((rf627_profile_t*)_base)->rf627_profile->header.proto_version_minor;
                        hardware_params_offset = ((rf627_profile_t*)_base)->rf627_profile->header.hardware_params_offset;
                        data_offset = ((rf627_profile_t*)_base)->rf627_profile->header.data_offset;
                        packet_count = ((rf627_profile_t*)_base)->rf627_profile->header.packet_count;
                        measure_count = ((rf627_profile_t*)_base)->rf627_profile->header.measure_count;

                        zmr = ((rf627_profile_t*)_base)->rf627_profile->header.zmr;
                        xemr = ((rf627_profile_t*)_base)->rf627_profile->header.xemr;
                        discrete_value = ((rf627_profile_t*)_base)->rf627_profile->header.discrete_value;

                        exposure_time = ((rf627_profile_t*)_base)->rf627_profile->header.exposure_time;
                        laser_value = ((rf627_profile_t*)_base)->rf627_profile->header.laser_value;
                        step_count = ((rf627_profile_t*)_base)->rf627_profile->header.step_count;
                        dir = ((rf627_profile_t*)_base)->rf627_profile->header.dir;
                    }

                }

                public Profile(void* _base)
                {
                    if (_base == null)
                        return;
                    header = new Header(_base);

                    switch (header.data_type)
                    {
                        case PROFILE_TYPE.PIXELS_NORMAL:
                        case PROFILE_TYPE.PIXELS_INTERPOLATED:
                            {
                                pixels = new List<ushort>();
                                for (int i = 0;
                                    i < ((rf627_profile_t*)_base)->rf627_profile->pixelsFormat.pixels_count;
                                    i++)
                                {
                                    pixels.Add(((rf627_profile_t*)_base)->rf627_profile->pixelsFormat.pixels[i]);
                                }

                                if (((rf627_profile_t*)_base)->rf627_profile->intensity_count > 0)
                                {
                                    intensities = new List<byte>();
                                    for (int i = 0;
                                        i < ((rf627_profile_t*)_base)->rf627_profile->intensity_count;
                                        i++)
                                        intensities.Add(((rf627_profile_t*)_base)->rf627_profile->intensity[i]);
                                }
                                break;
                            }
                        case PROFILE_TYPE.PROFILE_NORMAL:
                        case PROFILE_TYPE.PROFILE_INTERPOLATED:
                            {
                                points = new List<Point2D>();
                                for (int i = 0;
                                    i < ((rf627_profile_t*)_base)->rf627_profile->profileFormat.points_count;
                                    i++)
                                {
                                    Point2D point = new Point2D(
                                        ((rf627_profile_t*)_base)->rf627_profile->profileFormat.points[i].x,
                                        ((rf627_profile_t*)_base)->rf627_profile->profileFormat.points[i].z);
                                    points.Add(point);
                                }

                                if (((rf627_profile_t*)_base)->rf627_profile->intensity_count > 0)
                                {
                                    intensities = new List<byte>();
                                    for (int i = 0;
                                        i < ((rf627_profile_t*)_base)->rf627_profile->intensity_count;
                                        i++)
                                        intensities.Add(((rf627_profile_t*)_base)->rf627_profile->intensity[i]);
                                }
                                break;
                            }
                        default:
                            break;
                    }

                }

                public Header header { get; private set; }
                public List<byte> intensities { get; }
                public List<Point2D> points { get; }
                public List<ushort> pixels { get; }

            }



            /// <summary>
            /// SdkVersion - Return info about SDK version
            /// </summary>
            /// <returns>SDK version</returns>
            public static uint SdkVersion()
            {
                return CORES.RF62X.CoreVersion();
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
                CORES.RF62X.Init();
                return true;
            }

            /// <summary>
            /// SdkCleanup - Cleanup resources allocated with sdk_init() function
            /// </summary>
            public static void SdkCleanup()
            {

            }

            public unsafe class RF627old
            {
                private void* _base { get; set; }
                public RF627old(void* Base)
                {
                    _base = Base;
                }

                public static List<RF627old> Search(PROTOCOLS_TYPES protocol = PROTOCOLS_TYPES.SERVICE_PROTOKOL)
                {
                    List<RF627old> result = new List<RF627old>();

                    switch (protocol)
                    {
                        case PROTOCOLS_TYPES.SERVICE_PROTOKOL:
                            {
                                vector_t* scanners = stackalloc vector_t[1];
                                vector_init(&scanners);

                                NetworkInterface[] networkInterfaces = NetworkInterface.GetAllNetworkInterfaces();
                                foreach (NetworkInterface adapter in networkInterfaces)
                                {
                                    if (adapter.OperationalStatus == OperationalStatus.Up && (adapter.NetworkInterfaceType == NetworkInterfaceType.Wireless80211 || adapter.NetworkInterfaceType == NetworkInterfaceType.Ethernet))
                                    {
                                        Console.WriteLine("Choose \"{0}\" Network Interface", adapter.Name.ToString());
                                        foreach (UnicastIPAddressInformation ip in adapter.GetIPProperties().UnicastAddresses)
                                        {
                                            if (ip.Address.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork)
                                            {
                                                set_platform_adapter_settings(BitConverter.ToUInt32(ip.IPv4Mask.GetAddressBytes(), 0), BitConverter.ToUInt32(ip.Address.GetAddressBytes(), 0));

                                                search_scanners(scanners, SCANNERS_TYPES.RF627_OLD, PROTOCOLS_TYPES.SERVICE_PROTOKOL);
                                                Console.WriteLine("Send hello packet from {0} IP Address", ip.Address.ToString());
                                            }
                                        }

                                    }
                                }





                                for (int i = 0; i < vector_count(scanners).ToUInt32(); i++)
                                {
                                    scanner_base_t* t = ((scanner_base_t*)vector_get(scanners, (UIntPtr)i));

                                    if (t->type == SCANNERS_TYPES.RF627_OLD)
                                    {
                                        result.Add(new RF627old(t));
                                    }

                                }

                                return result;
                                break;
                            }
                    }
                    return result;

                }

                public bool Connect(PROTOCOLS_TYPES protocol = PROTOCOLS_TYPES.SERVICE_PROTOKOL)
                {
                    switch (protocol)
                    {
                        case PROTOCOLS_TYPES.SERVICE_PROTOKOL:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                result = connect_to_scanner(
                                            ((scanner_base_t*)_base), PROTOCOLS_TYPES.SERVICE_PROTOKOL);
                                return result == 0 ? true : false;
                                break;
                            }
                    }
                    return false;
                }
                public bool Disconnect(PROTOCOLS_TYPES protocol = PROTOCOLS_TYPES.SERVICE_PROTOKOL)
                {
                    switch (protocol)
                    {
                        case PROTOCOLS_TYPES.SERVICE_PROTOKOL:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                result = disconnect_from_scanner(
                                            ((scanner_base_t*)_base), PROTOCOLS_TYPES.SERVICE_PROTOKOL);
                                return result == 0 ? true : false;
                                break;
                            }
                    }
                    return false;
                }

                public Profile GetProfile(PROTOCOLS_TYPES protocol = PROTOCOLS_TYPES.SERVICE_PROTOKOL)
                {
                    switch (protocol)
                    {
                        case PROTOCOLS_TYPES.SERVICE_PROTOKOL:
                            {
                                // Establish connection to the RF627 device by Service Protocol.



                                rf627_profile_t* profile_from_scanner = get_profile2D_from_scanner(
                                            (scanner_base_t*)_base, false, PROTOCOLS_TYPES.SERVICE_PROTOKOL);

                                if (profile_from_scanner->rf627_profile != null)
                                {
                                    Profile profile = new Profile(profile_from_scanner);
                                    CORES.RF62X.Memory.Free(profile_from_scanner->rf627_profile->intensity);
                                    CORES.RF62X.Memory.Free(profile_from_scanner->rf627_profile->pixelsFormat.pixels);
                                    CORES.RF62X.Memory.Free(profile_from_scanner->rf627_profile);
                                    CORES.RF62X.Memory.Free(profile_from_scanner);
                                    return profile;
                                }
                                CORES.RF62X.Memory.Free(profile_from_scanner);
                                break;
                            }
                        default:
                            break;
                    }
                    return new Profile(null);

                }

                public bool ReadParams(PROTOCOLS_TYPES protocol = PROTOCOLS_TYPES.SERVICE_PROTOKOL)
                {
                    switch (protocol)
                    {
                        case PROTOCOLS_TYPES.SERVICE_PROTOKOL:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                result = read_params_from_scanner(
                                            (scanner_base_t*)_base, PROTOCOLS_TYPES.SERVICE_PROTOKOL);

                                return result == 0 ? true : false;
                                break;
                            }
                    }
                    return false;
                }
                public dynamic GetParam(Params.Description paramInfo)
                {
                    return GetParam(paramInfo.Key);
                }
                public dynamic GetParam(string nameKey)
                {
                    byte[] bytes = Encoding.ASCII.GetBytes(nameKey);
                    IntPtr unmanagedPointer = Marshal.AllocHGlobal(bytes.Length);
                    Marshal.Copy(bytes, 0, unmanagedPointer, bytes.Length);

                    parameter_t* param = get_parameter((scanner_base_t*)_base, (byte*)unmanagedPointer);
                    if (param != null)
                        switch (Marshal.PtrToStringAnsi((IntPtr)param->_base.type))
                        {
                            case "unkn_t":
                                {
                                    break;
                                }
                            case "uint32_t":
                                {
                                    List<Param<uint>.ValuesEnum> valEnum = new List<Param<uint>.ValuesEnum>();
                                    if (param->val_uint->enumValues != null)
                                        for (int i = 0; i < param->val_uint->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Param<uint>.ValuesEnum(
                                                    (uint)param->val_uint->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint->enumValues->rec.key)));

                                    Param<uint> result = new Param<uint>(
                                        param,
                                        param->val_uint->min,
                                        param->val_uint->max,
                                        1,
                                        1,
                                        param->val_uint->defValue,
                                        valEnum,
                                        param->val_uint->step,
                                        param->val_uint->value);
                                    return result;
                                    break;
                                }
                            case "uint64_t":
                                {
                                    List<Param<ulong>.ValuesEnum> valEnum = new List<Param<ulong>.ValuesEnum>();
                                    if (param->val_uint64->enumValues != null)
                                        for (int i = 0; i < param->val_uint64->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Param<ulong>.ValuesEnum(
                                                    (ulong)param->val_uint64->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_uint64->enumValues->rec.key)));

                                    Param<ulong> result = new Param<ulong>(
                                        param,
                                        param->val_uint64->min,
                                        param->val_uint64->max,
                                        1,
                                        1,
                                        param->val_uint64->defValue,
                                        valEnum,
                                        param->val_uint64->step,
                                        param->val_uint64->value);
                                    break;
                                }
                            case "int32_t":
                                {
                                    List<Param<int>.ValuesEnum> valEnum = new List<Param<int>.ValuesEnum>();
                                    if (param->val_int->enumValues != null)
                                        for (int i = 0; i < param->val_int->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Param<int>.ValuesEnum(
                                                    (int)param->val_int->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_int->enumValues->rec.key)));

                                    Param<int> result = new Param<int>(
                                        param,
                                        param->val_int->min,
                                        param->val_int->max,
                                        1,
                                        1,
                                        param->val_int->defValue,
                                        valEnum,
                                        param->val_int->step,
                                        param->val_int->value);
                                    return result;
                                    break;
                                }
                            case "int64_t":
                                {
                                    List<Param<long>.ValuesEnum> valEnum = new List<Param<long>.ValuesEnum>();
                                    if (param->val_int64->enumValues != null)
                                        for (int i = 0; i < param->val_int64->enumValues->recCount; i++)
                                            valEnum.Add(
                                                new Param<long>.ValuesEnum(
                                                    (long)param->val_int64->enumValues->rec.value,
                                                    Marshal.PtrToStringAnsi((IntPtr)param->val_int64->enumValues->rec.key)));

                                    Param<long> result = new Param<long>(
                                        param,
                                        param->val_int64->min,
                                        param->val_int64->max,
                                        1,
                                        1,
                                        param->val_int64->defValue,
                                        valEnum,
                                        param->val_int64->step,
                                        param->val_int64->value);
                                    break;
                                }
                            case "float_t":
                                {
                                    Param<float> result = new Param<float>(
                                        param,
                                        param->val_flt->min,
                                        param->val_flt->max,
                                        1,
                                        1,
                                        param->val_flt->defValue,
                                        null,
                                        param->val_flt->step,
                                        param->val_flt->value);
                                    break;
                                }
                            case "double_t":
                                {
                                    Param<double> result = new Param<double>(
                                        param,
                                        param->val_dbl->min,
                                        param->val_dbl->max,
                                        1,
                                        1,
                                        param->val_dbl->defValue,
                                        null,
                                        param->val_dbl->step,
                                        param->val_dbl->value);
                                    break;
                                }
                            case "u32_arr_t":
                                {
                                    break;
                                }
                            case "u64_arr_t":
                                {
                                    break;
                                }
                            case "i32_arr_t":
                                {
                                    break;
                                }
                            case "i64_arr_t":
                                {
                                    break;
                                }
                            case "flt_array_t":
                                {
                                    break;
                                }
                            case "dbl_array_t":
                                {
                                    break;
                                }
                            case "string_t":
                                {
                                    Param<string> result = new Param<string>(
                                        param,
                                        "0",
                                        param->val_str->maxLen.ToString(),
                                        1,
                                        1,
                                        Marshal.PtrToStringAnsi((IntPtr)(param->val_str->defValue)),
                                        null,
                                        "",
                                        Marshal.PtrToStringAnsi((IntPtr)(param->val_str->value)));
                                    return result;
                                }
                            default:
                                {
                                    return null;
                                }
                        }

                    return null;

                }

                public bool SetParam(dynamic param)
                {
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
                        set_parameter((scanner_base_t*)_base, p);
                        return true;
                    }
                    return false;
                }

                public bool WriteParams(PROTOCOLS_TYPES protocol = PROTOCOLS_TYPES.SERVICE_PROTOKOL)
                {
                    switch (protocol)
                    {
                        case PROTOCOLS_TYPES.SERVICE_PROTOKOL:
                            {
                                // Establish connection to the RF627 device by Service Protocol.
                                byte result;
                                result = write_params_to_scanner(
                                            (scanner_base_t*)_base, PROTOCOLS_TYPES.SERVICE_PROTOKOL);

                                return result == 0 ? true : false;
                                break;
                            }
                    }
                    return false;
                }

            }
        }
    }
}
