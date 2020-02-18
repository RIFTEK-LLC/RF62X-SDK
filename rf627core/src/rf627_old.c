#include "rf627_sdk.h"
#include "iostream_platform.h"
#include "rf627_protocol.h"
#include "custom_string.h"

#include <pthread.h>

#define RF627_OLD_API_VERSION       0x14010a00  //20.01.10.0

#define RF627_REENUM_IFS_ON_SEARCH  1

#define RF627_DEVICE_ID             627

#define RF627_SERVICE_PORT          50011
#define RF627_STREAM_PORT           50001

#define RF627_RECV_TIMEOUT          100

#define RF627_PROFILE_SIZE          648
#define RF627_EXT_PROFILE_SIZE      1296

#define RF627_IMAGE_WIDTH           648
#define RF627_IMAGE_HEIGHT          488
#define RF627_IMAGE_SIZE            (RF627_IMAGE_WIDTH * RF627_IMAGE_HEIGHT)

#define RF627_MAX_PAYLOAD_SIZE      32754

#define RF627_API_MAX_ERROR_TEXT_LENGTH     256

#define RF627_MAX_LOG_ENTRIES_PER_PAYLOAD   (RF627_MAX_PAYLOAD_SIZE / sizeof(rf627_log_record_t))

#define RF627_SERVICE_PROTO_REPEAT_RATE     5

#define WRITE_PARAMS_TIMEOUT        (3 * 1000)
#define FLUSH_PARAMS_TIMEOUT        (3 * 1000)
#define REBOOT_TIMEOUT              (2 * 1000)
#define READ_PARAMS_TIMEOUT         (3 * 1000)
#define WRITE_CHUNK_TIMEOUT         (10 * 1000)
#define FLUSH_FIRMWARE_TIMEOUT      (2 * 1000)
#define WRITE_SPI_TIMEOUT           (100 * 1000)
#define WRITE_SPI_FINISHED_BS       0

//Режим отражения изображения (в фэктори) или профиля (в юзер)
typedef enum{
    FM_NO					= 0x00,
    FM_X					= 0x01,
    FM_Z					= 0x02,
    FM_XZ					= 0x03
}flipMode_t;

//Формат представления профиля
typedef enum{
    DF_PIXELS				= 0x10,
    DF_PROFILE				= 0x11,
    DF_PIXELS_INTRP			= 0x12,
    DF_PROFILE_INTRP		= 0x13
}dataFormat_t;

//Режим первичной обработки видео
typedef enum{
    PM_ACCURACY				= 0x00,
    PM_WELDING				= 0x01
}procMode_t;

//Режим выбора пика для рассчета профиля
typedef enum{
    PM_MAX_INTENSITY		= 0x00,
    PM_FIRST				= 0x01,
    PM_LAST					= 0x02,
    PM_NUMBER_2				= 0x03,
    PM_NUMBER_3				= 0x04,
    PM_NUMBER_4				= 0x05,
    PM_NUMBER_5				= 0x06,
    PM_NUMBER_6				= 0x07,
}peakMode_t;

//Режимы управления положением ROI
typedef enum{
    RPM_MANUAL				= 0,
    RPM_AUTO				= 1
}roiPosMode_t;

//Состояния соединения по сети
typedef enum{
    LS_DISCONNECTED			= 0,
    LS_CONNECTED			= 1
}linkState_t;

//Скорости соединения по сети
typedef enum{
    LS_UNKN					= 0,
    LS_10MBIT				= 10,
    LS_100MBIT				= 100,
    LS_1GBIT				= 1000,
}linkSpeed_t;

//Режимы работы лазера
typedef enum{
    LASER_PLAIN_INT				= 0x00,
    LASER_PLAIN_INT_INV			= 0x02,
    LASER_PLAIN_EXT				= 0x01,
    LASER_PLAIN_EXT_INV			= 0x03,
    LASER_STROBE				= 0x04,
    LASER_STROBE_INV			= 0x05,
    LASER_ALWAYS_ONE			= 0x06,
    LASER_ALWAYS_ZERO			= 0x07,
    LASER_HEART_BEAT			= 0x10,
    LASER_HEART_BEAT_INV		= 0x12,
    LASER_PULS_SLOW				= 0x20,
    LASER_PULS_SLOW_INV			= 0x22,
    LASER_PULS_FAST				= 0x30,
    LASER_PULS_FAST_INV			= 0x32,
}laserMode_t;

//Параметры запуска экспозиции для входа №1
typedef enum{
    IN1_EVENT_IGEN				= 0,
    IN1_EVENT_EXT				= 1,
    IN1_EVENT_SREQ				= 3
}in1Event_t;

//Режим срабатывания входа №1
typedef enum{
    IN1_MODE_RISE				= 0,
    IN1_MODE_FALL				= 1,
    IN1_MODE_LVL1				= 2,
    IN1_MODE_LVL0				= 3
}in1Mode_t;

//Режим срабатывания входа №2
typedef enum{
    IN2_MODE_LVL				= 0,
    IN2_MODE_PHASE				= 1
}in2Mode_t;

//Режим работы входа №2
typedef enum{
    IN3_MODE_RISE				= 0,
    IN3_MODE_FALL				= 1
}in3Mode_t;

//Режим работы выходов
typedef enum{
    OUT_MODE_EXP_START			= 0,
    OUT_MODE_IN1_LOG_LVL		= 1,
    OUT_MODE_IN1_RISE			= 2,
    OUT_MODE_IN1_FALL			= 3,
    OUT_MODE_IN2_LOG_LVL		= 4,
    OUT_MODE_IN2_RISE			= 5,
    OUT_MODE_IN2_FALL			= 6,
    OUT_MODE_IN3_LOG_LVL		= 7,
    OUT_MODE_IN3_RISE			= 8,
    OUT_MODE_IN3_FALL			= 9,
    OUT_MODE_EXP_TIME			= 10
}outMode_t;

//Селектор координаты Y для профилей
typedef enum{
    YA_SYSTEM_TIME				= 0,
    YA_STEP_COUNTER				= 1,
    YA_MEASURES_COUNTER			= 2,
}yAxisSource_t;

valuesEnum_t		boolEnum			= {2, {{0, "false"}, {1, "true"}}};

valuesEnum_t		flipEnum			= {4, {{FM_NO, "no"}, {FM_X, "X"}, {FM_Z, "Z"}, {FM_XZ, "XZ"}}};

valuesEnum_t		roiPosModeEnum		= {2, {{RPM_MANUAL, "manual"}, {RPM_AUTO, "auto"}}};

valuesEnum_t		netSpeedEnum		= {3, {{LS_10MBIT, "10"}, {LS_100MBIT, "100"}, {LS_1GBIT, "1000"}}};

valuesEnum_t		streamsFormatEnum	= {4, {{DF_PIXELS, "Pixels"}, {DF_PROFILE, "Profile"}, {DF_PIXELS_INTRP, "Interpolated pixels"}, {DF_PROFILE_INTRP, "Interpolated profile"}}};

valuesEnum_t		processingModeEnum	= {2, {{PM_ACCURACY, "High accuracy"}, {PM_WELDING, "Welding"}}};

valuesEnum_t		medianFilterEnum	= {8, {{0, "Off"}, {3, "3"}, {5, "5"}, {7, "7"}, {9, "9"}, {11, "11"}, {13, "13"}, {15, "15"}}};

valuesEnum_t		bilateralFilterEnum	= {8, {{0, "Off"}, {3, "3"}, {5, "5"}, {7, "7"}, {9, "9"}, {11, "11"}, {13, "13"}, {15, "15"}}};

valuesEnum_t		peakModeEnum		= {8, {{PM_MAX_INTENSITY, "Max intensity"}, {PM_FIRST, "First"}, {PM_LAST, "Last"}, {PM_NUMBER_2, "#2"}, {PM_NUMBER_3, "#3"}, {PM_NUMBER_4, "#4"}, {PM_NUMBER_5, "#5"}, {PM_NUMBER_6, "#6"}}};

valuesEnum_t		laserModeEnum		= {2, {{LASER_ALWAYS_ZERO, "Always on"}, {LASER_STROBE_INV, "Expose sync"}}};

valuesEnum_t		input1EventEnum		= {3, {{IN1_EVENT_IGEN, "Internal generator"}, {IN1_EVENT_EXT, "External sync"}, {IN1_EVENT_SREQ, "Software request"}}};

valuesEnum_t		input1ModeEnum		= {4, {{IN1_MODE_RISE, "Rise"}, {IN1_MODE_FALL, "Fall"}, {IN1_MODE_LVL1, "High level"}, {IN1_MODE_LVL0, "Low level"}}};

valuesEnum_t		input2ModeEnum		= {2, {{IN2_MODE_LVL, "Level"}, {IN2_MODE_PHASE, "Phase"}}};

valuesEnum_t		input3ModeEnum		= {2, {{IN3_MODE_RISE, "Rise"}, {IN3_MODE_FALL, "Fall"}}};

valuesEnum_t		outputModeEnum		= {11, {{OUT_MODE_EXP_START, "Exposure start"},
                                                {OUT_MODE_IN1_LOG_LVL, "In1 level"},
                                                {OUT_MODE_IN1_RISE, "In1 rise"},
                                                {OUT_MODE_IN1_FALL, "In1 fall"},
                                                {OUT_MODE_IN2_LOG_LVL, "In2 level"},
                                                {OUT_MODE_IN2_RISE, "In2 rise"},
                                                {OUT_MODE_IN2_FALL, "In2 fall"},
                                                {OUT_MODE_IN3_LOG_LVL, "In3 level"},
                                                {OUT_MODE_IN3_RISE, "In3 rise"},
                                                {OUT_MODE_IN3_FALL, "In3 fall"},
                                                {OUT_MODE_EXP_TIME, "Exposure time"}}};

valuesEnum_t		motionTypeEnum		= {2, {{0, "Linear"}, {1, "Radial"}}};

valuesEnum_t		ySourceEnum			= {3, {{YA_SYSTEM_TIME, "System time"}, {YA_STEP_COUNTER, "Step counter"}, {YA_MEASURES_COUNTER, "Measures counter"}}};

valuesEnum_t		paintModeEnum		= {2, {{0, "Heightmap"}, {1, "Intensity"}}};





pthread_mutex_t _mutex;

rfUint32 rf627_old_api_version()
{
    return RF627_OLD_API_VERSION;
}


int rf627_old_mutex_lock()
{
    return pthread_mutex_lock(&_mutex);
}

int rf627_old_mutex_trylock()
{
    rfInt error = pthread_mutex_trylock(&_mutex);
    if (error == 0) {
        /*... have the lock */
        return error;
    } else if (error == EBUSY) {
        /*... failed to get the lock because another thread holds lock */
        return error;
    } else if (error == EOWNERDEAD) {
        /*... got the lock, but the critical section state may not be consistent */
        return error;
    } else {
        switch (error) {
        case EAGAIN:
            /*... recursively locked too many times */
            return error;
            break;
        case EINVAL:
            /*... thread priority higher than mutex priority ceiling */
            return error;
            break;
        case ENOTRECOVERABLE:
            /*... mutex suffered EOWNERDEAD, and is no longer consistent */
            return error;
            break;
        default:
            /*...some other as yet undocumented failure reason */
            return error;
            break;
        }
    }
    return error;
}

int rf627_old_mutex_unlock()
{
    return pthread_mutex_unlock(&_mutex);
}



uint8_t rf627_old_search_by_service_protocol(vector_t *result, rfUint32 ip_addr)
{
    void* s;
    rf_sockaddr_in send_addr, from_addr;
    rf_socklen_t from_len;
    rfInt nret;
    rfSize RX_SIZE = rf627_protocol_old_get_size_of_header() + RF627_MAX_PAYLOAD_SIZE;
    rfUint8* RX = memory_platform.rf_calloc(1, RX_SIZE);
    rfSize TX_SIZE = rf627_protocol_old_get_size_of_header() + RF627_MAX_PAYLOAD_SIZE;
    rfUint8* TX =  memory_platform.rf_calloc(1, TX_SIZE);

    // pthread_mutex_lock(&_mutex);

    // create hello msg request
    rf627_old_header_msg_t hello_msg =
            rf627_protocol_old_create_hello_msg_request();

    // pack hello msg request to packet
    rfUint32 request_packet_size =
            rf627_protocol_old_pack_hello_msg_request_to_packet(
                (rfUint8*)TX, TX_SIZE, &hello_msg);

    s = network_platform.
            network_methods.create_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (*(rfInt32*)s == SOCKET_ERROR) {
        return 1;
    }

    network_platform.network_methods.set_socket_recv_timeout(
                s, RF627_RECV_TIMEOUT);

    nret = 1;
    network_platform.network_methods.set_socket_option(
                s, SOL_SOCKET, SO_BROADCAST, (char*)&nret, sizeof(nret));

    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.rf_s_addr = network_platform.network_methods.hton_long(INADDR_BROADCAST);
    send_addr.sin_port = network_platform.network_methods.hton_short(RF627_SERVICE_PORT);

    from_addr.sin_family = AF_INET;
    from_addr.sin_port = network_platform.network_methods.hton_short(0);
    from_addr.sin_addr.rf_s_addr = ip_addr;

    nret = network_platform.
            network_methods.socket_bind(s, &from_addr, sizeof(from_addr));

    if (nret != (rfSize)SOCKET_ERROR)
    {
        if (rf627_protocol_send_packet_by_udp(
                    s, TX, request_packet_size, &send_addr, 0, NULL))
        {
            from_len = sizeof(from_addr);
            memory_platform.rf_memset(&from_addr, 0, from_len);

            rfSize response_packet_size =
                    rf627_protocol_old_get_size_of_response_hello_packet();
            do
            {
                nret = network_platform.network_methods.recv_data_from(
                            s, RX, RX_SIZE, &from_addr, &from_len);

                if (nret == (rfSize)SOCKET_ERROR)
                {
                    //std::cout << "errno " << ::WSAGetLastError() << std::endl;
                }

                if (nret == response_packet_size)
                {
                    rfSize confirm_packet_size =
                            rf627_protocol_old_create_confirm_packet_from_response_packet(
                                TX, TX_SIZE, RX, RX_SIZE);
                    if(confirm_packet_size > 0)
                    {
                        from_addr.sin_port = send_addr.sin_port;
                        rf627_protocol_send_packet_by_udp(
                                    s, TX, confirm_packet_size, &from_addr, 0, NULL);
                    }

                    rf627_old_header_msg_t response_header_msg =
                            rf627_protocol_old_unpack_header_msg_from_hello_packet(RX);

                    rf627_old_device_info_t response_payload_msg =
                            rf627_protocol_old_unpack_payload_msg_from_hello_packet(RX);


                    rfBool existing = 0;

                    for (rfUint32 i = 0; i < vector_count(result); i++)
                    {
                        if(((scanner_base_t*)vector_get(result, i))->type == kRF627_OLD)
                        {
                            if (!memory_platform.
                                    rf_memcmp(((scanner_base_t*)vector_get(result, i))->
                                              rf627_old->factory_params.Network.MAC,
                                              response_payload_msg.hardware_address, 6))
                            {
                                existing = 1;
                                break;
                            }

                        }
                    }

                    if (!existing)
                    {
                        scanner_base_t* rf627 =
                                memory_platform.rf_calloc(1, sizeof(scanner_base_t));

                        rf627->type = kRF627_OLD;
                        rf627->rf627_old = rf627_old_create_from_hello_msg(
                                    &response_payload_msg, response_header_msg.msg_count + 1);
                        vector_add(result, rf627);
                    }
                }
            }
            while (nret > 0);
        }
        network_platform.network_methods.close_socket(s);
    }

//    _mx[0].unlock();

    memory_platform.rf_free(RX);
    memory_platform.rf_free(TX);

    return 0;
}

rf627_old_t* rf627_old_create_from_hello_msg(
        void* msg_info, rfUint16 init_msg_count)
{
    rf627_old_t* rf627_old = memory_platform.rf_calloc(1, sizeof (rf627_old_t));

    // copy device name
    memory_platform.rf_memcpy(
                rf627_old->user_params.general.name,
                ((rf627_old_device_info_t*)msg_info)->name, 64);

    // copy device_id
    rf627_old->factory_params.General.DeviceID =
            ((rf627_old_device_info_t*)msg_info)->device_id;

    // copy serial_number
    rf627_old->factory_params.General.Serial =
            ((rf627_old_device_info_t*)msg_info)->serial_number;

    // copy firmware_version
    rf627_old->factory_params.General.FirmWareVer =
            ((rf627_old_device_info_t*)msg_info)->firmware_version;

    // copy hardware_version
    rf627_old->factory_params.General.HardWareVer =
            ((rf627_old_device_info_t*)msg_info)->hardware_version;

    // copy config_version
    rf627_old->options.version =
            ((rf627_old_device_info_t*)msg_info)->config_version;

    // copy fsbl_version
    rf627_old->factory_params.General.FSBL_Version =
            ((rf627_old_device_info_t*)msg_info)->fsbl_version;

    // copy z_begin
    rf627_old->factory_params.General.BaseZ =
            ((rf627_old_device_info_t*)msg_info)->z_begin;

    // copy z_range
    rf627_old->factory_params.General.RangeZ =
            ((rf627_old_device_info_t*)msg_info)->z_range;

    // copy x_smr
    rf627_old->factory_params.General.RangeXStart =
            ((rf627_old_device_info_t*)msg_info)->x_smr;

    // copy x_emr
    rf627_old->factory_params.General.RangeXEnd =
            ((rf627_old_device_info_t*)msg_info)->x_emr;

    // copy eth_speed
    rf627_old->user_params.network.speed =
            ((rf627_old_device_info_t*)msg_info)->eth_speed;

    // copy ip_address
    rf627_old->user_params.network.ip_address =
            ((rf627_old_device_info_t*)msg_info)->ip_address;

    // copy net_mask
    rf627_old->user_params.network.net_mask =
            ((rf627_old_device_info_t*)msg_info)->net_mask;

    // copy gateway_ip
    rf627_old->user_params.network.gateway_ip =
            ((rf627_old_device_info_t*)msg_info)->gateway_ip;

    // copy host_ip
    rf627_old->user_params.network.host_ip =
            ((rf627_old_device_info_t*)msg_info)->host_ip;

    // copy stream_port
    rf627_old->user_params.network.stream_port =
            ((rf627_old_device_info_t*)msg_info)->stream_port;

    // copy http_port
    rf627_old->user_params.network.http_port =
            ((rf627_old_device_info_t*)msg_info)->http_port;

    // copy service_port
    rf627_old->user_params.network.service_port =
            ((rf627_old_device_info_t*)msg_info)->service_port;

    // copy hardware_address
    memory_platform.rf_memcpy(
                rf627_old->factory_params.Network.MAC,
                ((rf627_old_device_info_t*)msg_info)->hardware_address, 6);

//    // copy max_payload_size
//    rf627_old->user_params.network.max_payload_size =
//            ((rf627_old_device_info_t*)msg_info)->max_payload_size;

    // copy stream_enabled
    rf627_old->user_params.stream.enable =
            ((rf627_old_device_info_t*)msg_info)->stream_enabled;

    // copy stream_format
    rf627_old->user_params.stream.format =
            ((rf627_old_device_info_t*)msg_info)->stream_format;

    rf627_old->msg_count = init_msg_count;
    return rf627_old;
}


rfBool rf627_old_connect(rf627_old_t* scanner)
{
    rf_sockaddr_in recv_addr;
    rfInt nret;

    if (scanner->options.version > rf627_old_api_version())
    {
        iostream_platform.trace_error("This SDK version is not suitable");
        return -1;
    }

    scanner->m_svc_sock =
            network_platform.network_methods.create_socket(
                AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (*(rfInt32*)scanner->m_svc_sock == SOCKET_ERROR)
    {
        return -1;
    }

    network_platform.network_methods.set_socket_recv_timeout(
                scanner->m_svc_sock, RF627_RECV_TIMEOUT);


    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = 0;
    recv_addr.sin_addr.rf_s_addr = INADDR_ANY;

    nret = network_platform.network_methods.socket_bind(
                scanner->m_svc_sock, (rf_sockaddr_in*)&recv_addr, sizeof(recv_addr));
    if (nret == SOCKET_ERROR)
    {
        network_platform.network_methods.close_socket(scanner->m_svc_sock);
        scanner->m_svc_sock = NULL;
        return -1;
    }


    scanner->m_data_sock =
            network_platform.network_methods.create_socket(
                AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (*(rfInt32*)scanner->m_data_sock != SOCKET_ERROR)
    {
        nret = 1;
        network_platform.network_methods.set_socket_option(
                    scanner->m_data_sock, SOL_SOCKET, SO_REUSEADDR,
                    (rfChar*)&nret, sizeof(nret));

        network_platform.network_methods.set_socket_recv_timeout(
                    scanner->m_data_sock, RF627_RECV_TIMEOUT);
        recv_addr.sin_family = AF_INET;
        recv_addr.sin_port = network_platform.network_methods.hton_short(
                    scanner->user_params.network.stream_port);

        recv_addr.sin_addr.rf_s_addr = INADDR_ANY;

        nret = network_platform.network_methods.socket_bind(
                    scanner->m_data_sock, (rf_sockaddr_in*)&recv_addr, sizeof(recv_addr));
        if (nret == SOCKET_ERROR)
        {
            network_platform.network_methods.close_socket(scanner->m_data_sock);
            scanner->m_data_sock = NULL;
            return -1;
        }
    }
    else
    {
        iostream_platform.trace_error("Create data socket error");
        return -1;
    }


    return 0;
}

void rf627_old_disconnect(rf627_old_t* scanner)
{
    if (scanner->m_svc_sock != NULL &&
            *(rfInt32*)scanner->m_svc_sock != SOCKET_ERROR)
    {
        network_platform.network_methods.close_socket(scanner->m_svc_sock);
        scanner->m_svc_sock = NULL;
    }
    if (scanner->m_data_sock != NULL &&
            *(rfInt32*)scanner->m_data_sock != SOCKET_ERROR)
    {
        network_platform.network_methods.close_socket(scanner->m_data_sock);
        scanner->m_data_sock = NULL;
    }
}

rf627_old_profile_t* rf627_old_get_profile(rf627_old_t* scanner)
{

    rfSize RX_SIZE = rf627_protocol_old_get_size_of_header() + RF627_MAX_PAYLOAD_SIZE;
    rfUint8* RX = memory_platform.rf_calloc(1, RX_SIZE);
    rfSize TX_SIZE = rf627_protocol_old_get_size_of_header() + RF627_MAX_PAYLOAD_SIZE;
    rfUint8* TX =  memory_platform.rf_calloc(1, TX_SIZE);

//    const rfInt msg_size = sizeof(rf627_old_stream_msg_t);
//    const rfInt max_data_len = msg_size +
//            RF627_EXT_PROFILE_SIZE * sizeof(uint16_t) * 2 +
//            RF627_EXT_PROFILE_SIZE * sizeof(uint8_t);

    //std::cout << __LINE__ << " _mx[1].lock();" << std::endl << std::flush;
    //pthread_mutex_lock(&_mutex);



    rfInt nret = network_platform.network_methods.recv_data(
                scanner->m_data_sock, RX, RX_SIZE);
    if(nret > 0)
    {
        rfSize profile_header_size =
                rf627_protocol_old_get_size_of_response_profile_header_packet();

        rf627_old_profile_t* profile;
        profile = memory_platform.rf_calloc(1, sizeof(rf627_old_profile_t));

        profile->header = rf627_protocol_old_unpack_header_msg_from_profile_packet(RX);

        if(profile->header.serial_number == scanner->factory_params.General.Serial)
        {
            rfSize confirm_packet_size =
                    rf627_protocol_old_create_confirm_packet_from_response_profile_packet(
                        TX, TX_SIZE, RX, RX_SIZE);
            if(confirm_packet_size > 0)
            {
                network_platform.network_methods.send_tcp_data(
                            scanner->m_data_sock, TX, TX_SIZE);
            }


            rfInt16 x;
            rfUint16 z;

            rfUint32 pt_count;
            switch (profile->header.data_type)
            {
            case DTY_PixelsNormal:
                pt_count = RF627_PROFILE_SIZE;
                profile->pixels_format.pixels_count = pt_count;
                profile->pixels_format.pixels =
                        memory_platform.rf_calloc(pt_count, sizeof (rfUint16));
                if (profile->header.flags & 0x01){
                    profile->intensity_count = pt_count;
                    profile->intensity =
                            memory_platform.rf_calloc(pt_count, sizeof (rfUint8));
                }
                break;
            case DTY_ProfileNormal:
                pt_count = RF627_PROFILE_SIZE;
                profile->profile_format.points_count = pt_count;
                profile->profile_format.points =
                        memory_platform.rf_calloc(pt_count, sizeof (rf627_old_point_t));
                if (profile->header.flags & 0x01){
                    profile->intensity_count = pt_count;
                    profile->intensity =
                            memory_platform.rf_calloc(pt_count, sizeof (rfUint8));
                }
                break;
            case DTY_PixelsInterpolated:
                pt_count = RF627_EXT_PROFILE_SIZE;
                profile->pixels_format.pixels_count = pt_count;
                profile->pixels_format.pixels =
                        memory_platform.rf_calloc(pt_count, sizeof (rfUint16));
                if (profile->header.flags & 0x01){
                    profile->intensity_count = pt_count;
                    profile->intensity =
                            memory_platform.rf_calloc(pt_count, sizeof (rfUint8));
                }
                break;
            case DTY_ProfileInterpolated:
                pt_count = RF627_EXT_PROFILE_SIZE;
                profile->profile_format.points_count = pt_count;
                profile->profile_format.points =
                        memory_platform.rf_calloc(pt_count, sizeof (rf627_old_point_t));
                if (profile->header.flags & 0x01){
                    profile->intensity_count = pt_count;
                    profile->intensity =
                            memory_platform.rf_calloc(pt_count, sizeof (rfUint8));
                }
                break;
            }

            for (rfUint32 i=0; i<pt_count; i++)
            {
                rf627_old_point_t pt;
                switch (profile->header.data_type)
                {
                case DTY_ProfileNormal:
                case DTY_ProfileInterpolated:
                    z = *(rfUint16*)(&RX[profile_header_size + i*4 + 2]);
                    if (/*_fixed_result ||*/ z > 0)
                    {
                        x = *(rfInt16*)(&RX[profile_header_size + i*4]);
                        pt.x = (rfDouble)(x) * (rfDouble)(profile->header.xemr) /
                                (rfDouble)(profile->header.discrete_value);
                        pt.z = (rfDouble)(z) * (rfDouble)(profile->header.zmr) /
                                (rfDouble)(profile->header.discrete_value);
                    }
                    break;
                case DTY_PixelsNormal:
                case DTY_PixelsInterpolated:
                    z = *(rfUint16*)(&RX[profile_header_size + i*2]);
                    pt.x = i;

                    profile->pixels_format.pixels[i] = z;
                    pt.z = (rfDouble)(z) / (rfDouble)(profile->header.discrete_value);

                    break;
                }
                if (z > 0)
                {
                    profile->profile_format.points[i] = pt;
                    if (profile->header.flags & 0x01)
                    {
                        profile->intensity[i] = RX[profile_header_size + pt_count*4 + i];
                    }
                }
            }
            //_mx[1].unlock();
            memory_platform.rf_free(RX);
            memory_platform.rf_free(TX);
            return profile;
        }
    }
    return NULL;


//    if (nret < msg_size) {
//        //dprint("get_result!");
//        //_mx[1].unlock();
//        return NULL;
//    }

//    if (profile_header.data_type < DTY_PixelsNormal || msg->data_type > DTY_ProfileInterpolated) {
//        //_mx[1].unlock();
//        return NULL;
//    }



}

parameter_t* create_param_from_type(const rfChar* type)
{
    parameter_t* p = NULL;
    if(rf_strcmp(type, pvtKey[PVT_UINT]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->val_uint = memory_platform.rf_calloc(1, sizeof (value_uint32_t));
        p->base.type = pvtKey[PVT_UINT];
//        rfUint16 len = rf_strlen(type) + 1;
//        p->base.type = memory_platform.rf_calloc(1, sizeof(rfChar) * len);
//        memory_platform.rf_memcpy((void*)p->base.type, type, len);
    }else if(rf_strcmp(type, pvtKey[PVT_UINT64]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->val_uint64 = memory_platform.rf_calloc(1, sizeof (value_uint64_t));
        p->base.type = pvtKey[PVT_UINT64];
    }else if(rf_strcmp(type, pvtKey[PVT_INT]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->val_int = memory_platform.rf_calloc(1, sizeof (value_uint32_t));
        p->base.type = pvtKey[PVT_INT];
    }else if(rf_strcmp(type, pvtKey[PVT_INT64]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->val_int64 = memory_platform.rf_calloc(1, sizeof (value_int64_t));
        p->base.type = pvtKey[PVT_INT64];
    }else if(rf_strcmp(type, pvtKey[PVT_FLOAT]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->val_flt = memory_platform.rf_calloc(1, sizeof (value_flt_t));
        p->base.type = pvtKey[PVT_FLOAT];
    }else if(rf_strcmp(type, pvtKey[PVT_DOUBLE]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->val_dbl = memory_platform.rf_calloc(1, sizeof (value_dbl_t));
        p->base.type = pvtKey[PVT_DOUBLE];
    }else if(rf_strcmp(type, pvtKey[PVT_ARRAY_UINT32]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->arr_uint = memory_platform.rf_calloc(1, sizeof (value_uint32_t));
        p->base.type = pvtKey[PVT_ARRAY_UINT32];
    }else if(rf_strcmp(type, pvtKey[PVT_ARRAY_UINT64]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->arr_uint64 = memory_platform.rf_calloc(1, sizeof (array_uint64_t));
        p->base.type = pvtKey[PVT_ARRAY_UINT64];
    }else if(rf_strcmp(type, pvtKey[PVT_ARRAY_INT32]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->arr_int = memory_platform.rf_calloc(1, sizeof (value_uint32_t));
        p->base.type = pvtKey[PVT_ARRAY_INT32];
    }else if(rf_strcmp(type, pvtKey[PVT_ARRAY_INT64]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->arr_int64 = memory_platform.rf_calloc(1, sizeof (array_int64_t));
        p->base.type = pvtKey[PVT_ARRAY_INT64];
    }else if(rf_strcmp(type, pvtKey[PVT_ARRAY_FLT]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->arr_flt = memory_platform.rf_calloc(1, sizeof (array_flt_t));
        p->base.type = pvtKey[PVT_ARRAY_FLT];
    }else if(rf_strcmp(type, pvtKey[PVT_ARRAY_DBL]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->arr_dbl = memory_platform.rf_calloc(1, sizeof (array_dbl_t));
        p->base.type = pvtKey[PVT_ARRAY_DBL];
    }else if(rf_strcmp(type, pvtKey[PVT_STRING]) == 0)
    {
        p = memory_platform.rf_calloc(1, sizeof (parameter_t));
        p->val_str = memory_platform.rf_calloc(1, sizeof (value_str_t));
        p->base.type = pvtKey[PVT_STRING];
    }
    return p;
}

rfInt* get_value_by_key_from_enum(valuesEnum_t* values_enum, char* key)
{
    rfInt* result = NULL;
    for (rfInt32 idx = 0; idx < values_enum->recCount; idx++)
    {
        if (rf_strcmp(values_enum->rec[idx].key, key) == 0)
        {
            result = &values_enum->rec[idx].value;
        }
    }
    return result;
}

rfBool set_value_by_key(parameter_t* p, char* key)
{
    if (rf_strcmp(p->base.type, pvtKey[PVT_INT]))
    {
        for (rfInt32 idx = 0; idx < p->val_int->enumValues->recCount; idx++)
        {
            if (rf_strcmp(p->val_int->enumValues->rec[idx].key, key) == 0)
            {
                p->val_int->value = p->val_int->enumValues->rec[idx].value;
                return 0;
            }
        }
    }else
    if (rf_strcmp(p->base.type, pvtKey[PVT_UINT]))
    {
        for (rfInt32 idx = 0; idx < p->val_uint->enumValues->recCount; idx++)
        {
            if (rf_strcmp(p->val_uint->enumValues->rec[idx].key, key) == 0)
            {
                p->val_uint->value = p->val_uint->enumValues->rec[idx].value;
                return 0;
            }
        }
    }else
    if (rf_strcmp(p->base.type, pvtKey[PVT_INT64]))
    {
        for (rfInt32 idx = 0; idx < p->val_int64->enumValues->recCount; idx++)
        {
            if (rf_strcmp(p->val_int64->enumValues->rec[idx].key, key) == 0)
            {
                p->val_int64->value = p->val_int64->enumValues->rec[idx].value;
                return 0;
            }
        }
    }else
    if (rf_strcmp(p->base.type, pvtKey[PVT_UINT64]))
    {
        for (rfInt32 idx = 0; idx < p->val_uint64->enumValues->recCount; idx++)
        {
            if (rf_strcmp(p->val_uint64->enumValues->rec[idx].key, key) == 0)
            {
                p->val_uint64->value = p->val_uint64->enumValues->rec[idx].value;
                return 0;
            }
        }
    }

    return 1;
}



rfBool rf627_old_read_params_from_scanner(rf627_old_t* scanner)
{

    rfSize RX_SIZE = rf627_protocol_old_get_size_of_header() + RF627_MAX_PAYLOAD_SIZE;
    rfUint8* RX = memory_platform.rf_calloc(1, RX_SIZE);
    rfSize TX_SIZE = rf627_protocol_old_get_size_of_header() + RF627_MAX_PAYLOAD_SIZE;
    rfUint8* TX =  memory_platform.rf_calloc(1, TX_SIZE);


    rf_sockaddr_in send_addr;
    rfBool ret = 1;

    //std::cout << __LINE__ << " _mx[0].lock();" << std::endl << std::flush;
    //_mx[0].lock();

    // create read_params msg request
    rf627_old_header_msg_t read_user_params_msg =
            rf627_protocol_old_create_read_user_params_msg_request(
                kRF627_OLD_PROTOCOL_HEADER_CONFIRMATION_ON,
                scanner->factory_params.General.Serial,
                scanner->msg_count);

    // pack hello msg request to packet
    rfUint32 request_packet_size =
            rf627_protocol_old_pack_read_user_params_msg_request_to_packet(
                (rfUint8*)TX, TX_SIZE, &read_user_params_msg);

    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.rf_s_addr = scanner->user_params.network.ip_address;
    send_addr.sin_port = network_platform.network_methods.hton_short(
                scanner->user_params.network.service_port);



    if (rf627_protocol_send_packet_by_udp(
                scanner->m_svc_sock, TX, request_packet_size, &send_addr, 0, NULL))
    {
        scanner->msg_count++;
        const rfInt data_len =
                rf627_protocol_old_get_size_of_response_read_user_params_packet();
        rfInt nret = network_platform.network_methods.recv_data(
                    scanner->m_svc_sock, RX, data_len);
        if (nret == data_len)
        {
            rfSize confirm_packet_size =
                    rf627_protocol_old_create_confirm_packet_from_response_packet(
                        TX, TX_SIZE, RX, RX_SIZE);
            if(confirm_packet_size > 0)
            {
                network_platform.network_methods.send_tcp_data(
                            scanner->m_data_sock, TX, TX_SIZE);
            }

            rf627_old_header_msg_t header =
                    rf627_protocol_old_unpack_header_msg_from_user_params_packet(RX);

            if(header.serial_number == scanner->factory_params.General.Serial)
            {
                scanner->user_params =
                    rf627_protocol_old_unpack_payload_msg_from_user_params_packet(RX);

                vector_init(&scanner->params_list);



                rfUint16 index = 0;
                parameter_t* p = create_param_from_type(pvtKey[PVT_STRING]);
                p->base.name = parameter_names_array[USER_GENERAL_DEVICE_NAME];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 0;
                p->base.size = rf_strlen(scanner->user_params.general.name) + 1;
                p->base.units = "";

                p->val_str->value = memory_platform.rf_calloc(1, sizeof(rfChar) * p->base.size);
                memory_platform.rf_memcpy(
                            (void*)p->val_str->value,
                            scanner->user_params.general.name,
                            p->base.size);
                p->val_str->maxLen = sizeof (scanner->user_params.general.name);
                p->val_str->defValue = "SERVICE CONFIGURATION, contact with manufacturer";
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_GENERAL_SAVE_LOG];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 64;
                p->base.size = sizeof(scanner->user_params.general.save_log_to_spi);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.general.save_log_to_spi;
                p->val_uint->min = 0;
                p->val_uint->max = 0;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                rfInt* def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_FPGA_TEMP];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 192;
                p->base.size = sizeof(scanner->user_params.sysmon.fpga_temp);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.fpga_temp;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_SYSMON_PARAMS_CHANGED];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 194;
                p->base.size = sizeof(scanner->user_params.sysmon.params_changed);
                p->base.units = "°C";

                p->val_uint->value = scanner->user_params.sysmon.params_changed;
                p->val_uint->min = 0;
                p->val_uint->max = 7;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_00];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 195;
                p->base.size = sizeof(scanner->user_params.sysmon.sens00_temp);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens00_temp;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_00_MAX];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 197;
                p->base.size = sizeof(scanner->user_params.sysmon.sens00_max);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens00_max;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_00_MIN];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 199;
                p->base.size = sizeof(scanner->user_params.sysmon.sens00_min);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens00_min;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_01];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 201;
                p->base.size = sizeof(scanner->user_params.sysmon.sens01_temp);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens01_temp;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_01_MAX];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 203;
                p->base.size = sizeof(scanner->user_params.sysmon.sens01_max);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens01_max;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_01_MIN];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 205;
                p->base.size = sizeof(scanner->user_params.sysmon.sens01_min);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens01_min;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_10];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 207;
                p->base.size = sizeof(scanner->user_params.sysmon.sens10_temp);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens10_temp;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_10_MAX];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 209;
                p->base.size = sizeof(scanner->user_params.sysmon.sens10_max);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens10_max;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_10_MIN];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 211;
                p->base.size = sizeof(scanner->user_params.sysmon.sens10_min);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens10_min;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_11];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 213;
                p->base.size = sizeof(scanner->user_params.sysmon.sens11_temp);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens11_temp;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_11_MAX];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 215;
                p->base.size = sizeof(scanner->user_params.sysmon.sens11_max);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens11_max;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_FLOAT]);
                p->base.name = parameter_names_array[USER_SYSMON_TEMP_SENS_11_MIN];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 217;
                p->base.size = sizeof(scanner->user_params.sysmon.sens11_min);
                p->base.units = "°C";

                p->val_flt->value = scanner->user_params.sysmon.sens11_min;
                p->val_flt->min = -100;
                p->val_flt->max = 150;
                p->val_flt->step = 0;
                p->val_flt->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_COMPATIBILITY_RF625_ENABLED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 274;
                p->base.size = sizeof(scanner->user_params.rf625compat.enable);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.rf625compat.enable;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);


                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_COMPATIBILITY_RF625_TCP_PORT];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 275;
                p->base.size = sizeof(scanner->user_params.rf625compat.tcp_port);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.rf625compat.tcp_port;
                p->val_uint->min = 0;
                p->val_uint->max = 65535;
                p->val_uint->step = 0;
                p->val_uint->defValue = 620;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_SENSOR_DOUBLE_SPEED_ENABLED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 309;
                p->base.size = sizeof(scanner->user_params.sensor.dhs);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.sensor.dhs;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);


                //gain_analog
                //gain_digital


                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_SENSOR_EXPOSURE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 312;
                p->base.size = sizeof(scanner->user_params.sensor.exposure);
                p->base.units = "ns";

                p->val_uint->value = scanner->user_params.sensor.exposure;
                p->val_uint->min = 3000;
                p->val_uint->max = 300000000;
                p->val_uint->step = 100;
                p->val_uint->defValue = 300000;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_SENSOR_MAX_EXPOSURE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 316;
                p->base.size = sizeof(scanner->user_params.sensor.max_exposure);
                p->base.units = "ns";

                p->val_uint->value = scanner->user_params.sensor.max_exposure;
                p->val_uint->min = 3000;
                p->val_uint->max = 2147483647;
                p->val_uint->step = 0;
                p->val_uint->defValue = 1443298;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_SENSOR_FRAME_RATE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 320;
                p->base.size = sizeof(scanner->user_params.sensor.frame_rate);
                p->base.units = "Hz";

                p->val_uint->value = scanner->user_params.sensor.frame_rate;
                p->val_uint->min = 0;
                p->val_uint->max = 20000;
                p->val_uint->step = 0;
                p->val_uint->defValue = 485;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_SENSOR_MAX_FRAME_RATE];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 324;
                p->base.size = sizeof(scanner->user_params.sensor.max_frame_rate);
                p->base.units = "Hz";

                p->val_uint->value = scanner->user_params.sensor.max_frame_rate;
                p->val_uint->min = 0;
                p->val_uint->max = 20000;
                p->val_uint->step = 0;
                p->val_uint->defValue = 485;
                vector_add(scanner->params_list, p);


                // exposure_hdr_mode


                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_SENSOR_AUTO_EXPOSURE_ENABLED];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 329;
                p->base.size = sizeof(scanner->user_params.sensor.auto_exposure);
                p->base.units = "Hz";

                p->val_uint->value = scanner->user_params.sensor.auto_exposure;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);


                // column_edr_mode
                // column_exposure_div
                // column_exposure_max_div


                //roi
                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_ROI_ENABLED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 392;
                p->base.size = sizeof(scanner->user_params.roi.enable);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.roi.enable;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_ROI_ACTIVE];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 393;
                p->base.size = sizeof(scanner->user_params.roi.active);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.roi.active;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_ROI_SIZE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 394;
                p->base.size = sizeof(scanner->user_params.roi.size);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.roi.size;
                p->val_uint->min = 1;
                p->val_uint->max = 1024;
                p->val_uint->step = 8;
                p->val_uint->defValue = 64;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_ROI_POS_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 396;
                p->base.size = sizeof(scanner->user_params.roi.position_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.roi.position_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_ROI_POS];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 397;
                p->base.size = sizeof(scanner->user_params.roi.manual_position);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.roi.manual_position;
                p->val_uint->min = 0;
                p->val_uint->max = 1280;
                p->val_uint->step = 0;
                p->val_uint->defValue = 100;
                vector_add(scanner->params_list, p);

                //auto_position

                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_ROI_REQ_PROF_SIZE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 401;
                p->base.size = sizeof(scanner->user_params.roi.required_profile_size);
                p->base.units = "points";

                p->val_uint->value = scanner->user_params.roi.required_profile_size;
                p->val_uint->min = 0;
                p->val_uint->max = 1280;
                p->val_uint->step = 64;
                p->val_uint->defValue = 320;
                vector_add(scanner->params_list, p);


                //network
                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_NETWORK_SPEED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 483;
                p->base.size = sizeof(scanner->user_params.network.speed);
                p->base.units = "points";

                p->val_uint->value = scanner->user_params.network.speed;
                p->val_uint->min = 10;
                p->val_uint->max = 1000;
                p->val_uint->step = 0;
                p->val_uint->defValue = 1000;
                p->val_uint->enumValues = &netSpeedEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "1000");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_NETWORK_AUTO_NEG];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 485;
                p->base.size = sizeof(scanner->user_params.network.autonegotiation);
                p->base.units = "points";

                p->val_uint->value = scanner->user_params.network.autonegotiation;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->defValue = 1;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "true");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_NETWORK_IP];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 486;
                p->base.size = sizeof(scanner->user_params.network.ip_address);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.network.ip_address;
                p->val_uint->min = 0;
                p->val_uint->max = 0xFFFFFFFF;
                p->val_uint->step = 64;
                p->val_uint->defValue = 0xC0A8011E;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_NETWORK_MASK];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 490;
                p->base.size = sizeof(scanner->user_params.network.ip_address);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.network.ip_address;
                p->val_uint->min = 0;
                p->val_uint->max = 0xFFFFFFFF;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0xFFFFFF00;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_NETWORK_GATEWAY];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 494;
                p->base.size = sizeof(scanner->user_params.network.gateway_ip);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.network.gateway_ip;
                p->val_uint->min = 0;
                p->val_uint->max = 0xFFFFFFFF;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0xC0A80101;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_NETWORK_HOST_IP];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 498;
                p->base.size = sizeof(scanner->user_params.network.host_ip);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.network.host_ip;
                p->val_uint->min = 0;
                p->val_uint->max = 0xFFFFFFFF;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0xC0A80102;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_NETWORK_HOST_PORT];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 502;
                p->base.size = sizeof(scanner->user_params.network.stream_port);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.network.stream_port;
                p->val_uint->min = 0;
                p->val_uint->max = 65535;
                p->val_uint->step = 0;
                p->val_uint->defValue = 50001;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_NETWORK_WEB_PORT];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 504;
                p->base.size = sizeof(scanner->user_params.network.http_port);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.network.http_port;
                p->val_uint->min = 0;
                p->val_uint->max = 65535;
                p->val_uint->step = 0;
                p->val_uint->defValue = 80;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_NETWORK_SERVICE_PORT];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 506;
                p->base.size = sizeof(scanner->user_params.network.service_port);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.network.service_port;
                p->val_uint->min = 0;
                p->val_uint->max = 65535;
                p->val_uint->step = 0;
                p->val_uint->defValue = 50011;
                vector_add(scanner->params_list, p);


                //stream
                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_STREAMS_UDP_ENABLE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 576;
                p->base.size = sizeof(scanner->user_params.stream.enable);
                p->base.units = "points";

                p->val_uint->value = scanner->user_params.stream.enable;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->defValue = 1;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_STREAMS_FORMAT];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 577;
                p->base.size = sizeof(scanner->user_params.stream.format);
                p->base.units = "points";

                p->val_uint->value = scanner->user_params.stream.format;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->defValue = 1;
                p->val_uint->enumValues = &streamsFormatEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Profile");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_STREAMS_INCLUDE_INTENSITY];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 579;
                p->base.size = sizeof(scanner->user_params.stream.include_intensivity);
                p->base.units = "points";

                p->val_uint->value = scanner->user_params.stream.include_intensivity;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                //image_processing
                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_PROCESSING_THRESHOLD];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 611;
                p->base.size = sizeof(scanner->user_params.image_processing.brightness_threshold);
                p->base.units = "%";

                p->val_uint->value = scanner->user_params.image_processing.brightness_threshold;
                p->val_uint->min = 0;
                p->val_uint->max = 100;
                p->val_uint->step = 0;
                p->val_uint->defValue = 10;
                vector_add(scanner->params_list, p);

                //filter_width

                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_PROCESSING_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 616;
                p->base.size = sizeof(scanner->user_params.image_processing.processing_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.image_processing.processing_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &processingModeEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "High accuracy");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);

                //reduce_noise

                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_PROCESSING_PROF_PER_SEC];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 618;
                p->base.size = sizeof(scanner->user_params.image_processing.frame_rate);
                p->base.units = "pps";

                p->val_uint->value = scanner->user_params.image_processing.frame_rate;
                p->val_uint->min = 0;
                p->val_uint->max = 20000;
                p->val_uint->step = 0;
                p->val_uint->defValue = 485;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_PROCESSING_MEDIAN_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 622;
                p->base.size = sizeof(scanner->user_params.image_processing.median_filter_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.image_processing.median_filter_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &medianFilterEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Off");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_PROCESSING_BILATERAL_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 623;
                p->base.size = sizeof(scanner->user_params.image_processing.bilateral_filter_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.image_processing.bilateral_filter_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &bilateralFilterEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Off");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_PROCESSING_PEAK_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 624;
                p->base.size = sizeof(scanner->user_params.image_processing.peak_select_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.image_processing.peak_select_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 7;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &peakModeEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Max intensity");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_PROCESSING_FLIP];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 625;
                p->base.size = sizeof(scanner->user_params.image_processing.profile_flip);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.image_processing.profile_flip;
                p->val_uint->min = 0;
                p->val_uint->max = 7;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &flipEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "no");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                //laser
                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_LASER_ENABLED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 682;
                p->base.size = sizeof(scanner->user_params.laser.enable);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.laser.enable;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_LASER_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 683;
                p->base.size = sizeof(scanner->user_params.laser.level_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.laser.level_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &laserModeEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Expose sync");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_LASER_VALUE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 684;
                p->base.size = sizeof(scanner->user_params.laser.level);
                p->base.units = "%";

                p->val_uint->value = scanner->user_params.laser.level;
                p->val_uint->min = 0;
                p->val_uint->max = 100;
                p->val_uint->step = 5;
                p->val_uint->defValue = 50;
                vector_add(scanner->params_list, p);


                //inputs
                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_PRESET];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 718;
                p->base.size = sizeof(scanner->user_params.inputs.preset_index);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.inputs.preset_index;
                p->val_uint->min = 0;
                p->val_uint->max = 11;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_PARAMS_MASK];
                p->base.access = patKey[PAT_READ_ONLY];
                p->base.index = index++;
                p->base.offset = 719 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].params_mask);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].params_mask;
                p->val_uint->min = 0;
                p->val_uint->max = 511;
                p->val_uint->step = 0;
                p->val_uint->defValue = 0;
                vector_add(scanner->params_list, p);


                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_1_ENABLED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 721 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].in1_enable);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].in1_enable;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_1_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 722 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].in1_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].in1_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 3;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &input1ModeEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Rise");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_1_DELAY];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 723 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].in1_delay);
                p->base.units = "ns";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].in1_delay ;
                p->val_uint->min = 30;
                p->val_uint->max = 1000000000;
                p->val_uint->step = 10;
                p->val_uint->defValue = 30;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_1_DIVIDER];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 727 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].in1_decimation);
                p->base.units = "ns";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].in1_decimation ;
                p->val_uint->min = 1;
                p->val_uint->max = 4096;
                p->val_uint->step = 0;
                p->val_uint->defValue = 1;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_2_ENABLED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 728 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].in2_enable);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].in2_enable;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_2_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 729 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].in2_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].in2_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &input2ModeEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Level");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_2_INVERSE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 730 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].in2_invert);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].in2_invert;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);


                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_3_ENABLED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 731 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].in3_enable);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].in3_enable;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_INPUTS_3_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 732 + 26*scanner->user_params.inputs.preset_index;
                p->base.size = sizeof(scanner->user_params.inputs.params[
                                      scanner->user_params.inputs.preset_index].in3_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.inputs.params[
                        scanner->user_params.inputs.preset_index].in3_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &input3ModeEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Rise");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);


                //outputs
                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_1_ENABLED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1063;
                p->base.size = sizeof(scanner->user_params.outputs.out1_enable);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.outputs.out1_enable;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_1_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1064;
                p->base.size = sizeof(scanner->user_params.outputs.out1_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.outputs.out1_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 10;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &outputModeEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Exposure start");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_1_DELAY];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1065;
                p->base.size = sizeof(scanner->user_params.outputs.out1_delay);
                p->base.units = "ns";

                p->val_uint->value = scanner->user_params.outputs.out1_delay ;
                p->val_uint->min = 220;
                p->val_uint->max = 1000000000;
                p->val_uint->step = 10;
                p->val_uint->defValue = 220;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_1_PULSE_WIDTH];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1069;
                p->base.size = sizeof(scanner->user_params.outputs.out1_pulse_width);
                p->base.units = "ns";

                p->val_uint->value = scanner->user_params.outputs.out1_pulse_width ;
                p->val_uint->min = 10;
                p->val_uint->max = 10000;
                p->val_uint->step = 10;
                p->val_uint->defValue = 10;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_1_INVERSE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1073;
                p->base.size = sizeof(scanner->user_params.outputs.out1_invert);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.outputs.out1_invert;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_2_ENABLED];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1074;
                p->base.size = sizeof(scanner->user_params.outputs.out2_enable);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.outputs.out2_enable;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_2_MODE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1075;
                p->base.size = sizeof(scanner->user_params.outputs.out2_mode);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.outputs.out2_mode;
                p->val_uint->min = 0;
                p->val_uint->max = 10;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &outputModeEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "Exposure start");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_2_DELAY];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1076;
                p->base.size = sizeof(scanner->user_params.outputs.out2_delay);
                p->base.units = "ns";

                p->val_uint->value = scanner->user_params.outputs.out2_delay ;
                p->val_uint->min = 220;
                p->val_uint->max = 1000000000;
                p->val_uint->step = 10;
                p->val_uint->defValue = 220;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_2_PULSE_WIDTH];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1080;
                p->base.size = sizeof(scanner->user_params.outputs.out2_pulse_width);
                p->base.units = "ns";

                p->val_uint->value = scanner->user_params.outputs.out2_pulse_width ;
                p->val_uint->min = 10;
                p->val_uint->max = 10000;
                p->val_uint->step = 10;
                p->val_uint->defValue = 10;
                vector_add(scanner->params_list, p);



                p = create_param_from_type(pvtKey[PVT_UINT]);
                p->base.name = parameter_names_array[USER_OUTPUTS_2_INVERSE];
                p->base.access = patKey[PAT_WRITE];
                p->base.index = index++;
                p->base.offset = 1084;
                p->base.size = sizeof(scanner->user_params.outputs.out2_invert);
                p->base.units = "";

                p->val_uint->value = scanner->user_params.outputs.out2_invert;
                p->val_uint->min = 0;
                p->val_uint->max = 1;
                p->val_uint->step = 0;
                p->val_uint->enumValues = &boolEnum;
                def = get_value_by_key_from_enum(p->val_uint->enumValues, "false");
                if (def != NULL)
                    p->val_uint->defValue = *def;
                else p->val_uint->defValue = p->val_uint->value;
                vector_add(scanner->params_list, p);

                ret = 0;
            }


        }
    }
//    _mx[0].unlock();

    memory_platform.rf_free(RX);
    memory_platform.rf_free(TX);
    return ret;
}

rfBool rf627_old_write_params_to_scanner(rf627_old_t* scanner)
{
    return 0;
}

parameter_t* rf627_old_get_parameter(
        rf627_old_t* scanner, const rfChar* param_name)
{
    for(rfSize i = 0; i < vector_count(scanner->params_list); i++)
    {
        parameter_t* p = vector_get(scanner->params_list, i);
        if (rf_strcmp(p->base.name, param_name) == 0)
        {
            return p;
        }
    }
    return NULL;
}

