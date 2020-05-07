*******************************************************************************
Компиляция из исходников
*******************************************************************************

Библиотека содержит ряд модулей (программных классов). На рисунке ниже представлена UML
диаграмма классов библиотеки:

.. figure:: ../_static/ClassDiagram(v2).jpg
    :alt: Рисунок 1 – UML диаграмма классов
    :width: 100%
    :align: center


Описание программных классов библиотеки:

*  **Channel** (файл Channel.h) - Абстрактный класс, определяющий интерфейс для
   классов UDPChannel, SerialChannel, PureUDPChannel и PureSerialChannel. Этот
   класс определяет интерфейс класса обмена информацией для пользователя.

*  **UDPPort** (файлы UDPPort.h, UDPPort.cpp) - Класс обмена информацией через 
   UDP порт. Класс реализует интерфейс приема и отправки данных через сокет UDP 
   и предоставляет простой интерфейс работы с UDP портом.

*  **SerialPort** (файлы SerialPort.h, SerialPort.cpp) - Класс обмена информацией 
   по последовательному порту. Класс реализует интерфейс приема и отправки 
   данных через последовательный порт и предоставляет простой интерфейс работы 
   с последовательным портом.

*  **PureUDPChannel** (файлы PureUDPChannel.h, PureUDPChannel.cpp) - Класс для 
   организации обмена информацией через UDP-порт без дополнительной инкапсуляции 
   данных в протокол приклодного уровня, иными словами - чистый обмен данными 
   по UDP протоколу. Класс открывает сокеты и UDP порты и осуществляет обмен 
   информацией через них. Один экземпляр класса позволяет организовать обмен 
   информацией «точка-точка», при этом не допускается инициализации двух и более 
   объектов класса для обмена информацией через один UDP порт.

*  **PureSerialChannel** (файлы PureSerialChannel.h, PureSerialChannel.cpp) - Класс 
   для организации обмена информацией через COM-порт без дополнительной инкапсуляции 
   данных в протокол приклодного уровня, иными словами - чистый обмен данными 
   по СОМ-порту. Класс открывает файл последовательного порта и осуществляет обмен 
   информацией через него. Один экземпляр класса позволяет организовать обмен информацией 
   «точка-точка», при этом не допускается инициализации двух и более объектов класса для 
   обмена через один последовательный порт.

*  **ProtocolParser** (файлы ProtocolParser.h, ProtocolParser.cpp) - Класс парсера 
   информационных пакетов протокола `TransportProtocol <https://constantrobotics.com>`__. 
   Класс предназначен для кодирования/декодирования информационных пакетов, 
   а также предназначен для осуществления логики информационного обмена протокола 
   `TransportProtocol <https://constantrobotics.com>`__.

*  **UDPChannel** (файлы UDPChannel.h, UDPChannel.cpp) - Класс для 
   организации обмена информацией через UDP-порт посредством дополнительной инкапсуляции 
   данных в протокол приклодного уровня - `TransportProtocol <https://constantrobotics.com>`__. 
   Класс открывает сокеты и UDP порты и осуществляет обмен информацией через них. 
   Один экземпляр класса позволяет организовать обмен информацией «точка-точка», 
   при этом не допускается инициализации двух и более объектов класса для обмена 
   информацией через один UDP порт.

*  **SerialChannel** (файлы SerialChannel.h, SerialChannel.cpp) - Класс для организации 
   обмена информацией через COM-порт посредством дополнительной инкапсуляции 
   данных в протокол приклодного уровня - `TransportProtocol <https://constantrobotics.com>`__. 
   Класс открывает файл последовательного порта и осуществляет обмен информацией через него. 
   Один экземпляр класса позволяет организовать обмен информацией «точка-точка», 
   при этом не допускается инициализации двух и более объектов класса для обмена через 
   один последовательный порт.



Для использования библиотеки clib в проектах C++ разработчик может включить 
необходимые файлы библиотеки в свой проект, либо предварительно собрать 
статическую или динамическую программную библиотеки. 

Возможно, вы захотите собрать clib из исходного кода одним из предлагаемых нами 
методом.

Windows
===============================================================================

В Windows мы советуем использовать Visual Studio 2017 или новее, поскольку clib 
в значительной степени опирается на языковые функции C++ 11.

1. Зависимости 
-------------------------------------------------------------------------------

Для удобства компиляции мы включили исходный код всех зависимых библиотек в 
папку ``modules``. Поэтому вам не нужно устанавливать никаких зависимостей.

2. Сборка clib в качестве программной библиотеки 
-------------------------------------------------------------------------------

Для использования clib в разрабатываемом проекте в качестве программной 
библиотеки необходимо:
1. В вверхнем меню Visual Studio выберите **«Файл»** > **«Создать»** > **«Проект»**, 
   для открытия диалогового окно **«Создание проекта»**. 
   
2. В верхней части диалогового окна установите язык на **C++**, платформу для 
   **Windows** и тип проекта в **Библиотеку**. 
   
3. В отфильтрованном списке типов проектов выберите 
   **мастер классических приложенией Windows** и нажмите **Далее**:

.. figure:: ../_static/vs2019_create_new_project.jpg
    :alt: Рисунок 1 – Создание нового проекта при помощи мастера
    :width: 100%
    :align: center

.. warning:: Илюстрации по созданию проекта могут различаться в зависимости от вашей версии Visual Studio.

4. На странице настройки нового проекта введите *clib* в поле **Имя проекта**, 
   чтобы указать имя для проекта. Нажмите кнопку «Создать», чтобы открыть диалоговое окно 
   **«Проект классического приложения Windows»**.
   
5. В диалоговом окне **«Проект классического приложения Windows»** в разделе 
   **«Тип приложения»** выбрать необходимый тип - Динамическая библиотека (.dll) или 
   Статическая библиотека (.lib). В качестве примера демонстрируется создание статической библиотеки clib. 

.. note:: В разделе **«Дополнительные параметры»** снимите флажок **«Прекомпилированный заголовок»**, если он установлен. Установите флажок **Пустой проект**.

.. figure:: ../_static/vs2019_config_new_project.jpg
    :alt: Рисунок 2 – Настройка нового проекта при помощи мастера
    :width: 100%
    :align: center

6. Нажмите **OK**, чтобы создать проект.

7. Добавьте необходимые исходные файлы в проект, выберите *x64 Debug* или *x64 Release* 
   в качестве целевой платформы приложения и запустите локальный отладчик Windows.
   По окончанию сборки в выходном каталоге появится статическая библиотека clib.lib

.. figure:: ../_static/vs2019_build_clib.jpg
    :alt: Рисунок 3 – Создание статической библиотека clib.lib
    :width: 100%
    :align: center

3. Использования clib в качестве программной библиотеки
-------------------------------------------------------------------------------

**Создание консольного приложения C++**

1. В **обозревателе решений** щелкните правой кнопкой мыши на верхний узел Решение *clib*, 
   чтобы открыть контекстное меню. Выберите **«Добавить»** > **«Новый проект»**, чтобы 
   открыть диалоговое окно **«Добавить новый проект»**.

2. В верхней части диалогового окна установите фильтр типа проекта **«Консоль»**.

3. Из отфильтрованного списка типов проектов выберите **Консольное приложение**, затем нажмите **Далее**. 
   На следующей странице введите *TestSender* в поле **«Имя»**, чтобы указать имя для проекта, нажмите кнопку **«Создать»** 

4. После создания консольного приложения для вас создается пустая программа. 
   Имя исходного файла совпадает с именем, которое вы выбрали ранее. В примере оно называется TestSender.cpp

.. figure:: ../_static/vs2019_test_sender.jpg
    :alt: Рисунок 4 – Создание консольного приложения
    :width: 100%
    :align: center

**Использование функциональности библиотеки clib**

1. Прежде чем вы сможете использовать статическую библиотеку clib, вы должны обратиться к ней. 
   Откройте контекстное меню для проекта TestSender в **Обозревателе решений**, а затем выберите **«Добавить»** > **«Ссылка»** .

2. В диалоговом окне **«Добавить ссылку»** перечислены библиотеки, на которые вы можете ссылаться. 
   Откройте вкладку **«Проекты»**, установите флажок **«clib»** и нажмите кнопку **«ОК»**.

3. Чтобы сослаться на заголовочные файлы библиотеки, вы должны изменить путь включенных каталогов. 
   Для этого в **обозревателе решений** щелкните правой кнопкой мыши на проекте *TestSender*, 
   чтобы открыть контекстное меню. Выберите **«Свойства»**, чтобы открыть диалоговое окно «Страницы свойств TestSender».

4. На странице свойств установите настройки **Конфигурация** в *Все конфигурации* и **«Платформа»** выберите *Все платформы*.

5. Далее выберите **Свойства конфигурации** > **C/C++** > **Общие**. В поле дополнительные каталоги включения укажите путь к clib каталогу.

6. Теперь вы можете использовать методы статической библиотеки clib в консольном приложении. Ниже приведен пример передачи данных 

.. code-block:: cpp

   // Sender.cpp - example data-sender application

   #include <iostream>
   #include "Channel.h"
   #include "PureSerialChannel.h"


   int main(void)
   {
      clib::Channel* channel;
      std::string initString = "\\\\.\\COM1;19200;128;2400";
      uint32_t dataSize = 2400;
      float bandwidthMbps = (float)19200 / 1048576.0f;
      
      // Create channel object
      channel = new clib::PureSerialChannel();
	
      // Init channel
      if (!channel->Init(initString))
      {
         std::cout << "Channel not init" << std::endl;
         return -1;
      }


      // Allocate memory for output data.
      uint8_t* data = new uint8_t[dataSize];
      // Value of data.
      uint8_t dataValue = 0;
      // Fill data buffer.
      memset(data, dataValue, dataSize);
      
      std::cout << "Start sending data..." << std::endl;

      // Sending loop
      while (true)
      {
         // Fill data by new value.
         ++dataValue;
         memset(data, dataValue, dataSize);
         
         // Send data to 0 logic port
         channel->SendData(data, dataSize, 0, 0, bandwidthMbps);
            
         std::cout << dataSize << " bytes was sent. Data value: " << (int)dataValue << std::endl;
      }
      
      return 1;
   }


4. Использования clib в качестве исходных файлов
-------------------------------------------------------------------------------

Обмен данными через UDP порт
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

При подключении исходных файлов clib в разрабатываемый вами проект по 
организации обмена информацией через порт UDP разработчик должен включить в 
свой проект следующие файлы:

.. table:: 

   +-----------------------------+-------------------------------------------------------+
   | Channel (*.h)               | Абстрактный класс-интерфейс                           |
   +-----------------------------+-------------------------------------------------------+
   | UDPPort (*.cpp, *.h)        | Враппер обмена данными через UDP порт                 |
   +-----------------------------+-------------------------------------------------------+
   | PureUDPChannel (*.cpp, *.h) | Чистый обмена данными по UDP (без инкапсуляции)       |
   +-----------------------------+-------------------------------------------------------+
   | ProtocolParser (*.cpp, *.h) | Парсер пакетов протокола TransportProtocol            |
   +-----------------------------+-------------------------------------------------------+
   | UDPChannel (*.cpp, *.h)     | Обмен данными по протоколу TransportProtocol через UDP|
   +-----------------------------+-------------------------------------------------------+


Пример кода для организации обмена данными через UDP порт с использованием исходных файлов библиотеки clib:

.. code-block:: cpp

   // Sender.cpp - example data-sender application
   // destination port: 50020, source port: 50021

   #include <iostream>
   #include "Channel.h"
   #include "UDPChannel.h"
   #include "PureUDPChannel.h"


   int main(void)
   {
      std::cout << "### EXAMPLE UDP DATA SENDER ###" << std::endl << std::endl;
      
      clib::Channel* channel;
      std::string initString = "";
      std::string dstIP = "";
      uint32_t dataSize = 0;
      float bandwidthMbps = 0.0f;
      int protocolType = 0;


      // Dialogue to enter destination IP
      std::cout << "Enter reciever IP: ";
      std::cin >> dstIP;
      // Dialogue to enter communication channel bandwidth
      std::cout << "Enter communication channel bandwidth in Mbps: ";
      std::cin >> bandwidthMbps;

      // Calculate dataSize
      dataSize = (uint32_t)(bandwidthMbps * 131072.0f);
      std::cout << dataSize << " bytes to send" << std::endl << std::endl;

      // Dialogue to enter protocol type (transport Protocol or Pure)
      std::cout << "Enter protocol type (1 - Transport Protocol or 2 - Pure): ";
      std::cin >> protocolType;
      if (protocolType != 1 && protocolType != 2) protocolType = 1;

      // Create channel object
      if (protocolType == 1)
         channel = new clib::UDPChannel();
      else
         channel = new clib::PureUDPChannel();

      // Create initialization string
      initString = dstIP + ";50020;50021;1024;" + std::to_string(dataSize);
	

      // Init channel
      if (!channel->Init(initString))
      {
         std::cout << "Channel not init" << std::endl;
         return -1;
      }


      // Allocate memory for output data.
      uint8_t* data = new uint8_t[dataSize];
      // Value of data.
      uint8_t dataValue = 0;
      // Fill data buffer.
      memset(data, dataValue, dataSize);
      
      std::cout << "Start sending data..." << std::endl;

      // Sending loop
      while (true)
      {
         // Fill data by new value.
         ++dataValue;
         memset(data, dataValue, dataSize);
         
         // Send data to 0 logic port
         if (protocolType == 1)
            // Send data until confirmation during 2s.
            channel->SendData(data, dataSize, 0, 2000, bandwidthMbps);
         else
            // Send data once.
            channel->SendData(data, dataSize, 0, 0, bandwidthMbps);
            
         std::cout << dataSize << " bytes was sent. Data value: " << (int)dataValue << std::endl;
      }
      
      return 1;
   }


.. code-block:: cpp

   // Receiver.cpp - example data-receiver application
   // destination port: 50021, source port: 50020

   #include <iostream>
   #include "Channel.h"
   #include "UDPChannel.h"
   #include "PureUDPChannel.h"


   int main(void)
   {
      std::cout << "### EXAMPLE UDP DATA RECEIVER ###" << std::endl << std::endl;
      
      clib::Channel* channel;
      std::string initString = "";
      std::string dstIP = "";
      int protocolType = 0;
      const uint32_t maxDataSize = 186624000;
      
      // Dialogue to enter destination IP
      std::cout << "Enter sender IP: ";
      std::cin >> dstIP;
      
      // Dialogue to enter protocol type (transport Protocol or Pure)
      std::cout << "Enter protocol type (1 - Transport Protocol or 2 - Pure): ";
      std::cin >> protocolType;
      if (protocolType != 1 && protocolType != 2) protocolType = 1;
      
      // Create channel object
      if (protocolType == 1)
         channel = new clib::UDPChannel();
      else
         channel = new clib::PureUDPChannel();
         
      // Create initialization string
      initString = dstIP + ";50021;50020;1024;" + std::to_string(maxDataSize);
      
      
      // Init channel
      if (!channel->Init(initString))
      {
         std::cout << "Channel not init" << std::endl;
         return -1;
      }
      
      
      // Allocate memory for output data.
      uint8_t* data = new uint8_t[maxDataSize];
      // Fill data buffer.
      memset(data, 0, maxDataSize);
      
      std::cout << "Start reading data..." << std::endl;
      
      // Reading loop
      while (true)
      {
         // Wait data from 0 logic port without time limit.
         uint32_t inputSize = 0;
         if (channel->GetData(data, maxDataSize, inputSize, 0, 2000))
         {
            // Print calculated bandwidth value.
            std::cout << "Recieved " << inputSize << " bytes" << std::endl;
         }
      }
      return 1;
   }

Результат вывода приложений Receiver и Sender при обмене данными через UDP порт с использование протокола TransportProtocol:

.. figure:: ../_static/UDPChannel_example.jpg
    :alt: Рисунок 2 – Результат запуска приложений Receiver и Sender
    :width: 100%
    :align: center


Пример использования библиотеки для организации обмена данными через COM порт
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Для организации обмена информацией через последовательный порт разработчик 
должен включить в свой проект следующие файлы:

.. table:: 

   +--------------------------------+------------------------------------------------------------+
   | Channel (*.h)                  | Абстрактный класс-интерфейс                                |
   +--------------------------------+------------------------------------------------------------+
   | SerialPort (*.cpp, *.h)        | Враппер обмена данными по COM порту                        |
   +--------------------------------+------------------------------------------------------------+
   | PureSerialChannel (*.cpp, *.h) | Чистый обмена данными по COM порту (без инкапсуляции)      |
   +--------------------------------+------------------------------------------------------------+
   | ProtocolParser (*.cpp, *.h)    | Парсер пакетов протокола TransportProtocol                 |
   +--------------------------------+------------------------------------------------------------+
   | SerialChannel (*.cpp, *.h)     | Обмен данными по протоколу TransportProtocol через COM порт|
   +--------------------------------+------------------------------------------------------------+


Пример кода для организации обмена данными через COM порт с использованием исходных файлов библиотеки clib:

.. code-block:: cpp

   // Sender.cpp - example data-sender application

   #include <iostream>
   #include "Channel.h"
   #include "SerialChannel.h"
   #include "PureSerialChannel.h"


   int main(void)
   {
      std::cout << "### EXAMPLE SERIAL DATA SENDER ###" << std::endl << std::endl;
      
      clib::Channel* channel;
      std::string initString = "";
      uint32_t dataSize = 0;
      float bandwidthMbps = 0.0f;
      int protocolType = 0;


      int serialPortNumToSend = 0;
      int serialPortBaudrate = 0;
      
      // Dialogue to enter serial port num to send data.
      std::cout << "Enter serial port num to send data: ";
      std::cin >> serialPortNumToSend;
      // Dialogue to enter baudrate value.
      std::cout << "Enter serial port baudrate in bits per second: ";
      std::cin >> serialPortBaudrate;
      
      
      // Calculate data size
      bandwidthMbps = (float)serialPortBaudrate / 1048576.0f;
      dataSize = (uint32_t)(bandwidthMbps * 131072.0f);
      std::cout << dataSize << " bytes to send" << std::endl << std::endl;
      
      // Dialogue to enter protocol type (transport Protocol or Pure)
      std::cout << "Enter protocol type (1 - Transport Protocol or 2 - Pure): ";
      std::cin >> protocolType;
      if (protocolType != 1 && protocolType != 2) protocolType = 1;

      // Create channel object
      if (protocolType == 1)
         channel = new clib::SerialChannel();
      else
         channel = new clib::PureSerialChannel();

      // Create initialization string
      const std::string serialPortNamePrefix = "\\\\.\\COM";
      initString = serialPortNamePrefix + std::to_string(serialPortNumToSend) + ";" +
                   std::to_string(serialPortBaudrate) + ";128;" + std::to_string(dataSize);
	

      // Init channel
      if (!channel->Init(initString))
      {
         std::cout << "Channel not init" << std::endl;
         return -1;
      }


      // Allocate memory for output data.
      uint8_t* data = new uint8_t[dataSize];
      // Value of data.
      uint8_t dataValue = 0;
      // Fill data buffer.
      memset(data, dataValue, dataSize);
      
      std::cout << "Start sending data..." << std::endl;

      // Sending loop
      while (true)
      {
         // Fill data by new value.
         ++dataValue;
         memset(data, dataValue, dataSize);
         
         // Send data to 0 logic port
         if (protocolType == 1)
            // Send data until confirmation during 2s.
            channel->SendData(data, dataSize, 0, 2000, bandwidthMbps);
         else
            // Send data once.
            channel->SendData(data, dataSize, 0, 0, bandwidthMbps);
            
         std::cout << dataSize << " bytes was sent. Data value: " << (int)dataValue << std::endl;
      }
      
      return 1;
   }


.. code-block:: cpp

   // Receiver.cpp - example data-receiver application

   #include <iostream>
   #include "Channel.h"
   #include "SerialChannel.h"
   #include "PureSerialChannel.h"


   int main(void)
   {
      std::cout << "### EXAMPLE SERIAL DATA RECEIVER ###" << std::endl << std::endl;
      
      clib::Channel* channel;
      std::string initString = "";
      int protocolType = 0;
      const uint32_t maxDataSize = 186624000;      
      int serialPortNumToRead = 0;
      int serialPortBaudrate = 0;
      
      // Dialogue to enter serial port num to send data.
      std::cout << "Enter serial port num to read data: ";
      std::cin >> serialPortNumToRead;
      // Dialogue to enter baudrate value.
      std::cout << "Enter serial port baudrate in bits per second: ";
      std::cin >> serialPortBaudrate;
      
      // Dialogue to enter protocol type (transport Protocol or Pure)
      std::cout << "Enter protocol type (1 - Transport Protocol or 2 - Pure): ";
      std::cin >> protocolType;
      if (protocolType != 1 && protocolType != 2) protocolType = 1;
      
      // Create channel object
      if (protocolType == 1)
         channel = new clib::SerialChannel();
      else
         channel = new clib::PureSerialChannel();
         
      // Create initialization string
      const std::string serialPortNamePrefix = "\\\\.\\COM";
      initString = serialPortNamePrefix + std::to_string(serialPortNumToRead) + ";" +
                   std::to_string(serialPortBaudrate) + ";128;" + std::to_string(maxDataSize);
      
      
      // Init channel
      if (!channel->Init(initString))
      {
         std::cout << "Channel not init" << std::endl;
         return -1;
      }
      
      
      // Allocate memory for output data.
      uint8_t* data = new uint8_t[maxDataSize];
      // Fill data buffer.
      memset(data, 0, maxDataSize);
      
      std::cout << "Start reading data..." << std::endl;
      
      // Reading loop
      while (true)
      {
         // Wait data from 0 logic port without time limit.
         uint32_t inputSize = 0;
         if (channel->GetData(data, maxDataSize, inputSize, 0, 2000))
         {
            // Print calculated bandwidth value.
            std::cout << "Recieved " << inputSize << " bytes" << std::endl;
         }
      }
      return 1;
   }


Результат вывода приложений Receiver и Sender при обмене данными через COM порт с использование протокола TransportProtocol:

.. figure:: ../_static/SerialChannel_example.jpg
    :alt: Рисунок 3 – Результат запуска приложений Receiver и Sender
    :width: 100%
    :align: center



Ubuntu
===============================================================================

1. Установка зависимостей (опционально)
-------------------------------------------------------------------------------

2. Конфигурирование проекта
-------------------------------------------------------------------------------

2. Сборка и установка clib
-------------------------------------------------------------------------------

MacOS
===============================================================================

Шаги компиляции MacOS в основном идентичны Ubuntu.

1. Установка зависимостей (опционально)
-------------------------------------------------------------------------------

2. Конфигурирование проекта
-------------------------------------------------------------------------------

2. Сборка и установка clib
-------------------------------------------------------------------------------
