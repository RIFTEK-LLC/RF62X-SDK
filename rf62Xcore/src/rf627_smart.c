#include "rf62X_sdk.h"
#include "iostream_platform.h"
#include "custom_string.h"
#include "smartchannel.h"
#include "smartmsg.h"
#include <stdarg.h>
#include <stdio.h>


#include<time.h>
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int answ_count = 0;
void rf627_smart_get_hello_callback(char* data, uint32_t data_size)
{
    answ_count++;
    printf("%d - Answers were received. Received payload size: %d\n", answ_count, data_size);

//    rfBool existing = 0;

//    for (rfUint32 i = 0; i < vector_count(result); i++)
//    {
//        if(((scanner_base_t*)vector_get(result, i))->type == kRF627_OLD)
//        {
//            if (!memory_platform.
//                    rf_memcmp(((scanner_base_t*)vector_get(result, i))->
//                              rf627_old->factory_params.network.mac,
//                              response_payload_msg.hardware_address, 6))
//            {
//                existing = 1;
//                break;
//            }

//        }
//    }

//    if (!existing)
//    {
//        scanner_base_t* rf627 =
//                memory_platform.rf_calloc(1, sizeof(scanner_base_t));

//        rf627->type = kRF627_OLD;
//        rf627->rf627_old = rf627_old_create_from_hello_msg(
//                    &response_payload_msg, response_header_msg.msg_count + 1);
//        vector_add(result, rf627);
//    }
}

void rf627_smart_get_hello_timeout_callback()
{
    printf("get_hello_timeout\n");
}

uint8_t rf627_smart_search_by_service_protocol(vector_t *result, rfUint32 ip_addr)
{
    char* config = "-dst_ip_addr 192.168.1.255 "
                   "-in_udp_port 50011 "
                   "-max_packet_size 65000 "
                   "-out_udp_port 50011 "
                   "-socket_timeout 100 "
                   "-max_data_size 65535";

    smart_channel channel;

    smart_channel_init(&channel, config);

    smart_msg_t* msg = smart_create_rqst_msg("GET_HELLO", NULL, 0, FALSE, FALSE, 3000,
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

