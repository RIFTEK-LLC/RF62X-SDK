

.. _rf62x_wrappers_cpp_init:

*******************************************************************************
Инициализация SDK
*******************************************************************************

Файл ``rf62Xsdk.h`` является основным файлом программного интерфейса (API) и 
определяет функциональность библиотеки-«обёртки». 
Файл ``rf62Xtypes.h`` содержит дополнительный набор классов, структур, типов и 
перечеслений используемых в SDK.

.. _rf62x_wrappers_cpp_sdk_init:

**sdk_init**
===============================================================================

**Прототип:**
   *bool sdk_init();*

**Описание:**
   *Функция инициализации SDK. Должна быть вызванна один раз перед дальнейшими 
   вызовами любых библиотечных функций* 

**Возвращаемое значение:**
   *После успешного завершения возвращается 1 (true). В противном случае должен быть* 
   *возвращен код ошибки.*

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 26

   /** @file rf62Xsdk.h */

   /**
    * @brief sdk_init - Initialize sdk library
    * @details Must be called once before further calls to any
    * library functions
    *
    * @return true if success.
    */
   int8_t sdk_init();

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {

      // Initialize sdk library
      bool isInit = sdk_init();

      if (isInit)
         std::cout << "SDK version: " << sdk_version() << std::endl;
      else
      {
         std::cout << "SDK initialization error!" << std::endl;
         return -1;
      }

      // some code...

   }

.. _rf62x_wrappers_cpp_sdk_cleanup:

**sdk_cleanup**
===============================================================================

**Прототип:**
   *void sdk_cleanup();*

**Описание:**
   *Функция высвобождает ресурсы, выделенные при инициализации СДК 
   функцией* ``sdk_init`` 

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 27

   /** @file rf62Xsdk.h */

   /**
    * @brief sdk_cleanup - Cleanup resources allocated with
    * sdk_init() function
    */
   void sdk_cleanup();

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {
      // Initialize sdk library
      sdk_init();

      // some code...

      // Cleanup resources
      sdk_cleanup();  
   }

.. _rf62x_wrappers_cpp_sdk_version:

**sdk_version**
===============================================================================

**Прототип:**
   *std::string sdk_version();*

**Описание:**
   *Функция получения информации о версии SDK* 

**Возвращаемое значение:**
   *версии SDK в формате X.Y.Z (мажорная, минорная, патч)*

**Пример в коде:**

.. code-block:: cpp
   :emphasize-lines: 26

   /** @file rf62Xsdk.h */

   /**
    * @brief sdk_version - Return info about SDK version
    *
    * @return SDK version
    */
   std::string sdk_version();

   ------------------------------------------------------------------------------

   /** @file main.cpp */

   #include <string>
   #include <iostream>

   #include "rf62Xsdk.h"
   #include "rf62Xtypes.h"

   int main()
   {
      // Initialize sdk library
      sdk_init();

      // Print return rf62X sdk version
      std::cout << "SDK version: " << sdk_version() << std::endl;

      // some code...
   }