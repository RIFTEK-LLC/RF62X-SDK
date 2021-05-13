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
    printf("#         Search Example v2.x.x         #\n");
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
        printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));
        printf("-----------------------------------------\n");
    }


    for (int i = 0; i < (int)vector_count(scanners); i++)
    {
        hello_information result =
                get_info_about_scanner(vector_get(scanners,i), kSERVICE);

        rf627_smart_hello_info_by_service_protocol* info =
                result.rf627smart.hello_info_service_protocol;

        printf("\n\nID scanner's list: %d\n", i);
        printf("-----------------------------------------\n");
        printf("Device information: \n");
        printf("* Name\t: %s\n", info->user_general_deviceName);
        printf("* Serial\t: %d\n", info->fact_general_serial);
        printf("* IP Addr\t: %s\n", info->user_network_ip);
        printf("* MAC Addr\t: %s\n", info->fact_network_macAddr);

        printf("\nWorking ranges: \n");
        printf("* Zsmr, mm\t: %d\n", info->fact_general_smr);
        printf("* Zmr , mm\t: %d\n", info->fact_general_mr);
        printf("* Xsmr, mm\t: %d\n", info->fact_general_xsmr);
        // printf("* Xemr, mm\t: %d\n", info->fact_general_xemr);

        printf("\nVersions: \n");
        printf("* Firmware\t: %d.%d.%d\n",
               info->fact_general_firmwareVer[0],
               info->fact_general_firmwareVer[1],
               info->fact_general_firmwareVer[2]);
        printf("* Hardware\t: %d\n", info->fact_general_hardwareVer);
        printf("-----------------------------------------\n");
    }

    // Cleanup resources allocated with core_init()
    FreeAdapterAddresses();
#ifdef _WIN32
    WinSockDeinit();
#endif
}


























