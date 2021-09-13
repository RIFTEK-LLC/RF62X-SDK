.. _rf62x_wrappers_c_init:

*******************************************************************************
Инициализация SDK
*******************************************************************************

Файл ``rf62Xcore.h`` необходим для вызова функции инициализации SDK: ``core_init()``

Файл ``rf62X_sdk.h`` является основным файлом программного интерфейса (API) для 
разработки программ на языке C и определяет функциональность библиотеки-«обёртки» 
для rf62Xcore. 

Файл ``rf62X_types.h`` содержит основные структуры и типы, используемые в SDK. 

**core_init**
===============================================================================

**Прототип:**
   *int8_t core_init();*

**Описание:**
   *Функция инициализации SDK. Должна быть вызванна один раз перед дальнейшими 
   вызовами любых библиотечных функций* 

**Возвращаемое значение:**
   *После успешного завершения везвращается 1 (TRUE). В противном случае должен быть* 
   *возвращен код ошибки.*

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 27

   /** @file rf62Xcore.h */

   /**
    * @brief core_init - Initialize sdk library
    * @details Must be called once before further calls to any
    * library functions
    *
    * @return 1 if success or error code.
    */
   int8_t core_init();

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {

      // Initialize sdk library
      uint8_t is_init = core_init();

      if (is_init == 1)
         printf("SDK version: %s\n", sdk_version());
      else
      {
         printf("SDK initialization error: %s\n", is_init);
         return -1;
      }

      // some code...

   }



**core_cleanup**
===============================================================================

**Прототип:**
   *void core_cleanup();*

**Описание:**
   *Функция высвобождает ресурсы, выделенные с помощью функции* ``core_init`` 

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 28

   /** @file rf62Xcore.h */

   /**
    * @brief core_cleanup - Cleanup resources allocated
    * with core_init() function
    */
   void core_cleanup();

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Initialize sdk library
      core_init();

      // some code...

      // Cleanup resources
      core_cleanup();  
   }

**sdk_version**
===============================================================================

**Прототип:**
   *char\* sdk_version();*

**Описание:**
   *Функция получения информации о версии SDK* 

**Пример в коде:**

.. code-block:: c
   :emphasize-lines: 28

   /** @file rf62Xcore.h */

   /**
    * @brief sdk_version - Return info about SDK version
    *
    * @return SDK version
    */
   char* sdk_version();

   ------------------------------------------------------------------------------

   /** @file main.c */

   #include <stdio.h>
   #include <stdlib.h>

   #include "rf62Xcore.h"
   #include "rf62X_sdk.h"
   #include "rf62X_types.h"

   int main()
   {
      // Initialize sdk library
      core_init();

      // Print return rf627 sdk version
      printf("SDK version: %s\n", sdk_version());

      // Cleanup resources
      core_cleanup();  
   }


