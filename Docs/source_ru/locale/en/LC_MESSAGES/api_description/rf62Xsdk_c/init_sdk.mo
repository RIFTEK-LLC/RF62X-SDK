��          T               �      �   -  �   }   �  ~   X  I   �  �   !  {  �     j  �   }  S   -  ]   �  (   �  _      Инициализация SDK Файл ``rf62X_sdk.h`` является основным файлом программного интерфейса (API) для разработки программ на языке C и определяет функциональность библиотеки-«обёртки» для rf62Xcore. Файл ``rf62X_types.h`` содержит основные структуры и типы, используемые в SDK. Файл ``rf62Xcore.h`` необходим для вызова функции инициализации SDK: ``core_init()`` Функция для получения текущей версии SDK: Функция инициализации SDK. Должна быть вызванна один раз перед дальнейшими вызовами любых библиотечных функций: Project-Id-Version: RF62X-SDK 
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2020-08-31 17:52+0300
PO-Revision-Date: YEAR-MO-DA HO:MI+ZONE
Last-Translator: FULL NAME <EMAIL@ADDRESS>
Language: en
Language-Team: en <LL@li.org>
Plural-Forms: nplurals=2; plural=(n != 1)
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
Content-Transfer-Encoding: 8bit
Generated-By: Babel 2.9.1
 SDK initialization The file ``rf62X_sdk.h`` is the main program interface (API) file for developing programs in C language and defines the functionality of the «wrapper» library for rf62Xcore. The file ``rf62X_types.h`` contains the basic structures and types used in the SDK. The file ``rf62Xcore.h`` is required to call the SDK initialization function: ``core_init()`` Function to get the current SDK version: SDK initialization function. Must be called once before further calls to any library functions: 