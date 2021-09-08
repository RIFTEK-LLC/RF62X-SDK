.. _rf62x_wrappers_python:

.. |pydll| replace:: rf62Xsdk.dll
.. |PYSDK| replace:: PYSDK.py
.. |PYSDK_functions| replace:: PYSDK_functions.py
.. |PYCLASS| replace:: rf627old

*******************************************************************************
Инициализация SDK
*******************************************************************************

Файл |PYSDK| является основным файлом программного интерфейса (API) для 
разработки программ на языке Python и определяет функциональность библиотеки-«обёртки» 
для |pydll|.  |PYSDK| содержит следующий набор классов и функций для разработки для инициализации SDK:

sdk_init()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция инициализации SDK. Должна быть вызванна один раз перед дальнейшими вызовами 
любых библиотечных функций:


.. code-block:: python

    def sdk_init():

sdk_version()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения текущей версии SDK

.. code-block:: python

    def get_sdk_version():

**Возвращаемое значение:**

- ``version`` (*string*) - текущая версия SDK



search_scanners()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для поиска устройств RF62X по сети. Происходит перебор всех доступных сетевых адаптеров в 
текущей системе и отправка «Hello»-запросов. Результатом является список обнаруженных устройств.

.. code-block:: python

    def search_scanners(scanner_type=const_scanner_type.kRF627_OLD, protocol=const_protocol.kSERVICE):


    
**Входные параметры:**

-  ``scanner_type`` (*scanner_types_t*) - тип сканера (RF627-old, RF627-smart)

- ``protocol`` (*protocol_types_t*) - тип протокола (Service Protocol, ENIP, Modbus-TCP)

**Возвращаемое значение:**

-  ``scannerList`` (*list*) - список сканеров серии RF627, найденные в сети


**Пример использования в коде:**

.. code-block:: python

   list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)

select_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Выбрать конкретный сканер из списка сканеров, полученного с помощью функции search_scanners. 
Список параметров находится в (*rf627_old_hello_info_by_service_protocol*) и содержит: device_name, serial_number,ip_address, mac_address, profile_port, service_port, firmware_version, hardware_version, z_begin, z_range, x_begin, x_end


.. code-block:: python

   def select_scanner(scannerList, **option):
    
**Входные параметры:**

-  ``scannerList`` (*list*) - список сканеров серии RF627, найденные в сети

-  ``option`` (*dict*) - параметр, по которомы отбирать сканер. 

**Возвращаемое значение:**

-  ``scanner`` (*rf627_device*)  - указатель на выбранный сканер. *None* если сканер не найден.

**Пример использования в коде:**

.. code-block:: python
   :emphasize-lines: 2

   list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
   current_scanner=select_scanner(list, ip_address='192.168.1.30')
