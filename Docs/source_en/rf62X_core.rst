RF62X Core
===============

RF62X CORE is the main library with basic functionality for work with
scanners and platform dependent methods (such as memory, network,
output/input methods, etc.) requiring initialization. This library was
written in C programming language in accordance with C99 Sdandart
(ISO/IEC 9899:1999).

.. table:: Last release libraries:

   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Compiler      | 64bit                                                                         | Includes                                                                  |
   +===============+===============================================================================+===========================================================================+
   | MinGW 7.3.0   | `rf62Xcore.dll </uploads/8d5bdec0c244ec9afb6c977014dc870e/rf62Xcore.dll>`__   | `include.zip </uploads/94210ce658946e97df0facd217d9d230/include.zip>`__   |
   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | MSVC2017      | `rf62Xcore.dll </uploads/5ff2632b9bb0a4a4f1344f58e71966c4/rf62Xcore.dll>`__   | `include.zip </uploads/94210ce658946e97df0facd217d9d230/include.zip>`__   |
   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+
   | Clang 9.1.0   | `rf62Xcore.dll </uploads/79520e5615eed8632f807bd667df3880/rf62Xcore.dll>`__   | `include.zip </uploads/94210ce658946e97df0facd217d9d230/include.zip>`__   |
   +---------------+-------------------------------------------------------------------------------+---------------------------------------------------------------------------+

--------------

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
