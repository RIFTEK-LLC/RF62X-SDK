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
    printf("#          Dump Example v2.x.x          #\n");
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
        printf("* MAC Addr\t: %s\n", info->fact_network_macAddr);

        uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);

        uint8_t is_read = read_params_from_scanner(scanner, 3000, kSERVICE);

        while (TRUE)
        if (is_connected && is_read)
        {
            uint8_t status = FALSE;
            rf627_profile2D_t** dumps = NULL;
            uint32_t profiles_in_dump = 0;

            uint32_t count_of_profiles = 1000;
            // Get parameter of user_dump_capacity
            parameter_t* capacity = get_parameter(scanner,"user_dump_capacity");
            if (capacity != NULL && strcmp(capacity->base.type, "uint32_t")== 0)
            {
                capacity->val_uint32->value = count_of_profiles;
                set_parameter(scanner, capacity);
                write_params_to_scanner(scanner, 3000, kSERVICE);
            }

            // Get parameter of user_dump_enabled
            parameter_t* enabled  = get_parameter(scanner,"user_dump_enabled");
            if (enabled != NULL && strcmp(enabled->base.type,"uint32_t")== 0)
            {
                enabled->val_uint32->value = TRUE;
                set_parameter(scanner, enabled);
                write_params_to_scanner(scanner, 3000, kSERVICE);
            }


            uint32_t size = 0;
            // wait dump recording
            do {
                read_params_from_scanner(scanner, 3000, kSERVICE);
                size = get_parameter(scanner,"user_dump_size")->val_uint32->value;
                printf("Current profiles in the dump: %d\n", size);
            }while(size < count_of_profiles);



            // Get parameter of user_dump_enabled
            parameter_t* unit_size =get_parameter(scanner,"fact_dump_unitSize");
            if (unit_size != NULL && strcmp(unit_size->base.type,"uint32_t")== 0)
            {
                dumps = calloc(count_of_profiles, sizeof (rf627_profile2D_t*));
                uint32_t start_index = 0;
                status = get_dumps_profiles_from_scanner(
                            scanner, start_index, count_of_profiles,
                            1000, kSERVICE,
                            dumps, &profiles_in_dump,
                            unit_size->val_uint32->value);
            }

            if (status) {
                printf("%d Profiles were received!\n", profiles_in_dump);
                printf("-----------------------------------------\n");
            }else {
                printf("Dump was not received!\n");
                printf("-----------------------------------------\n");
            }

            for(uint32_t i = 0; i < profiles_in_dump; i++)
                free_profile2D(dumps[i]);
            free(dumps);
        }
    }

    // Cleanup resources allocated with core_init()
    FreeAdapterAddresses();
#ifdef _WIN32
    WinSockDeinit();
#endif
}


























