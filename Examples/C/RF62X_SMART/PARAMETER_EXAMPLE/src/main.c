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
    printf("#       Parameter Example v2.x.x        #\n");
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
        printf("\n\nID scanner's list: %d\n", i);
        printf("-----------------------------------------\n");

        uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);

        uint8_t is_read = read_params_from_scanner(scanner, 3000, kSERVICE);

        if (is_connected && is_read)
        {
            //
            // Example of working with the parameter type:
            // std::string
            //
            // Get parameter of Device Name (first way to get parameter by string name)
            parameter_t* name = get_parameter(scanner,"user_general_deviceName");
            if (name != NULL && strcmp(name->base.type, "string_t")== 0)
            {
                char* value = name->val_str->value;
                printf("Current Device Name\t: %s\n", value);

                parameter_t* temp_param = create_parameter_from_type(name->base.type);

                char* name_param = name->base.name;
                uint32_t name_param_size = strlen(name_param) + 1;
                temp_param->base.name = platform_calloc(name_param_size, sizeof (char));
                platform_memcpy(temp_param->base.name, name_param, name_param_size);

                char* new_value = "TEST NAME";
                printf("New Device Name\t: %s\n", new_value);
                uint32_t new_value_size = strlen(new_value) + 1;
                temp_param->val_str->value = platform_calloc(new_value_size, sizeof (char));
                platform_memcpy(temp_param->val_str->value, new_value, new_value_size);
                temp_param->base.size = new_value_size;
                printf("-------------------------------------\n");

                set_parameter(scanner, temp_param);
                free_parameter(temp_param, scanner->type);

            }


            //
            // Example of working with the parameter type:
            // uint32_t
            //
            // Get parameter of Laser Enabled
            parameter_t* laser_enabled = get_parameter(
                        scanner,parameter_names[USER_LASER_ENABLED]);
            if (laser_enabled != NULL && strcmp(
                        laser_enabled->base.type, parameter_value_types[PVT_UINT])== 0)
            {
                uint32_t isEnabled = laser_enabled->val_uint32->value;
                printf("Current Laser State\t: %s\n", (isEnabled?"ON":"OFF"));

                // Change the current state to the opposite
                isEnabled = !isEnabled;
                laser_enabled->val_uint32->value = isEnabled;
                printf("New Laser State\t: %s\n", (isEnabled?"ON":"OFF"));
                printf("-------------------------------------\n");

                set_parameter(scanner, laser_enabled);
            }
        }

        // Apply changed parameters to the device
        char answer = 'n';
        printf("Apply changed params to the device? (y/n): ");
        scanf("%c", &answer);
        if (answer == 'y' || answer == 'Y')
        {
            write_params_to_scanner(scanner, 3000, kSERVICE);
            // Save changes to the device's memory
            printf("\nSave changes to device's memory? (y/n): ");
            scanf("%c", &answer);
            if (answer == 'y' || answer == 'Y')
                save_params_to_scanner(scanner, 3000, kSERVICE);
        }

    }

    // Cleanup resources allocated with core_init()
    FreeAdapterAddresses();
#ifdef _WIN32
    WinSockDeinit();
#endif
}


























