��    	      d               �      �   
   �      �      �   �  �   y   �  I   "  �   l  {  9     �  
   �     �     �  	  �  J   �  /   D  _   t   sdk_cleanup() sdk_init() sdk_version() Инициализация SDK Файл ``rf62Xsdk.h`` является основным файлом программного интерфейса (API) для разработки программ на языке C++ и определяет функциональность библиотеки-«обёртки» для rf62Xcore. ``rf62Xsdk.h`` содержит следующий набор классов и функций для инициализации SDK: Функция для очистки ресурсов выделенных с помощью функции ``sdk_init``: Функция для получения текущей версии SDK: Функция инициализации SDK. Должна быть вызванна один раз перед дальнейшими вызовами любых библиотечных функций: Project-Id-Version: RF62X-SDK 
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2020-05-26 10:17+0300
PO-Revision-Date: YEAR-MO-DA HO:MI+ZONE
Last-Translator: FULL NAME <EMAIL@ADDRESS>
Language: en
Language-Team: en <LL@li.org>
Plural-Forms: nplurals=2; plural=(n != 1)
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
Content-Transfer-Encoding: 8bit
Generated-By: Babel 2.8.0
 sdk_cleanup() sdk_init() sdk_version() SDK initialization The file ``rf62Xsdk.h`` is the main file for the programming interface (API) for developing C++ programs and defines the functionality of the wrapper library for rf62Xcore. ``rf62Xsdk.h`` contains the following set of classes and functions for initializing the SDK: Function for cleaning resources allocated using the ``sdk_init`` function: Function to get the current version of the SDK: SDK initialization function. Must be called once before further calls to any library functions: 