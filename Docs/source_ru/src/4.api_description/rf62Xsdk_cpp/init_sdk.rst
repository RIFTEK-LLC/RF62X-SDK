

.. _rf62x_wrappers_description_cpp:

*******************************************************************************
Инициализация SDK
*******************************************************************************

Файл ``rf62Xsdk.h`` является основным файлом программного интерфейса (API) и 
определяет функциональность библиотеки-«обёртки». 
Файл ``rf62Xtypes.h`` содержит дополнительный набор классов, структур, типов и 
перечеслений используемых в SDK.

**sdk_init**
===============================================================================

**Прототип:**
   *bool sdk_init();*

**Описание:**
   *Функция инициализации SDK. Должна быть вызванна один раз перед дальнейшими 
   вызовами любых библиотечных функций* 

**Возвращаемое значение:**
   *После успешного завершения везвращается 1 (TRUE). В противном случае должен быть* 
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