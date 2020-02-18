#ifndef RF627_TYPES_H
#define RF627_TYPES_H


#include "platform_types.h"
#include "rf627_protocol.h"
#include <stddef.h>


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
        rfUint16					DeviceID;			//Идентификатор типа сканера
        rfUint32					Serial;				//Серийный номер сканера
        rfUint32					SerialOfPCB;		//Серийный номер электроники
        rfUint32					OperatingTime_H;	//Наработка сканера, часов
        rfUint8						OperatingTime_M;	//Наработка сканера, минут
        rfUint8						OperatingTime_S;	//Наработка сканера, секунд
        rfUint32					RunTime_H;			//Время работы после запуска, часов
        rfUint8						RunTime_M;	        //Время работы после запуска, минут
        rfUint8						RunTime_S;	        //Время работы после запуска, секунд
        rfUint32					StartUp_Counter;    //Количество запусков сканера
        rfUint32					FirmWareVer;		//Версия прошивки
        rfUint32					HardWareVer;		//Версия аппаратного обеспечения
        rfUint32					CustomerID;
        rfUint32					PL_SystemClk;		//Системная тактовая для PL - частота AXI в Гц
        rfUint32					BaseZ;
        rfUint32					RangeZ;
        rfUint32					RangeXStart;
        rfUint32					RangeXEnd;
        rfUint16					PixelsDivider;
        rfUint16					ProfilesDivider;
        rfUint32					FSBL_Version;		//Версия загрузчика
        rfChar                        oemDeviceName[16];
        rfUint8						Reserved[76];
    }General;
/*-------Параметры установленной матрицы-------------------*/
    struct
    {
        rfChar						Name[32];					//Имя матрицы - для отображения
        rfUint16					Width;						//Количество пикселов по горизонтали
        rfUint16					Height;						//Количество пикселов но вертикали
        rfUint32					PixelClock;					//Пиксельная частота в Гц
        rfUint16					Black_OddLines;
        rfUint16					Black_EvenLines;
        rfUint32					FrameCycle_ConstPart;
        rfUint32					FrameCycle_PerLinePart;
        rfUint8						FrameRateORExposure;		//Селектор по чем настраивать матрицу - по частоте кадров или экспозиции: 0 - по частоте, 1 - по экспозиции
        rfUint32					MinExposure;				//Минимальное время экспозиции в нс.
        rfUint8						ImageFlipping;				//Режим отражения изображения: 0 - без отражения, 1 - по X, 2 - по Y, 3 - и по X и по Y
        rfUint32					MaxExposure;				//Максимальное время экспозиции, заданное при настройке сканера
        rfUint8						edrPoint1Value;				//Значение напряжения (в условных единицах 0..63) в 1-й точке излома прямой накопления (стр.30-31 даташита CMV300)
        rfUint8						edrPoint2Value;				//Значение напряжения (в условных единицах 0..63) во 2-й точке излома прямой накопления (стр.30-31 даташита CMV300)
        rfUint16					edrPoint1Pos;				//Положение в 1/1000 точки относительно начала экспозиции, т.е. 0 - одновременно с началом экспозиции, 999 - сразу в конце
        rfUint16					edrPoint2Pos;				//Положение в 1/1000 точки относительно начала экспозиции, т.е. 0 - одновременно с началом экспозиции, 999 - сразу в конце
        rfUint8						Reserved[113];
        struct
        {
            rfUint16 Addr;
            rfUint16 Value;
        }                           InitRegs[64];               //Структура с параметрами инициализации регистров матрицы
    }Sensor;
/*-------Параметры сетевого подключения-------------------*/
    struct
    {
        rfUint8						MAC[6];
        rfUint16					EIP_VendorID;
        rfUint16					EIP_DeviceType;
        rfUint8						forceAutoNegTime;			//Количество секунд, через которое сканер установит автосогласование принудительно в случае отсутствия связи по Ethernet
        rfUint8						Reserved[31];
    }Network;
/*-------Параметры управления лазером----------------------*/
    struct
    {
        rfUint16					Wavelength;				//Длина волны в нм
        rfUint8						Koeff1;					//Коээфициент крутизны регулирования отпределяется как Koeff1/128
        rfUint8						Koeff2;
        rfUint32					MinValue;				//Значение, при котором лазер зажигается
        rfUint32					MaxValue;				//Максимальное допустимое значение
        rfUint8						EnableModeChange;		//Разрешение изменения режима работы лазера: 0 - запрещено, 1 - разрешено
        rfUint8						Reserved[31];
    }Laser;
/*------------Параметры входных каналов--------------------*/
    struct
    {
        rfUint16					In1_MinDelay;			//Минимальная задержка в нс
        rfUint32					In1_MaxDelay;			//Максимальная задержка в нс
        rfUint16					MaxDividerIn1;			//Максимальное значение делителя частоты кадров
        rfUint16					MinDividerIn1;			//Минимальное значение делителя частоты кадров
        rfUint8						Reserved[62];
    }Inputs;
/*------------Параметры выходных каналов-------------------*/
    struct
    {
        rfUint16					Out1_MinDelay;
        rfUint32					Out1_MaxDelay;
        rfUint16					Out1_MinPulseWidth;
        rfUint32					Out1_MaxPulseWidth;
        rfUint16					Out2_MinDelay;
        rfUint32					Out2_MaxDelay;
        rfUint16					Out2_MinPulseWidth;
        rfUint32					Out2_MaxPulseWidth;
        rfUint8						Reserved[32];
    }Outputs;
    /*------------Параметры обработки профилей-----------------*/
        struct
        {
            rfUint32					maxDumpSize;
            rfUint8						Reserved[60];
        }Profiles;
    /*------------Параметры протокола EthernetIP---------------*/
        struct
        {
            struct
            {
                rfUint16				vendorID;				// Attribute 1: Vendor ID - идентификационный номер производителя устройства
                rfUint16				deviceType;				// Attribute 2: Device Type - тип устройства, который определяет его область использования
                rfUint16				productCode;			// Attribute 3: Product Code - идентифицирует номер конкретного продукта
                struct
                {	uint8_t					majorRev;			// Attribute 4: Revision	USINT Major
                    rfUint8					minorRev;			//							USINT Minor
                }revision;										// Структура, хранящая EIP-версию девайса
            }identity;

            struct
            {
                rfUint32				configCapability;		// Attribute 2: Данный атрибут описывает поддержку устройством дополнительных возможностей конфигурации сети
                struct
                {	uint16_t				pathSize;			// Path size in 16 bit words (path_size * 16 bit)
                    rfUint16				classId;			// Class ID of the linked object
                    rfUint16				instanceNumber;		// Requested Instance Number of the linked object
                    rfUint16				attributeNumber;	// Requested Attribute Number of the linked object
                }phyLinkObject;									// Attribute 4: Этот атрибут идентифицирует объект, связанный с базовым физическим интерфейсом связи (Ethernet Link Object)
            }tcpInterface;

            rfUint8						intrfType;				//Type of rfInterface: twisted pair, fiber, rfInternal, etc
            struct
            {	uint16_t					capabilityBits;
                rfUint8						speedDupCount;
                struct
                {
                    rfUint16					speed;
                    rfUint8						duplex;
                }speedDuplex[4];
            }intrfCapability;									//Path to physical link object

            rfUint8						Reserved[44];
        }eip;
    /*-------Резерв--------------------------------------------*/
        rfUint8							Reserved[167];
    /*---------------------------------------------------------*/
}factory_params_t;

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
    rfChar        name[64];
    rfUint8     save_log_to_spi;
    rfUint8		reserved[127];
}
general_params_t;

typedef struct
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
}sysmon_params_t;

typedef struct
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
}sensor_params_t;

typedef struct
{
    rfUint8		enable;
    rfUint16	tcp_port;
    rfUint8		reserved[32];
}rf625compat_params_t;

typedef struct
{
    rfUint8		enable;
    rfUint8		active;
    rfUint16	window_height;
    rfUint8		position_mode;
    rfUint16	window_top;
    rfUint16	current_window_top;
    rfUint16	profile_size;
    rfUint8		reserved[80];
}roi_params_t;

typedef struct
{
    rfUint16	speed;
    rfUint8		autonegotiation;
    rfUint32    ip_address;
    rfUint32    net_mask;
    rfUint32    gateway_ip;
    rfUint32    host_ip;
    rfUint16    stream_port;
    rfUint16    http_port;
    rfUint16    service_port;
//    rfUint16    eip_broadcast_port;
//    rfUint16    eip_port;
    rfUint8		reserved[68];
}network_params_t;

typedef struct
{
    rfUint8		enable;
    rfUint8		format;
    rfUint8		ack;
    rfUint8     include_intensivity;
    rfUint8		reserved[31];
}stream_params_t;

typedef struct
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
}image_processing_params_t;

typedef struct
{
    rfUint8		enable;
    rfUint8		auto_level;
    rfUint16	level;
    rfUint8		reserved[32];
}laser_params_t;

typedef struct
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
}inputs_preset_t;

typedef struct
{
    rfUint8                 preset_index;
    inputs_preset_t   params[12];
    rfUint8                 reserved[32];
}inputs_params_t;

typedef struct
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
}outputs_params_t;

typedef struct
{
    general_params_t          general;
    sysmon_params_t           sysmon;
    rf625compat_params_t      rf625compat;
    sensor_params_t           sensor;
    roi_params_t              roi;
    network_params_t          network;
    stream_params_t           stream;
    image_processing_params_t image_processing;
    laser_params_t            laser;
    inputs_params_t           inputs;
    outputs_params_t          outputs;
    rfUint8                   reserved[283];
}user_params_t;

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
}rf627_old_point_t;

/*! Structure to store a profile for rf627_old
 */
typedef struct
{
    rf627_old_stream_msg_t header;
    union{
        struct{
            rfUint16* pixels;
            rfUint32 pixels_count;
        }pixels_format;
        struct{
            rf627_old_point_t* points;
            rfUint32 points_count;
        }profile_format;
    };
    rfUint8* intensity;
    rfUint32 intensity_count;
}rf627_old_profile_t;


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
    PAT_RESTRICTED,
}paramAccessType_t;

//Поддерживаемый доступ к модулю
typedef enum
{
    MAT_UNKN				= 0,
    MAT_FACTORY_ONLY,
    MAT_USER,
}moduleAccessType_t;



typedef enum {
    USER_GENERAL_DEVICE_NAME = 0,
    USER_GENERAL_SAVE_LOG,
    USER_SYSMON_FPGA_TEMP,
    USER_SYSMON_PARAMS_CHANGED,
    USER_SYSMON_TEMP_SENS_00,
    USER_SYSMON_TEMP_SENS_00_MAX,
    USER_SYSMON_TEMP_SENS_00_MIN,
    USER_SYSMON_TEMP_SENS_01,
    USER_SYSMON_TEMP_SENS_01_MAX,
    USER_SYSMON_TEMP_SENS_01_MIN,
    USER_SYSMON_TEMP_SENS_10,
    USER_SYSMON_TEMP_SENS_10_MAX,
    USER_SYSMON_TEMP_SENS_10_MIN,
    USER_SYSMON_TEMP_SENS_11,
    USER_SYSMON_TEMP_SENS_11_MAX,
    USER_SYSMON_TEMP_SENS_11_MIN,
    USER_SENSOR_EXPOSURE,
    USER_SENSOR_MAX_EXPOSURE,
    USER_SENSOR_AUTO_EXPOSURE_ENABLED,
    USER_SENSOR_FRAME_RATE,
    USER_SENSOR_MAX_FRAME_RATE,
    USER_ROI_ENABLED,
    USER_ROI_ACTIVE,
    USER_ROI_POS_MODE,
    USER_ROI_POS,
    USER_ROI_MAX_POS,
    USER_ROI_REQ_PROF_SIZE,
    USER_NETWORK_SPEED,
    USER_NETWORK_AUTO_NEG,
    USER_NETWORK_IP,
    USER_NETWORK_MASK,
    USER_NETWORK_GATEWAY,
    USER_NETWORK_HOST_IP,
    USER_NETWORK_HOST_PORT,
    USER_NETWORK_WEB_PORT,
    USER_NETWORK_SERVICE_PORT,
    USER_STREAMS_UDP_ENABLE,
    USER_STREAMS_FORMAT,
    USER_STREAMS_INCLUDE_INTENSITY,
    USER_PROCESSING_THRESHOLD,
    USER_PROCESSING_MODE,
    USER_PROCESSING_PROF_PER_SEC,
    USER_PROCESSING_MEDIAN_MODE,
    USER_PROCESSING_BILATERAL_MODE,
    USER_PROCESSING_PEAK_MODE,
    USER_PROCESSING_FLIP,
    USER_LASER_ENABLED,
    USER_LASER_MODE,
    USER_LASER_VALUE,
    USER_INPUTS_PRESET,
    USER_INPUTS_PARAMS_MASK,
    USER_INPUTS_1_ENABLED,
    USER_INPUTS_1_EVENT,
    USER_INPUTS_1_MODE,
    USER_INPUTS_1_DELAY,
    USER_INPUTS_1_DIVIDER,
    USER_INPUTS_2_ENABLED,
    USER_INPUTS_2_MODE,
    USER_INPUTS_2_INVERSE,
    USER_INPUTS_3_ENABLED,
    USER_INPUTS_3_MODE,
    USER_OUTPUTS_1_ENABLED,
    USER_OUTPUTS_1_MODE,
    USER_OUTPUTS_1_DELAY,
    USER_OUTPUTS_1_PULSE_WIDTH,
    USER_OUTPUTS_1_INVERSE,
    USER_OUTPUTS_2_ENABLED,
    USER_OUTPUTS_2_MODE,
    USER_OUTPUTS_2_DELAY,
    USER_OUTPUTS_2_PULSE_WIDTH,
    USER_OUTPUTS_2_INVERSE,
    USER_VIEW_3D_MOTION_TYPE,
    USER_VIEW_3D_Y_SOURCE,
    USER_VIEW_3D_Y_STEP,
    USER_VIEW_3D_PAINT_MODE,
    USER_VIEW_3D_DECIMATION,
    USER_EIP_TCP_PORT,
    USER_EIP_UDP_PORT,
    USER_EIP_TCP_TTL,
    USER_EIP_TCP_TIMEOUT,
    USER_EIP_TCP_MULTICAST_ALLOC,
    USER_EIP_TCP_MULTICAST_NUM,
    USER_EIP_TCP_MULTICAST_ADDR,
    USER_COMPATIBILITY_RF625_ENABLED,
    USER_COMPATIBILITY_RF625_TCP_PORT,
    USER_SENSOR_DOUBLE_SPEED_ENABLED,
    USER_SENSOR_EDR_TYPE_1_ENABLED,
    USER_SENSOR_EDRTYPE2_ENABLED,
    USER_SENSOR_EDR_TYPE_2_DIVIDER,
    USER_SENSOR_EDR_TYPE_2_MAX_DIVIDER,
    USER_ROI_SIZE
}parameter_name_keys_t;

const static rfChar* parameter_names_array[]	=
{
    [USER_GENERAL_DEVICE_NAME] 			= "user_general_deviceName",
    [USER_GENERAL_SAVE_LOG]			    = "user_general_saveLog",
    [USER_SYSMON_FPGA_TEMP]             = "user_sysMon_fpgaTemp",
    [USER_SYSMON_PARAMS_CHANGED]		= "user_sysMon_paramsChanged",
    [USER_SYSMON_TEMP_SENS_00]			= "user_sysMon_tempSens00",
    [USER_SYSMON_TEMP_SENS_00_MAX]		= "user_sysMon_tempSens00Max",
    [USER_SYSMON_TEMP_SENS_00_MIN]		= "user_sysMon_tempSens00Min",
    [USER_SYSMON_TEMP_SENS_01]          = "user_sysMon_tempSens01",
    [USER_SYSMON_TEMP_SENS_01_MAX]      = "user_sysMon_tempSens01Max",
    [USER_SYSMON_TEMP_SENS_01_MIN]		= "user_sysMon_tempSens01Min",
    [USER_SYSMON_TEMP_SENS_10]          = "user_sysMon_tempSens10",
    [USER_SYSMON_TEMP_SENS_10_MAX]		= "user_sysMon_tempSens10Max",
    [USER_SYSMON_TEMP_SENS_10_MIN]		= "user_sysMon_tempSens10Min",
    [USER_SYSMON_TEMP_SENS_11]          = "user_sysMon_tempSens11",
    [USER_SYSMON_TEMP_SENS_11_MAX]		= "user_sysMon_tempSens11Max",
    [USER_SYSMON_TEMP_SENS_11_MIN]		= "user_sysMon_tempSens11Min",
    [USER_SENSOR_EXPOSURE]              = "user_sensor_exposure",
    [USER_SENSOR_MAX_EXPOSURE]			= "user_sensor_maxExposure",
    [USER_SENSOR_AUTO_EXPOSURE_ENABLED] = "user_sensor_autoExposureEnabled",
    [USER_SENSOR_FRAME_RATE]			= "user_sensor_framerate",
    [USER_SENSOR_MAX_FRAME_RATE]		= "user_sensor_maxFramerate",
    [USER_ROI_ENABLED]                  = "user_roi_enable",
    [USER_ROI_ACTIVE]                   = "user_roi_active",
    [USER_ROI_POS_MODE]                 = "user_roi_posMode",
    [USER_ROI_POS]                      = "user_roi_pos",
    [USER_ROI_MAX_POS]          		= "user_roi_maxPos",
    [USER_ROI_REQ_PROF_SIZE]    		= "user_roi_reqProfSize",
    [USER_NETWORK_SPEED]            	= "user_network_speed",
    [USER_NETWORK_AUTO_NEG]         	= "user_network_autoNeg",
    [USER_NETWORK_IP]               	= "user_network_ip",
    [USER_NETWORK_MASK]                 = "user_network_mask",
    [USER_NETWORK_GATEWAY]          	= "user_network_gateway",
    [USER_NETWORK_HOST_IP]      		= "user_network_hostIP",
    [USER_NETWORK_HOST_PORT]			= "user_network_hostPort",
    [USER_NETWORK_WEB_PORT]         	= "user_network_webPort",
    [USER_NETWORK_SERVICE_PORT]     	= "user_network_servicePort",
    [USER_STREAMS_UDP_ENABLE]         	= "user_streams_udpEnable",
    [USER_STREAMS_FORMAT]               = "user_streams_format",
    [USER_STREAMS_INCLUDE_INTENSITY]    = "user_streams_includeIntensity",
    [USER_PROCESSING_THRESHOLD]         = "user_processing_threshold",
    [USER_PROCESSING_MODE]          	= "user_processing_mode",
    [USER_PROCESSING_PROF_PER_SEC]		= "user_processing_profPerSec",
    [USER_PROCESSING_MEDIAN_MODE]		= "user_processing_medianMode",
    [USER_PROCESSING_BILATERAL_MODE]	= "user_processing_bilateralMode",
    [USER_PROCESSING_PEAK_MODE]			= "user_processing_peakMode",
    [USER_PROCESSING_FLIP]              = "user_processing_flip",
    [USER_LASER_ENABLED]            	= "user_laser_enabled",
    [USER_LASER_MODE]           		= "user_laser_mode",
    [USER_LASER_VALUE]          		= "user_laser_value",
    [USER_INPUTS_PRESET]                = "user_laser_preset",
    [USER_INPUTS_PARAMS_MASK]           = "user_laser_params_mask",
    [USER_INPUTS_1_ENABLED]   			= "user_inputs_1_enabled",
    [USER_INPUTS_1_EVENT]   			= "user_inputs_1_event",
    [USER_INPUTS_1_MODE]        		= "user_inputs_1_mode",
    [USER_INPUTS_1_DELAY]               = "user_inputs_1_delay",
    [USER_INPUTS_1_DIVIDER]         	= "user_inputs_1_divider",
    [USER_INPUTS_2_ENABLED]         	= "user_inputs_2_enabled",
    [USER_INPUTS_2_MODE]                = "user_inputs_2_mode",
    [USER_INPUTS_2_INVERSE]         	= "user_inputs_2_inverse",
    [USER_INPUTS_3_ENABLED]         	= "user_inputs_3_enabled",
    [USER_INPUTS_3_MODE]            	= "user_inputs_3_mode",
    [USER_OUTPUTS_1_ENABLED]    		= "user_outputs_1_enabled",
    [USER_OUTPUTS_1_MODE]       		= "user_outputs_1_mode",
    [USER_OUTPUTS_1_DELAY]      		= "user_outputs_1_delay",
    [USER_OUTPUTS_1_PULSE_WIDTH]		= "user_outputs_1_pulseWidth",
    [USER_OUTPUTS_1_INVERSE]			= "user_outputs_1_inverse",
    [USER_OUTPUTS_2_ENABLED]			= "user_outputs_2_enabled",
    [USER_OUTPUTS_2_MODE]       		= "user_outputs_2_mode",
    [USER_OUTPUTS_2_DELAY]          	= "user_outputs_2_delay",
    [USER_OUTPUTS_2_PULSE_WIDTH]    	= "user_outputs_2_pulseWidth",
    [USER_OUTPUTS_2_INVERSE]        	= "user_outputs_2_inverse",
    [USER_VIEW_3D_MOTION_TYPE]  		= "user_view_3D_motionType",
    [USER_VIEW_3D_Y_SOURCE]             = "user_view_3D_ySource",
    [USER_VIEW_3D_Y_STEP]               = "user_view_3D_yStep",
    [USER_VIEW_3D_PAINT_MODE]       	= "user_view_3D_paintMode",
    [USER_VIEW_3D_DECIMATION]       	= "user_view_3D_decimation",
    [USER_EIP_TCP_PORT]                 = "user_eip_tcpPort",
    [USER_EIP_UDP_PORT]             	= "user_eip_udpPort",
    [USER_EIP_TCP_TTL]              	= "user_eip_tcp_ttl",
    [USER_EIP_TCP_TIMEOUT]          	= "user_eip_tcp_timeout",
    [USER_EIP_TCP_MULTICAST_ALLOC]  	= "user_eip_tcp_multiCast_alloc",
    [USER_EIP_TCP_MULTICAST_NUM]        = "user_eip_tcp_multiCast_num",
    [USER_EIP_TCP_MULTICAST_ADDR]   	= "user_eip_tcp_multiCast_addr",
    [USER_COMPATIBILITY_RF625_ENABLED]	= "user_compatibility_rf625Enabled",
    [USER_COMPATIBILITY_RF625_TCP_PORT]	= "user_compatibility_rf625TCPPort",
    [USER_SENSOR_DOUBLE_SPEED_ENABLED]	= "user_sensor_doubleSpeedEnabled",
    [USER_SENSOR_EDR_TYPE_1_ENABLED]	= "user_sensor_edrType1Enabled",
    [USER_SENSOR_EDRTYPE2_ENABLED]      = "user_sensor_edrType2Enabled",
    [USER_SENSOR_EDR_TYPE_2_DIVIDER]	= "user_sensor_edrType2Divider",
    [USER_SENSOR_EDR_TYPE_2_MAX_DIVIDER]= "user_sensor_edrType2MaxDivider",
    [USER_ROI_SIZE]                     = "user_roi_size"
};

const static rfChar* pvtKey[]	=
{
    [PVT_UNKN]			= "unkn_t",
    [PVT_UINT]			= "uint32_t",
    [PVT_UINT64]		= "uint64_t",
    [PVT_INT]			= "int32_t",
    [PVT_INT64]			= "int64_t",
    [PVT_FLOAT]			= "float_t",
    [PVT_DOUBLE]		= "double_t",
    [PVT_ARRAY_UINT32]	= "u32_arr_t",
    [PVT_ARRAY_UINT64]	= "u64_arr_t",
    [PVT_ARRAY_INT32]	= "i32_arr_t",
    [PVT_ARRAY_INT64]	= "i64_arr_t",
    [PVT_ARRAY_FLT]		= "flt_array_t",
    [PVT_ARRAY_DBL]		= "dbl_array_t",
    [PVT_STRING]		= "string_t"
};
const static rfChar*	patKey[]	=
{
    [PAT_UNKN]			= "unkn",
    [PAT_READ_ONLY]		= "read_only",
    [PAT_WRITE]			= "write",
    [PAT_RESTRICTED]	= "restricted",
};
const static rfChar*	matKey[]	=
{
    [MAT_UNKN]			= "unkn",
    [MAT_FACTORY_ONLY]	= "factory_only",
    [MAT_USER]			= "user",
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
        value_uint32_t*		val_uint;
        value_uint64_t*		val_uint64;
        value_int32_t*		val_int;
        value_int64_t*		val_int64;
        value_flt_t*		val_flt;
        value_dbl_t*		val_dbl;
        array_uint32_t*		arr_uint;
        array_uint64_t*		arr_uint64;
        array_int32_t*		arr_int;
        array_int64_t*		arr_int64;
        array_flt_t*		arr_flt;
        array_dbl_t*		arr_dbl;
        value_str_t*		val_str;
    };
}parameter_t;









typedef enum {
    kRF627_OLD = 1,
    kRF627_SMART = 2
}scanner_types_t;

typedef enum {
    kSERVICE_PROTOKOL = 1,
    kETHERNET_IP = 2,
    kMODBUS_TCP = 3,
}protocol_types_t;

/*! Structure to store a profile
 */
typedef struct
{
    scanner_types_t type;
    union{
        rf627_old_profile_t* rf627_profile;
    };
}rf627_profile_t;

#endif // RF627_TYPES_H
