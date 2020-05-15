#ifndef RF62X_TYPES_H
#define RF62X_TYPES_H


#include "platform_types.h"
#include <stddef.h>
#include <stdarg.h>


typedef struct{
    rfUint32 version;
    rfUint32 length;
    rfUint8 validated;
    rfUint8 reserved;
}config_options_t;

typedef struct
{
/*-------Общие параметры устройства-----------------------*/
    struct
    {
        rfUint16					device_id;			//Идентификатор типа сканера
        rfUint32					serial;				//Серийный номер сканера
        rfUint32					serial_of_pcb;		//Серийный номер электроники
        rfUint32					operating_time_h;	//Наработка сканера, часов
        rfUint8						operating_time_m;	//Наработка сканера, минут
        rfUint8						operating_time_s;	//Наработка сканера, секунд
        rfUint32					runtime_h;			//Время работы после запуска, часов
        rfUint8						runtime_m;	        //Время работы после запуска, минут
        rfUint8						runtime_s;	        //Время работы после запуска, секунд
        rfUint32					startup_counter;    //Количество запусков сканера
        rfUint32					firmware_ver;		//Версия прошивки
        rfUint32					hardware_ver;		//Версия аппаратного обеспечения
        rfUint32					customer_id;
        rfUint32					fpga_freq;		//Системная тактовая для PL - частота AXI в Гц
        rfUint32					base_z;
        rfUint32					range_z;
        rfUint32					range_x_start;
        rfUint32					range_x_end;
        rfUint16					pixels_divider;
        rfUint16					profiles_divider;
        rfUint32					fsbl_version;		//Версия загрузчика
        rfChar                      oem_device_name[16];
        rfUint8						reserved[76];
    }general;
/*-------Параметры установленной матрицы-------------------*/
    struct
    {
        rfChar						name[32];					//Имя матрицы - для отображения
        rfUint16					width;						//Количество пикселов по горизонтали
        rfUint16					height;						//Количество пикселов но вертикали
        rfUint32					pixel_clock;					//Пиксельная частота в Гц
        rfUint16					black_odd_lines;
        rfUint16					black_even_lines;
        rfUint32					frame_cycle_const_part;
        rfUint32					frame_cycle_per_line_part;
        rfUint8						frame_rate_or_exposure;		//Селектор по чем настраивать матрицу - по частоте кадров или экспозиции: 0 - по частоте, 1 - по экспозиции
        rfUint32					min_exposure;				//Минимальное время экспозиции в нс.
        rfUint8						image_flipping;				//Режим отражения изображения: 0 - без отражения, 1 - по X, 2 - по Y, 3 - и по X и по Y
        rfUint32					max_exposure;				//Максимальное время экспозиции, заданное при настройке сканера
        rfUint8						edr_point1_value;				//Значение напряжения (в условных единицах 0..63) в 1-й точке излома прямой накопления (стр.30-31 даташита CMV300)
        rfUint8						edr_point2_value;				//Значение напряжения (в условных единицах 0..63) во 2-й точке излома прямой накопления (стр.30-31 даташита CMV300)
        rfUint16					edr_point1_pos;				//Положение в 1/1000 точки относительно начала экспозиции, т.е. 0 - одновременно с началом экспозиции, 999 - сразу в конце
        rfUint16					edr_point2_pos;				//Положение в 1/1000 точки относительно начала экспозиции, т.е. 0 - одновременно с началом экспозиции, 999 - сразу в конце
        rfUint8						reserved[113];
        struct
        {
            rfUint16 addr;
            rfUint16 value;
        }init_regs[64];               //Структура с параметрами инициализации регистров матрицы
    }sensor;
/*-------Параметры сетевого подключения-------------------*/
    struct
    {
        rfUint8						mac[6];
        rfUint16					eip_vendor_id;
        rfUint16					eip_device_type;
        rfUint8						force_autoneg_time;			//Количество секунд, через которое сканер установит автосогласование принудительно в случае отсутствия связи по Ethernet
        rfUint8						reserved[31];
    }network;
/*-------Параметры управления лазером----------------------*/
    struct
    {
        rfUint16					wave_length;				//Длина волны в нм
        rfUint8						koeff1;					//Коээфициент крутизны регулирования отпределяется как Koeff1/128
        rfUint8						koeff2;
        rfUint32					min_value;				//Значение, при котором лазер зажигается
        rfUint32					max_value;				//Максимальное допустимое значение
        rfUint8						enable_mode_change;		//Разрешение изменения режима работы лазера: 0 - запрещено, 1 - разрешено
        rfUint8						reserved[31];
    }laser;
/*------------Параметры входных каналов--------------------*/
    struct
    {
        rfUint16					in1_min_delay;			//Минимальная задержка в нс
        rfUint32					in1_max_delay;			//Максимальная задержка в нс
        rfUint16					max_divider_in1;			//Максимальное значение делителя частоты кадров
        rfUint16					min_divider_in1;			//Минимальное значение делителя частоты кадров
        rfUint8						reserved[62];
    }inputs;
/*------------Параметры выходных каналов-------------------*/
    struct
    {
        rfUint16					out1_min_delay;
        rfUint32					out1_max_delay;
        rfUint16					out1_min_pulse_width;
        rfUint32					out1_max_pulse_width;
        rfUint16					out2_min_delay;
        rfUint32					out2_max_delay;
        rfUint16					out2_min_pulse_width;
        rfUint32					out2_max_pulse_width;
        rfUint8						reserved[32];
    }outputs;
    /*------------Параметры обработки профилей-----------------*/
    struct
    {
        rfUint32					max_dump_size;
        rfUint8						reserved[60];
    }profiles;
    /*------------Параметры протокола EthernetIP---------------*/
    struct
    {
        struct
        {
            rfUint16				vendor_iD;				// Attribute 1: Vendor ID - идентификационный номер производителя устройства
            rfUint16				device_type;				// Attribute 2: Device Type - тип устройства, который определяет его область использования
            rfUint16				product_code;			// Attribute 3: Product Code - идентифицирует номер конкретного продукта
            struct
            {	uint8_t					major_rev;			// Attribute 4: Revision	USINT Major
                rfUint8					minor_rev;			//							USINT Minor
            }revision;										// Структура, хранящая EIP-версию девайса
        }identity;

        struct
        {
            rfUint32				config_capability;		// Attribute 2: Данный атрибут описывает поддержку устройством дополнительных возможностей конфигурации сети
            struct
            {	uint16_t				path_size;			// Path size in 16 bit words (path_size * 16 bit)
                rfUint16				classId;			// Class ID of the linked object
                rfUint16				instance_number;		// Requested Instance Number of the linked object
                rfUint16				attribute_number;	// Requested Attribute Number of the linked object
            }phyLinkObject;									// Attribute 4: Этот атрибут идентифицирует объект, связанный с базовым физическим интерфейсом связи (Ethernet Link Object)
        }tcpInterface;

        rfUint8						intrf_type;				//Type of rfInterface: twisted pair, fiber, rfInternal, etc
        struct
        {	uint16_t					capability_bits;
            rfUint8						speed_dup_count;
            struct
            {
                rfUint16					speed;
                rfUint8						duplex;
            }speedDuplex[4];
        }intrfCapability;									//Path to physical link object

        rfUint8						reserved[44];
    }eip;
    /*-------Резерв--------------------------------------------*/
    rfUint8							reserved[167];
    /*---------------------------------------------------------*/
}rf627_old_factory_params_t;

typedef struct
{
    rfChar                        Tag[4];            //<! File header tag = "DTF+"
    rfUint16                    FormatVersion;     //<! Version of header format (1)
    struct
    {
        struct
        {
            rfUint8            Day;
            rfUint8            Month;
            rfUint16            Year;
        }date;
        struct
        {
            rfUint8            Hour;
            rfUint8            Minute;
            rfUint8            Second;
        }time;
    }timestamp;                                     //<! date and time of calibration
    rfUint16                    DevType;            //<! Device type (627)
    rfUint32                    SerialNumber;       //<! Serial Number of Scanner
    rfUint16					BaseZ;              //<! Z base, mm
    rfUint16					RangeZ;             //<! Z measurement range, mm
    rfUint16					RangeXStart;        //<! X start measurement range, mm
    rfUint16					RangeXEnd;          //<! X end measurement range, mm
    rfUint16					YSteps;             //<! Number of calibration steps
    rfUint16					StartPosition;      //<! Start position
    rfUint16					EndPosition;        //<! End position
    rfUint16					CutXLeft;           //<! Amount of pixels to cut from left
    rfUint16					CutXRight;          //<! Amount of pixels to cut from right
    rfUint8                     PlaneType;          //<! 0 - ZPlane, 1 - TrianglesXY
    rfUint8                     InvertZ;            //<! 0 - no invert, other - invert
    rfUint32					TriangleWidth;      //<! Triangle width, um
    rfUint32					TriangleHeight;     //<! Triangle height, um
    rfUint8                     AveragingSize;      //<! Number of pixels profiles for averaging
    rfUint32                    Exposure;           //<! Exposure time, ns (0 for Auto)
    rfInt16                     Temp;               //<! Temperature upon calibration, C/10
    rfDouble                      StepLength;         //<! Z Step Length
    rfUint32					FirmwareVer;		//<! Firmware Version
    rfUint32					HardwareVer;		//<! Hardware Version
    rfUint8                     Reserved[186];      //<!- Reserved
}DTF_header;

typedef struct
{
    rfUint8                    FormatVersion;     //<! Version of header format (1)
    rfUint16                    CRC;                //<!- CRC
    rfUint32                    SerialNumber;       //<! Serial Number of Scanner
    struct
    {
        struct
        {
            rfUint16            Year;
            rfUint8            Month;
            rfUint8            Day;
        }date;
        struct
        {
            rfUint8            Hour;
            rfUint8            Minute;
            rfUint8            Second;
        }time;
    }timestamp;                                     //<! date and time of calibration
    rfUint8                     Zero[242];          //<! Must be filled with zeroes
}TBL_header;

typedef struct
{
    struct
    {
        rfChar        name[64];
        rfUint8     save_log_to_spi;
        rfUint8		reserved[127];
    }general;

    struct
    {
        rfInt16		fpga_temp;
        rfUint8		params_changed;			//Параметры были изменены, но не сохранены: 1 - factory, 2 - user, 3 - factory & user
        rfInt16		sens00_temp;
        rfInt16		sens00_max;
        rfInt16		sens00_min;
        rfInt16		sens01_temp;
        rfInt16		sens01_max;
        rfInt16		sens01_min;
        rfInt16		sens10_temp;
        rfInt16		sens10_max;
        rfInt16		sens10_min;
        rfInt16		sens11_temp;
        rfInt16		sens11_max;
        rfInt16		sens11_min;
        rfUint8		reserved[55];
    }sysmon;

    struct
    {
        rfUint8		enable;
        rfUint16	tcp_port;
        rfUint8		reserved[32];
    }rf625compat;

    struct
    {
        rfUint8		dhs;
        rfUint8		gain_analog;
        rfUint8		gain_digital;
        rfUint32	exposure;
        rfUint32	max_exposure;
        rfUint32	frame_rate;
        rfUint32	max_frame_rate;
        rfUint8     exposure_hdr_mode;
        rfUint8     auto_exposure;
        rfUint8		column_edr_mode;
        rfUint8		column_exposure_div;
        rfUint8     column_exposure_max_div;
        rfUint8		reserved_1[59];
    }sensor;

    struct
    {
        rfUint8		enable;
        rfUint8		active;
        rfUint16	size;
        rfUint8		position_mode;
        rfUint16	manual_position;
        rfUint16	auto_position;
        rfUint16	required_profile_size;
        rfUint8		reserved[80];
    }roi;

    struct
    {
        rfUint16	speed;
        rfUint8		autonegotiation;
        rfUint8     ip_address[4];
        rfUint8     net_mask[4];
        rfUint8     gateway_ip[4];
        rfUint8     host_ip[4];
        rfUint16    stream_port;
        rfUint16    http_port;
        rfUint16    service_port;
    //    rfUint16    eip_broadcast_port;
    //    rfUint16    eip_port;
        rfUint8		reserved[68];
    }network;

    struct
    {
        rfUint8		enable;
        rfUint8		format;
        rfUint8		ack;
        rfUint8     include_intensivity;
        rfUint8		reserved[31];
    }stream;

    struct
    {
        rfUint32	brightness_threshold;
        rfUint8		filter_width;
        rfUint8		processing_mode;
        rfUint8		reduce_noise;
        rfUint32    frame_rate;
        rfUint8		median_filter_mode;
        rfUint8		bilateral_filter_mode;
        rfUint8     peak_select_mode;
        rfUint8     profile_flip;
        rfUint8		reserved[56];
    }image_processing;

    struct
    {
        rfUint8		enable;
        rfUint8		level_mode;
        rfUint16	level;
        rfUint8		reserved[32];
    }laser;

    struct
    {
        rfUint8                 preset_index;
        struct
        {
            rfUint16    params_mask;
            rfUint8		in1_enable;
            rfUint8		in1_mode;
            rfUint32	in1_delay;
            rfUint8		in1_decimation;
            rfUint8		in2_enable;
            rfUint8		in2_mode;
            rfUint8		in2_invert;
            rfUint8		in3_enable;
            rfUint8		in3_mode;
            rfUint8		reserved[12];
        }params[12];
        rfUint8                 reserved[32];
    }inputs;

    struct
    {
        rfUint8		out1_enable;
        rfUint8		out1_mode;
        rfUint32	out1_delay;
        rfUint32	out1_pulse_width;
        rfUint8		out1_invert;
        rfUint8		out2_enable;
        rfUint8		out2_mode;
        rfUint32	out2_delay;
        rfUint32	out2_pulse_width;
        rfUint8		out2_invert;
        rfUint8		reserved[32];
    }outputs;

    rfUint8                   reserved[283];
}rf627_old_user_params_t;

typedef struct
{
    rfUint8     data_type;
    rfUint8     flags;
    rfUint16    device_type;
    rfUint32    serial_number;
    rfUint64    system_time;

    rfUint8     proto_version_major;
    rfUint8     proto_version_minor;
    rfUint8     hardware_params_offset;
    rfUint8     data_offset;
    rfUint32    packet_count;
    rfUint32    measure_count;

    rfUint16    zmr;
    rfUint16    xemr;
    rfUint16    discrete_value;
    rfUint8     reserved_0[14];

    rfUint32    exposure_time;
    rfUint32    laser_value;
    rfUint32    step_count;
    rfUint8     dir;
    rfUint8     reserved_1[3];
}
rf627_old_profile_header_t;

typedef struct{
    struct{
        rfUint32 H;
        rfUint8  M;
        rfUint8  S;
    }Time;
    rfUint8  ModuleID;
    rfUint8  EventID;
    rfChar     String[128];
}log_record_t;

typedef enum
{
    DTY_PixelsNormal        = 0x10,
    DTY_ProfileNormal       = 0x11,
    DTY_PixelsInterpolated  = 0x12,
    DTY_ProfileInterpolated = 0x13
} rf627_old_data_type_t;

/*! Structure to store a point of profile
 */
typedef struct
{
    rfFloat x;
    rfFloat z;
}rf627_old_point2D_t;

/*! Structure to store a point of profile
 */
typedef struct
{
    rfFloat x;
    rfFloat y;
    rfFloat z;
}rf627_old_point3D_t;

/*! Structure to store a profile for rf627_old
 */
typedef struct
{
    rf627_old_profile_header_t header;
    union{
        struct{
            rfUint16* pixels;
            rfUint32 pixels_count;
        }pixels_format;
        struct{
            rf627_old_point2D_t* points;
            rfUint32 points_count;
        }profile_format;
    };
    rfUint8* intensity;
    rfUint32 intensity_count;
}rf627_old_profile2D_t;

/*! Structure to store a profile for rf627_old
 */
typedef struct
{
    rf627_old_profile_header_t header;
    union{
        struct{
            rfUint16* pixels;
            rfUint32 pixels_count;
        }pixels_format;
        struct{
            rf627_old_point3D_t* points;
            rfUint32 points_count;
        }profile_format;
    };
    rfUint8* intensity;
    rfUint32 intensity_count;
}rf627_old_profile3D_t;

/*! Structure to store a profile for rf627_old
 */
typedef struct
{
    rf627_old_profile_header_t header;
    union{
        struct{
            rfUint16* pixels;
            rfUint32 pixels_count;
        }pixels_format;
        struct{
            rf627_old_point2D_t* points;
            rfUint32 points_count;
        }profile_format;
    };
    rfUint8* intensity;
    rfUint32 intensity_count;
}rf627_smart_profile2D_t;

/*! Structure to store a profile for rf627_old
 */
typedef struct
{
    rf627_old_profile_header_t header;
    union{
        struct{
            rfUint16* pixels;
            rfUint32 pixels_count;
        }pixels_format;
        struct{
            rf627_old_point3D_t* points;
            rfUint32 points_count;
        }profile_format;
    };
    rfUint8* intensity;
    rfUint32 intensity_count;
}rf627_smart_profile3D_t;


typedef struct
{
    rfChar* device_name;
    rfUint32 serial_number;
    rfUint8 ip_address[4];
    rfUint8 mac_address[6];
    rfUint16 profile_port;
    rfUint16 service_port;
    rfUint32 firmware_version;
    rfUint32 hardware_version;
    rfUint32 z_begin;
    rfUint32 z_range;
    rfUint32 x_begin;
    rfUint32 x_end;
}rf627_old_hello_info_by_service_protocol;

//Типы значений параметров
typedef enum
{
    PVT_UNKN				= 0,
    PVT_UINT,
    PVT_UINT64,
    PVT_INT,
    PVT_INT64,
    PVT_FLOAT,
    PVT_DOUBLE,
    PVT_ARRAY_UINT32,
    PVT_ARRAY_UINT64,
    PVT_ARRAY_INT32,
    PVT_ARRAY_INT64,
    PVT_ARRAY_FLT,
    PVT_ARRAY_DBL,
    PVT_STRING
}paramValueType_t;

//Поддерживаемый доступ к параметру
typedef enum
{
    PAT_UNKN				= 0,
    PAT_READ_ONLY,
    PAT_WRITE,
    PAT_LOCKED,
}paramAccessType_t;

//Поддерживаемый доступ к модулю
typedef enum
{
    MAT_UNKN				= 0,
    MAT_FACTORY_ONLY,
    MAT_USER,
}moduleAccessType_t;



typedef enum {
    FACT_GENERAL_PROTOCOLREV = 0,
    FACT_GENERAL_DEVICETYPE,
    FACT_GENERAL_SERIAL,
    FACT_GENERAL_PCBSERIAL,
    FACT_GENERAL_LIFETIME,
    FACT_GENERAL_WORKTIME,
    FACT_GENERAL_STARTSCOUNT,
    FACT_GENERAL_FIRMWAREREV,
    FACT_GENERAL_HARDWAREREV,
    FACT_GENERAL_FSBLREV,
    FACT_GENERAL_CUSTOMERID,
    FACT_GENERAL_FPGAFREQ,
    FACT_GENERAL_SMR,
    FACT_GENERAL_MR,
    FACT_GENERAL_XSMR,
    FACT_GENERAL_XEMR,
    FACT_GENERAL_PIXDIVIDER,
    FACT_GENERAL_PROFDIVIDER,
    FACT_GENERAL_OEMDEVNAME,
    FACT_GENERAL_AUTHSTATUS,
    FACT_SENSOR_NAME,
    FACT_SENSOR_WIDTH,
    FACT_SENSOR_HEIGHT,
    FACT_SENSOR_PIXFREQ,
    FACT_SENSOR_FRMCONSTPART,
    FACT_SENSOR_FRMPERLINEPART,
    FACT_SENSOR_FPSOREXP,
    FACT_SENSOR_MINEXPOSURE,
    FACT_SENSOR_MAXEXPOSURE,
    FACT_SENSOR_IMGFLIP,
    FACT_NETWORK_MACADDR,
    FACT_NETWORK_FORCEAUTONEGTIME,
    FACT_NETWORK_WEBSOCKSERVICEPORT,
    FACT_NETWORK_WEBSOCKDATAPORT,
    FACT_NETWORK_WEBSOCKMATHPORT,
    FACT_LASER_WAVELENGTH,
    FACT_LASER_KOEFF1,
    FACT_LASER_KOEFF2,
    FACT_LASER_MINVALUE,
    FACT_LASER_MAXVALUE,
    FACT_PROFILES_MAXDUMPSIZE,
    FACT_EIP_IDENTITY_VENDORID,
    FACT_EIP_IDENTITY_DEVICETYPE,
    FACT_EIP_IDENTITY_PRODUCTCODE,
    FACT_EIP_IDENTITY_REV,
    FACT_EIP_TCPINTRF_CAPABILITY,
    FACT_EIP_TCPINTRF_PHY_PATHSIZE,
    FACT_EIP_TCPINTRF_PHY_CLASSID,
    FACT_EIP_TCPINTRF_PHY_INSTNUMBER,
    FACT_EIP_TCPINTRF_PHY_ATTRNUMBER,
    FACT_EIP_INTRFTYPE,
    FACT_EIP_INTRFCAPABILITY_BITS,
    FACT_EIP_INTRFCAPABILITY_SPEEDDUPCOUNT,
    FACT_EIP_INTRFCAPABILITY_SPEEDDUPLEX_SPEED,
    FACT_EIP_INTRFCAPABILITY_SPEEDDUPLEX_DUPLEX,
    FACT_SENSOR_ANALOGGAIN,
    FACT_SENSOR_DIGITALGAIN,
    FACT_SENSOR_BLACKODD,
    FACT_SENSOR_BLACKEVEN,
    FACT_SENSOR_HDRPIECEWISEDIV1,
    FACT_SENSOR_HDRPIECEWISEDIV2,
    FACT_SENSOR_INITREGS,

    USER_GENERAL_DEVICESTATE,
    USER_GENERAL_DEVICENAME,
    USER_GENERAL_SAVELOG,
    USER_SYSMON_FPGATEMP,
    USER_SYSMON_PARAMSCHANGED,
    USER_SYSMON_TEMPSENS00,
    USER_SYSMON_TEMPSENS00MAX,
    USER_SYSMON_TEMPSENS00MIN,
    USER_SYSMON_TEMPSENS01,
    USER_SYSMON_TEMPSENS01MAX,
    USER_SYSMON_TEMPSENS01MIN,
    USER_SYSMON_TEMPSENS10,
    USER_SYSMON_TEMPSENS10MAX,
    USER_SYSMON_TEMPSENS10MIN,
    USER_SYSMON_TEMPSENS11,
    USER_SYSMON_TEMPSENS11MAX,
    USER_SYSMON_TEMPSENS11MIN,
    USER_SENSOR_SYNCSOURCE,
    USER_SENSOR_FRAMERATE,
    USER_SENSOR_MAXFRAMERATE,
    USER_SENSOR_EXPOSURECONTROL,
    USER_SENSOR_EXPOSURE1,
    USER_SENSOR_EXPOSURE2,
    USER_SENSOR_EXPOSURE3,
    USER_SENSOR_EXPOSURE4,
    USER_SENSOR_MAXEXPOSURE,
    USER_ROI_ENABLED,
    USER_ROI_ACTIVE,
    USER_ROI_POSMODE,
    USER_ROI_POS,
    USER_ROI_MAXPOS,
    USER_ROI_REQPROFSIZE,
    USER_NETWORK_SPEED,
    USER_NETWORK_REQUIREDSPEED,
    USER_NETWORK_AUTONEG,
    USER_NETWORK_IP,
    USER_NETWORK_MASK,
    USER_NETWORK_GATEWAY,
    USER_NETWORK_HOSTIP,
    USER_NETWORK_HOSTPORT,
    USER_NETWORK_WEBPORT,
    USER_NETWORK_SERVICEPORT,
    USER_STREAMS_UDPENABLED,
    USER_STREAMS_FORMAT,
    USER_STREAMS_INCLUDEINTENSITY,
    USER_PROCESSING_THRESHOLD,
    USER_PROCESSING_PROFPERSEC,
    USER_PROCESSING_MEDIANMODE,
    USER_PROCESSING_BILATERALMODE,
    USER_PROCESSING_PEAKMODE,
    USER_PROCESSING_FLIP,
    USER_LASER_ENABLED,
    USER_LASER_VALUE,
    USER_TRIGGER_SYNC_SOURCE,
    USER_TRIGGER_SYNC_STRICTENABLED,
    USER_TRIGGER_SYNC_DIVIDER,
    USER_TRIGGER_SYNC_DELAY,
    USER_TRIGGER_COUNTER_TYPE,
    USER_TRIGGER_COUNTER_MAXVALUEENABLED,
    USER_TRIGGER_COUNTER_MAXVALUE,
    USER_TRIGGER_COUNTER_RESETTIMERENABLED,
    USER_TRIGGER_COUNTER_RESETTIMERVALUE,
    USER_TRIGGER_COUNTER_VALUE,
    USER_INPUT1_ENABLED,
    USER_INPUT1_MODE,
    USER_INPUT2_ENABLED,
    USER_INPUT2_MODE,
    USER_INPUT3_ENABLED,
    USER_INPUT3_MODE,
    USER_INPUT1_SAMPLES,
    USER_INPUT2_SAMPLES,
    USER_INPUT3_SAMPLES,
    USER_OUTPUT1_ENABLED,
    USER_OUTPUT1_MODE,
    USER_OUTPUT1_PULSEWIDTH,
    USER_OUTPUT2_ENABLED,
    USER_OUTPUT2_MODE,
    USER_OUTPUT2_PULSEWIDTH,
    USER_DUMP_ENABLED,
    USER_DUMP_CAPACITY,
    USER_DUMP_SIZE,
    USER_DUMP_TIMESTAMP,
    USER_DUMP_VIEW3D_MOTIONTYPE,
    USER_DUMP_VIEW3D_YSOURCE,
    USER_DUMP_VIEW3D_YSTEP,
    USER_DUMP_VIEW3D_PAINTMODE,
    USER_DUMP_VIEW3D_DECIMATION,
    USER_EIP_TCPPORT,
    USER_EIP_UDPPORT,
    USER_EIP_TCP_TTL,
    USER_EIP_TCP_TIMEOUT,
    USER_EIP_TCP_MULTICAST_ALLOC,
    USER_EIP_TCP_MULTICAST_NUM,
    USER_EIP_TCP_MULTICAST_ADDR,
    USER_COMPATIBILITY_RF625ENABLED,
    USER_COMPATIBILITY_RF625TCPPORT,
    USER_SENSOR_DOUBLESPEEDENABLED,
    USER_SENSOR_EDRTYPE,
    USER_SENSOR_EDRCOLUMNDIVIDER,
    USER_STREAMS_POINTSCOUNT,
    USER_ROI_SIZE

}parameter_name_keys_t;

const static rfChar* parameter_names[]	=
{
    "fact_general_protocolRev",
    "fact_general_deviceType",
    "fact_general_serial",
    "fact_general_pcbSerial",
    "fact_general_lifeTime",
    "fact_general_workTime",
    "fact_general_startsCount",
    "fact_general_firmWareRev",
    "fact_general_hardWareRev",
    "fact_general_fsblRev",
    "fact_general_customerID",
    "fact_general_fpgaFreq",
    "fact_general_smr",
    "fact_general_mr",
    "fact_general_xsmr",
    "fact_general_xemr",
    "fact_general_pixDivider",
    "fact_general_profDivider",
    "fact_general_oemDevName",
    "fact_general_authStatus",
    "fact_sensor_name",
    "fact_sensor_width",
    "fact_sensor_height",
    "fact_sensor_pixFreq",
    "fact_sensor_frmConstPart",
    "fact_sensor_frmPerLinePart",
    "fact_sensor_fpsOrExp",
    "fact_sensor_minExposure",
    "fact_sensor_maxExposure",
    "fact_sensor_imgFlip",
    "fact_network_macAddr",
    "fact_network_forceAutoNegTime",
    "fact_network_webSockServicePort",
    "fact_network_webSockDataPort",
    "fact_network_webSockMathPort",
    "fact_laser_waveLength",
    "fact_laser_koeff1",
    "fact_laser_koeff2",
    "fact_laser_minValue",
    "fact_laser_maxValue",
    "fact_profiles_maxDumpSize",
    "fact_eip_identity_vendorID",
    "fact_eip_identity_deviceType",
    "fact_eip_identity_productCode",
    "fact_eip_identity_rev",
    "fact_eip_tcpIntrf_capability",
    "fact_eip_tcpIntrf_phy_pathSize",
    "fact_eip_tcpIntrf_phy_classId",
    "fact_eip_tcpIntrf_phy_instNumber",
    "fact_eip_tcpIntrf_phy_attrNumber",
    "fact_eip_intrfType",
    "fact_eip_intrfCapability_bits",
    "fact_eip_intrfCapability_speedDupCount",
    "fact_eip_intrfCapability_speedDuplex_speed",
    "fact_eip_intrfCapability_speedDuplex_duplex",
    "fact_sensor_analogGain",
    "fact_sensor_digitalGain",
    "fact_sensor_blackOdd",
    "fact_sensor_blackEven",
    "fact_sensor_hdrPiecewiseDiv1",
    "fact_sensor_hdrPiecewiseDiv2",
    "fact_sensor_initRegs",

    "user_general_deviceState",
    "user_general_deviceName",
    "user_general_saveLog",
    "user_sysMon_fpgaTemp",
    "user_sysMon_paramsChanged",
    "user_sysMon_tempSens00",
    "user_sysMon_tempSens00Max",
    "user_sysMon_tempSens00Min",
    "user_sysMon_tempSens01",
    "user_sysMon_tempSens01Max",
    "user_sysMon_tempSens01Min",
    "user_sysMon_tempSens10",
    "user_sysMon_tempSens10Max",
    "user_sysMon_tempSens10Min",
    "user_sysMon_tempSens11",
    "user_sysMon_tempSens11Max",
    "user_sysMon_tempSens11Min",
    "user_sensor_syncSource",
    "user_sensor_framerate",
    "user_sensor_maxFramerate",
    "user_sensor_exposureControl",
    "user_sensor_exposure1",
    "user_sensor_exposure2",
    "user_sensor_exposure3",
    "user_sensor_exposure4",
    "user_sensor_maxExposure",
    "user_roi_enabled",
    "user_roi_active",
    "user_roi_posMode",
    "user_roi_pos",
    "user_roi_maxPos",
    "user_roi_reqProfSize",
    "user_network_speed",
    "user_network_requiredSpeed",
    "user_network_autoNeg",
    "user_network_ip",
    "user_network_mask",
    "user_network_gateway",
    "user_network_hostIP",
    "user_network_hostPort",
    "user_network_webPort",
    "user_network_servicePort",
    "user_streams_udpEnabled",
    "user_streams_format",
    "user_streams_includeIntensity",
    "user_processing_threshold",
    "user_processing_profPerSec",
    "user_processing_medianMode",
    "user_processing_bilateralMode",
    "user_processing_peakMode",
    "user_processing_flip",
    "user_laser_enabled",
    "user_laser_value",
    "user_trigger_sync_source",
    "user_trigger_sync_strictEnabled",
    "user_trigger_sync_divider",
    "user_trigger_sync_delay",
    "user_trigger_counter_type",
    "user_trigger_counter_maxValueEnabled",
    "user_trigger_counter_maxValue",
    "user_trigger_counter_resetTimerEnabled",
    "user_trigger_counter_resetTimerValue",
    "user_trigger_counter_value",
    "user_input1_enabled",
    "user_input1_mode",
    "user_input2_enabled",
    "user_input2_mode",
    "user_input3_enabled",
    "user_input3_mode",
    "user_input1_samples",
    "user_input2_samples",
    "user_input3_samples",
    "user_output1_enabled",
    "user_output1_mode",
    "user_output1_pulseWidth",
    "user_output2_enabled",
    "user_output2_mode",
    "user_output2_pulseWidth",
    "user_dump_enabled",
    "user_dump_capacity",
    "user_dump_size",
    "user_dump_timeStamp",
    "user_dump_view3d_motionType",
    "user_dump_view3d_ySource",
    "user_dump_view3d_yStep",
    "user_dump_view3d_paintMode",
    "user_dump_view3d_decimation",
    "user_eip_tcpPort",
    "user_eip_udpPort",
    "user_eip_tcp_ttl",
    "user_eip_tcp_timeout",
    "user_eip_tcp_multiCast_alloc",
    "user_eip_tcp_multiCast_num",
    "user_eip_tcp_multiCast_addr",
    "user_compatibility_rf625Enabled",
    "user_compatibility_rf625TCPPort",
    "user_sensor_doubleSpeedEnabled",
    "user_sensor_edrType",
    "user_sensor_edrColumnDivider",
    "user_streams_pointsCount",
    "user_roi_size"

};

const static rfChar* parameter_value_types[]	=
{
    "unkn_t",
    "uint32_t",
    "uint64_t",
    "int32_t",
    "int64_t",
    "float_t",
    "double_t",
    "u32_arr_t",
    "u64_arr_t",
    "i32_arr_t",
    "i64_arr_t",
    "flt_array_t",
    "dbl_array_t",
    "string_t"
};
const static rfChar*	patKey[]	=
{
    "unkn",
    "read_only",
    "write",
    "locked",
};
const static rfChar*	matKey[]	=
{
    "unkn",
    "factory_only",
    "user",
};

//Структура для перечислений - сопоставляет значение параметра и его текстовый ключ
typedef struct
{
    rfInt32				value;
    rfChar*				key;
}enumRec_t;

typedef struct
{
    rfInt32				recCount;
    enumRec_t			rec[];
}valuesEnum_t;

typedef struct
{
    const rfChar*			name;
    const rfChar*         type;
    const rfChar*         access;
    rfUint16			index;
    rfUint32			offset;
    rfUint32			size;
    const rfChar*			units;
}value_base_t;

typedef struct value_uint32_t
{
    rfUint32			min;
    rfUint32			max;
    rfUint32			step;
    rfUint32			defValue;
    valuesEnum_t*		enumValues;
    rfUint32			value;

}value_uint32_t;

typedef struct value_uint64_t
{
    rfUint64			min;
    rfUint64			max;
    rfUint64			step;
    rfUint64			defValue;
    valuesEnum_t*		enumValues;
    rfUint64			value;
}value_uint64_t;

typedef struct value_int32_t
{
    rfInt32				min;
    rfInt32				max;
    rfInt32				step;
    rfInt32				defValue;
    valuesEnum_t*		enumValues;
    rfInt32				value;
}value_int32_t;

typedef struct value_int64_t
{
    rfInt64				min;
    rfInt64				max;
    rfInt64				step;
    rfInt64				defValue;
    valuesEnum_t*		enumValues;
    rfInt64				value;
}value_int64_t;

typedef struct value_flt_t
{
    rfFloat				min;
    rfFloat				max;
    rfFloat				step;
    rfFloat				defValue;
    rfFloat				value;
}value_flt_t;

typedef struct value_dbl_t
{
    rfDouble				min;
    rfDouble				max;
    rfDouble				step;
    rfDouble				defValue;
    rfDouble				value;
}value_dbl_t;

typedef struct array_uint32_t
{
    rfUint32			min;
    rfUint32			max;
    rfUint32			step;
    rfUint32			maxCount;
    rfUint32			defCount;
    rfUint32*			defValue;
    rfUint32			count;
    rfUint32*			value;
}array_uint32_t;

typedef struct array_uint64_t
{
    rfUint64			min;
    rfUint64			max;
    rfUint64			step;
    rfUint32			maxCount;
    rfUint32			defCount;
    rfUint64*			defValue;
    rfUint32			count;
    rfUint64*			value;
}array_uint64_t;

typedef struct array_int32_t
{
    rfInt32				min;
    rfInt32				max;
    rfInt32				step;
    rfUint32			maxCount;
    rfUint32			defCount;
    rfInt32*			defValue;
    rfUint32			count;
    rfInt32*			value;
}array_int32_t;

typedef struct array_int64_t
{
    rfInt64				min;
    rfInt64				max;
    rfInt64				step;
    rfUint32			maxCount;
    rfUint32			defCount;
    rfInt64*			defValue;
    rfUint32			count;
    rfInt64*			value;
}array_int64_t;

typedef struct array_flt_t
{
    rfFloat				min;
    rfFloat				max;
    rfFloat				step;
    rfUint32			maxCount;
    rfUint32			defCount;
    rfFloat*			defValue;
    rfUint32			count;
    rfFloat*			value;
}array_flt_t;

typedef struct array_dbl_t
{
    rfDouble				min;
    rfDouble				max;
    rfDouble				step;
    rfUint32			maxCount;
    rfUint32			defCount;
    rfDouble*				defValue;
    rfUint32			count;
    rfDouble*				value;
}array_dbl_t;

typedef struct value_str_t
{
    rfUint16			maxLen;
    rfChar*				defValue;
    rfChar*				value;
}value_str_t;


typedef struct
{
    value_base_t			base;
    union{
        void*				rawData;
        value_uint32_t*		val_uint32;
        value_uint64_t*		val_uint64;
        value_int32_t*		val_int32;
        value_int64_t*		val_int64;
        value_flt_t*		val_flt;
        value_dbl_t*		val_dbl;
        array_uint32_t*		arr_uint32;
        array_uint64_t*		arr_uint64;
        array_int32_t*		arr_int32;
        array_int64_t*		arr_int64;
        array_flt_t*		arr_flt;
        array_dbl_t*		arr_dbl;
        value_str_t*		val_str;
    };
}parameter_t;


typedef struct
{
    const rfChar* name;
    va_list arg_list;
}command_t;






typedef enum {
    kRF627_OLD = 1,
    kRF627_SMART = 2
}scanner_types_t;

typedef enum {
    kSERVICE = 1,
    kETHERNET_IP = 2,
    kMODBUS_TCP = 3,
}protocol_types_t;

typedef enum {
    kSTEP = 1,
    kMEASURE = 2,
    kPACKET = 3,
}count_types_t;

/*! Structure to store a profile
 */
typedef struct
{
    scanner_types_t type;
    union{
        rf627_old_profile2D_t* rf627_profile2D;
        rf627_smart_profile2D_t* rf627smart_profile2D;
    };
}rf627_profile2D_t;

/*! Structure to store a profile
 */
typedef struct
{
    scanner_types_t type;
    union{
        rf627_old_profile3D_t* rf627_profile3D;
        rf627_smart_profile3D_t* rf627smart_profile3D;
    };
}rf627_profile3D_t;

/*! Structure of hello info about scanner
 */
typedef struct
{
    scanner_types_t scanner_type;
    protocol_types_t protocol_type;
    union{
        union{
            rf627_old_hello_info_by_service_protocol* hello_info_service_protocol;
        }rf627old;
        union{
            rf627_old_hello_info_by_service_protocol* hello_info_service_protocol;
        }rf627smart;
    };
}hello_information;

#endif // RF62X_TYPES_H
