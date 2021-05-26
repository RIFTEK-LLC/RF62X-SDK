#include <stdio.h>
#include <stdlib.h>

#include "network.h"
#include "rf62Xcore.h"
#include "rf62X_sdk.h"
#include "rf62X_types.h"

int main()
{
    printf("#########################################\n");
    printf("#                                       #\n");
    printf("#         Frame Example v2.x.x          #\n");
    printf("#                                       #\n");
    printf("#########################################\n");

    // Initialize sdk library
    core_init();

    // Print return rf627 sdk version
    printf("SDK version: %s\n", sdk_version());
    printf("=========================================\n");


    // Create value for scanners vector's type
    vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
    // Initialization vector
    vector_init(&scanners);

    // Iterate over all available network adapters in the current operating
    // system to send "Hello" requests.
    uint32_t count = 0;
    for (int i=0; i<GetAdaptersCount(); i++)
    {
        // Get another IP Addr and set this changes in adapter settings.
        printf("Search scanners from:\n "
               "* IP Address\t: %s\n "
               "* Netmask\t: %s\n",
               GetAdapterAddress(i), GetAdapterMasks(i));
        uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
        uint32_t host_mask = ntohl(inet_addr(GetAdapterMasks(i)));
        // call the function to change adapter settings inside the library.
        set_platform_adapter_settings(host_mask, host_ip_addr);

        // Search for RF627-old devices over network by Service Protocol.
        search_scanners(scanners, kRF627_SMART, 500, kSERVICE);

        // Print count of discovered rf627-smart in network by Service Protocol
        printf("Discovered: %d RF627-Smart\n",(int)vector_count(scanners)-count);
        printf("-----------------------------------------\n");
        count = (int)vector_count(scanners);
    }


    for (int i = 0; i < (int)vector_count(scanners); i++)
    {
        scanner_base_t* scanner = vector_get(scanners,i);

        hello_information result = get_info_about_scanner(scanner, kSERVICE);

        rf627_smart_hello_info_by_service_protocol* info =
                result.rf627smart.hello_info_service_protocol;

        printf("\n\nID scanner's list: %d\n", i);
        printf("-----------------------------------------\n");
        printf("Device information: \n");
        printf("* Name\t\t: %s\n", info->user_general_deviceName);
        printf("* Serial\t: %d\n", info->fact_general_serial);
        printf("* IP Addr\t: %s\n", info->user_network_ip);

        uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);

        uint8_t is_read = read_params_from_scanner(scanner, 3000, kSERVICE);

        if (is_connected && is_read)
        {
            rf627_frame_t* _frame = get_frame_from_scanner(scanner, kSERVICE);
            if (_frame != NULL && _frame->rf627smart_frame != NULL)
            {
                // Get parameter of user_dump_enabled
                parameter_t* width = get_parameter(scanner,"fact_sensor_width");
                if (width != NULL && strcmp(width->base.type,"uint32_t")== 0)
                {
                    _frame->rf627smart_frame->width = width->val_uint32->value;
                }

                // Get parameter of user_dump_enabled
                parameter_t* height = get_parameter(scanner,"fact_sensor_height");
                if (height != NULL && strcmp(height->base.type,"uint32_t")== 0)
                {
                    _frame->rf627smart_frame->height = height->val_uint32->value;
                }

                uint32_t data_size = width->val_uint32->value * height->val_uint32->value;
                if (_frame->rf627smart_frame->data_size == data_size)
                {
                    _frame->rf627smart_frame->pixel_size = 1;
                }


                printf("Frame information: \n");
                printf("* Data Size\t: %d\n", data_size);
                printf("* Frame Height\t: %d\n", _frame->rf627smart_frame->height);
                printf("* Frame Width\t: %d\n", _frame->rf627smart_frame->width);
                printf("Frame was successfully received!\n");
                printf("-----------------------------------------\n");

                if(_frame->rf627smart_frame->data != NULL)
                    free(_frame->rf627smart_frame->data);
                free(_frame);
            }
        }

    }

    // Cleanup resources allocated with core_init()
    FreeAdapterAddresses();
#ifdef _WIN32
    WinSockDeinit();
#endif
}


























