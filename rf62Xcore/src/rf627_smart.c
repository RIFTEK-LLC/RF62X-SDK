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
vector_t *search_result;
rfInt8 rf627_smart_get_hello_callback(char* data, uint32_t data_size)
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
    mpack_node_t root = mpack_tree_root(&tree);

    // Серийник сканера
    uint32_t fact_general_serial = 0;
    if (mpack_node_map_contains_cstr(root, "fact_general_serial"))
    {
        fact_general_serial = mpack_node_uint(mpack_node_map_cstr(root, "fact_general_serial"));
    }else
    {
        result = SMART_PARSER_RETURN_STATUS_DATA_ERROR;
        mpack_tree_destroy(&tree);
        return result;
    }


    for (rfUint32 i = 0; i < vector_count(search_result); i++)
    {
        if(((scanner_base_t*)vector_get(search_result, i))->type == kRF627_SMART)
        {
            parameter_t* param = rf627_smart_get_parameter(((scanner_base_t*)vector_get(search_result, i))->rf627_smart, "fact_general_serial");
            if (param != NULL)
            {
                if (param->val_uint32->value == fact_general_serial)
                    existing = TRUE;
            }
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
}

rfInt8 rf627_smart_get_hello_timeout_callback()
{
    printf("get_hello_timeout\n");
}

uint8_t rf627_smart_search_by_service_protocol(vector_t *result, rfUint32 ip_addr)
{
    char config[1024];
    search_result = result;
    unsigned char bytes[4];
    bytes[0] = ip_addr & 0xFF;
    bytes[1] = (ip_addr >> 8) & 0xFF;
    bytes[2] = (ip_addr >> 16) & 0xFF;
    bytes[3] = (ip_addr >> 24) & 0xFF;

    sprintf(config, "-dst_ip_addr %d.%d.%d.%d "
                    "-host_ip_addr %d.%d.%d.%d "
                    "-in_udp_port 50011 "
                    "-max_packet_size 65000 "
                    "-out_udp_port 50011 "
                    "-socket_timeout 100 "
                    "-max_data_size 65535",
            bytes[3], bytes[2], bytes[1], 255,
            bytes[3], bytes[2], bytes[1], bytes[0]);

    smart_channel channel;

    smart_channel_init(&channel, config);

    smart_msg_t* msg = smart_create_rqst_msg("GET_HELLO", NULL, 0, FALSE, FALSE, FALSE,
                                             3000,
                                             rf627_smart_get_hello_callback,
                                             rf627_smart_get_hello_timeout_callback);

    // Send test msg
    if (!smart_channel_send_msg(&channel, msg))
        printf("No data has been sent.\n");
    else
        printf("Requests were sent.\n");


    delay(3000);

    // Cleanup test msg
    smart_cleanup_msg(msg);
    smart_channel_cleanup(&channel);

    return answ_count;
}



rf627_smart_t* rf627_smart_create_from_hello_msg(
        char* data, rfUint32 data_size)
{
    rf627_smart_t* rf627_smart = memory_platform.rf_calloc(1, sizeof (rf627_smart_t));

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
                    "-max_packet_size 65000 "
                    "-out_udp_port %d "
                    "-socket_timeout 100 "
                    "-max_data_size 65535",
            scanner->info_by_service_protocol.user_network_ip,
            scanner->info_by_service_protocol.user_network_hostIP,
            scanner->info_by_service_protocol.user_network_servicePort,
            scanner->info_by_service_protocol.user_network_servicePort);

    smart_channel channel;

    if (smart_channel_init(&channel, config))
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
    smart_channel_cleanup(scanner->channel);

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

rfInt8 rf627_smart_read_params_callback(char* data, uint32_t data_size)
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
    mpack_node_t root = mpack_tree_root(&tree);

    // Серийник сканера
    uint32_t fact_general_serial = 0;
    if (mpack_node_map_contains_cstr(root, "fact_general_serial"))
    {
        fact_general_serial = mpack_node_uint(mpack_node_map_cstr(root, "fact_general_serial"));
    }else
    {
        result = SMART_PARSER_RETURN_STATUS_DATA_ERROR;
        mpack_tree_destroy(&tree);
        return result;
    }


    for (rfUint32 i = 0; i < vector_count(search_result); i++)
    {
        if(((scanner_base_t*)vector_get(search_result, i))->type == kRF627_SMART)
        {
            parameter_t* param = rf627_smart_get_parameter(((scanner_base_t*)vector_get(search_result, i))->rf627_smart, "fact_general_serial");
            if (param != NULL)
            {
                if (param->val_uint32->value == fact_general_serial)
                    existing = TRUE;
            }
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
}

rfInt8 rf627_smart_read_params_timeout_callback()
{
    printf("get_hello_timeout\n");
}


//rfBool rf627_smart_read_params_from_scanner(rf627_smart_t* scanner)
//{

//    smart_msg_t* msg = smart_create_rqst_msg("GET_PARAMS_DESCRIPTION", NULL, 0, FALSE, FALSE, TRUE,
//                                             3000,
//                                             rf627_smart_read_params_callback,
//                                             rf627_smart_read_params_timeout_callback);

//    // Send test msg
//    if (!smart_channel_send_msg(&channel, msg))
//        printf("No data has been sent.\n");
//    else
//        printf("Requests were sent.\n");


//    delay(3000);

//    // Cleanup test msg
//    smart_cleanup_msg(msg);


//                rfUint16 index = 0;
//                parameter_t* p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_DEVICETYPE];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 0;
//                p->base.size = sizeof(scanner->factory_params.general.device_id);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.general.device_id;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 65535;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_SERIAL];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 2;
//                p->base.size = sizeof(scanner->factory_params.general.serial);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.general.serial;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 4294967295;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_PCBSERIAL];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 6;
//                p->base.size = sizeof(scanner->factory_params.general.serial_of_pcb);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.general.serial_of_pcb;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 4294967295;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_LIFETIME];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 10;
//                p->base.size = sizeof(scanner->factory_params.general.operating_time_h);
//                p->base.units = "s";

//                p->val_uint32->value =
//                        scanner->factory_params.general.operating_time_h * 60 * 60 +
//                        scanner->factory_params.general.operating_time_m * 60 +
//                        scanner->factory_params.general.operating_time_s;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 1577846272;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_WORKTIME];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 16;
//                p->base.size = sizeof(scanner->factory_params.general.runtime_h);
//                p->base.units = "s";

//                p->val_uint32->value =
//                        scanner->factory_params.general.runtime_h * 60 * 60 +
//                        scanner->factory_params.general.runtime_m * 60 +
//                        scanner->factory_params.general.runtime_s;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 1577846272;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_STARTSCOUNT];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 22;
//                p->base.size = sizeof(scanner->factory_params.general.startup_counter);
//                p->base.units = "count";

//                p->val_uint32->value = scanner->factory_params.general.startup_counter;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 8760;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_FIRMWAREREV];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 26;
//                p->base.size = sizeof(scanner->factory_params.general.firmware_ver);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.general.firmware_ver;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 4294967295;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_HARDWAREREV];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 30;
//                p->base.size = sizeof(scanner->factory_params.general.hardware_ver);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.general.hardware_ver;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 4294967295;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_CUSTOMERID];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 34;
//                p->base.size = sizeof(scanner->factory_params.general.customer_id);
//                p->base.units = "id";

//                p->val_uint32->value = scanner->factory_params.general.customer_id;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 4294967295;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_FPGAFREQ];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 38;
//                p->base.size = sizeof(scanner->factory_params.general.fpga_freq);
//                p->base.units = "Hz";

//                p->val_uint32->value = scanner->factory_params.general.fpga_freq;
//                p->val_uint32->min = 100000000;
//                p->val_uint32->max = 100000000;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_SMR];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 42;
//                p->base.size = sizeof(scanner->factory_params.general.base_z);
//                p->base.units = "mm";

//                p->val_uint32->value = scanner->factory_params.general.base_z;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 10000;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_MR];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 46;
//                p->base.size = sizeof(scanner->factory_params.general.range_z);
//                p->base.units = "mm";

//                p->val_uint32->value = scanner->factory_params.general.range_z;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 10000;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_XSMR];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 50;
//                p->base.size = sizeof(scanner->factory_params.general.range_x_start);
//                p->base.units = "mm";

//                p->val_uint32->value = scanner->factory_params.general.range_x_start;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 10000;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_XEMR];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 54;
//                p->base.size = sizeof(scanner->factory_params.general.range_x_end);
//                p->base.units = "mm";

//                p->val_uint32->value = scanner->factory_params.general.range_x_end;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 20000;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_PIXDIVIDER];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 58;
//                p->base.size = sizeof(scanner->factory_params.general.pixels_divider);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.general.pixels_divider;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 65535;
//                p->val_uint32->step = 8;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_PROFDIVIDER];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 60;
//                p->base.size = sizeof(scanner->factory_params.general.profiles_divider);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.general.profiles_divider;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 65535;
//                p->val_uint32->step = 8;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_GENERAL_FSBLREV];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 62;
//                p->base.size = sizeof(scanner->factory_params.general.fsbl_version);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.general.fsbl_version;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 4294967295;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_STRING]);
//                p->base.name = parameter_names[FACT_GENERAL_OEMDEVNAME];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 66;
//                p->base.size = rf_strlen(scanner->factory_params.general.oem_device_name) + 1;
//                p->base.units = "";

//                p->val_str->value = memory_platform.rf_calloc(1, sizeof(rfChar) * p->base.size);
//                memory_platform.rf_memcpy(
//                            (void*)p->val_str->value,
//                            scanner->factory_params.general.oem_device_name,
//                            p->base.size);
//                p->val_str->maxLen = sizeof (scanner->factory_params.general.oem_device_name);
//                p->val_str->defValue = "Laser scanner";
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_STRING]);
//                p->base.name = parameter_names[FACT_SENSOR_NAME];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 158;
//                p->base.size = rf_strlen(scanner->factory_params.sensor.name) + 1;
//                p->base.units = "";

//                p->val_str->value = memory_platform.rf_calloc(1, sizeof(rfChar) * p->base.size);
//                memory_platform.rf_memcpy(
//                            (void*)p->val_str->value,
//                            scanner->factory_params.sensor.name,
//                            p->base.size);
//                p->val_str->maxLen = sizeof (scanner->factory_params.sensor.name);
//                p->val_str->defValue = "TYPE1";
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_WIDTH];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 190;
//                p->base.size = sizeof(scanner->factory_params.sensor.width);
//                p->base.units = "pixels";

//                p->val_uint32->value = scanner->factory_params.sensor.width;
//                p->val_uint32->min = 648;
//                p->val_uint32->max = 648;
//                p->val_uint32->step = 4;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_HEIGHT];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 192;
//                p->base.size = sizeof(scanner->factory_params.sensor.height);
//                p->base.units = "lines";

//                p->val_uint32->value = scanner->factory_params.sensor.height;
//                p->val_uint32->min = 488;
//                p->val_uint32->max = 488;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_PIXFREQ];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 194;
//                p->base.size = sizeof(scanner->factory_params.sensor.pixel_clock);
//                p->base.units = "Hz";

//                p->val_uint32->value = scanner->factory_params.sensor.pixel_clock;
//                p->val_uint32->min = 40000000;
//                p->val_uint32->max = 40000000;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_BLACKODD];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 198;
//                p->base.size = sizeof(scanner->factory_params.sensor.black_odd_lines);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.sensor.black_odd_lines;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 65535;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_BLACKEVEN];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 200;
//                p->base.size = sizeof(scanner->factory_params.sensor.black_even_lines);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.sensor.black_even_lines;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 65535;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_FRMCONSTPART];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 202;
//                p->base.size = sizeof(scanner->factory_params.sensor.frame_cycle_const_part);
//                p->base.units = "ticks";

//                p->val_uint32->value = scanner->factory_params.sensor.frame_cycle_const_part;
//                p->val_uint32->min = 6500;
//                p->val_uint32->max = 6500;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_FRMPERLINEPART];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 206;
//                p->base.size = sizeof(scanner->factory_params.sensor.frame_cycle_per_line_part);
//                p->base.units = "ticks";

//                p->val_uint32->value = scanner->factory_params.sensor.frame_cycle_per_line_part;
//                p->val_uint32->min = 410;
//                p->val_uint32->max = 410;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_FPSOREXP];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 210;
//                p->base.size = sizeof(scanner->factory_params.sensor.frame_rate_or_exposure);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.sensor.frame_rate_or_exposure;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 1;
//                p->val_uint32->step = 0;
//                p->val_uint32->enumValues = &boolEnum;
//                rfInt* def = get_value_by_key_from_enum(p->val_uint32->enumValues, "false");
//                if (def != NULL)
//                    p->val_uint32->defValue = *def;
//                else p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_MINEXPOSURE];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 211;
//                p->base.size = sizeof(scanner->factory_params.sensor.min_exposure);
//                p->base.units = "ns";

//                p->val_uint32->value = scanner->factory_params.sensor.min_exposure;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 100000000;
//                p->val_uint32->step = 10;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_IMGFLIP];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 215;
//                p->base.size = sizeof(scanner->factory_params.sensor.image_flipping);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.sensor.image_flipping;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 3;
//                p->val_uint32->step = 0;
//                p->val_uint32->enumValues = &flipEnum;
//                def = get_value_by_key_from_enum(p->val_uint32->enumValues, "No");
//                if (def != NULL)
//                    p->val_uint32->defValue = *def;
//                else p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);



//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_SENSOR_MAXEXPOSURE];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 216;
//                p->base.size = sizeof(scanner->factory_params.sensor.max_exposure);
//                p->base.units = "ns";

//                p->val_uint32->value = scanner->factory_params.sensor.max_exposure;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 300000000;
//                p->val_uint32->step = 10;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);

//                //edr_point1_value
//                //edr_point2_value
//                //edr_point1_pos
//                //edr_point2_pos
//                //init_regs


//                p = create_parameter_from_type(parameter_value_types[PVT_ARRAY_UINT32]);
//                p->base.name = parameter_names[FACT_NETWORK_MACADDR];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 595;
//                p->base.size = sizeof (scanner->factory_params.network.mac);
//                p->base.units = "";

//                p->arr_uint32->value = memory_platform.rf_calloc(1, sizeof(rfUint32) * 6);
//                for (rfUint32 i = 0; i < p->base.size; i++)
//                    p->arr_uint32->value[i] = scanner->factory_params.network.mac[i];
//                p->arr_uint32->min = 0;
//                p->arr_uint32->max = 255;
//                p->arr_uint32->step = 0;
//                p->arr_uint32->defCount = 6;
//                p->arr_uint32->defValue = memory_platform.rf_calloc(1, sizeof (rfUint32) * 6);
//                rfUint32 de_arr[6] = {0, 10, 53, 1, 2, 3};
//                for (rfUint32 i = 0; i < 6; i++)
//                    p->arr_uint32->defValue[i] = de_arr[i];
//                p->arr_uint32->maxCount = 6;
//                vector_add(scanner->params_list, p);




//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_EIP_IDENTITY_VENDORID];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 601;
//                p->base.size = sizeof(scanner->factory_params.network.eip_vendor_id);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.network.eip_vendor_id;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 65535;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);




//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_EIP_IDENTITY_DEVICETYPE];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 603;
//                p->base.size = sizeof(scanner->factory_params.network.eip_device_type);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.network.eip_device_type;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 65535;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);




//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_NETWORK_FORCEAUTONEGTIME];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 605;
//                p->base.size = sizeof(scanner->factory_params.network.force_autoneg_time);
//                p->base.units = "s";

//                p->val_uint32->value = scanner->factory_params.network.force_autoneg_time;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 255;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);




//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_LASER_WAVELENGTH];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 637;
//                p->base.size = sizeof(scanner->factory_params.laser.wave_length);
//                p->base.units = "nm";

//                p->val_uint32->value = scanner->factory_params.laser.wave_length;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 10000;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);




//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_LASER_KOEFF1];
//                p->base.access = patKey[PAT_READ_ONLY];
//                p->base.index = index++;
//                p->base.offset = 639;
//                p->base.size = sizeof(scanner->factory_params.laser.koeff1);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.laser.koeff1;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 255;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);




//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_LASER_KOEFF2];
//                p->base.access = patKey[PAT_READ_ONLY];
//                p->base.index = index++;
//                p->base.offset = 640;
//                p->base.size = sizeof(scanner->factory_params.laser.koeff2);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.laser.koeff2;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 255;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);




//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_LASER_MINVALUE];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 641;
//                p->base.size = sizeof(scanner->factory_params.laser.min_value);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.laser.min_value;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 4095;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);




//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_LASER_MAXVALUE];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 645;
//                p->base.size = sizeof(scanner->factory_params.laser.max_value);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.laser.max_value;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 4095;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);

//                //enable_mode_change


//                //in1_min_delay
//                //in1_max_delay
//                //max_divider_in1
//                //min_divider_in1

//                //out1_min_delay
//                //out1_max_delay
//                //out1_min_pulse_width
//                //out1_max_pulse_width
//                //out2_min_delay
//                //out2_max_delay
//                //out2_min_pulse_width
//                //out2_max_pulse_width


//                p = create_parameter_from_type(parameter_value_types[PVT_UINT]);
//                p->base.name = parameter_names[FACT_PROFILES_MAXDUMPSIZE];
//                p->base.access = patKey[PAT_LOCKED];
//                p->base.index = index++;
//                p->base.offset = 809;
//                p->base.size = sizeof(scanner->factory_params.profiles.max_dump_size);
//                p->base.units = "";

//                p->val_uint32->value = scanner->factory_params.profiles.max_dump_size;
//                p->val_uint32->min = 0;
//                p->val_uint32->max = 80000;
//                p->val_uint32->step = 0;
//                p->val_uint32->defValue = p->val_uint32->value;
//                vector_add(scanner->params_list, p);


//                ret = 0;
//            }


//        }
//    }
////    _mx[0].unlock();

//    memory_platform.rf_free(RX);
//    memory_platform.rf_free(TX);
//    return ret;
//}

