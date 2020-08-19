#include <rf62Xcore.h>
#include <network.h>

#include <stdio.h>
#include <stdlib.h>

#include <rf62X_sdk.h>
#include <rf62X_core.h>
#include <rf62X_types.h>

int main()
{

    // Initialize sdk library
    core_init();

    // Print return rf627 sdk version
    printf("SDK version: %s\n", core_version());
    printf("=========================================\n");


    // Create value for scanners vector's type
    vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
    //Initialization vector
    vector_init(&scanners);

    //Iterate over all available network adapters in the current operating
    //system to send "Hello" requests.
    for (int i=0; i<GetAdaptersCount(); i++)
    {
        // get another IP Addr and set this changes in network adapter settings.
        uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
        uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
        // call the function to change adapter settings inside the library.
        set_platform_adapter_settings(host_mask, host_ip_addr);

        // Search for RF627-old devices over network by Service Protocol.
        search_scanners(scanners, kRF627_OLD, kSERVICE);
    }


    // Print count of discovered rf627-old in network by Service Protocol
    printf("Discovered: %d rf627-old\n", (int)vector_count(scanners));

    for (int i = 0; i < (int)vector_count(scanners); i++)
    {
        hello_information info = get_info_about_scanner(vector_get(scanners,i), kSERVICE);


        printf("\n\n\nID scanner's list: %d\n", i);
        printf("-----------------------------------------\n");
        printf("Device information: \n");
        printf("* Name\t: %s\n", info.rf627old.hello_info_service_protocol->device_name);
        printf("* Serial\t: %d\n", info.rf627old.hello_info_service_protocol->serial_number);
        printf("* IP Addr\t: %d.%d.%d.%d\n",
                info.rf627old.hello_info_service_protocol->ip_address[0],
                info.rf627old.hello_info_service_protocol->ip_address[1],
                info.rf627old.hello_info_service_protocol->ip_address[2],
                info.rf627old.hello_info_service_protocol->ip_address[3]);
        printf("* MAC Addr\t: %d:%d:%d:%d:%d:%d\n",
                info.rf627old.hello_info_service_protocol->mac_address[0],
                info.rf627old.hello_info_service_protocol->mac_address[1],
                info.rf627old.hello_info_service_protocol->mac_address[2],
                info.rf627old.hello_info_service_protocol->mac_address[3],
                info.rf627old.hello_info_service_protocol->mac_address[4],
                info.rf627old.hello_info_service_protocol->mac_address[5]);

        printf("\nWorking ranges: \n");
        printf("* Zsmr, mm\t: %d\n", info.rf627old.hello_info_service_protocol->z_begin);
        printf("* Zmr , mm\t: %d\n", info.rf627old.hello_info_service_protocol->z_range);
        printf("* Xsmr, mm\t: %d\n", info.rf627old.hello_info_service_protocol->x_begin);
        printf("* Xemr, mm\t: %d\n", info.rf627old.hello_info_service_protocol->x_end);

        printf("\nVersions: \n");
        printf("* Firmware\t: %d\n", info.rf627old.hello_info_service_protocol->firmware_version);
        printf("* Hardware\t: %d\n", info.rf627old.hello_info_service_protocol->hardware_version);
        printf("-----------------------------------------\n");

    }

    // Cleanup resources allocated with sdk_init()
    FreeAdapterAddresses();
    WinSockDeinit();
}


























