.. _compilation_rf62x_core:

*******************************************************************************
Компиляция «ядра» на C
*******************************************************************************

.. _how_to_compile_rf62x_core:

Как скомпилировать
===============================================================================

RF62X-CORE может быть скомпилирован при помощи консоли или среды разработки (Visual Studio, Qt Creator)

Во-первых, вы должны загрузить проект (если не сделали этого ранее)

.. note::
   для получения дополнительной информации о шагах загрузки проекта см. :ref:`clone_rf62x_sdk`

.. _how_to_compile_rf62x_core_cmake:

CMake
-------------------------------------------------------------------------------

Находясь в папке с проектом, для построения RF62X-Core 
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd RF62X-Core
   mkdir build && cd build
   cmake ..
   cmake --build .

.. _how_to_compile_rf62x_core_qt_creator:

Qt Creator
-------------------------------------------------------------------------------

Для построения RF62X-Core с использованием IDE Qt Creator: 

-  Загрузите файл CMakeLists.txt из папки **RF62X-Core** через 
   **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC, Clang)
   и нажмите **Configure Project** 
-  Скомпилируйте проект

.. _how_to_compile_rf62x_core_vs:

Visual Studio
-------------------------------------------------------------------------------

Находясь в папке с проектом, для построения RF62X-CORE  
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

При желании использовать библиотеку RF62X-Core вместо имеющихся библиотек-«обёрток» 
разработчику необходимо самостоятельно реализовать платформозависимую часть «ядра».

.. _rf62x_core_description_dependence:

Обзор платформозависимых функций
-------------------------------------------------------------------------------

В «Ядре» RF62X-CORE платформозависимые функции (работа с памятью, работа с сетью, 
функции ввода/вывода) представлены в виде указателей на функции. 

Указатели на платформозависимые функции объявлены в файлах, 
``memory_platform.h``, ``network_platform.h`` и ``iostream_platform.h``:

memory_platform.h
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygentypedef:: calloc_t

.. doxygentypedef:: malloc_t

.. doxygentypedef:: realloc_t

.. doxygentypedef:: free_t

.. doxygentypedef:: memset_t

.. doxygentypedef:: memcpy_t

.. doxygentypedef:: memcmp_t

network_platform.h
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygentypedef:: hton_long_t

.. doxygentypedef:: ntoh_long_t

.. doxygentypedef:: hton_short_t

.. doxygentypedef:: ntoh_short_t

.. doxygentypedef:: create_udp_socket_t

.. doxygentypedef:: set_broadcast_socket_option_t

.. doxygentypedef:: set_reuseaddr_socket_option_t

.. doxygentypedef:: set_socket_option_t

.. doxygentypedef:: set_socket_recv_timeout_t

.. doxygentypedef:: socket_connect_t

.. doxygentypedef:: socket_bind_t

.. doxygentypedef:: socket_listen_t

.. doxygentypedef:: socket_accept_t

.. doxygentypedef:: close_socket_t

.. doxygentypedef:: send_tcp_data_t

.. doxygentypedef:: send_udp_data_t

.. doxygentypedef:: recv_data_from_t

.. doxygentypedef:: recv_data_t

iostream_platform.h
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygentypedef:: trace_info_t

.. doxygentypedef:: trace_warning_t

.. doxygentypedef:: trace_error_t

Запуск «ядра»
-------------------------------------------------------------------------------

После реализации всех платформозависимых функций разработчику необходимо проинициализировать 
следующие структуры ``iostream_platform_dependent_methods_t``, ``memory_platform_dependent_methods_t`` 
и ``network_platform_dependent_methods_t`` 

.. doxygenstruct:: memory_platform_dependent_methods_t
   :members:
   :protected-members:
   :private-members:
   :undoc-members:
   :outline:
   :no-link:

.. doxygenstruct:: network_platform_dependent_methods_t
   :members:
   :protected-members:
   :private-members:
   :undoc-members:
   :outline:
   :no-link:

.. doxygenstruct:: iostream_platform_dependent_methods_t
   :members:
   :protected-members:
   :private-members:
   :undoc-members:
   :outline:
   :no-link:

.. doxygenstruct:: network_platform_dependent_settings_t
   :members:
   :protected-members:
   :private-members:
   :undoc-members:
   :outline:
   :no-link:

Инициализация данных структур производится путем присваивания указателей на реализованные 
платформозависимые функции, а адреса проинициализированных экземпляров структур передаются в метод 
init_platform_dependent_methods для инициализации кросс-платформенной части «ядра».

.. doxygenfunction:: init_platform_dependent_methods(memory_platform_dependent_methods_t *, iostream_platform_dependent_methods_t *, network_platform_dependent_methods_t *, network_platform_dependent_settings_t *)