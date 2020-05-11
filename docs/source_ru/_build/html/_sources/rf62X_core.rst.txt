
.. _rf62x_core_description:

*******************************************************************************
RF62X-CORE
*******************************************************************************

**RF62X-CORE** - это основная библиотека (ядро) с базовым набором функций для 
работы со сканерами, а также платформозависимыми функциями (такими как работа 
с памятью, работа с сетью, функциями ввода/вывода и т.п.), 
требующими предварительной инициализации. Библиотека написана на языке 
программирования CИ в соответствии со стандартом C99 (ISO / IEC 9899: 1999).

.. table:: Последние выпуски:

   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Compiler      | 64bit                                                                         | Includes                                                                  |
   +===============+===============================================================================+===========================================================================+
   | MinGW 7.3.0   | `rf62Xcore.dll </uploads/8d5bdec0c244ec9afb6c977014dc870e/rf62Xcore.dll>`__   | `include.zip </uploads/94210ce658946e97df0facd217d9d230/include.zip>`__   |
   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | MSVC2017      | `rf62Xcore.dll </uploads/5ff2632b9bb0a4a4f1344f58e71966c4/rf62Xcore.dll>`__   | `include.zip </uploads/94210ce658946e97df0facd217d9d230/include.zip>`__   |
   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Clang 9.1.0   | `rf62Xcore.dll </uploads/79520e5615eed8632f807bd667df3880/rf62Xcore.dll>`__   | `include.zip </uploads/94210ce658946e97df0facd217d9d230/include.zip>`__   |
   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+


Обзор платформозависимых функций
===============================================================================

В ядре RF62X-CORE платформозависимые функции (работа с памятью, работа с сетью, 
функции ввода/вывода и т.п.) представлены в виде указателей на функции. При желании 
разработчика использовать библиотеку RF62X-CORE вместо предоставляемых 
библиотек-«обёрток» на языках C++, C# и PYTHON, разработчику будет необходимо перед  
непосредственным использованием ядра самостоятельно реализовать платформозависимую часть.

Указатели на платформозависимые функции объявлены в файлах ``iostream_platform.h``, 
``memory_platform.h`` и ``network_platform.h``: После реализации всех платформозависимых 
функций разработчику необходимо инициализировать структуры ``iostream_platform_dependent_methods_t``, 
``memory_platform_dependent_methods_t`` и ``network_platform_dependent_methods_t`` путем 
присваивания указателей на реализованные им функции, а адреса проинициализированных 
экземпляров структур передавать в метод init_platform_dependent_methods перед использованием ядра

How to compile
~~~~~~~~~~~~~~

RF62X CORE can be built on the console or in an IDE.
Firstly, you should download the project (if you have already done it, skip next commands)

.. code-block:: bash

   git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
   cd RF62X-SDK
   git submodule update --init --recursive

.. note::
   for more information about project downloading steps, see an `overview <#overview>`__

CMake
"""""

To build the code:

.. code-block:: bash

   cd rf62Xcore
   cmake .
   cmake --build . 

Qt Creator
""""""""""

To build the code: 

-  Load the CMakeLists.txt file from the **rf62Xcore** folder 
   via **File > Open File or Project** (Select the CMakeLists.txt file) 

-  Select compiler (MinGW, MSVC2017, Clang, etc..)
   and click **Configure Project** \* Open **Build Settings** and check

-  **install*** target for **Build Steps** \* Compile project

Visual Studio
"""""""""""""

To build the code:

.. code-block:: bash

   cd rf62Xcore
   cmake .

-  Open rf62Xcore.sln with Visual Studio
-  Compile
