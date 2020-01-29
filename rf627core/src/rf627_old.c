#include "rf627_core.h"
#include "srvc_proto.h"

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


pthread_mutex_t _mutex;

uint32_t rf627_old_api_version()
{
    return RF627_OLD_API_VERSION;
}


int rf627_old_mutex_lock()
{
    return pthread_mutex_lock(&_mutex);
}

int rf627_old_mutex_trylock()
{
    int error = pthread_mutex_trylock(&_mutex);
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
    rfInt32 nret;
    rfUint8* RX = memory_platform.rf_calloc(1,
                srvc_proto_627_old_get_header_size() + RF627_MAX_PAYLOAD_SIZE);
    rfUint8* TX =  memory_platform.rf_calloc(1,
                srvc_proto_627_old_get_header_size() + RF627_MAX_PAYLOAD_SIZE);

//    pthread_mutex_lock(&_mutex);

    rf627_old_service_msg_t* send_header = (rf627_old_service_msg_t*)TX;

    srvc_proto_627_old_create_hello_header(
                (rfUint8*)send_header, srvc_proto_627_old_get_header_size());

    s = network_platform.
            network_methods.create_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (*(rfInt32*)s == SOCKET_ERROR) {
        return 1;
    }
    network_platform.network_methods.set_socket_recv_timeout(s, RF627_RECV_TIMEOUT);
    nret = 1;
    network_platform.network_methods.set_socket_option(s, SOL_SOCKET, SO_BROADCAST, (char*)&nret, sizeof(nret));

    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.rf_s_addr = network_platform.network_methods.hton_long(INADDR_BROADCAST);
    send_addr.sin_port = network_platform.network_methods.hton_short(RF627_SERVICE_PORT);

    from_addr.sin_family = AF_INET;
    from_addr.sin_port = network_platform.network_methods.hton_short(0);
    from_addr.sin_addr.rf_s_addr = ip_addr;

    nret = network_platform.
            network_methods.socket_bind(s, &from_addr, sizeof(from_addr));

    if (nret != SOCKET_ERROR) {
        if (srvc_proto_627_old_send_message_by_udp(
                    s, TX, srvc_proto_627_old_get_header_size(), &send_addr, 0, NULL))
        {
            from_len = sizeof(from_addr);
            memory_platform.rf_memset(&from_addr, 0, from_len);

            const int data_len =
                    sizeof(rf627_old_service_msg_t) + sizeof(rf627_old_device_info_t);
            do
            {
                nret = network_platform.network_methods.recv_data_from(
                            s, RX, data_len, &from_addr, &from_len);
                if (nret == SOCKET_ERROR)
                {
                    //std::cout << "errno " << ::WSAGetLastError() << std::endl;
                }

                if (nret == data_len)
                {
                    rf627_old_service_msg_t *answ_header =
                            (rf627_old_service_msg_t*)&RX[0];

                    rf627_old_device_info_t* answ_payload =
                            (rf627_old_device_info_t*)&RX[
                                srvc_proto_627_old_get_header_size()];

                    rfUint32 size = srvc_proto_627_old_create_answer_packet(RX, nret,
                            TX, sizeof(srvc_proto_627_old_get_header_size()));
                    if(size > 0)
                    {
                        from_addr.sin_port = send_addr.sin_port;
                        srvc_proto_627_old_send_message_by_udp(
                                    s, TX, size, &from_addr, 0, NULL);
                    }


                    rfBool existing = 0;

                    for (rfUint32 i = 0; i < vector_count(result); i++)
                    {
                        if(((scanner_base_t*)vector_get(result, i))->type == kRF627_OLD)
                        {
                            if (!memory_platform.
                                    rf_memcmp(((scanner_base_t*)vector_get(result, i))->
                                              rf627_old->factory_params.Network.MAC,
                                              answ_payload->hardware_address, 6))
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
                                    answ_payload, answ_header->msg_count + 1);
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
        void* msg_info, uint16_t init_msg_count)
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
    int nret;

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

    rfUint8* RX = memory_platform.rf_calloc(1,
                srvc_proto_627_old_get_header_size() + RF627_MAX_PAYLOAD_SIZE);

    rf627_old_stream_msg_t* msg = (rf627_old_stream_msg_t*)&RX[0];

    const int msg_size = sizeof(rf627_old_stream_msg_t);
    const int max_data_len = msg_size +
            RF627_EXT_PROFILE_SIZE * sizeof(uint16_t) * 2 +
            RF627_EXT_PROFILE_SIZE * sizeof(uint8_t);

    int16_t x;
    uint16_t z;

    //std::cout << __LINE__ << " _mx[1].lock();" << std::endl << std::flush;
    //pthread_mutex_lock(&_mutex);

    int nret = network_platform.network_methods.recv_data(
                scanner->m_data_sock, RX, max_data_len);
    if (msg->flags & 0x80)
    {
        //TODO ACK
    }

    if (nret < msg_size) {
        //dprint("get_result!");
        //_mx[1].unlock();
        return NULL;
    }

    if (msg->data_type < DTY_PixelsNormal || msg->data_type > DTY_ProfileInterpolated) {
        //_mx[1].unlock();
        return NULL;
    }

    rf627_old_profile_t* profile;
    profile = memory_platform.rf_calloc(sizeof(rf627_old_profile_t), 1);

    memory_platform.rf_memcpy(&profile->header, msg, msg_size);

    rfUint32 pt_count;
    switch (msg->data_type)
    {
    case DTY_PixelsNormal:
        pt_count = RF627_PROFILE_SIZE;
        profile->pixels_format.pixels_count = pt_count;
        profile->pixels_format.pixels =
                memory_platform.rf_calloc(pt_count, sizeof (rfUint16));
        if (msg->flags & 0x01){
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
        if (msg->flags & 0x01){
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
        if (msg->flags & 0x01){
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
        if (msg->flags & 0x01){
            profile->intensity_count = pt_count;
            profile->intensity =
                    memory_platform.rf_calloc(pt_count, sizeof (rfUint8));
        }
        break;
    }

    for (rfUint32 i=0; i<pt_count; i++)
    {
        rf627_old_point_t pt;
        switch (msg->data_type)
        {
        case DTY_ProfileNormal:
        case DTY_ProfileInterpolated:
            z = *(rfUint16*)(&RX[msg_size + i*4 + 2]);
            if (/*_fixed_result ||*/ z > 0)
            {
                x = *(rfInt16*)(&RX[msg_size + i*4]);
                pt.x = (rfDouble)(x) * (rfDouble)(msg->xemr) / (rfDouble)(msg->discrete_value);
                pt.z = (rfDouble)(z) * (rfDouble)(msg->zmr) / (rfDouble)(msg->discrete_value);
            }
            break;
        case DTY_PixelsNormal:
        case DTY_PixelsInterpolated:
            z = *(rfUint16*)(&RX[msg_size + i*2]);
            pt.x = i;

            profile->pixels_format.pixels[i] = z;
            pt.z = (rfDouble)(z) / (rfDouble)(msg->discrete_value);

            break;
        }
        if (z > 0)
        {
            profile->profile_format.points[i] = pt;
            if (msg->flags & 0x01)
            {
                profile->intensity[i] = RX[msg_size + pt_count*4 + i];
            }
        }
    }
    //_mx[1].unlock();
    return profile;
}
