.. _compilation_rf62x_core:

*******************************************************************************
Компиляция «ядра» на C
*******************************************************************************

**RF62X-CORE** - основная библиотека («Ядро») с базовым набором функций и типов  
для работы с лазерными сканерами серии RF62X. Библиотека написана на языке 
программирования CИ в соответствии со стандартом C99 (ISO / IEC 9899: 1999) и 
является кросс-платформенной. Для использования данной библиотеки необходима 
реализация платформозависимых функций (работа с памятью, работа с сетью, функции 
ввода/вывода). 

.. _rf62Xcore_dll_mingw_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/178471d04d864e6110deba9ac9074df1/rf62Xcore.dll
.. _rf62Xcore_a_mingw_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/4391dcfc692165676df647cbc65fb570/rf62Xcore.a
.. _rf62Xcore_mingw_64_include: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/e2dc04f462b16838265ffcd069f9324c/include.zip

.. _rf62Xcore_dll_msvc17_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/b97b1cec97a78ab3c9b09de946fd7e70/rf62Xcore.dll
.. _rf62Xcore_lib_msvc17_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/4eb42c2565bc2f61ed6714fc1bcf9d90/rf62Xcore.lib
.. _rf62Xcore_msvc17_64_include: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/912861a038055097ae482022a9003702/include.zip

.. _rf62Xcore_dll_clang_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/49e8e99d59fba95fa9f952c5befe8e92/rf62Xcore.dll
.. _rf62Xcore_lib_clang_64: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/5f96d0e7bb69d9a6ad60f41644a7e72d/rf62Xcore.lib
.. _rf62Xcore_clang_64_include: https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK/uploads/e2dc04f462b16838265ffcd069f9324c/include.zip

.. _rf62x_core_last_release:

.. table:: Последние выпуски:

   +---------------+-----------------------------------------------------------------------------------------+-----------------------------------------------+
   | Compiler      | 64bit                                                                                   | Includes                                      |
   +===============+=========================================================================================+===============================================+
   | MinGW 7.3.0   | `rf62Xcore.dll <rf62Xcore_dll_mingw_64_>`_ `rf62Xcore.a <rf62Xcore_a_mingw_64_>`_       | `include.zip <rf62Xcore_mingw_64_include>`_   |
   +---------------+-----------------------------------------------------------------------------------------+-----------------------------------------------+
   | MSVC2017      | `rf62Xcore.dll <rf62Xcore_dll_msvc17_64_>`_ `rf62Xcore.lib <rf62Xcore_lib_msvc17_64_>`_ | `include.zip <rf62Xcore_msvc17_64_include_>`_ |
   +---------------+-----------------------------------------------------------------------------------------+-----------------------------------------------+
   | Clang 9.1.0   | `rf62Xcore.dll <rf62Xcore_dll_clang_64_>`_ `rf62Xcore.lib <rf62Xcore_lib_clang_64_>`_   | `include.zip <rf62Xcore_clang_64_include_>`_  |
   +---------------+-----------------------------------------------------------------------------------------+-----------------------------------------------+

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

Находясь в папке с проектом, для построения RF62X-CORE 
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd rf62Xcore
   mkdir build
   cd build
   cmake ..
   cmake --build .

.. _how_to_compile_rf62x_core_qt_creator:

Qt Creator
-------------------------------------------------------------------------------

Для построения RF62X-CORE с использованием IDE Qt Creator: 

-  Загрузите файл CMakeLists.txt из папки **rf62Xcore** через 
   **File > Open File or Project** (выберите файл CMakeLists.txt)
-  Выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project** 
-  Откройте **Build Settings** и отметьте пункт **install** для **Build Steps**
-  Скомпилируйте проект

.. _how_to_compile_rf62x_core_vs:

Visual Studio
-------------------------------------------------------------------------------

Находясь в папке с проектом, для построения RF62X-CORE  
введите следующую команду в консоль (терминал):

.. code-block:: bash

   cd rf62Xcore
   mkdir build
   cd build
   cmake ..

-  Откройте полученное решение rf62Xcore.sln в Visual Studio
-  Скомпилируйте проект

.. _rf62x_core_description_how_to_use:

Как использовать
===============================================================================

При желании использовать библиотеку RF62X-CORE вместо предоставляемых библиотек-«обёрток» 
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