#ifndef RF627_TYPES_H
#define RF627_TYPES_H

#include "rf627_devices.h"
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
        uint16_t					DeviceID;			//Идентификатор типа сканера
        uint32_t					Serial;				//Серийный номер сканера
        uint32_t					SerialOfPCB;		//Серийный номер электроники
        uint32_t					OperatingTime_H;	//Наработка сканера, часов
        uint8_t						OperatingTime_M;	//Наработка сканера, минут
        uint8_t						OperatingTime_S;	//Наработка сканера, секунд
        uint32_t					RunTime_H;			//Время работы после запуска, часов
        uint8_t						RunTime_M;	        //Время работы после запуска, минут
        uint8_t						RunTime_S;	        //Время работы после запуска, секунд
        uint32_t					StartUp_Counter;    //Количество запусков сканера
        uint32_t					FirmWareVer;		//Версия прошивки
        uint32_t					HardWareVer;		//Версия аппаратного обеспечения
        uint32_t					CustomerID;
        uint32_t					PL_SystemClk;		//Системная тактовая для PL - частота AXI в Гц
        uint32_t					BaseZ;
        uint32_t					RangeZ;
        uint32_t					RangeXStart;
        uint32_t					RangeXEnd;
        uint16_t					PixelsDivider;
        uint16_t					ProfilesDivider;
        uint32_t					FSBL_Version;		//Версия загрузчика
        char                        oemDeviceName[16];
        uint8_t						Reserved[76];
    }General;
/*-------Параметры установленной матрицы-------------------*/
    struct
    {
        char						Name[32];					//Имя матрицы - для отображения
        uint16_t					Width;						//Количество пикселов по горизонтали
        uint16_t					Height;						//Количество пикселов но вертикали
        uint32_t					PixelClock;					//Пиксельная частота в Гц
        uint16_t					Black_OddLines;
        uint16_t					Black_EvenLines;
        uint32_t					FrameCycle_ConstPart;
        uint32_t					FrameCycle_PerLinePart;
        uint8_t						FrameRateORExposure;		//Селектор по чем настраивать матрицу - по частоте кадров или экспозиции: 0 - по частоте, 1 - по экспозиции
        uint32_t					MinExposure;				//Минимальное время экспозиции в нс.
        uint8_t						ImageFlipping;				//Режим отражения изображения: 0 - без отражения, 1 - по X, 2 - по Y, 3 - и по X и по Y
        uint32_t					MaxExposure;				//Максимальное время экспозиции, заданное при настройке сканера
        uint8_t						edrPoint1Value;				//Значение напряжения (в условных единицах 0..63) в 1-й точке излома прямой накопления (стр.30-31 даташита CMV300)
        uint8_t						edrPoint2Value;				//Значение напряжения (в условных единицах 0..63) во 2-й точке излома прямой накопления (стр.30-31 даташита CMV300)
        uint16_t					edrPoint1Pos;				//Положение в 1/1000 точки относительно начала экспозиции, т.е. 0 - одновременно с началом экспозиции, 999 - сразу в конце
        uint16_t					edrPoint2Pos;				//Положение в 1/1000 точки относительно начала экспозиции, т.е. 0 - одновременно с началом экспозиции, 999 - сразу в конце
        uint8_t						Reserved[113];
        struct
        {
            uint16_t Addr;
            uint16_t Value;
        }                           InitRegs[64];               //Структура с параметрами инициализации регистров матрицы
    }Sensor;
/*-------Параметры сетевого подключения-------------------*/
    struct
    {
        uint8_t						MAC[6];
        uint16_t					EIP_VendorID;
        uint16_t					EIP_DeviceType;
        uint8_t						forceAutoNegTime;			//Количество секунд, через которое сканер установит автосогласование принудительно в случае отсутствия связи по Ethernet
        uint8_t						Reserved[31];
    }Network;
/*-------Параметры управления лазером----------------------*/
    struct
    {
        uint16_t					Wavelength;				//Длина волны в нм
        uint8_t						Koeff1;					//Коээфициент крутизны регулирования отпределяется как Koeff1/128
        uint8_t						Koeff2;
        uint32_t					MinValue;				//Значение, при котором лазер зажигается
        uint32_t					MaxValue;				//Максимальное допустимое значение
        uint8_t						EnableModeChange;		//Разрешение изменения режима работы лазера: 0 - запрещено, 1 - разрешено
        uint8_t						Reserved[31];
    }Laser;
/*------------Параметры входных каналов--------------------*/
    struct
    {
        uint16_t					In1_MinDelay;			//Минимальная задержка в нс
        uint32_t					In1_MaxDelay;			//Максимальная задержка в нс
        uint16_t					MaxDividerIn1;			//Максимальное значение делителя частоты кадров
        uint16_t					MinDividerIn1;			//Минимальное значение делителя частоты кадров
        uint8_t						Reserved[62];
    }Inputs;
/*------------Параметры выходных каналов-------------------*/
    struct
    {
        uint16_t					Out1_MinDelay;
        uint32_t					Out1_MaxDelay;
        uint16_t					Out1_MinPulseWidth;
        uint32_t					Out1_MaxPulseWidth;
        uint16_t					Out2_MinDelay;
        uint32_t					Out2_MaxDelay;
        uint16_t					Out2_MinPulseWidth;
        uint32_t					Out2_MaxPulseWidth;
        uint8_t						Reserved[32];
    }Outputs;
    /*------------Параметры обработки профилей-----------------*/
        struct
        {
            uint32_t					maxDumpSize;
            uint8_t						Reserved[60];
        }Profiles;
    /*------------Параметры протокола EthernetIP---------------*/
        struct
        {
            struct
            {
                uint16_t				vendorID;				// Attribute 1: Vendor ID - идентификационный номер производителя устройства
                uint16_t				deviceType;				// Attribute 2: Device Type - тип устройства, который определяет его область использования
                uint16_t				productCode;			// Attribute 3: Product Code - идентифицирует номер конкретного продукта
                struct
                {	uint8_t					majorRev;			// Attribute 4: Revision	USINT Major
                    uint8_t					minorRev;			//							USINT Minor
                }revision;										// Структура, хранящая EIP-версию девайса
            }identity;

            struct
            {
                uint32_t				configCapability;		// Attribute 2: Данный атрибут описывает поддержку устройством дополнительных возможностей конфигурации сети
                struct
                {	uint16_t				pathSize;			// Path size in 16 bit words (path_size * 16 bit)
                    uint16_t				classId;			// Class ID of the linked object
                    uint16_t				instanceNumber;		// Requested Instance Number of the linked object
                    uint16_t				attributeNumber;	// Requested Attribute Number of the linked object
                }phyLinkObject;									// Attribute 4: Этот атрибут идентифицирует объект, связанный с базовым физическим интерфейсом связи (Ethernet Link Object)
            }tcpInterface;

            uint8_t						intrfType;				//Type of interface: twisted pair, fiber, internal, etc
            struct
            {	uint16_t					capabilityBits;
                uint8_t						speedDupCount;
                struct
                {
                    uint16_t					speed;
                    uint8_t						duplex;
                }speedDuplex[4];
            }intrfCapability;									//Path to physical link object

            uint8_t						Reserved[44];
        }eip;
    /*-------Резерв--------------------------------------------*/
        uint8_t							Reserved[167];
    /*---------------------------------------------------------*/
}factory_params_t;

typedef struct
{
    char                        Tag[4];            //<! File header tag = "DTF+"
    uint16_t                    FormatVersion;     //<! Version of header format (1)
    struct
    {
        struct
        {
            uint8_t            Day;
            uint8_t            Month;
            uint16_t            Year;
        }date;
        struct
        {
            uint8_t            Hour;
            uint8_t            Minute;
            uint8_t            Second;
        }time;
    }timestamp;                                     //<! date and time of calibration
    uint16_t                    DevType;            //<! Device type (627)
    uint32_t                    SerialNumber;       //<! Serial Number of Scanner
    uint16_t					BaseZ;              //<! Z base, mm
    uint16_t					RangeZ;             //<! Z measurement range, mm
    uint16_t					RangeXStart;        //<! X start measurement range, mm
    uint16_t					RangeXEnd;          //<! X end measurement range, mm
    uint16_t					YSteps;             //<! Number of calibration steps
    uint16_t					StartPosition;      //<! Start position
    uint16_t					EndPosition;        //<! End position
    uint16_t					CutXLeft;           //<! Amount of pixels to cut from left
    uint16_t					CutXRight;          //<! Amount of pixels to cut from right
    uint8_t                     PlaneType;          //<! 0 - ZPlane, 1 - TrianglesXY
    uint8_t                     InvertZ;            //<! 0 - no invert, other - invert
    uint32_t					TriangleWidth;      //<! Triangle width, um
    uint32_t					TriangleHeight;     //<! Triangle height, um
    uint8_t                     AveragingSize;      //<! Number of pixels profiles for averaging
    uint32_t                    Exposure;           //<! Exposure time, ns (0 for Auto)
    int16_t                     Temp;               //<! Temperature upon calibration, C/10
    double                      StepLength;         //<! Z Step Length
    uint32_t					FirmwareVer;		//<! Firmware Version
    uint32_t					HardwareVer;		//<! Hardware Version
    uint8_t                     Reserved[186];      //<!- Reserved
}DTF_header;

typedef struct
{
    uint8_t                    FormatVersion;     //<! Version of header format (1)
    uint16_t                    CRC;                //<!- CRC
    uint32_t                    SerialNumber;       //<! Serial Number of Scanner
    struct
    {
        struct
        {
            uint16_t            Year;
            uint8_t            Month;
            uint8_t            Day;
        }date;
        struct
        {
            uint8_t            Hour;
            uint8_t            Minute;
            uint8_t            Second;
        }time;
    }timestamp;                                     //<! date and time of calibration
    uint8_t                     Zero[242];          //<! Must be filled with zeroes
}TBL_header;

typedef struct
{
    char        name[64];
    uint8_t     save_log_to_spi;
    uint8_t		reserved[127];
}
general_params_t;

typedef struct
{
    int16_t		fpga_temp;
    uint8_t		params_changed;			//Параметры были изменены, но не сохранены: 1 - factory, 2 - user, 3 - factory & user
    int16_t		sens00_temp;
    int16_t		sens00_max;
    int16_t		sens00_min;
    int16_t		sens01_temp;
    int16_t		sens01_max;
    int16_t		sens01_min;
    int16_t		sens10_temp;
    int16_t		sens10_max;
    int16_t		sens10_min;
    int16_t		sens11_temp;
    int16_t		sens11_max;
    int16_t		sens11_min;
    uint8_t		reserved[55];
}sysmon_params_t;

typedef struct
{
    uint8_t		dhs;
    uint8_t		gain_analog;
    uint8_t		gain_digital;
    uint32_t	exposure;
    uint32_t	max_exposure;
    uint32_t	frame_rate;
    uint32_t	max_frame_rate;
    uint8_t     exposure_hdr_mode;
    uint8_t     auto_exposure;
    uint8_t		column_edr_mode;
    uint8_t		column_exposure_div;
    uint8_t     column_exposure_max_div;
    uint8_t		reserved_1[59];
}sensor_params_t;

typedef struct
{
    uint8_t		enable;
    uint16_t	tcp_port;
    uint8_t		reserved[32];
}rf625compat_params_t;

typedef struct
{
    uint8_t		enable;
    uint8_t		active;
    uint16_t	window_height;
    uint8_t		position_mode;
    uint16_t	window_top;
    uint16_t	current_window_top;
    uint16_t	profile_size;
    uint8_t		reserved[80];
}roi_params_t;

typedef struct
{
    uint16_t	speed;
    uint8_t		autonegotiation;
    uint32_t    ip_address;
    uint32_t    net_mask;
    uint32_t    gateway_ip;
    uint32_t    host_ip;
    uint16_t    stream_port;
    uint16_t    http_port;
    uint16_t    service_port;
//    uint16_t    eip_broadcast_port;
//    uint16_t    eip_port;
    uint8_t		reserved[68];
}network_params_t;

typedef struct
{
    uint8_t		enable;
    uint8_t		format;
    uint8_t		ack;
    uint8_t     include_intensivity;
    uint8_t		reserved[31];
}stream_params_t;

typedef struct
{
    uint32_t	brightness_threshold;
    uint8_t		filter_width;
    uint8_t		processing_mode;
    uint8_t		reduce_noise;
    uint32_t    frame_rate;
    uint8_t		median_filter_mode;
    uint8_t		bilateral_filter_mode;
    uint8_t     peak_select_mode;
    uint8_t     profile_flip;
    uint8_t		reserved[56];
}image_processing_params_t;

typedef struct
{
    uint8_t		enable;
    uint8_t		auto_level;
    uint16_t	level;
    uint8_t		reserved[32];
}laser_params_t;

typedef struct
{
    uint16_t    params_mask;
    uint8_t		in1_enable;
    uint8_t		in1_mode;
    uint32_t	in1_delay;
    uint8_t		in1_decimation;
    uint8_t		in2_enable;
    uint8_t		in2_mode;
    uint8_t		in2_invert;
    uint8_t		in3_enable;
    uint8_t		in3_mode;
    uint8_t		reserved[12];
}inputs_preset_t;

typedef struct
{
    uint8_t                 preset_index;
    inputs_preset_t   params[12];
    uint8_t                 reserved[32];
}inputs_params_t;

typedef struct
{
    uint8_t		out1_enable;
    uint8_t		out1_mode;
    uint32_t	out1_delay;
    uint32_t	out1_pulse_width;
    uint8_t		out1_invert;
    uint8_t		out2_enable;
    uint8_t		out2_mode;
    uint32_t	out2_delay;
    uint32_t	out2_pulse_width;
    uint8_t		out2_invert;
    uint8_t		reserved[32];
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
    uint8_t                   reserved[283];
}user_params_t;

typedef struct{
    struct{
        uint32_t H;
        uint8_t  M;
        uint8_t  S;
    }Time;
    uint8_t  ModuleID;
    uint8_t  EventID;
    char     String[128];
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
