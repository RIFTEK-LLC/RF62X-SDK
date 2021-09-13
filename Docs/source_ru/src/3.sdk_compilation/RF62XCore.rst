.. _compilation_rf62x_core:

*******************************************************************************
Компиляция «ядра»
*******************************************************************************

.. _how_to_compile_rf62x_core:

Как скомпилировать
===============================================================================

**RF62X-Core** может быть скомпилирован при помощи консоли или 
среды разработки (Visual Studio, Qt Creator).

Во-первых, вы должны загрузить проект (если не сделали этого ранее).

.. note::
   Для получения дополнительной информации о шагах загрузки проекта см. :ref:`clone_rf62x_sdk`

.. _how_to_compile_rf62x_core_cmake:

CMake
-------------------------------------------------------------------------------

Находясь в папке проекта **RF62X-SDK** для построения RF62X-Core 
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd RF62X-Core
   mkdir build && cd build
   cmake ..
   cmake --build .

.. _how_to_compile_rf62x_core_qt_creator:

Qt Creator
-------------------------------------------------------------------------------

Для построения **RF62X-Core** с использованием **IDE Qt Creator**: 

-  Загрузите файл ``CMakeLists.txt`` из папки **RF62X-Core** через 
   **File > Open File or Project** (выберите файл ``CMakeLists.txt``)
-  Выберите компилятор (*MinGW*, *MSVC*, *Clang*)
   и нажмите **Configure Project** 
-  Скомпилируйте проект

.. _how_to_compile_rf62x_core_vs:

Visual Studio
-------------------------------------------------------------------------------

Находясь в папке проекта **RF62X-SDK** для построения **RF62X-Core**  
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd RF62X-Core
   mkdir build && cd build
   cmake ..

-  Откройте полученное решение RF62X-Core.sln в Visual Studio
-  Скомпилируйте проект

.. _rf62x_core_description_how_to_use:

Как использовать
===============================================================================

Для использования библиотеки **RF62X-Core** вместо имеющихся библиотек-«обёрток» 
разработчику необходимо будет самостоятельно реализовать платформозависимую 
часть «ядра».

.. _rf62x_core_description_dependence:

Обзор платформозависимых функций
-------------------------------------------------------------------------------

В **RF62X-Core** платформозависимые функции (работа с памятью, работа с сетью, 
функции ввода/вывода) представлены в виде указателей на функции. 

Указатели на платформозависимые функции объявлены в файлах, 
``memory_platform.h``, ``network_platform.h`` и ``iostream_platform.h``.

**calloc_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef void\* (\*calloc_t)(rfSize num, rfSize size);*

**Описание:**
   *Указатель на функцию* ``calloc_t`` *выделяет блок памяти для массива размером* 
   ``num`` *элементов, каждый из которых занимает* ``size`` *байт. В результате* 
   *выделяется блок памяти размером* ``number * size`` *байт, причём весь* 
   *блок заполнен нулями.* 

**Параметры:**
   - ``num`` *- Количество элементов массива, под который выделяется память.*
   - ``size`` *- Размер одного элемента в байтах.*

**Возвращаемое значение:**
   *Указатель на выделенный блок памяти. Тип данных на который ссылается* 
   *указатель всегда* ``void*`` *, поэтому это тип данных может быть приведен* 
   *к желаемому типу. Если функции не удалось выделить требуемый блок* 
   *памяти, возвращается нулевой указатель.*

**Пример в коде:**

.. code-block:: cpp

   /** @file memory_platform.h */

   /**
    * @brief Allocates an array in memory with elements initialized to 0.
    *
    * @param num Number of elements to allocate.
    * @param size Size of each element.
    *
    * @return
    * - On success: returns a pointer to the allocated space.
    * - On error: NULL
    */
   typedef void* (*calloc_t)(rfSize num, rfSize size);


**malloc_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef void\* (\*malloc_t)(rfSize size);*

**Описание:**
   *Указатель на функцию* ``malloc_t`` *выделяет блок памяти размером* ``size`` 
   *байт и возвращает указатель на начало блока. Содержание выделенного блока* 
   *памяти не инициализируется, оно остается с неопределенными значениями.* 

**Параметры:**
   - ``size`` *- Размер выделяемого блока памяти в байтах.*

**Возвращаемое значение:**
   *Указатель на выделенный блок памяти. Тип данных на который ссылается* 
   *указатель всегда* ``void*`` *, поэтому это тип данных может быть приведен* 
   *к желаемому типу. Если функции не удалось выделить требуемый блок* 
   *памяти, возвращается нулевой указатель.*

**Пример в коде:**
   
.. code-block:: cpp

   /** @file memory_platform.h */

   /**
    * @brief malloc_t - ptr to function whish allocates memory block
    * Allocates a block of size bytes of memory, returning a pointer
    * to the beginning of the block.
    *
    * @param size Size of the memory block, in bytes.
    *
    * @return
    * - On success: returns a pointer to the allocated space.
    * - On error: NULL.
    */
   typedef void* (*malloc_t)(rfSize size);

**realloc_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef void\* (\*realloc_t)(void \*ptr, rfSize newsize);*

**Описание:**
   *Указатель на функцию* ``realloc_t`` *выполняет перераспределение блоков памяти.*
   *Размер блока памяти, на который ссылается параметр* ``ptr`` *изменяется на*
   ``newsize`` *байтов. Блок памяти может уменьшаться или увеличиваться в размере.*

   *Эта функция может перемещать блок памяти на новое место, в этом случае функция* 
   *возвращает указатель на новое место в памяти. Содержание блока памяти сохраняется* 
   *даже если новый блок имеет меньший размер, чем старый. Отбрасываются только те* 
   *данные, которые не вместились в новый блок. Если новое значение* ``newsize`` *больше* 
   *старого, то содержимое вновь выделенной памяти будет неопределенным.*
   
   *В случае, если* ``ptr`` *равен* ``NULL`` *, функция ведет себя именно так, как* 
   *функция* ``malloc_t`` *, т. е. выделяет память и возвращает указатель на этот* 
   *участок памяти.*
   
   *В случае, если* ``newsize`` *равен 0, ранее выделенная память будет освобождена,* 
   *как если бы была вызвана функция* ``free_t`` *, и возвращается нулевой указатель.* 

**Параметры:**
   - ``ptr`` *- Указатель на блок ранее выделенной памяти функциями* ``malloc_t`` 
     *,* ``calloc_t`` *или* ``realloc_t`` *для перемещения в новое место. Если этот* 
     *параметр —* ``NULL`` *, просто выделяется новый блок, и функция возвращает на* 
     *него указатель.*
   - ``newsize`` *- Новый размер, в байтах, выделяемого блока памяти. Если* ``newsize`` 
     *равно 0, ранее выделенная память освобождается и функция возвращает нулевой* 
     *указатель,* ``ptr`` *устанавливается в 0.*

**Возвращаемое значение:**
   *Указатель на перераспределенный блок памяти, который может быть либо таким же,* 
   *как аргумент* ``ptr`` *или ссылаться на новое место.

   *Тип данных возвращаемого значения всегда* ``void*`` *, который может быть приведен*
   *к любому другому.*

   *Если функции не удалось выделить требуемый блок памяти, возвращается нулевой* 
   *указатель, и блок памяти, на который указывает аргумент* ``ptr`` 
   *остается неизменным.*

**Пример в коде:**
   
.. code-block:: cpp

   /** @file memory_platform.h */

   /**
    * @brief realloc_t - ptr to function whish reallocates memory block
    * Changes the size of the memory block pointed to by ptr. The function 
    * may move the memory block to a new location (whose address is 
    * returned by the function).
    *
    * @param ptr Pointer to a memory block previously allocated.
    * @param newsize New size for the memory block, in bytes.
    * 
    * @return A pointer to the reallocated memory block, which may be either 
    * the same as ptr or a new location.
    */
   typedef void* (*realloc_t)(void *ptr, rfSize newsize);

**free_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef void (\*free_t)(void\* data);*

**Описание:**
   *Указатель на функцию* ``free_t`` *освобождает место в памяти. Блок памяти,* 
   *ранее выделенный с помощью вызова* ``malloc_t`` *,* ``calloc_t`` *или* 
   ``realloc_t`` *освобождается.* 

   *Обратите внимание, что эта функция оставляет значение* ``data`` *неизменным,* 
   *следовательно, он по-прежнему указывает на тот же блок памяти, а не на нулевой* 
   *указатель.*

**Параметры:**
   - ``data`` *- Указатель на блок памяти, ранее выделенный функциями* ``malloc_t`` 
     *,* ``calloc_t`` *или* ``realloc_t`` *, которую необходимо высвободить.* 
     *Если в качестве аргумента передается нулевой указатель, никаких действий* 
     *не происходит.*

**Возвращаемое значение:**
   *Функция не имеет возвращаемое значение.*

**Пример в коде:**

.. code-block:: cpp

   /** @file memory_platform.h */

   /**
    * @brief Deallocates or frees a memory block.
    *
    * @param data Previously allocated memory block to be freed.
    */
   typedef void (*free_t)(void* data);

**memset_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef void\* (\*memset_t)(void\* memptr, rfInt val, rfSize num);*

**Описание:**
   *Указатель на функцию* ``memset_t`` *заполняет* ``num`` *байтов блока памяти,* 
   *через указатель* ``memptr`` *. Код заполняемого символа передаётся в функцию* 
   *через параметр* ``val`` *.* 

**Параметры:**
   - ``memptr`` *- Указатель на блок памяти для заполнения.*
   - ``val`` *- Передается целое число, но функция заполняет блок памяти* 
     *символом, преобразуя это число в символ*
   - ``num`` *- Количество байт, которые необходимо заполнить указанным символом.*

**Возвращаемое значение:**
   *Функция возвращает указатель на блок памяти.*

**Пример в коде:**

.. code-block:: cpp

   /** @file memory_platform.h */

   /**
    * @brief memset_t - ptr to function whish fills block of memory
    * Sets the first num bytes of the block of memory pointed by ptr to the
    * specified value (interpreted as an unsigned rfChar).
    *
    * @param memptr Pointer to the block of memory to fill.
    * @param val Value to be set.
    * @param num Number of bytes to be set to the value.
    * rfSize is an unsigned rfIntegral type.
    *
    * @return ptr is returned.
    */
   typedef void* (*memset_t)(void* memptr, rfInt val, rfSize num);

**memcpy_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef void\* (\*memcpy_t)(void\* destination, const void\* source, rfSize num);*

**Описание:**
   *Указатель на функцию* ``memset_t`` *копирует* ``num`` *байтов первого блока* 
   *памяти, на который ссылается указатель* ``source`` *, во второй блок памяти,* 
   *на который ссылается указатель* ``destination`` *.* 

**Параметры:**
   - ``destination`` *- Указатель на блок памяти назначения (куда будут копироваться байты данных).*
   - ``source`` *- Указатель на блок памяти источник (т. е., откуда будут копироваться байты данных).* 
   - ``num`` *- Количество копируемых байтов.*

**Возвращаемое значение:**
   *Указатель на блок памяти назначения.*

**Пример в коде:**

.. code-block:: cpp

   /** @file memory_platform.h */

   /**
    * @brief memcpy_t - ptr to function whish copies block of memory
    * Copies the values of num bytes from the location pointed to by source
    * directly to the memory block pointed to by destination.
    *
    * @param destination Pointer to the destination array where the content is to
    * be copied, type-casted to a pointer of type void*.
    * @param source Pointer to the source of data to be copied, type-casted to a
    * pointer of type const void*.
    * @param num Number of bytes to copy. rfSize is an unsigned rfIntegral type.
    *
    * @return destination is returned.
    */
   typedef void* (*memcpy_t)(void* destination, const void* source, rfSize num);

**memcmp_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt (\*memcmp_t)(const void\* ptr1, const void\* ptr2, rfSize num );*

**Описание:**
   *Указатель на функцию* ``memcmp_t`` *сравнивает первые* ``num`` *байтов блока* 
   *памяти указателя* ``ptr1`` *с первыми* ``num`` *байтами блока памяти* ``ptr2`` *.*
   *Возвращаемое значение 0 если блоки равны, и значение отличное от 0, если  блоки не равны.* 

**Параметры:**
   - ``ptr1`` *- Указатель на первый блок памяти.*
   - ``ptr2`` *- Указатель на второй блок памяти.* 
   - ``num`` *- Количество байтов для сравнения.*

**Возвращаемое значение:**
   *Возвращает значение, информирующее о результате сравнения содержимого блоков памяти.*
   *Нулевое значение указывает, что содержимое обоих блоков памяти равны.* 
   *Значение больше нуля говорит о том, что первый блок памяти —* ``ptr1`` *больше,* 
   *чем блок памяти —* ``ptr2`` *, и значение меньше нуля свидетельствует об обратном*

**Пример в коде:**

.. code-block:: cpp

   /** @file memory_platform.h */

   /**
    * @brief memcmp_t - ptr to function whish compare two blocks of memory
    * Compares the first num bytes of the block of memory pointed by ptr1 to the
    * first num bytes pointed by ptr2, returning zero if they all match or a 
    * value different from zero representing which is greater if they do not.
    *
    * @param ptr1 Pointer to block of memory.
    * @param ptr2 Pointer to block of memory.
    * @param num Number of bytes to compare.
    *
    * @return
    * 0 - if the contents of both memory blocks are equal,
    * <0 - if the first byte that does not match in both memory blocks has a 
    * lower value in ptr1 than in ptr2.
    * >0 - if the first byte that does not match in both memory blocks has a
    * greater value in ptr1 than in ptr2.
    */
   typedef rfInt (*memcmp_t)(const void* ptr1, const void* ptr2, rfSize num);

**hton_long_t, ntoh_long_t, hton_short_t, ntoh_short_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   - *typedef rfUint32 (\*hton_long_t) (rfUint32 hostlong);*
   - *typedef rfUint32 (\*ntoh_long_t) (rfUint32 netlong);*
   - *typedef rfUint16 (\*hton_short_t)(rfUint16 hostshort);*
   - *typedef rfUint16 (\*ntoh_short_t)(rfUint16 netshort);*

**Описание:**
   *Указатели на функции* ``hton_long_t`` *,* ``ntoh_long_t`` *,* ``hton_short_t``
   *,* ``ntoh_short_t`` *необходимы для преобразования многобайтовых*
   *целочисленных типов из байтового порядка хоста в сетевой порядок байтов и* 
   *наоборот.* 

**Параметры:**
   - ``hostlong/hostshort`` *- 32/16-битное число в байтовом порядке хоста.*
   - ``netlong/netshort`` *- 32/16-битное число в сетевом порядке байтов.* 

**Возвращаемое значение:**
   *Функция возвращает значение в сетевом/обратном порядке байтов.*

**Пример в коде:**

.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief The hton_long_t function converts a u_long from host to network byte
    * order (which is big-endian).
    *
    * @param hostlong A 32-bit number in host byte order.
    *
    * @return The function returns the value in network byte order.
    */
   typedef rfUint32 (*hton_long_t) (rfUint32 hostlong);      

   /**
    * @brief The ntoh_long_t function converts a u_long from network order to 
    * host byte order (which is little-endian on rfIntel processors).
    *
    * @param netlong A 32-bit number in network byte order.
    *
    * @return: The function returns the value supplied in the netlong parameter
    * with the byte order reversed.
    */
   typedef rfUint32 (*ntoh_long_t) (rfUint32 netlong);

   /**
    * @brief The hton_short_t function converts a u_short from host to network
    * byte order (which is big-endian).
    *
    * @param hostlong A 16-bit number in host byte order.
    *
    * @return The modbusHtoN_short_t function returns the value in network
    * byte order.
    */
   typedef rfUint16 (*hton_short_t)(rfUint16 hostshort);

   /**
    * @brief The ntoh_short_t function converts a u_short from network byte order
    * to host byte order
    *
    * @param netshort A 16-bit number in network byte order.
    *
    * @return The function returns the value in host byte order.
    */
   typedef rfUint16 (*ntoh_short_t)(rfUint16 netshort);


**create_udp_socket_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef void\* (\*create_udp_socket_t)();*

**Описание:**
   *Указатель на функцию* ``create_udp_socket_t`` *создает несвязанный UDP сокет* 

**Возвращаемое значение:**
   *После успешного завершения* ``create_udp_socket_t`` *должен вернуть указатель* 
   *на дескриптор сокета. В противном случае должно быть возвращено значение* 
   ``NULL`` *и вызвана ​​ошибка создания сокета.*

**Пример в коде:**

.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to UDP socket creation function
    *
    * @param af The address family specification.
    * @param type The type specification for the new socket.
    * @param protocol The protocol to be used.
    *
    * @return
    * - On success: A descriptor referencing the new socket
    * - On error: NULL
    */
   typedef void* (*create_udp_socket_t)();


**set_broadcast_socket_option_t, set_reuseaddr_socket_option_t, set_socket_recv_timeout_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   - *typedef rfInt8 (\*set_broadcast_socket_option_t)(void\* socket);*
   - *typedef rfInt8 (\*set_reuseaddr_socket_option_t)(void\* socket);*
   - *typedef rfInt8 (\*set_socket_recv_timeout_t)(void\* socket, rfInt32 msec);*

**Описание:**
   *Указатели на функции* ``set_broadcast_socket_option_t`` *,* 
   ``set_reuseaddr_socket_option_t`` *,* ``set_socket_recv_timeout_t`` *,* 
   *необходимы для вкючение в UDP сокетах таких сетевых настроек как:*
   *broadcast (позволяет отправлять или получать широковещательные пакеты),*
   *reuseaddr (позволяет сокету принудительно связываться с портом, используемым* 
   *другим сокетом), recv_timeout (время, в течение которого сокет ожидает,* 
   *пока данные станут доступными для чтения).*

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``msec`` *(только для set_socket_recv_timeout_t) - Время ожидания в миллисекундах.* 

**Возвращаемое значение:**
   *После успешного завершения везвращается 0. В противном случае должно быть* 
   *возвращено значение -1.*

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the function that sets a broadcast socket option.
    *
    * @param socket A descriptor that identifies a socket.
    *
    * @return
    * - On success: 0
    * - On error: -1
    */
   typedef rfInt8 (*set_broadcast_socket_option_t)(void* socket);

   /**
    * @brief Pointer to the function that sets a reuseaddr socket option.
    *
    * @param socket A descriptor that identifies a socket.
    *
    * @return
    * - On success: 0
    * - On error: -1
    */
   typedef rfInt8 (*set_reuseaddr_socket_option_t)(void* socket);

   /**
    * @brief Pointer to the function that sets a timeout for socket receive.
    *
    * @param socket A descriptor that identifies a socket.
    * @param msec The timeout in millisec.
    *
    * @return
    * - On success: 0
    * - On error: -1
    */
   typedef rfInt8 (*set_socket_recv_timeout_t)(void* socket, rfInt32 msec);

**set_socket_option_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt8 (\*set_socket_option_t)(void\* socket, rfInt32 level, rfInt32 optname, const rfChar\* optval, rfInt32 optlen);*

**Описание:**
   *Указатель на функцию* ``set_socket_option_t`` *устанавливает параметр сокета.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``level`` *- Уровень, на котором определена опция (например, SOL_SOCKET).* 
   - ``optname`` *- Параметр сокета, для которого должно быть установлено значение (например, SO_BROADCAST)*
   - ``optval`` *- Указатель на буфер, в котором указано значение запрошенной опции.*
   - ``optlen`` *- Размер в байтах буфера, на который указывает параметр* ``optval``

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``set_socket_option_t`` *возвращает ноль.*
   *В противном случае возвращается значение* ``RF_SOCKET_ERROR``

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the function that sets a socket option.
    *
    * @param socket A descriptor that identifies a socket.
    * @param level The level at which the option is defined.
    * @param optname The socket option for which the value is to be set.
    * @param optval A pointer to the buffer in which the value for the requested
    * option is specified.
    * @param optlen The size, in bytes, of the buffer pointed to by the optval
    * parameter.
    *
    * @return
    * - On success: 0
    * - On error: -1
    */
   typedef rfInt8 (*set_socket_option_t)(
           void* socket, rfInt32 level, rfInt32 optname,
           const rfChar* optval, rfInt32 optlen);

**socket_connect_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt8 (\*socket_connect_t)(void\* socket, rfUint32 dst_ip_addr, rfUint16 dst_port);*

**Описание:**
   *Указатель на функцию* ``socket_connect_t`` *устанавливает соединение с* 
   *указанным сокетом.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``dst_ip_addr`` *- IP-адрес назначения, с которым должно быть установлено соединение.* 
   - ``dst_port`` *- Порт назначения, к которому должно быть установлено соединение.*

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``socket_connect_t`` *возвращает ноль.*
   *В противном случае возвращается значение* ``RF_SOCKET_ERROR``

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the function that establishes a connection to a
    * specified socket
    *
    * @param socket A descriptor identifying an unconnected socket.
    * @param dst_ip_addr Destination IP Addr to which the connection should be
    * established.
    * @param dst_port Destination port to which the connection should be
    * established.
    *
    * @return
    * - On success: 0
    * - On error: -1
    */
   typedef rfInt8 (*socket_connect_t)(
           void* socket, rfUint32 dst_ip_addr, rfUint16 dst_port);

**socket_bind_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt (\*socket_bind_t)(void\* socket, rfUint32 host_ip_addr, rfUint16 host_port);*

**Описание:**
   *Указатель на функцию* ``socket_bind_t`` *связывает локальный адрес с сокетом.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``dst_ip_addr`` *- IP-адрес, с которым должен быть связан сокет.* 
   - ``dst_port`` *- Порт, с которым должен быть связан сокет.*

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``socket_bind_t`` *возвращает ноль.*
   *В противном случае возвращается значение* ``RF_SOCKET_ERROR``

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the function that associates a local address with 
    * a socket.
    *
    * @param socket A descriptor identifying an unconnected socket.
    * @param host_ip_addr Host IP Addr to which the connection should be bind.
    * @param host_port Host port to which the connection should be bind.
    *
    * @return
    * - On success: 0
    * - On error: -1
    */
   typedef rfInt (*socket_bind_t)(
           void* socket, rfUint32 host_ip_addr, rfUint16 host_port);

**socket_listen_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt8 (\*socket_listen_t)(void\* socket, rfInt32 backlog);*

**Описание:**
   *Указатель на функцию* ``socket_listen_t`` *переводит сокет в состояние, в* 
   *котором он ожидает входящее соединения.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``backlog`` *- Максимальная длина очереди ожидающих подключений.* 

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``socket_listen_t`` *возвращает ноль.*
   *В противном случае возвращается значение* ``RF_SOCKET_ERROR``

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /** @brief Pointer to the function that places a socket in a state in which
    * it is listening for an incoming connection.
    *
    * @param socket A descriptor identifying a bound, unconnected socket.
    * @param backlog The maximum length of the queue of pending connections.
    *
    * @return
    * - On success: 0
    * - On error: -1
    */
   typedef rfInt8 (*socket_listen_t)(void* socket, rfInt32 backlog);   

**socket_accept_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef void\* (\*socket_accept_t)(void\* socket, rfUint32\* srs_ip_addr, rfUint16\* srs_port);*

**Описание:**
   *Указатель на функцию* ``socket_accept_t`` *разрешает попытку входящего* 
   *подключения к сокету.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``srs_ip_addr`` *- Указатель на IP-адрес входящего соединения.* 
   - ``srs_port`` *- Указатель на порт входящего соединения.* 

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``socket_accept_t`` *возвращает указатель на* 
   *дескриптор принятого сокета. В противном случае возвращается нулевой указатель.*

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the function that permits an incoming connection attempt
    * on a socket.
    *
    * @param socket A descriptor that identifies a socket that has been placed in
    * a listening state with the modbusSocketListen_t function.
    * The connection is actually made with the socket that is returned by accept.
    * @param srs_ip_addr Pointer to the IP address of the incoming connection.
    * @param srs_port Pointer to the port of the incoming connection.
    *
    * @return
    * - On success: value is a handle for the socket
    * - On error : NULL
    */
   typedef void* (*socket_accept_t)(
           void* socket, rfUint32* srs_ip_addr, rfUint16* srs_port);

**close_socket_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt8 (\*close_socket_t)(void\* socket);*

**Описание:**
   *Указатель на функцию* ``close_socket_t`` *закрывает существующий сокет.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``close_socket_t`` *возвращает ноль.*
   *В противном случае возвращается значение* ``RF_SOCKET_ERROR``

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the function that closes an existing socket.
    *
    * @param socket A descriptor identifying the socket to close.
    *
    * @return
    * - On success: 0
    * - On error: -1
    */
   typedef rfInt8 (*close_socket_t)(void* socket);   

**send_tcp_data_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt (\*send_tcp_data_t)(void\* socket, const void \*buf, rfSize len);*

**Описание:**
   *Указатель на функцию* ``send_tcp_data_t`` *отправляет данные в подключенный TCP сокет.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``buf`` *- Указатель на буфер, содержащий данные для передачи.*
   - ``len`` *- Длина в байтах данных в буфере, на который указывает параметр* ``buf``

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``send_tcp_data_t`` *возвращает общее количество*
   *отправленных байтов, которое может быть меньше количества, запрошенного*
   *для отправки в параметре* ``len`` *. В противном случае возвращается значение -1.*

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the send function that sends data on a TCP 
    * connected socket.
    *
    * @param socket A descriptor identifying a connected socket.
    * @param buf A pointer to a buffer containing the data to be transmitted.
    * @param len The length, in bytes, of the data in buffer pointed to by the
    * buf parameter.
    *
    * @return
    * - On success: the total number of bytes sent, which can be less than the
    * number requested to be sent in the len parameter.
    * - On error: -1
    */
   typedef rfInt (*send_tcp_data_t)(void* socket, const void *buf, rfSize len);

**send_udp_data_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt (\*send_udp_data_t)(void\* socket, const void \*data, rfSize len, rfUint32 dest_ip_addr, rfUint16 dest_port);*

**Описание:**
   *Указатель на функцию* ``send_udp_data_t`` *отправляет данные по UDP в*
   *определенное место назначения.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``data`` *- Указатель на буфер, содержащий данные для передачи.*
   - ``len`` *- Длина в байтах данных в буфере, на который указывает параметр* ``data``
   - ``dest_ip_addr`` *- IP-адрес, на который данные должны быть отправлены.* 
   - ``dest_port`` *- Порт, на который данные должны быть отправлены.*

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``send_udp_data_t`` *возвращает общее количество*
   *отправленных байтов, которое может быть меньше количества, запрошенного*
   *для отправки в параметре* ``len`` *. В противном случае возвращается значение -1.*

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the send function that sends data on a UDP socket
    *
    * @param socket A descriptor identifying a socket.
    * @param buf A pointer to a buffer containing the message to be sent.
    * @param len The size of the message in bytes.
    * @param dest_addr Points to a sockaddr_in structure containing the
    * destination address.
    * @param addrlen Specifies the length of the sockaddr_in structure pointed
    * to by the dest_addr argument.
    *
    * @return
    * - On success: the total number of bytes sent, which can be less than
    * the number requested to be sent in the len parameter
    * - On error: -1
    */
   typedef rfInt (*send_udp_data_t)(
           void* socket, const void *data, rfSize len,
           rfUint32 dest_ip_addr, rfUint16 dest_port);   

**recv_data_from_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt (\*recv_data_from_t)(void\* socket, void \*buf, rfSize len, rfUint32\* srs_ip_addr, rfUint16\* srs_port);*

**Описание:**
   *Указатель на функцию* ``recv_data_from_t`` *получает данные из сокета и*
   *адрес отправителя.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``buf`` *- Указатель на буфер для приема входящих данных*
   - ``len`` *- Длина в байтах буфера, на который указывает параметр* ``buf`` 
   - ``srs_ip_addr`` *- Указатель на IP-адрес из которого были получены данные* 
   - ``srs_port`` *- Указатель на порт из которого были получены данные*

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``recv_data_from_t`` *возвращает общее количество*
   *принятых байтов. В противном случае возвращается значение -1.*

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the function that receive message from socket and capture
    * address of sender.
    *
    * @param socket Specifies a socket descriptor from which data should
    * be received.
    * @param buf Specifies the buffer in which to place the message.
    * @param len Specifies the length of the buffer area.
    * @param srs_ip_addr Pointer to the IP address from which the data 
    * was received.
    * @param srs_port Pointer to the port from which the data was received.
    *
    * @return
    * - On success: the number of bytes received
    * - On error: -1
    */
   typedef rfInt (*recv_data_from_t)(
           void* socket, void *buf, rfSize len,
           rfUint32* srs_ip_addr, rfUint16* srs_port);

**recv_data_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   *typedef rfInt (\*recv_data_t)(void\* socket, void \*buf, rfSize len);*

**Описание:**
   *Указатель на функцию* ``recv_data_t`` *получает данные от подключенного*
   *сокета или привязанного сокета без установления соединения.* 

**Параметры:**
   - ``socket`` *- Указатель дескриптора сокета*
   - ``buf`` *- Указатель на буфер для приема входящих данных*
   - ``len`` *- Длина в байтах буфера, на который указывает параметр* ``buf``

**Возвращаемое значение:**
   *Если ошибок не происходит,* ``recv_data_t`` *возвращает общее количество*
   *принятых байтов. В противном случае возвращается значение -1.*

**Пример в коде:**
   
.. code-block:: cpp

   /** @file network_platform.h */

   /**
    * @brief Pointer to the function that receive message from socket and capture
    * address of sender.
    *
    * @param sockfd Specifies a socket descriptor from which data 
    * should be received.
    * @param buf Specifies the buffer in which to place the message.
    * @param len Specifies the length of the buffer area.
    *
    * @return
    * - On success: the number of bytes received
    * - On error: -1
    */
   typedef rfInt (*recv_data_t)(void* socket, void *buf, rfSize len);

**trace_info_t, trace_warning_t, trace_error_t**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Прототип:**
   - *typedef rfInt(\*trace_info_t)(const rfChar\* msg, ...);*
   - *typedef rfInt(\*trace_warning_t)(const rfChar\* msg, ...);*
   - *typedef rfInt(\*trace_error_t)(const rfChar\* msg, ...);*

**Описание:**
   *Указатели на функции* ``trace_info_t`` *,* 
   ``trace_warning_t`` *и* ``trace_error_t`` *,* 
   *необходимы для вывода как информационных сообщений, так и сообщений о* 
   *предупреждениях и ошибках.*

**Параметры:**
   - ``msg`` *- Указатель на строку, содержащую текст для вывода*
   - ``...`` *(дополнительные аргументы) - В зависимости от формата строки,*
     *функция может ожидать последовательность дополнительных аргументов.* 

**Возвращаемое значение:**
   *В случае успеха возвращается общее количество написанных символов*

**Пример в коде:**

.. code-block:: cpp

   /** @file iostream_platform.h */

   /**
    * @brief Method for outputting debugging information
    *
    * @param msg Pointer to a string containing the text to be output
    * @param ...(additional arguments) Depending on the format string, 
    * the function may expect a sequence of additional arguments
    *
    * @return On success, the total number of characters written is returned.
    */
   typedef rfInt(*trace_info_t)(const rfChar* msg, ...);

   /**
    * @brief Method for outputting alert information
    *
    * @param msg Pointer to a string containing the text to be output
    * @param ...(additional arguments) Depending on the format string, 
    * the function may expect a sequence of additional arguments
    *
    * @return On success, the total number of characters written is returned.
    */
   typedef rfInt(*trace_warning_t)(const rfChar* msg, ...);

   /**
    * @brief Method for outputting error information
    *
    * @param msg Pointer to a string containing the text to be output
    * @param ...(additional arguments) Depending on the format string, 
    * the function may expect a sequence of additional arguments
    *
    * @return On success, the total number of characters written is returned.
    */
   typedef rfInt(*trace_error_t)(const rfChar* msg, ...);


Запуск «ядра»
-------------------------------------------------------------------------------

После реализации всех платформозависимых функций разработчику необходимо проинициализировать 
следующие структуры ``iostream_platform_dependent_methods_t``, ``memory_platform_dependent_methods_t`` 
и ``network_platform_dependent_methods_t`` 

**Пример в коде:**

.. code-block:: cpp

   /** @file iostream_platform.h */

   /**
    * @brief Structure with user-provided iostream platform-specific methods
    */
   typedef struct
   {
      trace_info_t trace_info;
      trace_warning_t trace_warning;
      trace_error_t trace_error;
   }iostream_platform_dependent_methods_t;
   extern iostream_platform_dependent_methods_t iostream_platform;


   /** @file memory_platform.h */

   /**
    * @brief Structure with user-provided memory platform-specific methods
    */
   typedef struct
   {
      calloc_t rf_calloc;
      malloc_t rf_malloc;
      realloc_t rf_realloc;
      free_t rf_free;

      memset_t rf_memset;
      memcpy_t rf_memcpy;
      memcmp_t rf_memcmp;

   }memory_platform_dependent_methods_t;
   extern memory_platform_dependent_methods_t memory_platform;


      /** @file memory_platform.h */

   /**
    * @brief Structure with user-provided network platform-specific methods
    */
   typedef struct
   {
      hton_long_t hton_long;
      ntoh_long_t ntoh_long;
      hton_short_t hton_short;
      ntoh_short_t ntoh_short;

      create_udp_socket_t create_udp_socket;
      set_broadcast_socket_option_t set_broadcast_socket_option;
      set_reuseaddr_socket_option_t set_reuseaddr_socket_option;
      set_socket_option_t set_socket_option;
      set_socket_recv_timeout_t set_socket_recv_timeout;
      socket_connect_t socket_connect;
      socket_bind_t socket_bind;
      socket_listen_t socket_listen;
      socket_accept_t  socket_accept;
      close_socket_t close_socket;

      send_tcp_data_t send_tcp_data;
      send_udp_data_t send_udp_data;

      recv_data_from_t recv_data_from;
      recv_data_t recv_data;
   }network_platform_dependent_methods_t;

   typedef struct
   {
      rfUint32 host_ip_addr;
      rfUint32 host_mask;
   }network_platform_dependent_settings_t;

   typedef struct
   {
      network_platform_dependent_methods_t network_methods;
      network_platform_dependent_settings_t network_settings;
   }network_platform_t;
   extern network_platform_t network_platform;   

Инициализация данных структур производится путем присваивания указателей на реализованные 
платформозависимые функции, а адреса проинициализированных экземпляров структур передаются в метод 
``init_platform_dependent_methods`` для инициализации кросс-платформенной части «ядра».

**Пример в коде:**
   
.. code-block:: cpp

   /** @file rf62X_core.h */

   /**
    * @brief Init platform dependent methods and settings
    *
    * @param memory_methods Structure with platform-specific methods 
    * for work with memory
    * @param iostream_methods Structure with platform-specific methods 
    * for work with iostream
    * @param network_methods Structure with platform-specific methods 
    * for work with network
    * @param adapter_settings Structure with adapter settings
    */
   API_EXPORT void init_platform_dependent_methods(
            memory_platform_dependent_methods_t* memory_methods,
            iostream_platform_dependent_methods_t* iostream_methods,
            network_platform_dependent_methods_t* network_methods,
            network_platform_dependent_settings_t* adapter_settings);   