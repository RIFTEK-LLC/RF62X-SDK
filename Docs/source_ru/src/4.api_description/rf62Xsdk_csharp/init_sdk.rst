

.. _rf62x_wrappers_csharp_init:

*******************************************************************************
Инициализация SDK
*******************************************************************************

Файл ``RF62X-SDK.cs`` является основным файлом программного интерфейса (API) 
и определяет функциональность библиотеки-«обёртки». 
``RF62X-TYPES.cs`` содержит дополнительный набор классов, структур, типов и 
перечислений используемых в SDK.

.. _rf62x_wrappers_csharp_sdk_init:

**SdkInit**
===============================================================================

**Прототип:**
   *bool SdkInit();*

**Описание:**
   *Функция инициализации SDK. Должна быть вызвана один раз перед дальнейшими 
   вызовами любых библиотечных функций* 

**Возвращаемое значение:**
   *После успешного завершения возвращается true. В противном случае должен быть* 
   *возвращен false.*

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 28

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// SdkInit - Initialize sdk library
   /// </summary>
   /// <remarks>
   /// Must be called once before further calls to any library functions
   /// </remarks> 
   /// <returns>true if success.</returns>
   public static bool SdkInit();

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            bool isInit = RF62X.SdkInit();

            if (isInit)
               Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
            else
            {
               Console.WriteLine("SDK initialization error!");
            }

            // some code...
         }
      }
   }

.. _rf62x_wrappers_csharp_sdk_cleanup:

**SdkCleanup**
===============================================================================

**Прототип:**
   *void SdkCleanup();*

**Описание:**
   *Функция высвобождает ресурсы, выделенные при инициализации СДК 
   функцией* :ref:`rf62x_wrappers_csharp_sdk_init`

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 36

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// SdkCleanup - Cleanup resources allocated with sdk_init() function
   /// </summary>
   public static void SdkCleanup();

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            bool isInit = RF62X.SdkInit();

            if (isInit)
               Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
            else
            {
               Console.WriteLine("SDK initialization error!");
            }

            // some code...

            // Cleanup resources
            SdkCleanup();  
         }
      }
   }

.. _rf62x_wrappers_csharp_sdk_version:

**SdkVersion**
===============================================================================

**Прототип:**
   *string SdkVersion();*

**Описание:**
   *Функция получения информации о версии SDK* 

**Возвращаемое значение:**
   *версия SDK в формате X.Y.Z (мажорная, минорная, патч)*

**Пример в коде:**

.. code-block:: c#
   :emphasize-lines: 27

   /// <file> RF62X-SDK.cs

   /// <summary>
   /// SdkCleanup - Cleanup resources allocated with sdk_init() function
   /// </summary>
   public static void SdkCleanup();

   ------------------------------------------------------------------------------

   /// <file> Program.cs

   using System;
   using System.Collections.Generic;
   using System.Threading;
   using SDK.SCANNERS;

   namespace EXAMPLE
   {
      class Program
      {
         static void Main(string[] args)
         {
            // Initialize sdk library
            bool isInit = RF62X.SdkInit();

            if (isInit)
               Console.WriteLine("SDK version: {0}", RF62X.SdkVersion());
            else
            {
               Console.WriteLine("SDK initialization error!");
            }

            // some code...

            // Cleanup resources
            RF62X.SdkCleanup();  
         }
      }
   }