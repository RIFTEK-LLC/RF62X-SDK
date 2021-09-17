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
    printf("#        Profile Example v2.x.x         #\n");
    printf("#                                       #\n");
    printf("#########################################\n");

    // Initialize sdk library
    core_init();

    // Print return rf627 sdk version
    printf("SDK version: %s\n", sdk_version());
    printf("=========================================\n");


    // Create value for scanners vector's type
    void* scanners = NULL;// = calloc(1, sizeof (vector_t));
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
        printf("* MAC Addr\t: %s\n", info->fact_network_macAddr);

        uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);

        uint8_t is_read = read_params_from_scanner(scanner, 3000, kSERVICE);

        if (is_connected && is_read)
        {
            uint8_t zero_points = TRUE;
            uint8_t realtime = TRUE;
            // Get profile from scanner's data stream by Service Protocol.
            rf627_profile2D_t* result = get_profile2D_from_scanner(
                        scanner, zero_points, realtime, kSERVICE);
            rf627_smart_profile2D_t* profile2D = result->rf627smart_profile2D;
            if (profile2D != NULL)
            {
                printf("Profile information: \n");
                switch (profile2D->header.data_type)
                {
                case (int)DTY_PixelsNormal:
                {
                    printf("* DataType\t: PIXELS\n");
                    printf("* Count\t\t: %d\n", profile2D->pixels_format.pixels_count);
                    break;
                }
                case (int)DTY_PixelsInterpolated:
                {
                    printf("* DataType\t: PIXELS_INTRP\n");
                    printf("* Count\t\t: %d\n", profile2D->pixels_format.pixels_count);
                    break;
                }
                case (int)DTY_ProfileNormal:
                {
                    printf("* DataType\t: PROFILE\n");
                    printf("* Count\t\t: %d\n", profile2D->profile_format.points_count);
                    break;
                }
                case (int)DTY_ProfileInterpolated:
                {
                    printf("* DataType\t: PROFILE_INTRP\n");
                    printf("* Count\t\t: %d\n", profile2D->profile_format.points_count);
                    break;
                }
                }
                printf("Profile was successfully received!\n");
                printf("-----------------------------------------\n");
                free_profile2D(result);
            }else
            {
                printf("Profile was not received!\n");
                printf("-----------------------------------------\n");
            }
        }

        disconnect_from_scanner(scanner, kSERVICE);
    }


    // Cleanup resources allocated with core_init()
    FreeAdapterAddresses();
#ifdef _WIN32
    WinSockDeinit();
#endif
}


























