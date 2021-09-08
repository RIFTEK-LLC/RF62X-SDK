
.. _rf62x_wrappers_description_python_rf627old:

.. |pydll| replace:: rf62Xsdk.dll
.. |PYSDK| replace:: PYSDK.py
.. |PYSDK_functions| replace:: PYSDK_functions.py
.. |PYCLASS| replace:: rf627old

*******************************************************************************
Класс rf627_device
*******************************************************************************

Данный класс определён в файле |PYSDK| и предоставляет интерфейс 
для работы со сканерами cерии RF62X


__init__()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Конструктор

.. code-block:: python

    def __init__(self, scanner_object, scanner_type, protocol)

**Входные параметры:**

-  ``scanner_object`` (*scanner_base_t*) –  указатель на структуру сканера

-  ``scanner_type`` (*scanner_types_t*) - тип сканера (RF627-old, RF627-smart)

- ``protocol`` (*protocol_types_t*) - тип протокола (Service Protocol, ENIP, Modbus-TCP)

**Возвращаемое значение:**

- (*None*)

**Пример использования в коде:**

.. code-block:: python

    from PYSDK import rf627_device


__str__()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Представить информацию об объекте класса rf627_device в виде строки, удобной для чтения

.. code-block:: python

    def __str__(self):  

**Возвращаемое значение:**

- ``info`` (*string*) - информацию об объекте в виде строки

**Пример использования в коде:**

.. code-block:: python
    :emphasize-lines: 3

    list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')
    print(current_scanner)


connect_to_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Функция для установки соединения со сканером серии RF627. 
При выборе сканера подключение к нему устанавливается автоматически.


.. code-block:: python

    def connect_to_scanner(self):

**Возвращаемое значение:**

- Код ошибки (*int*) - 1 в случае успеха

**Пример использования в коде:**

.. code-block:: python
    :emphasize-lines: 4

    list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')
    current_scanner.disconnect_from_scanner()
    current_scanner.connect_to_scanner()


disconnect_from_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для закрытия ранее установленного соединения со сканером серии RF627


.. code-block:: python

    def disconnect_from_scanner(self):

**Возвращаемое значение:**

- Код ошибки (*int*) - 1 в случае успеха

**Пример использования в коде:**

.. code-block:: python
    :emphasize-lines: 3

    list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')
    current_scanner.disconnect_from_scanner()



get_profile2D_from_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Функция для получения профиля со сканеров серии RF627

.. code-block:: python

    def get_profile2D_from_scanner(self, is_include_zero_points=True):
    
**Входные параметры:**

-  ``is_include_zero_points`` (*boolean*) –  включать ли нулевые точки в итоговый профиль

**Возвращаемое значение:**

-  ``profile`` (*rf627_profile2D_t*)  - указатель на структуру с профилем. *None* если профиль отсутствует

**Пример использования в коде:**

.. code-block:: python
    :emphasize-lines: 3

    list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')
    prof = current_scanner.get_profile2D_from_scanner()


get_info_about_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция для получения информации о сканере из пакета приветствия (Hello-пакет)

.. code-block:: python

    def get_info_about_scanner(self):
  

**Возвращаемое значение:**

-  ``hello_information`` (*dict*)  - информация о сканере в виде словаря Pyhton

**Пример использования в коде:**

.. code-block:: python
    :emphasize-lines: 3

    list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')
    hello = current_scanner.get_info_about_scanner()
    print('* Name\t: ', hello['device_name'])


get_parameter()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения конкретного параметра по его имени. При вызове 
данной функции «ядро» осуществляет поиск нужного параметра из последних прочитанных 
при вызове функции :ref:`read_params_from_scanner`. В случае, если запрашиваемый 
параметр отсутствует в конкретном сканере, функция вернёт *None*.

Для более удобной работы с параметрами можно использовать соответствующие «ключи» 
(ключ имени параметра, значение параметра). Для этого в файле 
|PYSDK| находятся следующие ``enum``: *const_parameter_name*


.. code-block:: python

    def get_parameter(self,name_as_number):

    
**Входные параметры:**

-  ``param name_as_number`` (*int*) - номер параметра (см. *const_parameter_name*)

**Возвращаемое значение:**
-  ``param`` (*dict*) - значение параметра в виде словаря. В случае отсутствия параметра будет возвращено *None*

**Пример использования в коде:**

.. code-block:: python
    :emphasize-lines: 4

    list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')
    current_scanner.read_params_from_scanner()
    device_name = current_scanner.get_parameter(const_parameter_name.USER_GENERAL_DEVICENAME)



set_parameter()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция установки конкретного параметра. 
Новое значение new_value может быть задано двумя способами.
*Способ 1:* новое значение передется в виде переменной variable типа (dict) с измененным полем value
 ( variable['value']=new_value )
*Способ 2:* новое значение передется в виде значения (variable=new_value), однако, при этом должен быть передан 
второй параметр - имя («ключ») изменяемого параметра. 

Для более удобной работы с параметрами можно использовать соответствующие «ключи» 
(ключ имени параметра, значение параметра). Для этого в файле 
|PYSDK| находятся следующие ``enum``: *const_parameter_name*
    
При вызове данной функции происходит установка 
передаваемого параметра в локальном списке параметров в «ядре». Для отправки изменений 
в сканер необходимо вызвать функцию ``write_params_to_scanner``.

.. code-block:: python

    def set_parameter(self,new_value, name_as_number=-1):

  
**Входные параметры:**

- ``new_value`` - новое значение

-  ``param name_as_number`` (*int*) - номер параметра (см. *const_parameter_name*)

**Возвращаемое значение:**

- Код ошибки (*int*) - 1 в случае успеха

**Пример использования в коде:**

Изменение именю устройства двумя способами

.. code-block:: python

    list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')
    current_scanner.read_params_from_scanner()
    device_name = current_scanner.get_parameter(const_parameter_name.USER_GENERAL_DEVICENAME)
    if device_name:
        print('Старое имя устройства \t:', device_name['value'])
        device_name['value']+='_TEST'
        # Способ 1: изменить значение результата выполенения get_parameter()  
        current_scanner.set_parameter(device_name)
        device_name_new1 = current_scanner.get_parameter(const_parameter_name.USER_GENERAL_DEVICENAME)
        print('Метод 1: Новое имя \t:', device_name_new1['value']) # к имени будет добавлено _TEST
        #  Добавить '_TEST2' к концу имени устройства
        new_name=device_name['value']+"2"
        #  Способ 2: задать новое значение и имя изменяемого параметра
        current_scanner.set_parameter(new_name,const_parameter_name.USER_GENERAL_DEVICENAME)
        device_name_new2 = current_scanner.get_parameter(const_parameter_name.USER_GENERAL_DEVICENAME)
        print('Метод 2: Новое имя \t:', device_name_new2['value'])


read_params_from_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция получения текущих параметров сканера. При вызове данной функции «ядро» вычитывает 
со сканера все актуальные параметры, сохраняя их ввиде «списка параметров» для дальнейшей 
работы.

.. code-block:: python

    def read_params_from_scanner(self):

    
**Возвращаемое значение:**
- Код ошибки (*int*) - 1 в случае успеха

**Пример использования в коде:**

.. code-block:: python

    list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')
    current_scanner.read_params_from_scanner()


write_params_to_scanner()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Функция записи локальных параметров из «ядра» в сканер. При вызове данной функции 
происходит отправка списка локальных параметров из «ядра» в сканер.

.. code-block:: python

    def write_params_to_scanner(self):

  
**Возвращаемое значение:**
- Код ошибки (*int*) - 1 в случае успеха

**Пример использования в коде:**

.. code-block:: python
    :emphasize-lines: 8

    list = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
    current_scanner=select_scanner(list, ip_address='192.168.1.30')
    current_scanner.read_params_from_scanner()
    device_name = current_scanner.get_parameter(const_parameter_name.USER_GENERAL_DEVICENAME)
    if device_name:
        device_name['value']+='_TEST'
        current_scanner.set_parameter(device_name)
        current_scanner.write_params_to_scanner()
