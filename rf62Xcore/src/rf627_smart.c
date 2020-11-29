#include "rf62X_sdk.h"
#include "rf627_protocol.h"
#include "iostream_platform.h"
#include "netwok_platform.h"
#include "memory_platform.h"
#include "custom_string.h"
#include "smartchannel.h"
#include "smartmsg.h"
#include <stdarg.h>
#include <stdio.h>

#include <mpack/mpack.h>
#include <smartutils.h>


#include<time.h>
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int answ_count = 0;
vector_t *search_result = NULL;
rfInt8 rf627_smart_get_hello_callback(char* data, uint32_t data_size, uint32_t device_id, void* rqst_msg)
{
    answ_count++;
    printf("%d - Answers were received. Received payload size: %d\n", answ_count, data_size);

    int32_t result = SMART_PARSER_RETURN_STATUS_NO_DATA;
    rfBool existing = FALSE;

    // Get params
    mpack_tree_t tree;
    mpack_tree_init_data(&tree, (const char*)data, data_size);
    mpack_tree_parse(&tree);
    if (mpack_tree_error(&tree) != mpack_ok)
    {
        result = SMART_PARSER_RETURN_STATUS_DATA_ERROR;
        mpack_tree_destroy(&tree);
        return result;
    }

    for (rfUint32 i = 0; i < vector_count(search_result); i++)
    {
        if(((scanner_base_t*)vector_get(search_result, i))->type == kRF627_SMART)
        {
            uint32_t serial = ((scanner_base_t*)vector_get(search_result, i))->rf627_smart->info_by_service_protocol.fact_general_serial;
            if (serial == device_id)
                existing = TRUE;
        }
    }

    if (!existing)
    {
        scanner_base_t* rf627 =
                memory_platform.rf_calloc(1, sizeof(scanner_base_t));

        rf627->type = kRF627_SMART;
        rf627->rf627_smart = rf627_smart_create_from_hello_msg(
                    data, data_size);
        vector_add(search_result, rf627);
    }

    mpack_tree_destroy(&tree);
    return TRUE;
}

rfInt8 rf627_smart_get_hello_timeout_callback()
{
    printf("get_hello_timeout\n");
}

uint8_t rf627_smart_search_by_service_protocol(vector_t *result, rfUint32 ip_addr, rfUint32 timeout)
{
    char config[1024];
    if (search_result != result && search_result != NULL)
    {
        while (vector_count(search_result) > 0) {
            vector_delete(search_result, vector_count(search_result)-1);
        }
        free (search_result); search_result = NULL;
    }
    search_result = result;
    unsigned char bytes[4];
    bytes[0] = ip_addr & 0xFF;
    bytes[1] = (ip_addr >> 8) & 0xFF;
    bytes[2] = (ip_addr >> 16) & 0xFF;
    bytes[3] = (ip_addr >> 24) & 0xFF;

    sprintf(config, "-dst_ip_addr %d.%d.%d.%d "
                    "-host_ip_addr %d.%d.%d.%d "
                    "-in_udp_port 50011 "
                    "-max_packet_size 65535 "
                    "-out_udp_port 50011 "
                    "-socket_timeout 100 "
                    "-max_data_size 350000",
            bytes[3], bytes[2], bytes[1], 255,
            bytes[3], bytes[2], bytes[1], bytes[0]);

    smart_channel channel;

    smart_channel_init(&channel, config);


    smart_msg_t* msg = smart_create_rqst_msg("GET_HELLO", NULL, 0, "blob", FALSE, FALSE, FALSE,
                                             timeout,
                                             rf627_smart_get_hello_callback,
                                             rf627_smart_get_hello_timeout_callback);

    // Send test msg
    if (!smart_channel_send_msg(&channel, msg))
        printf("No data has been sent.\n");
    else
        printf("Requests were sent.\n");


    delay(timeout);

    // Cleanup test msg
    smart_cleanup_msg(msg);
    smart_channel_cleanup(&channel);

    return answ_count;
}

rfInt8 rf627_smart_check_connection_callback(char* data, uint32_t data_size, uint32_t device_id, void* rqst_msg)
{
    answ_count++;
    printf("%d - Answers were received. Received payload size: %d\n", answ_count, data_size);

    int32_t result = SMART_PARSER_RETURN_STATUS_NO_DATA;
    rfBool existing = FALSE;

    // Get params
    mpack_tree_t tree;
    mpack_tree_init_data(&tree, (const char*)data, data_size);
    mpack_tree_parse(&tree);
    if (mpack_tree_error(&tree) != mpack_ok)
    {
        result = SMART_PARSER_RETURN_STATUS_DATA_ERROR;
        mpack_tree_destroy(&tree);
        return result;
    }

    for (rfUint32 i = 0; i < vector_count(search_result); i++)
    {
        if(((scanner_base_t*)vector_get(search_result, i))->type == kRF627_SMART)
        {
            uint32_t serial = ((scanner_base_t*)vector_get(search_result, i))->rf627_smart->info_by_service_protocol.fact_general_serial;
            if (serial == device_id)
                existing = TRUE;
        }
    }

    if (existing)
    {
        smart_msg_t* msg = rqst_msg;
        msg->result = memory_platform.rf_calloc(1, sizeof (int));
        *(int*)((smart_msg_t*)rqst_msg)->result = TRUE;
    }

    mpack_tree_destroy(&tree);
    return TRUE;
}

rfInt8 rf627_smart_check_connection_timeout_callback()
{
    printf("get_hello_timeout\n");
}


rfBool rf627_smart_check_connection_by_service_protocol(rf627_smart_t* scanner, rfUint32 timeout)
{
    int is_connected = FALSE;
    smart_msg_t* msg = smart_create_rqst_msg("GET_HELLO", NULL, 0, "blob", FALSE, FALSE, TRUE,
                                             timeout,
                                             rf627_smart_check_connection_callback,
                                             rf627_smart_check_connection_timeout_callback);

    // Send test msg
    if (!smart_channel_send_msg(&scanner->channel, msg))
        printf("No data has been sent.\n");
    else
        printf("Requests were sent.\n");


    clock_t goal = timeout + clock();
    while (goal > clock()){
        for(int i = 0; i < SMART_PARSER_OUTPUT_BUFFER_QUEUE; i++)
        {
            if (scanner->channel.smart_parser.output_msg_buffer[i].msg._msg_uid == msg->_msg_uid)
            {
                if (scanner->channel.smart_parser.output_msg_buffer[i].msg.result != NULL)
                {
                    is_connected = *(int*)scanner->channel.smart_parser.output_msg_buffer[i].msg.result;
                    free(scanner->channel.smart_parser.output_msg_buffer[i].msg.result);
                    scanner->channel.smart_parser.output_msg_buffer[i].msg.result = NULL;
                    if (is_connected) break;
                }
            }
        }
    }

    // Cleanup test msg
    smart_cleanup_msg(msg);

    if (is_connected)
        return TRUE;
    else return FALSE;
}



rf627_smart_t* rf627_smart_create_from_hello_msg(
        char* data, rfUint32 data_size)
{
    rf627_smart_t* rf627_smart = memory_platform.rf_calloc(1, sizeof (rf627_smart_t));
    memset(rf627_smart, 0, sizeof (rf627_smart_t));

    vector_init(&rf627_smart->params_list);

    int32_t result = SMART_PARSER_RETURN_STATUS_NO_DATA;

    // Get params
    mpack_tree_t tree;
    mpack_tree_init_data(&tree, (const char*)data, data_size);
    mpack_tree_parse(&tree);
    if (mpack_tree_error(&tree) != mpack_ok)
    {
        result = SMART_PARSER_RETURN_STATUS_NO_DATA;
        mpack_tree_destroy(&tree);
        return NULL;
    }
    mpack_node_t root = mpack_tree_root(&tree);

    // Device firmware version [Major, Minor, Patch].
    if (mpack_node_map_contains_cstr(root, "fact_general_firmwareVer"))
    {
        for(size_t i = 0; i < mpack_node_array_length(mpack_node_map_cstr(root, "fact_general_firmwareVer")); i++)
        {
            rf627_smart->info_by_service_protocol.fact_general_firmwareVer[i] =
                    mpack_node_uint(mpack_node_array_at(mpack_node_map_cstr(root, "fact_general_firmwareVer"), i));
        }
    }

    // Device hardware version.
    if (mpack_node_map_contains_cstr(root, "fact_general_hardwareVer"))
    {
        rf627_smart->info_by_service_protocol.fact_general_hardwareVer =
                mpack_node_uint(mpack_node_map_cstr(root, "fact_general_hardwareVer"));
    }

    // Size of the measuring range in Z axis in mm.
    if (mpack_node_map_contains_cstr(root, "fact_general_mr"))
    {
        rf627_smart->info_by_service_protocol.fact_general_mr =
                mpack_node_uint(mpack_node_map_cstr(root, "fact_general_mr"));
    }

    // Device type identifier.
    if (mpack_node_map_contains_cstr(root, "fact_general_productCode"))
    {
        rf627_smart->info_by_service_protocol.fact_general_productCode =
                mpack_node_uint(mpack_node_map_cstr(root, "fact_general_productCode"));
    }

    // Device serial number.
    if (mpack_node_map_contains_cstr(root, "fact_general_serial"))
    {
        rf627_smart->info_by_service_protocol.fact_general_serial =
                mpack_node_uint(mpack_node_map_cstr(root, "fact_general_serial"));
    }

    // Start of measuring range in Z axis in mm.
    if (mpack_node_map_contains_cstr(root, "fact_general_smr"))
    {
        rf627_smart->info_by_service_protocol.fact_general_smr =
                mpack_node_uint(mpack_node_map_cstr(root, "fact_general_smr"));
    }

    // The size along the X axis of the measuring range at the beginning of the range.
    if (mpack_node_map_contains_cstr(root, "fact_general_xsmr"))
    {
        rf627_smart->info_by_service_protocol.fact_general_xsmr =
                mpack_node_uint(mpack_node_map_cstr(root, "fact_general_xsmr"));
    }

    // The wavelength of the laser, installed in the device.
    if (mpack_node_map_contains_cstr(root, "fact_laser_waveLength"))
    {
        rf627_smart->info_by_service_protocol.fact_laser_waveLength =
                mpack_node_uint(mpack_node_map_cstr(root, "fact_laser_waveLength"));
    }

    // Physical address of the device.
    if (mpack_node_map_contains_cstr(root, "fact_network_macAddr"))
    {
        int type_strlen = mpack_node_strlen(mpack_node_map_cstr(root, "fact_network_macAddr")) + 1;
        rf627_smart->info_by_service_protocol.fact_network_macAddr =
                mpack_node_cstr_alloc(mpack_node_map_cstr(root, "fact_network_macAddr"), type_strlen);
    }

    // User-defined scanner name. It is displayed on the web page of the scanner
    // and can be used to quickly identify scanners.
    if (mpack_node_map_contains_cstr(root, "user_general_deviceName"))
    {
        int type_strlen = mpack_node_strlen(mpack_node_map_cstr(root, "user_general_deviceName")) + 1;
        rf627_smart->info_by_service_protocol.user_general_deviceName =
                mpack_node_cstr_alloc(mpack_node_map_cstr(root, "user_general_deviceName"), type_strlen);
    }

    // Turns on and off the automatic negotiation of the Ethernet connection speed.
    if (mpack_node_map_contains_cstr(root, "user_network_autoNeg"))
    {
        rf627_smart->info_by_service_protocol.user_network_autoNeg =
                mpack_node_bool(mpack_node_map_cstr(root, "user_network_autoNeg"));
    }

    // Gateway address.
    if (mpack_node_map_contains_cstr(root, "user_network_gateway"))
    {
        int type_strlen = mpack_node_strlen(mpack_node_map_cstr(root, "user_network_gateway")) + 1;
        rf627_smart->info_by_service_protocol.user_network_gateway =
                mpack_node_cstr_alloc(mpack_node_map_cstr(root, "user_network_gateway"), type_strlen);
    }

    // Host address.
    if (mpack_node_map_contains_cstr(root, "user_network_hostIP"))
    {
        int type_strlen = mpack_node_strlen(mpack_node_map_cstr(root, "user_network_hostIP")) + 1;
        rf627_smart->info_by_service_protocol.user_network_hostIP =
                mpack_node_cstr_alloc(mpack_node_map_cstr(root, "user_network_hostIP"), type_strlen);
    }

    // Turns on and off the automatic negotiation of the Ethernet connection speed.
    if (mpack_node_map_contains_cstr(root, "user_network_hostPort"))
    {
        rf627_smart->info_by_service_protocol.user_network_hostPort =
                mpack_node_uint(mpack_node_map_cstr(root, "user_network_hostPort"));
    }

    // The network address of the device
    if (mpack_node_map_contains_cstr(root, "user_network_ip"))
    {
        int type_strlen = mpack_node_strlen(mpack_node_map_cstr(root, "user_network_ip")) + 1;
        rf627_smart->info_by_service_protocol.user_network_ip =
                mpack_node_cstr_alloc(mpack_node_map_cstr(root, "user_network_ip"), type_strlen);
    }

    // Subnet mask for the device
    if (mpack_node_map_contains_cstr(root, "user_network_mask"))
    {
        int type_strlen = mpack_node_strlen(mpack_node_map_cstr(root, "user_network_mask")) + 1;
        rf627_smart->info_by_service_protocol.user_network_mask =
                mpack_node_cstr_alloc(mpack_node_map_cstr(root, "user_network_mask"), type_strlen);
    }

    // Port number for service protocol.
    if (mpack_node_map_contains_cstr(root, "user_network_servicePort"))
    {
        rf627_smart->info_by_service_protocol.user_network_servicePort =
                mpack_node_uint(mpack_node_map_cstr(root, "user_network_servicePort"));
    }

    // Current Ethernet connection speed. The connection speed is changed by writing
    // to this parameter. In case of auto-negotiation, writing is ignored.
    if (mpack_node_map_contains_cstr(root, "user_network_speed"))
    {
        rf627_smart->info_by_service_protocol.user_network_speed =
                mpack_node_uint(mpack_node_map_cstr(root, "user_network_speed"));
    }

    // Port number to access the Web page.
    if (mpack_node_map_contains_cstr(root, "user_network_webPort"))
    {
        rf627_smart->info_by_service_protocol.user_network_webPort =
                mpack_node_uint(mpack_node_map_cstr(root, "user_network_webPort"));
    }

    // Enabling and disabling the profile stream, transmitted via the UDP protocol
    // (sending to the network address, set by the user_network_hostIP parameter
    // and the port, set by the user_network_hostPort parameter).
    if (mpack_node_map_contains_cstr(root, "user_streams_udpEnabled"))
    {
        rf627_smart->info_by_service_protocol.user_streams_udpEnabled =
                mpack_node_uint(mpack_node_map_cstr(root, "user_streams_udpEnabled"));
    }

    // The format of the transmitted profiles.
    if (mpack_node_map_contains_cstr(root, "user_streams_format"))
    {
        rf627_smart->info_by_service_protocol.user_streams_format =
                mpack_node_uint(mpack_node_map_cstr(root, "user_streams_format"));
    }

    mpack_tree_destroy(&tree);
    return rf627_smart;

}

void rf627_smart_free(rf627_smart_t* scanner)
{
    smart_channel_cleanup(&scanner->channel);
    network_platform.network_methods.close_socket(scanner->m_data_sock);

    while (vector_count(scanner->params_list) > 0)
    {
        parameter_t* p = vector_get(scanner->params_list, vector_count(scanner->params_list)-1);
        free_parameter(p, kRF627_SMART);

        vector_delete(scanner->params_list, vector_count(scanner->params_list)-1);
    }

    if (scanner->info_by_service_protocol.user_general_deviceName != NULL)
    {
        free (scanner->info_by_service_protocol.user_general_deviceName);
        scanner->info_by_service_protocol.user_general_deviceName = NULL;
    }
    if (scanner->info_by_service_protocol.user_network_ip != NULL)
    {
        free (scanner->info_by_service_protocol.user_network_ip);
        scanner->info_by_service_protocol.user_network_ip = NULL;
    }
    if (scanner->info_by_service_protocol.user_network_mask != NULL)
    {
        free (scanner->info_by_service_protocol.user_network_mask);
        scanner->info_by_service_protocol.user_network_mask = NULL;
    }
    if (scanner->info_by_service_protocol.user_network_gateway != NULL)
    {
        free (scanner->info_by_service_protocol.user_network_gateway);
        scanner->info_by_service_protocol.user_network_gateway = NULL;
    }
    if (scanner->info_by_service_protocol.user_network_hostIP != NULL)
    {
        free (scanner->info_by_service_protocol.user_network_hostIP);
        scanner->info_by_service_protocol.user_network_hostIP = NULL;
    }
    if (scanner->info_by_service_protocol.user_network_hostIP != NULL)
    {
        free (scanner->info_by_service_protocol.user_network_hostIP);
        scanner->info_by_service_protocol.user_network_hostIP = NULL;
    }
    if (scanner != NULL)
    {
        free (scanner);
        scanner = NULL;
    }
}

rf627_smart_hello_info_by_service_protocol* rf627_smart_get_info_about_scanner_by_service_protocol(rf627_smart_t* scanner)
{
    return &scanner->info_by_service_protocol;
}

parameter_t* rf627_smart_get_parameter(
        rf627_smart_t* scanner, const rfChar* param_name)
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

rfBool rf627_smart_connect(rf627_smart_t* scanner)
{
    rfUint32 recv_ip_addr;
    rfUint16 recv_port;
    rfInt nret;

    char config[1024];

    sprintf(config, "-dst_ip_addr %s "
                    "-host_ip_addr %s "
                    "-in_udp_port %d "
                    "-max_packet_size 65535 "
                    "-out_udp_port %d "
                    "-socket_timeout 100 "
                    "-max_data_size 350000",
            scanner->info_by_service_protocol.user_network_ip,
            scanner->info_by_service_protocol.user_network_hostIP,
            scanner->info_by_service_protocol.user_network_servicePort,
            scanner->info_by_service_protocol.user_network_servicePort);


    if (smart_channel_init(&scanner->channel, config))
    {
        scanner->m_data_sock =
                network_platform.network_methods.create_udp_socket();
        if (scanner->m_data_sock != (void*)RF_SOCKET_ERROR)
        {
            nret = 1;
            network_platform.network_methods.set_reuseaddr_socket_option(scanner->m_data_sock);

            network_platform.network_methods.set_socket_recv_timeout(
                        scanner->m_data_sock, 100);
            //recv_addr.sin_family = RF_AF_INET;
            recv_port = scanner->info_by_service_protocol.user_network_hostPort;

            //recv_addr.sin_addr = RF_INADDR_ANY;
            ip_string_to_uint32(scanner->info_by_service_protocol.user_network_hostIP, &recv_ip_addr);

            nret = network_platform.network_methods.socket_bind(
                        scanner->m_data_sock, recv_ip_addr, recv_port);
            if (nret == RF_SOCKET_ERROR)
            {
                network_platform.network_methods.close_socket(scanner->m_data_sock);
                scanner->m_data_sock = NULL;
                return FALSE;
            }
        }
        else
        {
            iostream_platform.trace_error("Create data socket error");
            return FALSE;
        }


        return TRUE;
    }
    else
    {
        rf627_smart_disconnect(scanner);
    }

    return FALSE;

}


void rf627_smart_disconnect(rf627_smart_t* scanner)
{
    smart_channel_cleanup(&scanner->channel);

    if (scanner->m_data_sock != NULL &&
            scanner->m_data_sock != (void*)RF_SOCKET_ERROR)
    {
        network_platform.network_methods.close_socket(scanner->m_data_sock);
        scanner->m_data_sock = NULL;
    }
}
#define RF627_PROFILE_SIZE          648
#define RF627_EXT_PROFILE_SIZE      1296
rf627_smart_profile2D_t* rf627_smart_get_profile2D(rf627_smart_t* scanner, rfBool zero_points)
{

    rfSize RX_SIZE = rf627_protocol_old_get_size_of_header() + 65000;
    rfUint8* RX = memory_platform.rf_calloc(1, RX_SIZE);
    rfSize TX_SIZE = rf627_protocol_old_get_size_of_header() + 65000;
    rfUint8* TX =  memory_platform.rf_calloc(1, TX_SIZE);

    rfInt nret = network_platform.network_methods.recv_data(
                scanner->m_data_sock, RX, RX_SIZE);
    if(nret > 0)
    {
        rfSize profile_header_size =
                rf627_protocol_old_get_size_of_response_profile_header_packet();

        rf627_smart_profile2D_t* profile =
                memory_platform.rf_calloc(1, sizeof(rf627_smart_profile2D_t));

        rf627_old_stream_msg_t header_from_msg = rf627_protocol_old_unpack_header_msg_from_profile_packet(RX);

        profile->header.data_type = header_from_msg.data_type;
        profile->header.flags = header_from_msg.flags;
        profile->header.device_type = header_from_msg.device_type;
        profile->header.serial_number = header_from_msg.serial_number;
        profile->header.system_time = header_from_msg.system_time;

        profile->header.proto_version_major = header_from_msg.proto_version_major;
        profile->header.proto_version_minor = header_from_msg.proto_version_minor;
        profile->header.hardware_params_offset = header_from_msg.hardware_params_offset;
        profile->header.data_offset = header_from_msg.data_offset;
        profile->header.packet_count = header_from_msg.packet_count;
        profile->header.measure_count = header_from_msg.measure_count;

        profile->header.zmr = header_from_msg.zmr;
        profile->header.xemr = header_from_msg.xemr;
        profile->header.discrete_value = header_from_msg.discrete_value;

        profile->header.exposure_time = header_from_msg.exposure_time;
        profile->header.laser_value = header_from_msg.laser_value;
        profile->header.step_count = header_from_msg.step_count;
        profile->header.dir = header_from_msg.dir;

        if(profile->header.serial_number == scanner->info_by_service_protocol.fact_general_serial)
        {
            rfInt16 x;
            rfUint16 z;

            rfUint32 pt_count;
            switch (profile->header.data_type)
            {
            case DTY_PixelsNormal:
                pt_count = RF627_PROFILE_SIZE;
                profile->pixels_format.pixels_count = 0;
                profile->pixels_format.pixels =
                        memory_platform.rf_calloc(pt_count, sizeof (rfUint16));
                if (profile->header.flags & 0x01){
                    profile->intensity_count = 0;
                    profile->intensity =
                            memory_platform.rf_calloc(pt_count, sizeof (rfUint8));
                }
                break;
            case DTY_ProfileNormal:
                pt_count = RF627_PROFILE_SIZE;
                profile->profile_format.points_count = 0;
                profile->profile_format.points =
                        memory_platform.rf_calloc(pt_count, sizeof (rf627_old_point2D_t));
                if (profile->header.flags & 0x01){
                    profile->intensity_count = 0;
                    profile->intensity =
                            memory_platform.rf_calloc(pt_count, sizeof (rfUint8));
                }
                break;
            case DTY_PixelsInterpolated:
                pt_count = RF627_EXT_PROFILE_SIZE;
                profile->pixels_format.pixels_count = 0;
                profile->pixels_format.pixels =
                        memory_platform.rf_calloc(pt_count, sizeof (rfUint16));
                if (profile->header.flags & 0x01){
                    profile->intensity_count = 0;
                    profile->intensity =
                            memory_platform.rf_calloc(pt_count, sizeof (rfUint8));
                }
                break;
            case DTY_ProfileInterpolated:
                pt_count = RF627_EXT_PROFILE_SIZE;
                profile->profile_format.points_count = 0;
                profile->profile_format.points =
                        memory_platform.rf_calloc(pt_count, sizeof (rf627_old_point2D_t));
                if (profile->header.flags & 0x01){
                    profile->intensity_count = 0;
                    profile->intensity =
                            memory_platform.rf_calloc(pt_count, sizeof (rfUint8));
                }
                break;
            }

            for (rfUint32 i=0; i<pt_count; i++)
            {
                rf627_old_point2D_t pt;
                switch (profile->header.data_type)
                {
                case DTY_ProfileNormal:
                case DTY_ProfileInterpolated:
                    z = *(rfUint16*)(&RX[profile_header_size + i*4 + 2]);
                    x = *(rfInt16*)(&RX[profile_header_size + i*4]);
                    if (zero_points == 0 && z > 0 && x != 0)
                    {
                        pt.x = (rfDouble)(x) * (rfDouble)(profile->header.xemr) /
                                (rfDouble)(profile->header.discrete_value);
                        pt.z = (rfDouble)(z) * (rfDouble)(profile->header.zmr) /
                                (rfDouble)(profile->header.discrete_value);

                        profile->profile_format.points[profile->profile_format.points_count] = pt;
                        profile->profile_format.points_count++;
                        if (profile->header.flags & 0x01)
                        {
                            profile->intensity[profile->intensity_count] = RX[profile_header_size + pt_count*4 + i];
                            profile->intensity_count++;
                        }
                    }else if(zero_points != 0)
                    {
                        pt.x = (rfDouble)(x) * (rfDouble)(profile->header.xemr) /
                                (rfDouble)(profile->header.discrete_value);
                        pt.z = (rfDouble)(z) * (rfDouble)(profile->header.zmr) /
                                (rfDouble)(profile->header.discrete_value);

                        profile->profile_format.points[profile->profile_format.points_count] = pt;
                        profile->profile_format.points_count++;
                        if (profile->header.flags & 0x01)
                        {
                            profile->intensity[profile->intensity_count] = RX[profile_header_size + pt_count*4 + i];
                            profile->intensity_count++;
                        }
                    }
                    break;
                case DTY_PixelsNormal:
                case DTY_PixelsInterpolated:
                    z = *(rfUint16*)(&RX[profile_header_size + i*2]);
                    //pt.x = i;

                    profile->pixels_format.pixels[profile->pixels_format.pixels_count] = z;
                    profile->pixels_format.pixels_count++;
                    if (profile->header.flags & 0x01)
                    {
                        profile->intensity[profile->intensity_count] = RX[profile_header_size + pt_count*4 + i];
                        profile->intensity_count++;
                    }

                    //pt.z = (rfDouble)(z) / (rfDouble)(profile->header.discrete_value);

                    break;
                }

            }
            //_mx[1].unlock();
            memory_platform.rf_free(RX);
            memory_platform.rf_free(TX);
            return profile;
        }
    }
    memory_platform.rf_free(RX);
    memory_platform.rf_free(TX);
    return NULL;
}

rfBool is_smart_params_readed = false;
extern parameter_t* create_parameter_from_type(const rfChar* type);
rfInt8 rf627_smart_read_params_callback(char* data, uint32_t data_size, uint32_t device_id)
{
    answ_count++;
    printf("%d - Answers were received. Received payload size: %d\n", answ_count, data_size);

    int32_t result = SMART_PARSER_RETURN_STATUS_NO_DATA;

    int index = -1;
    for (rfUint32 i = 0; i < vector_count(search_result); i++)
    {
        scanner_base_t* scanner = (scanner_base_t*)vector_get(search_result, i);
        if(scanner->type == kRF627_SMART)
        {
            if (((scanner_base_t*)vector_get(search_result, i))->rf627_smart->info_by_service_protocol.fact_general_serial == device_id)
            {
                index = i;
                break;
            }


        }
    }
    if (index != -1)
    {
        // Get params
        mpack_tree_t tree;
        mpack_tree_init_data(&tree, (const char*)data, data_size);
        mpack_tree_parse(&tree);
        if (mpack_tree_error(&tree) != mpack_ok)
        {
            result = SMART_PARSER_RETURN_STATUS_DATA_ERROR;
            mpack_tree_destroy(&tree);
            return result;
        }
        mpack_node_t root = mpack_tree_root(&tree);

        mpack_node_t factory = mpack_node_map_cstr(root, "factory");
        uint32_t factory_arr_size = mpack_node_array_length(factory);

        for (uint32_t i = 0; i < factory_arr_size; i++)
        {
            parameter_t* p = NULL;
            // type
            if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "type"))
            {
                char* test = mpack_node_str(mpack_node_map_cstr(mpack_node_array_at(factory, i), "type"));
                p = (parameter_t*)create_parameter_from_type(test);
                p->is_changed = FALSE;
            }

            if (p == NULL)
            {
                continue;
            }


            // access
            if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "access"))
            {
                int param_strlen = mpack_node_strlen(mpack_node_map_cstr(mpack_node_array_at(factory, i), "access")) + 1;
                p->base.access = mpack_node_cstr_alloc(mpack_node_map_cstr(mpack_node_array_at(factory, i), "access"), param_strlen);
            }

            if(rf_strcmp(parameter_value_types[PVT_UINT], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {
                    p->val_uint32->defValue =
                            mpack_node_u32(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));

                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {
                    p->val_uint32->value =
                            mpack_node_u32(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));

                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->val_uint32->max = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->val_uint32->min = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->val_uint32->step = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
                // valuesEnum
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "valuesEnum"))
                {

                    p->val_uint32->enumValues = memory_platform.rf_calloc(1, sizeof(valuesEnum_t));
                    p->val_uint32->enumValues->recCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "valuesEnum"));
                    p->val_uint32->enumValues->rec = memory_platform.rf_calloc(p->val_uint32->enumValues->recCount, sizeof(enumRec_t));
                    for (int ii = 0; ii < p->val_uint32->enumValues->recCount; ii++)
                    {
                        p->val_uint32->enumValues->rec[ii].value =
                                mpack_node_i32(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    factory, i), "valuesEnum"), ii), "value"));
                        int key_strlen =
                                mpack_node_strlen(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    factory, i), "valuesEnum"), ii), "key")) + 1;
                        p->val_uint32->enumValues->rec[ii].key =
                                mpack_node_cstr_alloc(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    factory, i), "valuesEnum"), ii), "key"), key_strlen);


                        int label_strlen =
                                mpack_node_strlen(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    factory, i), "valuesEnum"), ii), "label")) + 1;
                        p->val_uint32->enumValues->rec[ii].label =
                                mpack_node_cstr_alloc(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    factory, i), "valuesEnum"), ii), "label"), label_strlen);
                    }
                }
            }else if(rf_strcmp(parameter_value_types[PVT_UINT64], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {
                    p->val_uint64->defValue =
                            mpack_node_u64(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {
                    p->val_uint64->value =
                            mpack_node_u64(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->val_uint64->max = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->val_uint64->min = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->val_uint64->step = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_INT], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {
                    p->val_int32->defValue =
                            mpack_node_i32(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {
                    p->val_int32->value =
                            mpack_node_i32(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->val_int32->max = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->val_int32->min = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->val_int32->step = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_INT64], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {
                    p->val_int64->defValue =
                            mpack_node_i64(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {
                    p->val_int64->value =
                            mpack_node_i64(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->val_int64->max = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->val_int64->min = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->val_int64->step = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_FLOAT], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {
                    p->val_flt->defValue =
                            mpack_node_float(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {
                    p->val_flt->value =
                            mpack_node_float(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->val_flt->max = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->val_flt->min = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->val_flt->step = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_DOUBLE], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {

                    p->val_dbl->defValue =
                            mpack_node_double(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {

                    p->val_dbl->value =
                            mpack_node_double(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->val_dbl->max = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->val_dbl->min = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->val_dbl->step = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_UINT32], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {

                    p->arr_uint32->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                    p->arr_uint32->defValue = memory_platform.rf_calloc(p->arr_uint32->defCount, sizeof (uint32_t));
                    for (int ii = 0; ii < p->arr_uint32->defCount; ii++)
                        p->arr_uint32->defValue[ii] =
                                mpack_node_u32(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {

                    p->arr_uint32->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                    p->arr_uint32->value = memory_platform.rf_calloc(p->arr_uint32->count, sizeof (uint32_t));
                    for (int ii = 0; ii < p->arr_uint32->count; ii++)
                        p->arr_uint32->value[ii] =
                                mpack_node_u32(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->arr_uint32->max = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->arr_uint32->min = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "maxCount"))
                {
                    p->arr_uint32->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->arr_uint32->step = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_UINT64], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {

                    p->arr_uint64->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                    p->arr_uint64->defValue = memory_platform.rf_calloc(p->arr_uint64->defCount, sizeof (uint64_t));
                    for (int ii = 0; ii < p->arr_uint64->defCount; ii++)
                        p->arr_uint64->defValue[ii] =
                                mpack_node_u64(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {

                    p->arr_uint64->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                    p->arr_uint64->value = memory_platform.rf_calloc(p->arr_uint64->count, sizeof (uint64_t));
                    for (int ii = 0; ii < p->arr_uint64->count; ii++)
                        p->arr_uint64->value[ii] =
                                mpack_node_u64(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->arr_uint64->max = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->arr_uint64->min = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "maxCount"))
                {
                    p->arr_uint64->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->arr_uint64->step = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_INT32], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {

                    p->arr_int32->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                    p->arr_int32->defValue = memory_platform.rf_calloc(p->arr_int32->defCount, sizeof (int32_t));
                    for (int ii = 0; ii < p->arr_int32->defCount; ii++)
                        p->arr_int32->defValue[ii] =
                                mpack_node_i32(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {

                    p->arr_int32->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                    p->arr_int32->value = memory_platform.rf_calloc(p->arr_int32->count, sizeof (int32_t));
                    for (int ii = 0; ii < p->arr_int32->count; ii++)
                        p->arr_int32->value[ii] =
                                mpack_node_i32(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->arr_int32->max = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->arr_int32->min = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "maxCount"))
                {
                    p->arr_int32->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->arr_int32->step = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_INT64], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {

                    p->arr_int64->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                    p->arr_int64->defValue = memory_platform.rf_calloc(p->arr_int64->defCount, sizeof (int64_t));
                    for (int ii = 0; ii < p->arr_int64->defCount; ii++)
                        p->arr_int64->defValue[ii] =
                                mpack_node_i64(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {

                    p->arr_int64->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                    p->arr_int64->value = memory_platform.rf_calloc(p->arr_int64->count, sizeof (int64_t));
                    for (int ii = 0; ii < p->arr_int64->count; ii++)
                        p->arr_int64->value[ii] =
                                mpack_node_i64(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->arr_int64->max = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->arr_int64->min = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "maxCount"))
                {
                    p->arr_int64->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->arr_int64->step = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_FLT], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {

                    p->arr_flt->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                    p->arr_flt->defValue = memory_platform.rf_calloc(p->arr_flt->defCount, sizeof (float));
                    for (int ii = 0; ii < p->arr_flt->defCount; ii++)
                        p->arr_flt->defValue[ii] =
                                mpack_node_float(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {

                    p->arr_flt->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                    p->arr_flt->value = memory_platform.rf_calloc(p->arr_flt->count, sizeof (float));
                    for (int ii = 0; ii < p->arr_flt->count; ii++)
                        p->arr_flt->value[ii] =
                                mpack_node_float(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->arr_flt->max = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->arr_flt->min = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "maxCount"))
                {
                    p->arr_flt->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->arr_flt->step = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_DBL], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {

                    p->arr_dbl->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "defaultValue"));
                    p->arr_dbl->defValue = memory_platform.rf_calloc(p->arr_dbl->defCount, sizeof (double));
                    for (int ii = 0; ii < p->arr_dbl->defCount; ii++)
                        p->arr_dbl->defValue[ii] =
                                mpack_node_double(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {

                    p->arr_dbl->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        factory, i), "value"));
                    p->arr_dbl->value = memory_platform.rf_calloc(p->arr_dbl->count, sizeof (double));
                    for (int ii = 0; ii < p->arr_dbl->count; ii++)
                        p->arr_dbl->value[ii] =
                                mpack_node_double(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                factory, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "max"))
                {
                    p->arr_dbl->max = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(factory, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "min"))
                {
                    p->arr_dbl->min = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(factory, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "maxCount"))
                {
                    p->arr_dbl->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "step"))
                {
                    p->arr_dbl->step = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(factory, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_STRING], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "defaultValue"))
                {

                    int param_strlen = mpack_node_strlen(mpack_node_map_cstr(mpack_node_array_at(factory, i), "defaultValue")) + 1;
                    p->val_str->defValue = mpack_node_cstr_alloc(mpack_node_map_cstr(mpack_node_array_at(factory, i), "defaultValue"), param_strlen);
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "value"))
                {

                    int param_strlen = mpack_node_strlen(mpack_node_map_cstr(mpack_node_array_at(factory, i), "value")) + 1;
                    p->val_str->value = mpack_node_cstr_alloc(mpack_node_map_cstr(mpack_node_array_at(factory, i), "value"), param_strlen);
                }
                // maxLen
                if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "maxLen"))
                {
                    p->val_str->maxLen = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(factory, i), "maxLen"));
                }
            }



            // index
            if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "index"))
            {
                p->base.index = mpack_node_uint(mpack_node_map_cstr(mpack_node_array_at(factory, i), "index"));
            }

            // name
            if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "name"))
            {
                int param_strlen = mpack_node_strlen(mpack_node_map_cstr(mpack_node_array_at(factory, i), "name")) + 1;
                p->base.name = mpack_node_cstr_alloc(mpack_node_map_cstr(mpack_node_array_at(factory, i), "name"), param_strlen);
            }

            // offset
            if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "offset"))
            {
                p->base.offset = mpack_node_uint(mpack_node_map_cstr(mpack_node_array_at(factory, i), "offset"));
            }

            // size
            if (mpack_node_map_contains_cstr(mpack_node_array_at(factory, i), "size"))
            {
                p->base.size = mpack_node_uint(mpack_node_map_cstr(mpack_node_array_at(factory, i), "size"));
            }

            vector_add(((scanner_base_t*)vector_get(search_result, index))->rf627_smart->params_list, p);
        }

        mpack_node_t user = mpack_node_map_cstr(root, "user");
        uint32_t user_arr_size = mpack_node_array_length(user);

        for (uint32_t i = 0; i < user_arr_size; i++)
        {
            parameter_t* p = NULL;
            // type
            if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "type"))
            {
                char* test = mpack_node_str(mpack_node_map_cstr(mpack_node_array_at(user, i), "type"));
                p = (parameter_t*)create_parameter_from_type(test);
            }

            if (p == NULL)
            {
                continue;
            }


            // access
            if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "access"))
            {
                int param_strlen = mpack_node_strlen(mpack_node_map_cstr(mpack_node_array_at(user, i), "access")) + 1;
                p->base.access = mpack_node_cstr_alloc(mpack_node_map_cstr(mpack_node_array_at(user, i), "access"), param_strlen);
            }

            if(rf_strcmp(parameter_value_types[PVT_UINT], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {
                    p->val_uint32->defValue =
                            mpack_node_u32(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));

                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {
                    p->val_uint32->value =
                            mpack_node_u32(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));

                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->val_uint32->max = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->val_uint32->min = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->val_uint32->step = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }

                // valuesEnum
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "valuesEnum"))
                {

                    p->val_uint32->enumValues = memory_platform.rf_calloc(1, sizeof(valuesEnum_t));
                    p->val_uint32->enumValues->recCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "valuesEnum"));
                    p->val_uint32->enumValues->rec = memory_platform.rf_calloc(p->val_uint32->enumValues->recCount, sizeof(enumRec_t));
                    for (int ii = 0; ii < p->val_uint32->enumValues->recCount; ii++)
                    {
                        p->val_uint32->enumValues->rec[ii].value =
                                mpack_node_i32(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    user, i), "valuesEnum"), ii), "value"));
                        int key_strlen =
                                mpack_node_strlen(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    user, i), "valuesEnum"), ii), "key")) + 1;
                        p->val_uint32->enumValues->rec[ii].key =
                                mpack_node_cstr_alloc(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    user, i), "valuesEnum"), ii), "key"), key_strlen);


                        int label_strlen =
                                mpack_node_strlen(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    user, i), "valuesEnum"), ii), "label")) + 1;
                        p->val_uint32->enumValues->rec[ii].label =
                                mpack_node_cstr_alloc(
                                    mpack_node_map_cstr(
                                        mpack_node_array_at(
                                            mpack_node_map_cstr(
                                                mpack_node_array_at(
                                                    user, i), "valuesEnum"), ii), "label"), label_strlen);
                    }
                }

            }else if(rf_strcmp(parameter_value_types[PVT_UINT64], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {
                    p->val_uint64->defValue =
                            mpack_node_u64(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {
                    p->val_uint64->value =
                            mpack_node_u64(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->val_uint64->max = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->val_uint64->min = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->val_uint64->step = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_INT], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {
                    p->val_int32->defValue =
                            mpack_node_i32(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {
                    p->val_int32->value =
                            mpack_node_i32(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->val_int32->max = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->val_int32->min = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->val_int32->step = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_INT64], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {
                    p->val_int64->defValue =
                            mpack_node_i64(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {
                    p->val_int64->value =
                            mpack_node_i64(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->val_int64->max = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->val_int64->min = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->val_int64->step = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_FLOAT], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {
                    p->val_flt->defValue =
                            mpack_node_float(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {
                    p->val_flt->value =
                            mpack_node_float(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->val_flt->max = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->val_flt->min = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->val_flt->step = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_DOUBLE], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {

                    p->val_dbl->defValue =
                            mpack_node_double(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {

                    p->val_dbl->value =
                            mpack_node_double(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->val_dbl->max = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->val_dbl->min = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->val_dbl->step = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_UINT32], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {

                    p->arr_uint32->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                    p->arr_uint32->defValue = memory_platform.rf_calloc(p->arr_uint32->defCount, sizeof (uint32_t));
                    for (int ii = 0; ii < p->arr_uint32->defCount; ii++)
                        p->arr_uint32->defValue[ii] =
                                mpack_node_u32(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {

                    p->arr_uint32->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                    p->arr_uint32->value = memory_platform.rf_calloc(p->arr_uint32->count, sizeof (uint32_t));
                    for (int ii = 0; ii < p->arr_uint32->count; ii++)
                        p->arr_uint32->value[ii] =
                                mpack_node_u32(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->arr_uint32->max = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->arr_uint32->min = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "maxCount"))
                {
                    p->arr_uint32->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->arr_uint32->step = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_UINT64], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {

                    p->arr_uint64->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                    p->arr_uint64->defValue = memory_platform.rf_calloc(p->arr_uint64->defCount, sizeof (uint64_t));
                    for (int ii = 0; ii < p->arr_uint64->defCount; ii++)
                        p->arr_uint64->defValue[ii] =
                                mpack_node_u64(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {

                    p->arr_uint64->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                    p->arr_uint64->value = memory_platform.rf_calloc(p->arr_uint64->count, sizeof (uint64_t));
                    for (int ii = 0; ii < p->arr_uint64->count; ii++)
                        p->arr_uint64->value[ii] =
                                mpack_node_u64(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->arr_uint64->max = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->arr_uint64->min = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "maxCount"))
                {
                    p->arr_uint64->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->arr_uint64->step = mpack_node_u64(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_INT32], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {

                    p->arr_int32->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                    p->arr_int32->defValue = memory_platform.rf_calloc(p->arr_int32->defCount, sizeof (int32_t));
                    for (int ii = 0; ii < p->arr_int32->defCount; ii++)
                        p->arr_int32->defValue[ii] =
                                mpack_node_i32(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {

                    p->arr_int32->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                    p->arr_int32->value = memory_platform.rf_calloc(p->arr_int32->count, sizeof (int32_t));
                    for (int ii = 0; ii < p->arr_int32->count; ii++)
                        p->arr_int32->value[ii] =
                                mpack_node_i32(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->arr_int32->max = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->arr_int32->min = mpack_node_i32(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "maxCount"))
                {
                    p->arr_int32->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->arr_int32->step = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_INT64], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {

                    p->arr_int64->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                    p->arr_int64->defValue = memory_platform.rf_calloc(p->arr_int64->defCount, sizeof (int64_t));
                    for (int ii = 0; ii < p->arr_int64->defCount; ii++)
                        p->arr_int64->defValue[ii] =
                                mpack_node_i64(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {

                    p->arr_int64->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                    p->arr_int64->value = memory_platform.rf_calloc(p->arr_int64->count, sizeof (int64_t));
                    for (int ii = 0; ii < p->arr_int64->count; ii++)
                        p->arr_int64->value[ii] =
                                mpack_node_i64(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->arr_int64->max = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->arr_int64->min = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "maxCount"))
                {
                    p->arr_int64->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->arr_int64->step = mpack_node_i64(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_FLT], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {

                    p->arr_flt->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                    p->arr_flt->defValue = memory_platform.rf_calloc(p->arr_flt->defCount, sizeof (float));
                    for (int ii = 0; ii < p->arr_flt->defCount; ii++)
                        p->arr_flt->defValue[ii] =
                                mpack_node_float(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {

                    p->arr_flt->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                    p->arr_flt->value = memory_platform.rf_calloc(p->arr_flt->count, sizeof (float));
                    for (int ii = 0; ii < p->arr_flt->count; ii++)
                        p->arr_flt->value[ii] =
                                mpack_node_float(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->arr_flt->max = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->arr_flt->min = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "maxCount"))
                {
                    p->arr_flt->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->arr_flt->step = mpack_node_float(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_DBL], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {

                    p->arr_dbl->defCount =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "defaultValue"));
                    p->arr_dbl->defValue = memory_platform.rf_calloc(p->arr_dbl->defCount, sizeof (double));
                    for (int ii = 0; ii < p->arr_dbl->defCount; ii++)
                        p->arr_dbl->defValue[ii] =
                                mpack_node_double(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "defaultValue"), ii));
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {

                    p->arr_dbl->count =
                            mpack_node_array_length(
                                mpack_node_map_cstr(
                                    mpack_node_array_at(
                                        user, i), "value"));
                    p->arr_dbl->value = memory_platform.rf_calloc(p->arr_dbl->count, sizeof (double));
                    for (int ii = 0; ii < p->arr_dbl->count; ii++)
                        p->arr_dbl->value[ii] =
                                mpack_node_double(
                                    mpack_node_array_at(
                                        mpack_node_map_cstr(
                                            mpack_node_array_at(
                                                user, i), "value"), ii));
                }
                // max
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "max"))
                {
                    p->arr_dbl->max = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(user, i), "max"));
                }
                // min
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "min"))
                {
                    p->arr_dbl->min = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(user, i), "min"));
                }
                // maxCount
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "maxCount"))
                {
                    p->arr_dbl->maxCount = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "maxCount"));
                }
                // step
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "step"))
                {
                    p->arr_dbl->step = mpack_node_double(mpack_node_map_cstr(mpack_node_array_at(user, i), "step"));
                }
            }else if(rf_strcmp(parameter_value_types[PVT_STRING], p->base.type) == 0)
            {
                // defaultValue
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "defaultValue"))
                {

                    int param_strlen = mpack_node_strlen(mpack_node_map_cstr(mpack_node_array_at(user, i), "defaultValue")) + 1;
                    p->val_str->defValue = mpack_node_cstr_alloc(mpack_node_map_cstr(mpack_node_array_at(user, i), "defaultValue"), param_strlen);
                }
                // value
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "value"))
                {

                    int param_strlen = mpack_node_strlen(mpack_node_map_cstr(mpack_node_array_at(user, i), "value")) + 1;
                    p->val_str->value = mpack_node_cstr_alloc(mpack_node_map_cstr(mpack_node_array_at(user, i), "value"), param_strlen);
                }
                // maxLen
                if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "maxLen"))
                {
                    p->val_str->maxLen = mpack_node_u32(mpack_node_map_cstr(mpack_node_array_at(user, i), "maxLen"));
                }
            }


            // index
            if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "index"))
            {
                p->base.index = mpack_node_uint(mpack_node_map_cstr(mpack_node_array_at(user, i), "index"));
            }

            // name
            if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "name"))
            {
                int param_strlen = mpack_node_strlen(mpack_node_map_cstr(mpack_node_array_at(user, i), "name")) + 1;
                p->base.name = mpack_node_cstr_alloc(mpack_node_map_cstr(mpack_node_array_at(user, i), "name"), param_strlen);
            }

            // offset
            if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "offset"))
            {
                p->base.offset = mpack_node_uint(mpack_node_map_cstr(mpack_node_array_at(user, i), "offset"));
            }

            // size
            if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "size"))
            {
                p->base.size = mpack_node_uint(mpack_node_map_cstr(mpack_node_array_at(user, i), "size"));
            }

            // units
            if (mpack_node_map_contains_cstr(mpack_node_array_at(user, i), "units"))
            {
                int param_strlen = mpack_node_strlen(mpack_node_map_cstr(mpack_node_array_at(user, i), "units")) + 1;
                p->base.units = mpack_node_cstr_alloc(mpack_node_map_cstr(mpack_node_array_at(user, i), "units"), param_strlen);
            }else
            {
                p->base.units = "";
            }

            vector_add(((scanner_base_t*)vector_get(search_result, index))->rf627_smart->params_list, p);
        }

        mpack_tree_destroy(&tree);
    }

    is_smart_params_readed = TRUE;
}

rfInt8 rf627_smart_read_params_timeout_callback()
{
    printf("smart_read_params_timeout\n");
}


rfBool rf627_smart_read_params_from_scanner(rf627_smart_t* scanner)
{

    smart_msg_t* msg = smart_create_rqst_msg("GET_PARAMS_DESCRIPTION", NULL, 0, "blob", FALSE, FALSE, TRUE,
                                             3000,
                                             rf627_smart_read_params_callback,
                                             rf627_smart_read_params_timeout_callback);

    is_smart_params_readed = FALSE;
    // Send test msg
    if (!smart_channel_send_msg(&scanner->channel, msg))
        printf("No data has been sent.\n");
    else
        printf("Requests were sent.\n");


    unsigned int mseconds = 3000;
    clock_t goal = mseconds + clock();
    while (goal > clock()){
        if (is_smart_params_readed) break;
    }
    // Cleanup test msg
    smart_cleanup_msg(msg);

    if (is_smart_params_readed)
        return TRUE;
    else return FALSE;
}

rfUint8 rf627_smart_set_parameter(
        rf627_smart_t* scanner, parameter_t* param)
{
    for(rfSize i = 0; i < vector_count(scanner->params_list); i++)
    {
        parameter_t* p = vector_get(scanner->params_list, i);
        if (rf_strcmp(p->base.name, param->base.name) == 0)
        {
            if (rf_strcmp(p->base.type, parameter_value_types[PVT_STRING]) == 0)
            {
                memory_platform.rf_free(p->val_str->value);
                p->val_str->value = memory_platform.rf_calloc(param->base.size, sizeof (rfChar));
                memory_platform.rf_memcpy(
                            (void*)p->val_str->value,
                            param->val_str->value,
                            param->base.size);
                p->base.size = param->base.size;
                p->is_changed = TRUE;
                return TRUE;
            }
            else if (rf_strcmp(p->base.type, parameter_value_types[PVT_INT]) == 0)
            {
                p->val_int32->value = param->val_int32->value;
                p->is_changed = TRUE;
                return TRUE;
            }
            else if (rf_strcmp(p->base.type, parameter_value_types[PVT_INT64]) == 0)
            {
                p->val_int64->value = param->val_int64->value;
                p->is_changed = TRUE;
                return TRUE;
            }
            else if (rf_strcmp(p->base.type, parameter_value_types[PVT_UINT]) == 0)
            {
                p->val_uint32->value = param->val_uint32->value;
                p->is_changed = TRUE;
                return TRUE;
            }
            else if (rf_strcmp(p->base.type, parameter_value_types[PVT_UINT64]) == 0)
            {
                p->val_uint64->value = param->val_uint64->value;
                p->is_changed = TRUE;
                return TRUE;
            }
            else if (rf_strcmp(p->base.type, parameter_value_types[PVT_FLOAT]) == 0)
            {
                p->val_flt->value = param->val_flt->value;
                p->is_changed = TRUE;
                return TRUE;
            }
            else if (rf_strcmp(p->base.type, parameter_value_types[PVT_DOUBLE]) == 0)
            {
                p->val_dbl->value = param->val_dbl->value;
                p->is_changed = TRUE;
                return TRUE;
            }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_UINT32]) == 0)
            {
                memory_platform.rf_free(p->arr_uint32->value);
                p->arr_uint32->value = memory_platform.rf_calloc(param->base.size, sizeof (uint8_t));
                memory_platform.rf_memcpy(
                            (void*)p->arr_uint32->value,
                            param->arr_uint32->value,
                            param->base.size);
                p->base.size = param->base.size;
                p->is_changed = TRUE;
                return TRUE;
            }

        }
    }
    return FALSE;
}

rfInt8 rf627_smart_write_params_callback(char* data, uint32_t data_size, uint32_t device_id)
{
    return TRUE;
}

rfInt8 rf627_smart_write_params_timeout_callback()
{
    printf("smart_write_params_timeout\n");
}

rfBool is_smart_frame_readed = false;
char* frame = NULL;
rfInt8 rf627_smart_get_frame_callback(char* data, uint32_t data_size, uint32_t device_id)
{
    answ_count++;
    printf("%d - Answers were received. Received payload size: %d\n", answ_count, data_size);

    int32_t result = SMART_PARSER_RETURN_STATUS_NO_DATA;

    int index = -1;
    for (rfUint32 i = 0; i < vector_count(search_result); i++)
    {
        if(((scanner_base_t*)vector_get(search_result, i))->type == kRF627_SMART)
        {
            if (((scanner_base_t*)vector_get(search_result, i))->rf627_smart->info_by_service_protocol.fact_general_serial == device_id)
            {
                index = i;
                break;
            }


        }
    }
    if (index != -1)
    {
        // Get params
        mpack_tree_t tree;
        mpack_tree_init_data(&tree, (const char*)data, data_size);
        mpack_tree_parse(&tree);
        if (mpack_tree_error(&tree) != mpack_ok)
        {
            result = SMART_PARSER_RETURN_STATUS_DATA_ERROR;
            mpack_tree_destroy(&tree);
            return result;
        }
        mpack_node_t root = mpack_tree_root(&tree);

        mpack_node_t frame_data = mpack_node_map_cstr(root, "frame");
        uint32_t frame_size = mpack_node_data_len(frame_data);
        frame = mpack_node_data_alloc(frame_data, frame_size+1);

        mpack_tree_destroy(&tree);
    }

    is_smart_frame_readed = TRUE;
}

rfInt8 rf627_smart_get_frame_timeout_callback()
{
    printf("smart_read_params_timeout\n");
}



rfChar* rf627_smart_get_frame(rf627_smart_t* scanner)
{
    smart_msg_t* msg = smart_create_rqst_msg("GET_FRAME", NULL, 0, "blob", FALSE, FALSE, TRUE,
                                             50000,
                                             rf627_smart_get_frame_callback,
                                             rf627_smart_get_frame_timeout_callback);

    is_smart_frame_readed = FALSE;
    // Send test msg
    if (!smart_channel_send_msg(&scanner->channel, msg))
        printf("No data has been sent.\n");
    else
        printf("Requests were sent.\n");


    unsigned int mseconds = 50000;
    clock_t goal = mseconds + clock();
    while (goal > clock()){
        if (is_smart_frame_readed) break;
    }
    // Cleanup test msg
    smart_cleanup_msg(msg);

    if (is_smart_frame_readed)
        return frame;
    else return NULL;
}

rfBool rf627_smart_write_params_to_scanner(rf627_smart_t* scanner)
{

    int count = 0;
    for(rfSize i = 0; i < vector_count(scanner->params_list); i++)
    {
        parameter_t* p = vector_get(scanner->params_list, i);
        if (p->is_changed)
        {
            count++;
        }
    }

    if (count > 0)
    {
        // Create FULL DATA packet for measurement SIZE of data packet
        mpack_writer_t writer;
        char* send_packet = NULL;
        size_t bytes = 0;				///< Number of msg bytes.
        mpack_writer_init_growable(&writer, &send_packet, &bytes);

        // write the example on the msgpack homepage
        mpack_start_map(&writer, count);
        {
            for(rfSize i = 0; i < vector_count(scanner->params_list); i++)
            {
                parameter_t* p = vector_get(scanner->params_list, i);
                if (p->is_changed)
                {
                    // Идентификатор устройства, отправившего сообщения
                    mpack_write_cstr(&writer, p->base.name);
                    if(rf_strcmp(parameter_value_types[PVT_UINT], p->base.type) == 0)
                    {
                        mpack_write_u32(&writer, p->val_uint32->value);
                    }else if(rf_strcmp(parameter_value_types[PVT_UINT64], p->base.type) == 0)
                    {
                       mpack_write_u64(&writer, p->val_uint64->value);
                    }else if(rf_strcmp(parameter_value_types[PVT_INT], p->base.type) == 0)
                    {
                       mpack_write_i32(&writer, p->val_int32->value);
                    }else if(rf_strcmp(parameter_value_types[PVT_INT64], p->base.type) == 0)
                    {
                        mpack_write_i64(&writer, p->val_int64->value);
                    }else if(rf_strcmp(parameter_value_types[PVT_FLOAT], p->base.type) == 0)
                    {
                       mpack_write_float(&writer, p->val_flt->value);
                    }else if(rf_strcmp(parameter_value_types[PVT_DOUBLE], p->base.type) == 0)
                    {
                        mpack_write_double(&writer, p->val_dbl->value);
                    }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_UINT32], p->base.type) == 0)
                    {
                        mpack_start_array(&writer, p->arr_uint32->count);
                        {
                            for (rfSize ii = 0; ii < p->arr_uint32->count; ii++)
                                mpack_write_u32(&writer, p->arr_uint32->value[ii]);
                        }mpack_finish_array(&writer);
                    }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_UINT64], p->base.type) == 0)
                    {
                        mpack_start_array(&writer, p->arr_uint64->count);
                        {
                            for (rfSize ii = 0; ii < p->arr_uint64->count; ii++)
                                mpack_write_u64(&writer, p->arr_uint64->value[ii]);
                        }mpack_finish_array(&writer);
                    }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_INT32], p->base.type) == 0)
                    {
                        mpack_start_array(&writer, p->arr_int32->count);
                        {
                            for (rfSize ii = 0; ii < p->arr_int32->count; ii++)
                                mpack_write_i32(&writer, p->arr_int32->value[ii]);
                        }mpack_finish_array(&writer);
                    }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_INT64], p->base.type) == 0)
                    {
                        mpack_start_array(&writer, p->arr_int64->count);
                        {
                            for (rfSize ii = 0; ii < p->arr_int64->count; ii++)
                                mpack_write_i64(&writer, p->arr_int64->value[ii]);
                        }mpack_finish_array(&writer);
                    }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_FLT], p->base.type) == 0)
                    {
                        mpack_start_array(&writer, p->arr_flt->count);
                        {
                            for (rfSize ii = 0; ii < p->arr_flt->count; ii++)
                                mpack_write_float(&writer, p->arr_flt->value[ii]);
                        }mpack_finish_array(&writer);
                    }else if(rf_strcmp(parameter_value_types[PVT_ARRAY_DBL], p->base.type) == 0)
                    {
                        mpack_start_array(&writer, p->arr_dbl->count);
                        {
                            for (rfSize ii = 0; ii < p->arr_dbl->count; ii++)
                                mpack_write_i32(&writer, p->arr_dbl->value[ii]);
                        }mpack_finish_array(&writer);
                    }else if(rf_strcmp(parameter_value_types[PVT_STRING], p->base.type) == 0)
                    {
                        mpack_write_str(&writer, p->val_str->value, p->base.size);
                    }
                    p->is_changed = FALSE;
                }

            }
        }mpack_finish_map(&writer);

        // finish writing
        if (mpack_writer_destroy(&writer) != mpack_ok) {
            fprintf(stderr, "An error occurred encoding the data!\n");
            return FALSE;
        }

        smart_msg_t* msg = smart_create_rqst_msg("SET_PARAMETERS", send_packet, bytes, "mpack", FALSE, FALSE, TRUE,
                                                 3000,
                                                 rf627_smart_write_params_callback,
                                                 rf627_smart_write_params_timeout_callback);
        // Send test msg
        if (!smart_channel_send_msg(&scanner->channel, msg))
            printf("No data has been sent.\n");
        else
            printf("Requests were sent.\n");

        // Cleanup test msg
        smart_cleanup_msg(msg);
        free(send_packet); send_packet = NULL;

        return TRUE;
    }

    return FALSE;
}



rfInt8 rf627_smart_get_authorization_token_callback(char* data, uint32_t data_size, uint32_t device_id, void* rqst_msg)
{
    answ_count++;
    printf("%d - Answers were received. Received payload size: %d\n", answ_count, data_size);

    int32_t result = SMART_PARSER_RETURN_STATUS_NO_DATA;
    rfBool existing = FALSE;

    // Get params
    mpack_tree_t tree;
    mpack_tree_init_data(&tree, (const char*)data, data_size);
    mpack_tree_parse(&tree);
    if (mpack_tree_error(&tree) != mpack_ok)
    {
        result = SMART_PARSER_RETURN_STATUS_DATA_ERROR;
        mpack_tree_destroy(&tree);
        return result;
    }

    for (rfUint32 i = 0; i < vector_count(search_result); i++)
    {
        if(((scanner_base_t*)vector_get(search_result, i))->type == kRF627_SMART)
        {
            uint32_t serial = ((scanner_base_t*)vector_get(search_result, i))->rf627_smart->info_by_service_protocol.fact_general_serial;
            if (serial == device_id)
                existing = TRUE;
        }
    }

    if (existing)
    {
        smart_msg_t* msg = rqst_msg;
        typedef struct
        {
            uint8_t status;
            char* token;
        }answer;
        msg->result = memory_platform.rf_calloc(1, sizeof (answer));

        mpack_node_t root = mpack_tree_root(&tree);
        mpack_node_t token_data = mpack_node_map_cstr(root, "token");
        uint32_t token_size = mpack_node_strlen(token_data) + 1;
        ((answer*)(msg->result))->token = mpack_node_cstr_alloc(token_data, token_size);
        ((answer*)(msg->result))->status = TRUE;

    }

    mpack_tree_destroy(&tree);
    return TRUE;
}

rfInt8 rf627_smart_get_authorization_token_timeout_callback()
{
    printf("get authorization token timeout\n");
}


rfBool rf627_smart_get_authorization_token_by_service_protocol(rf627_smart_t* scanner, char** token, rfUint32 timeout)
{
    bool is_ok = FALSE;
    smart_msg_t* msg = smart_create_rqst_msg("GET_AUTHORIZATION_TOKEN", NULL, 0, "blob", FALSE, FALSE, TRUE,
                                             timeout,
                                             rf627_smart_get_authorization_token_callback,
                                             rf627_smart_get_authorization_token_timeout_callback);

    // Send test msg
    if (!smart_channel_send_msg(&scanner->channel, msg))
        printf("No data has been sent.\n");
    else
        printf("Requests were sent.\n");

    //delay(timeout);
    int index = -1;
    clock_t goal = timeout + clock();
    smart_msg_t* a1 = &scanner->channel.smart_parser.output_msg_buffer[0].msg;
    smart_msg_t* a2 = &scanner->channel.smart_parser.output_msg_buffer[1].msg;
    while (goal > clock())
    {
        for(int i = 0; i < SMART_PARSER_OUTPUT_BUFFER_QUEUE; i++)
        {
            if (scanner->channel.smart_parser.output_msg_buffer[i].msg._msg_uid == msg->_msg_uid)
            {
                if (scanner->channel.smart_parser.output_msg_buffer[i].msg.result != NULL)
                {
                    typedef struct
                    {
                        uint8_t status;
                        char* token;
                    }answer;

                    answer* ans = (answer*)(scanner->channel.smart_parser.output_msg_buffer[i].msg.result);
                    is_ok = ans->status;
                    index = i;
                    break;
                }
            }
        }

        if (is_ok == TRUE)
            break;
    }

    if(is_ok)
    {
        typedef struct
        {
            uint8_t status;
            char* token;
        }answer;

        answer* ans = (answer*)(scanner->channel.smart_parser.output_msg_buffer[index].msg.result);
        int size = rf_strlen((rfChar*)(ans->token)) + 1;
        *token = memory_platform.rf_calloc(1, size);
        memory_platform.rf_memcpy(*token, ((answer*)(scanner->channel.smart_parser.output_msg_buffer[index].msg.result))->token, size);
        //                *token = (*(answer*)(scanner->channel.smart_parser.output_msg_buffer[i].msg.result)).token;
        free(ans->token); ans->token = NULL;
        free(ans); ans = NULL;
        is_ok = true;
    }

    // Cleanup test msg
    smart_cleanup_msg(msg);

    if (is_ok)
        return TRUE;
    else return FALSE;
}
