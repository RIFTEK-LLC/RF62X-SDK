

.. _rf62x_wrappers_c_rf627smart:

*******************************************************************************
Интерфейс работы со сканерами серии RF62X v2.x.x
*******************************************************************************

Файлы ``rf62X_sdk.h``, ``rf62X_types.h`` и ``rf62Xcore.h`` предоставляют весь 
необходимый интерфейс для работы со сканерами серии RF62X v2.x.x

.. _rf62x_wrappers_c_rf627smart_search_scanners:

**search_scanners**
===============================================================================

**Прототип:**
   *rfUint8 search_scanners(vector_t \*list, scanner_types_t type, rfUint32 timeout, protocol_types_t protocol);*

**Описание:**
   *Функция поиска устройств RF62X v2.x.x в сети* 

**Параметры:**
   - ``list`` *- Указатель на список, который будет заполнен найденными сканерами в сети.*
   - ``type`` *- Тип сканера для поиска (kRF627_OLD, kRF627_SMART).*
   - ``timeout`` *- Время поиска на каждом Ethernet интерфейсе (мс).*
   - ``protocol`` *- Тип протокола, по которому будет осуществляться поиск (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``TRUE`` *при успехе, иначе -* ``FALSE``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 60

   /** @file rf62X_sdk.h */

   /**
    * @brief search_scanners - Search for RF62X devices over network
    *
    * @param[out] list Ptr to list of rf627 objects. If not null list will be
    * filled with found devices
    * @param[in] type Scanner's type (RF627-old, RF627-smart)
    * @param[in] timeout Time to search
    * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return TRUE on success
    */
   rfUint8 search_scanners(
        vector_t *list, scanner_types_t type,
        rfUint32 timeout, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {

      // Initialize sdk library
      core_init();

      // Create value for scanners vector's type
      vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
      // Initialization vector
      vector_init(&scanners);


      // Iterate over all available network adapters in the current operating
      // system to send "Hello" requests.
      uint32_t count = 0;
      for (int i=0; i<GetAdaptersCount(); i++)
      {
         uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
         uint32_t host_mask = ntohl(inet_addr(GetAdapterMasks(i)));
         // call the function to change adapter settings inside the library.
         set_platform_adapter_settings(host_mask, host_ip_addr);

         // Search for rf627smart devices over network by Service Protocol.
         if (host_ip_addr != 0)
         {
            // Get another IP Addr and set this changes in adapter settings.
            printf("Search scanners from:\n "
                  "* IP Address\t: %s\n "
                  "* Netmask\t: %s\n",
                  GetAdapterAddress(i), GetAdapterMasks(i));
            search_scanners(scanners, kRF627_SMART, 300, kSERVICE);

            // Print count of discovered rf627smart in network
            printf("Discovered\t: %d RF627\n",(int)vector_count(scanners)-count);
            printf("-----------------------------------------\n");
            count = (int)vector_count(scanners);
         }
      }

      // Print count of discovered rf627smart in network
      printf("Was found\t: %d RF627 v2.x.x", (int)vector_count(scanners));
      
      // some code...
   }

.. _rf62x_wrappers_c_rf627smart_get_info_about_scanner:

**get_info_about_scanner**
===============================================================================

**Прототип:**
   *hello_information get_info_about_scanner(scanner_base_t \*device, protocol_types_t protocol);*

**Описание:**
   *Функция получения информации о сканере из пакета приветствия (Hello-пакет)* 

**Параметры:**
   - ``device`` *- Указатель на сканер*
   - ``protocol`` *- Тип протокола, по которому был получен пакет приветствия (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``hello_information`` *в случае успеха, иначе ошибка*

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 39-40, 42-43, 48-51, 54-57, 60-64

   /** @file rf62X_sdk.h */

   /**
    * @brief get_info_about_scanner - Get information about scanner from
    * hello packet
    *
    * @param[in] device Ptr to scanner
    * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return hello_information on success
    */
   hello_information get_info_about_scanner(
         scanner_base_t *device, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

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
         printf("* Xemr, mm\t: %d\n", info->fact_general_xemr);

         printf("\nVersions: \n");
         printf("* Firmware\t: %d.%d.%d\n",
                info->fact_general_firmwareVer[0],
                info->fact_general_firmwareVer[1],
                info->fact_general_firmwareVer[2]);
         printf("* Hardware\t: %d\n", info->fact_general_hardwareVer);
         printf("-----------------------------------------\n");
      }
      
      // some code...
   }

.. _rf62x_wrappers_c_rf627smart_free_scanner:

**free_scanner**
===============================================================================

**Прототип:**
   *void free_scanner(scanner_base_t *device);*

**Описание:**
   *Функция очистки памяти, используемой объектом типа* ``scanner_base_t`` 

**Параметры:**
   - ``device`` *- Указатель на сканер*

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 39

   /** @file rf62X_sdk.h */

   /**
    * @brief free_scanner - Cleanup resources allocated by device
    *
    * @param[in] device Prt to scanner
    */
   void free_scanner(scanner_base_t *device);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      while (vector_count(scanners) > 0)
      {
         uint32_t index = vector_count(scanners)-1;
         // Get last scanner in vector for delete
         scanner_base_t* device = vector_get(scanners, index);
         
         // Cleanup resources allocated by device
         free_scanner(device);

         // Delete from vector
         vector_delete(scanners, index);
      }
   }

.. _rf62x_wrappers_c_rf627smart_connect_to_scanner:

**connect_to_scanner**
===============================================================================

**Прототип:**
   *rfUint8 connect_to_scanner(scanner_base_t \*device, protocol_types_t protocol);*

**Описание:**
   *Функция установки соединения со сканером* 

**Параметры:**
   - ``device`` *- Указатель на сканер*
   - ``protocol`` *- Тип протокола, по которому будет выполнено подключение (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``TRUE`` *при успехе, иначе -* ``FALSE``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 41

   /** @file rf62X_sdk.h */

   /**
    * @brief connect_to_scanner - Establish connection to the RF62X device
    *
    * @param[in] device Ptr to scanner
    * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return TRUE on success
    */
   rfUint8 connect_to_scanner(
         scanner_base_t *device, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         
         // Establish connection to the RF627 device by Service Protocol.
         uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);
         if (!isConnected){
            printf("Failed to connect to scanner!");
            continue;
         }

         // some actions with scanner...
      }
   }

.. _rf62x_wrappers_c_rf627smart_disconnect_from_scanner:

**disconnect_from_scanner**
===============================================================================

**Прототип:**
   *rfUint8 disconnect_from_scanner(scanner_base_t \*device, protocol_types_t protocol);*

**Описание:**
   *Функция закрытия ранее установленного соединения со сканером* 

**Параметры:**
   - ``device`` *- Указатель на сканер*
   - ``protocol`` *- Тип протокола, по которому будет выполнено отключение (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``TRUE`` *при успехе, иначе -* ``FALSE``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 50

   /** @file rf62X_sdk.h */

   /**
    * @brief disconnect_from_scanner - Close connection to the device
    *
    * @param[in] device Prt to scanner
    * @param[in] protocol Protocol's type (Service, ENIP, Modbus-TCP)
    *
    * @return TRUE on success
    */
   rfUint8 disconnect_from_scanner(
         scanner_base_t *device, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         
         // Establish connection to the RF627 device by Service Protocol.
         uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);
         if (!isConnected){
            printf("Failed to connect to scanner!");
            continue;
         }

         // some actions with scanner...

         // Disconnect from scanner.
         disconnect_from_scanner(scanner, kSERVICE)
      }
   }

.. _rf62x_wrappers_c_rf627smart_check_connection_to_scanner:

**check_connection_to_scanner**
===============================================================================

**Прототип:**
   *check_connection_to_scanner(scanner_base_t \*device, rfUint32 timeout, protocol_types_t protocol);*

**Описание:**
   *Функция проверки доступности сканера в сети (после подключения к нему)* 

**Параметры:**
   - ``device`` *- Указатель на сканер*
   - ``timeout`` *- Время проверки соединения со сканером (мс).*
   - ``protocol`` *- Тип протокола, по которому будет выполнена проверка (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``TRUE`` *при успехе, иначе -* ``FALSE``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 49-50

   /** @file rf62X_sdk.h */

   /**
    * @brief check_connection_to_scanner - Check connection to the RF62X device
    *
    * @param[in] device Ptr to scanner
    * @param[in] timeout Time to check connection
    * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return TRUE on success
    */
   rfUint8 check_connection_to_scanner(
         scanner_base_t *device, rfUint32 timeout, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         
         // Establish connection to the RF627 device by Service Protocol.
         uint8_t is_connected = connect_to_scanner(scanner, kSERVICE);
         if (!isConnected){
            printf("Failed to connect to scanner!");
            continue;
         }

         // Check connection to the RF627 device.
         uint8_t is_available = 
               check_connection_to_scanner(scanner, 300, kSERVICE);
         if (!is_available){
            printf("Scanner is not available now!");
            continue;
         }

         // some actions with scanner...
      }
   }

.. _rf62x_wrappers_c_rf627smart_get_profile2D_from_scanner:

**get_profile2D_from_scanner**
===============================================================================

**Прототип:**
   *rf627_profile2D_t\* get_profile2D_from_scanner(scanner_base_t \*device, rfBool zero_points, rfBool realtime, protocol_types_t protocol);*

**Описание:**
   *Функция получения результатов измерений* 

**Параметры:**
   - ``device`` *- Указатель на сканер*
   - ``zero_points`` *- Включать нулевые точки в возвращаемом профиле.*
   - ``realtime`` *- Получение профиля в реальном времени (буферизация отключена).*
   - ``protocol`` *- Тип протокола, по которому будет получен профиль (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   *Указатель на* ``rf627_profile2D_t`` *при успехе, иначе -* ``NULL``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 48-49

   /** @file rf62X_sdk.h */

   /**
    * @brief get_profile2D_from_scanner - Get measurement from scanner's
    * data stream
    *
    * @param[in] device - ptr to scanner
    * @param[in] zero_points Enable zero points in return profile2D
    * @param[in] realtime Enable getting profile in realtime (buffering disabled)
    * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return ptr to rf627_profile_t structure
    */
   rf627_profile2D_t* get_profile2D_from_scanner(
         scanner_base_t *device, rfBool zero_points,
         rfBool realtime, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         connect_to_scanner(scanner, kSERVICE);
         
         uint8_t zero_points = TRUE;
         uint8_t realtime = TRUE;
         // Get profile from scanner's data stream by Service Protocol.
         rf627_profile2D_t* result = get_profile2D_from_scanner(
               scanner, zero_points, realtime, kSERVICE);
         rf627_smart_profile2D_t* profile2D = result->rf627smart_profile2D;
         if (profile2D != NULL) {
            printf("Profile was successfully received!");
            // some actions with profile...
            free_profile2D(result);
         }else
            printf("Profile was not received!");
      }
   }

.. _rf62x_wrappers_c_rf627smart_free_profile2D:

**free_profile2D**
===============================================================================

**Прототип:**
   *void free_profile2D(rf627_profile2D_t\* profile);*

**Описание:**
   *Функция очистки ресурсов, выделенных для rf627_profile2D_t* 

**Параметры:**
   - ``profile`` *- Указатель на профиль*

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 46

   /** @file rf62X_sdk.h */

   /**
    * @brief free_profile2D - Cleanup resources allocated for profile2D
    *
    * @param[in] profile Ptr to rf627_profile2D_t
    */
   void free_profile2D(rf627_profile2D_t* profile);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         connect_to_scanner(scanner, kSERVICE);
         
         uint8_t zero_points = TRUE;
         uint8_t realtime = TRUE;
         // Get profile from scanner's data stream by Service Protocol.
         rf627_profile2D_t* result = get_profile2D_from_scanner(
               scanner, zero_points, realtime, kSERVICE);
         rf627_smart_profile2D_t* profile2D = result->rf627smart_profile2D;
         if (profile2D != NULL) {
            printf("Profile was successfully received!");
            // some actions with profile...
            free_profile2D(result);
         }else
            printf("Profile was not received!");
      }
   }

.. _rf62x_wrappers_c_rf627smart_get_frame_from_scanner:

**get_frame_from_scanner**
===============================================================================

**Прототип:**
   *rf627_frame_t\* get_frame_from_scanner(scanner_base_t \*device, protocol_types_t protocol);*

**Описание:**
   *Функция получения кадров с матрицы устройства* 

**Параметры:**
   - ``device`` *- Указатель на сканер*
   - ``protocol`` *- Тип протокола, по которому будет получен кадр (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   *Указатель на* ``rf627_frame_t`` *при успехе, иначе -* ``NULL``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 42

   /** @file rf62X_sdk.h */

   /**
    * @brief get_frame_from_scanner - Get RAW frame from scanner
    * 
    * @param[in] device Ptr to scanner
    * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    * 
    * @return ptr to rf627_frame_t structure
    */
   rf627_frame_t* get_frame_from_scanner(
         scanner_base_t *device, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         connect_to_scanner(scanner, kSERVICE);
         
         // Get frame from CMOS-sensor.
         rf627_frame_t* frame = get_frame_from_scanner(scanner, kSERVICE);
         if (frame != NULL) {
            printf("Frame was successfully received!");
            // some actions with Frame...
            free_frame(frame);
         }else
            printf("Frame was not received!");
      }
   }

.. _rf62x_wrappers_c_rf627smart_free_frame:

**free_frame**
===============================================================================

**Прототип:**
   *void free_frame(rf627_frame_t\* profile);*

**Описание:**
   *Функция очистки ресурсов, выделенных для rf627_frame_t* 

**Параметры:**
   - ``frame`` *- Указатель на кадр*

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 42

   /** @file rf62X_sdk.h */

   /**
    * @brief free_frame - Cleanup resources allocated for frame
    *
    * @param[in] frame Ptr to rf627_frame_t
    */
   void free_frame(rf627_frame_t* frame);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         connect_to_scanner(scanner, kSERVICE);
         
         // Get frame from CMOS-sensor.
         rf627_frame_t* frame = get_frame_from_scanner(scanner, kSERVICE);
         if (frame != NULL) {
            printf("Frame was successfully received!");
            // some actions with Frame...
            free_frame(frame);
         }else
            printf("Frame was not received!");
      }
   }

.. _rf62x_wrappers_c_rf627smart_read_params_from_scanner:

**read_params_from_scanner**
===============================================================================

**Прототип:**
   *rfUint8 read_params_from_scanner(scanner_base_t \*device, uint32_t timeout, protocol_types_t protocol);*

**Описание:**
   *Функция получения текущих параметров сканера. При вызове данной функции SDK вычитывает*
   *со сканера все актуальные параметры, сохраняя их ввиде «списка параметров» для дальнейшей*
   *работы во внутренней памяти SDK.*

**Параметры:**
   - ``device`` *- Указатель на сканер*
   - ``timeout`` *- Время получения списка параметров со сканера.*
   - ``protocol`` *- Тип протокола, по которому будет выполнена проверка (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``TRUE`` *при успехе, иначе -* ``FALSE``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 43

   /** @file rf62X_sdk.h */

   /**
    * @brief read_params_from_scanner - Read parameters from device to 
    * Internal structure.
    *
    * @param device Ptr to scanner
    * @param timeout Time to read parameters
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return TRUE on success
    */
    rfUint8 read_params_from_scanner(
         scanner_base_t *device, rfUint32 timeout, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         connect_to_scanner(scanner, kSERVICE);
         
         uint8_t is_read = read_params_from_scanner(scanner, 300, kSERVICE);
         if (is_read) {
            printf("Scanner parameters were read successfully!");
            // some actions with params...
         }else
            printf("Scanner parameters were not read!");
      }
   }


.. _rf62x_wrappers_c_rf627smart_get_parameter:

**get_parameter**
===============================================================================

**Прототип:**
   *parameter_t\* get_parameter(scanner_base_t \*device, const rfChar\* param_name);*

**Описание:**
   *Функция получения конкретного параметра по его имени (ключу). При вызове* 
   *данной функции SDK осуществляет поиск нужного параметра из последних прочитанных*
   *при вызове функции* :ref:`rf62x_wrappers_c_rf627smart_read_params_from_scanner` 
   *. В случае, если запрашиваемый параметр отсутствует в конкретном сканере, функция* 
   *вернёт NULL.*

**Параметры:**
   - ``device`` *- Указатель на сканер*
   - ``param_name`` *- Имя (ключ) параметра.*

**Возвращаемое значение:**
   ``parameter_t*`` *при успехе, иначе -* ``NULL``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 47, 54

   /** @file rf62X_sdk.h */

   /**
    * @brief get_parameter - Search parameters by his name
    *
    * @param device - ptr to scanner
    * @param param_name - name of parameter
    *
    * @return param on success, else - null
    */
   parameter_t* get_parameter(
         scanner_base_t *device, const rfChar* param_name);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         
         // Establish connection.
         connect_to_scanner(scanner, kSERVICE);

         // Read params.
         read_params_from_scanner(scanner, 300, kSERVICE);

         // Get parameter of Device Name
         parameter_t* name = get_parameter(scanner,"user_general_deviceName");
         if (name != NULL) {
            char* value = name->val_str->value;
            printf("Current Device Name\t: %s\n", value);
         }

         // Get parameter of Sensor Framerate
         parameter_t* framerate = get_parameter(scanner,"user_sensor_framerate");
         if (framerate != NULL) {
            uint32_t value = framerate->val_uint32->value;
            printf("Current FPS\t\t: %d\n", value);
         }

         // some actions with other parameters...
         
      }
   }

.. note::
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__

.. _rf62x_wrappers_c_rf627smart_set_parameter:

**set_parameter**
===============================================================================

**Прототип:**
   *rfUint8 set_parameter(scanner_base_t \*device, parameter_t\* param)*

**Описание:**
   *Функция установки конкретного параметра. При вызове данной функции происходит*
   установка параметра в списке параметров во внутренней памяти SDK.*
   *Для отправки изменений в сканер необходимо вызвать метод* :ref:`rf62x_wrappers_c_rf627smart_write_params_to_scanner` *.*

**Параметры:**
   - ``device`` *- Указатель на сканер.*
   - ``param`` *- Указатель на параметр для установки.*

**Возвращаемое значение:**
   ``TRUE`` *при успехе, иначе -* ``FALSE``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 63

   /** @file rf62X_sdk.h */

   /**
    * @brief set_parameter - Set parameter
    *
    * @param device Ptr to scanner
    * @param param Parameter name
    *
    * @return TRUE on success
    */
   rfUint8 set_parameter(
         scanner_base_t *device, parameter_t* param);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         
         // Establish connection.
         connect_to_scanner(scanner, kSERVICE);

         // Read params.
         read_params_from_scanner(scanner, 300, kSERVICE);

         //
         // Example of working with the parameter type:
         // uint32_t
         //
         // Get parameter of Laser Enabled
         parameter_t* laser = get_parameter(scanner, "user_laser_enabled");
         if (laser != NULL) 
         {
            uint32_t is_enabled = laser->val_uint32->value;
            printf("Current Laser State\t: %s\n", (is_enabled? "ON":"OFF"));

            // Change the current state to the opposite
            is_enabled = !is_enabled;
            laser_enabled->val_uint32->value = is_enabled;
            printf("New Laser State\t: %s\n", (is_enabled? "ON":"OFF"));
            printf("-------------------------------------\n");

            set_parameter(scanner, laser_enabled);
         }

         // some actions with other parameters before applying changes...
         
      }
   }

.. note::
   Для более детального описания каждого параметра и его свойств см. `RF62X Firmware Cloud <https://cloud.riftek.com/index.php/s/je8KzPyLAWArCKj>`__


.. _rf62x_wrappers_c_rf627smart_write_params_to_scanner:

**write_params_to_scanner**
===============================================================================

**Прототип:**
   *rfUint8 write_params_to_scanner(scanner_base_t \*device, rfUint32 timeout, protocol_types_t protocol)*

**Описание:**
   *Функция передачи параметров из внутренней памяти SDK в сканер.* 
   *При вызове данной функции происходит отправка изменённых параметров в сканер*

**Параметры:**
   - ``device`` *- Указатель на сканер.*
   - ``timeout`` *- Время отправки изменённых параметров в сканер.*
   - ``protocol`` *- Тип протокола, по которому будет выполнена проверка (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``TRUE`` *при успехе, иначе -* ``FALSE``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 70

   /** @file rf62X_sdk.h */

   /**
    * @brief write_params_to_scanner - Send current parameters to device
    *
    * @param device Ptr to scanner
    * @param timeout Time to send parameters
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return TRUE on success
    */
   rfUint8 write_params_to_scanner(
         scanner_base_t *device, rfUint32 timeout, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      // Print count of discovered rf627smart in network by Service Protocol
      printf("Discovered: %d rf627-smart\n", (int)vector_count(scanners));

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         
         // Establish connection.
         connect_to_scanner(scanner, kSERVICE);

         // Read params.
         read_params_from_scanner(scanner, 300, kSERVICE);

         //
         // Example of working with the parameter type:
         // uint32_t
         //
         // Get parameter of Laser Enabled
         parameter_t* laser = get_parameter(scanner, "user_laser_enabled");
         if (laser != NULL) 
         {
            uint32_t is_enabled = laser->val_uint32->value;
            printf("Current Laser State\t: %s\n", (is_enabled? "ON":"OFF"));

            // Change the current state to the opposite
            is_enabled = !is_enabled;
            laser_enabled->val_uint32->value = is_enabled;
            printf("New Laser State\t: %s\n", (is_enabled? "ON":"OFF"));
            printf("-------------------------------------\n");

            set_parameter(scanner, laser_enabled);
         }

         // some actions with other parameters before applying changes...

         // Apply changed parameters to the device
         uint8_t is_applied = write_params_to_scanner(scanner, 300, kSERVICE);
         if (is_applied) 
            printf("Scanner parameters were applied successfully!");
         else 
            printf("Scanner parameters were not applied!");
         
      }
   }


.. _rf62x_wrappers_c_rf627smart_save_params_to_scanner:

**save_params_to_scanner**
===============================================================================

**Прототип:**
   *rfUint8 save_params_to_scanner(scanner_base_t \*device, rfUint32 timeout, protocol_types_t protocol);*

**Описание:**
   *Функция сохранения параметров сканера во внутреннюю память устройства.* 
   *Сохраненные параметры также будут использоваться после перезапуске устройства* 
   *или после смены(обновления) прошивки.*

**Параметры:**
   - ``device`` *- Указатель на сканер.*
   - ``timeout`` *- Время ожидания результата сохранения параметров в сканере.*
   - ``protocol`` *- Тип протокола, по которому будет выполнена проверка (Service Protocol, ENIP, Modbus-TCP)*

**Возвращаемое значение:**
   ``TRUE`` *при успехе, иначе -* ``FALSE``

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 50

   /** @file rf62X_sdk.h */

   /**
    * @brief save_params_to_scanner - Save changes to device's memory
    *
    * @param device Ptr to scanner
    * @param timeout Time to save parameters
    * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
    *
    * @return TRUE on success
    */
   rfUint8 save_params_to_scanner(
         scanner_base_t *device, rfUint32 timeout, protocol_types_t protocol);

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "network.h"
   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Actions before search (see example of search_scanners() method)...

      // Search for RF627-smart devices over network by Service Protocol.
      search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

      for (int i = 0; i < (int)vector_count(scanners); i++)
      {
         scanner_base_t* scanner = vector_get(scanners,i);
         
         // Establish connection.
         connect_to_scanner(scanner, kSERVICE);

         // Read params.
         read_params_from_scanner(scanner, 300, kSERVICE);

         // After changing some parameters...

         // Apply changed parameters to the device
         write_params_to_scanner(scanner, 300, kSERVICE);

         // Save current parameters in the device memory
         uint8_t is_saved = save_params_to_scanner(scanner, 300, kSERVICE);
         if (is_saved) 
            printf("Scanner parameters saved successfully!");
         else 
            printf("Scanner parameters were not saved!");
      }
   }

