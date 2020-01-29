#ifndef RF627_PROTOCOL_H
#define RF627_PROTOCOL_H

#include "platform_types.h"
#include "netwok_platform.h"
#include "memory_platform.h"

/* RF627_old - Service Message
 +--------+---------------+-------------+--------------------------------------+
 | Index  | Function      | Size, bytes | Description                          |
 |--------|---------------|-------------|--------------------------------------|
 | 0      | Msg type      | 1           | Bits 7-4 (Message type) :            |
 |        |               |             |  -b0001: command;                    |
 |        |               |             |  -b0010: confirmation of the command;|
 |        |               |             |  -b0011: response to the command;    |
 |        |               |             | Bit 3 (request for confirmation of   |
 |        |               |             |        response or command) :        |
 |        |               |             |  -b0: confirmation is not required;  |
 |        |               |             |  -b1: confirmation is required;      |
 |        |               |             | Bit 2 (is a sign of the last command |
 |        |               |             |        or response ) :               |
 |        |               |             |  -b0: command/response is not last;  |
 |        |               |             |  -b1: command/response is last;      |
 |        |               |             | Bit 1 (a sign of the presence of a   |
 |        |               |             |        checksum in the message       |
 |        |               |             |        parameters (in Index 2)) :    |
 |        |               |             |  -b0 - on checksum;                  |
 |        |               |             |  -b1 - off checksum;                 |
 |        |               |             | bit 0 (is the reserve)               |
 +--------+---------------+-------------+--------------------------------------+
 | 1      | Msg options   | 1           | Not used yet                         |
 +--------+---------------+-------------+--------------------------------------+
 | 2      | Data checksum | 1           | Data Area Checksum                   |
 +--------+---------------+-------------+--------------------------------------+
 | 3      | Reserve       | 1           | Not used yet                         |
 +--------+---------------+-------------+--------------------------------------+
 | 4      | Device id     | 4           | Unique identifier of the device      |
 |        |               |             | (SCANNER SERIAL NUMBER) to which     |
 |        |               |             | the message was sent. May be         |
 |        |               |             | broadcast: 0xFFFFFFFF. When sending a|
 |        |               |             | message or confirmation by the       |
 |        |               |             | scanner, contains the identifier of  |
 |        |               |             | the scanner.                         |
 +--------+---------------+-------------+--------------------------------------+
 | 8      | Unique msg id | 2           | The msg counter (for confirmation)   |
 |        |               |             | must be unique from message to       |
 |        |               |             | message, the repetition period of    |
 |        |               |             | 65536 messages is quite sufficient   |
 |        |               |             | for work.                            |
 +--------+---------------+-------------+--------------------------------------+
 | 10     | Module id     | 1           | Module ID - specific module command  |
 +--------+---------------+-------------+--------------------------------------+
 | 11     | Command id    | 1           | Command ID - specific for each module|
 +--------+---------------+-------------+--------------------------------------+
 | 12     | Data size     | 2           | Payload data size                    |
 +--------+---------------+-------------+--------------------------------------+
 | 14     | Payload       | N           | Command attributes or response data. |
 | ..     |               |             | In the case of sending a command, the|
 | ..     |               |             | field contains attributes (data that |
 | ..     |               |             | must be applied). In the case of     |
 | ..     |               |             | confirmation or response, the data   |
 | 14+N   |               |             | requested by the team.               |
 +--------+---------------+-------------+--------------------------------------+
 */

/**
 * @enum rf627_old_msg_type_t
 * @brief is a enum representing Message type (Index 0 Bits 7-4)
 */
typedef enum
{
    MSG_rf627_old_Command = 0x01, /**< command for */
    MSG_rf627_old_Ack     = 0x02, /**< command for */
    MSG_rf627_old_Answer  = 0x03  /**< command for */
} rf627_old_msg_type_t;

/**
 * @brief DEVICE_ID_ALL - Broadcast device identifier: 0xFFFFFFFF.
 */
#define DEVICE_ID_ALL 0xffffffff

/**
 * @enum rf627_old_module_id_t
 * @brief is a enum representing identifiers of commands (Index 10)
 */
typedef enum
{
    MID_rf627_old_FactoryParams   = 0x50, /**< command for get Factory Params */
    MID_rf627_old_UserParams      = 0x5e, /**< command for get User Params */
    MID_rf627_old_SensorDriver    = 0x51, /**< command for */
    MID_rf627_old_CalibrationCtrl = 0x52, /**< command for */
    MID_rf627_old_FrameCapture    = 0x53, /**< command for */
    MID_rf627_old_QSPIDriver      = 0x5a  /**< command for */
}
rf627_old_module_id_t;

typedef enum
{
    CMD_rf627_old_UGetDeviceInfo      = 0x00,
    CMD_rf627_old_UGetParams          = 0x01,
    CMD_rf627_old_USetParams          = 0x02,
    CMD_rf627_old_UGetSysMon          = 0x03,
    CMD_rf627_old_USetSysMon          = 0x04,
    CMD_rf627_old_UGetRF625Compat     = 0x05,
    CMD_rf627_old_USetRF625Compat     = 0x06,
    CMD_rf627_old_UGetSensor          = 0x07,
    CMD_rf627_old_USetSensor          = 0x08,
    CMD_rf627_old_UGetROI             = 0x09,
    CMD_rf627_old_USetROI             = 0x0a,
    CMD_rf627_old_UGetNetwork         = 0x0b,
    CMD_rf627_old_USetNetwork         = 0x0c,
    CMD_rf627_old_UGetStream          = 0x0d,
    CMD_rf627_old_USetStream          = 0x0e,
    CMD_rf627_old_UGetProcessing      = 0x0f,
    CMD_rf627_old_USetProcessing      = 0x10,
    CMD_rf627_old_UGetLaser           = 0x11,
    CMD_rf627_old_USetLaser           = 0x12,
    CMD_rf627_old_UGetInputs          = 0x13,
    CMD_rf627_old_USetInputs          = 0x14,
    CMD_rf627_old_UGetOutputs         = 0x15,
    CMD_rf627_old_USetOutputs         = 0x16,
    CMD_rf627_old_UGetLogItems        = 0x17,
    CMD_rf627_old_UGetLogItemCount    = 0x18
}
rf627_old_cmd_user_params_cmd_t;

typedef enum
{
    CMD_rf627_old_FGetParams          = 0x00,
    CMD_rf627_old_FSetParams          = 0x01,
    CMD_rf627_old_FGetUserParams      = 0x02,
    CMD_rf627_old_FSetUserParams      = 0x03,
    CMD_rf627_old_FSaveParams         = 0x10,
    CMD_rf627_old_FSaveDefault        = 0x11,
    CMD_rf627_old_FReset              = 0x12,
    CMD_rf627_old_FDefault            = 0x13,
    CMD_rf627_old_FSetStartupCount    = 0x20,
    CMD_rf627_old_FSetOperatingTime   = 0x21,
    CMD_rf627_old_FGetLaserWaveLength = 0x50,
    CMD_rf627_old_FGetLaserCoeff1     = 0x51,
    CMD_rf627_old_FGetLaserCoeff2     = 0x52,
    CMD_rf627_old_FGetLaserMinValue   = 0x53,
    CMD_rf627_old_FGetLaserMaxValue   = 0x54,
    CMD_rf627_old_FSetLaserWaveLength = 0xd0,
    CMD_rf627_old_FSetLaserCoeff1     = 0xd1,
    CMD_rf627_old_FSetLaserCoeff2     = 0xd2,
    CMD_rf627_old_FSetLaserMinValue   = 0xd3,
    CMD_rf627_old_FSetLaserMaxValue   = 0xd4
}
rf627_old_cmd_factory_params_cmd_t;

typedef enum
{
    CMD_rf627_old_CCWriteData         = 0x10,
    CMD_rf627_old_CCGetCRC16          = 0x12,
    CMD_rf627_old_CCSaveToFlash       = 0x20
}
cmd_rf627_old_calibration_ctrl_cmd_t;

typedef enum
{
    CMD_rf627_old_FCGetFrame          = 0x10
}
cmd_rf627_old_frame_capture_t;

typedef enum
{
    CMD_rf627_old_QReadFlash          = 0x10,
    CMD_rf627_old_QGetCRC16           = 0x12,
    CMD_rf627_old_QFWWriteData        = 0x20,
    CMD_rf627_old_QFWGetCRC16         = 0x21,
    CMD_rf627_old_QFWSaveToFlash      = 0x22
}
cmd_rf627_old_qspi_driver_cmd_t;

typedef uint8_t rf627_old_cmd_type_t;


typedef struct __attribute__((packed))
{
    uint8_t                 reserved_1  : 2;    //must be zero
    uint8_t                 is_last     : 1;
    uint8_t                 ack         : 1;
    uint8_t                 msg_type    : 4;
    uint8_t                 error;
    uint8_t                 reserved_2[2];
    uint32_t                serial_number;
    uint16_t                msg_count;
    uint8_t                 module;
    uint8_t                 cmd;
    uint16_t                payload_size;
}
rf627_old_service_msg_t;


#pragma pack(push,1)
typedef struct
{
    char        name[64];
    uint16_t    device_id;
    uint32_t    serial_number;
    uint32_t    firmware_version;
    uint32_t    hardware_version;
    uint32_t    config_version;
    uint32_t    fsbl_version;
    uint32_t    z_begin;
    uint32_t    z_range;
    uint32_t    x_smr;
    uint32_t    x_emr;
    uint8_t     reserved_0[36];

    uint16_t    eth_speed;
    uint32_t    ip_address;
    uint32_t    net_mask;
    uint32_t    gateway_ip;
    uint32_t    host_ip;
    uint16_t    stream_port;
    uint16_t    http_port;
    uint16_t    service_port;
    uint16_t    eip_broadcast_port;
    uint16_t    eip_port;
    uint8_t     hardware_address[6];
    uint8_t     reserved_1[26];

    uint32_t    max_payload_size;
    uint8_t     reserved_2[32];

    uint8_t     stream_enabled;
    uint8_t     stream_format;
    uint8_t     reserved_3[32];

    uint8_t     reserved_4[256];
}
rf627_old_device_info_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
    char        name[64];
    uint8_t     save_log_to_spi;
    uint8_t		reserved[127];
}
rf627_old_general_params_t;
#pragma pack(pop)

#pragma pack(push,1)
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
}rf627_old_sysmon_params_t;
#pragma pack(pop)

#pragma pack(push,1)
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
}rf627_old_sensor_params_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
    uint8_t		enable;
    uint16_t	tcp_port;
    uint8_t		reserved[32];
}rf627_old_rf625compat_params_t;
#pragma pack(pop)

#pragma pack(push,1)
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
}rf627_old_roi_params_t;
#pragma pack(pop)

#pragma pack(push,1)
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
}rf627_old_network_params_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
    uint8_t		enable;
    uint8_t		format;
    uint8_t		ack;
    uint8_t     include_intensivity;
    uint8_t		reserved[31];
}rf627_old_stream_params_t;
#pragma pack(pop)

#pragma pack(push,1)
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
}rf627_old_image_processing_params_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
    uint8_t		enable;
    uint8_t		auto_level;
    uint16_t	level;
    uint8_t		reserved[32];
}rf627_old_laser_params_t;
#pragma pack(pop)

#pragma pack(push,1)
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
}rf627_old_inputs_preset_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
    uint8_t                 preset_index;
    rf627_old_inputs_preset_t   params[12];
    uint8_t                 reserved[32];
}rf627_old_inputs_params_t;
#pragma pack(pop)

#pragma pack(push,1)
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
}rf627_old_outputs_params_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
    rf627_old_general_params_t          general;
    rf627_old_sysmon_params_t           sysmon;
    rf627_old_rf625compat_params_t      rf625compat;
    rf627_old_sensor_params_t           sensor;
    rf627_old_roi_params_t              roi;
    rf627_old_network_params_t          network;
    rf627_old_stream_params_t           stream;
    rf627_old_image_processing_params_t image_processing;
    rf627_old_laser_params_t            laser;
    rf627_old_inputs_params_t           inputs;
    rf627_old_outputs_params_t          outputs;
    uint8_t                         reserved[283];
}rf627_old_user_params_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct{
    struct{
        uint32_t H;
        uint8_t M;
        uint8_t S;
    }Time;
    uint8_t ModuleID;
    uint8_t EventID;
    char String[128];
}rf627_old_log_record_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
    uint8_t     data_type;
    uint8_t     flags;
    uint16_t    device_type;
    uint32_t    serial_number;
    uint64_t    system_time;

    uint8_t     proto_version_major;
    uint8_t     proto_version_minor;
    uint8_t     hardware_params_offset;
    uint8_t     data_offset;
    uint32_t    packet_count;
    uint32_t    measure_count;

    uint16_t    zmr;
    uint16_t    xemr;
    uint16_t    discrete_value;
    uint8_t     reserved_0[14];

    uint32_t    exposure_time;
    uint32_t    laser_value;
    uint32_t    step_count;
    uint8_t     dir;
    uint8_t     reserved_1[3];
}
rf627_old_stream_msg_t;
#pragma pack(pop)


rfBool srvc_proto_627_old_send_message_by_udp(
        void* s, rfUint8* msg, rfUint32 size,
        rf_sockaddr_in *send_addr,
        rfUint32 payload_length, void* payload);

uint32_t srvc_proto_627_old_get_header_size();

uint32_t srvc_proto_627_old_create_hello_header(
        uint8_t* buffer, uint32_t size);

uint32_t srvc_proto_627_old_get_user_params_packet(
        uint8_t* buffer, uint32_t size,
        uint32_t serial_number, uint16_t m_msg_count);

rfUint32 srvc_proto_627_old_create_answer_packet(
        uint8_t* recv, uint32_t recv_size,
        uint8_t* answer_buffer, uint32_t buffer_size);

uint32_t srvc_proto_627_old_get_serial_number_from_message(
        uint8_t* message, uint32_t message_size);

uint32_t srvc_proto_627_old_get_counter_from_message(
        uint8_t* message, uint32_t message_size);

uint32_t srvc_proto_627_old_get_payload_from_message(
        uint8_t* message, uint32_t message_size,
        uint8_t* buffer, uint32_t buffer_size);


#endif // RF627_PROTOCOL
