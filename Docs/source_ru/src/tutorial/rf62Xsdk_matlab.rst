*******************************************************************************
Примеры для MatLab
*******************************************************************************

.. _how_to_use_rf62x_sdk_csharp_for_search:

Поиск устройств RF62X
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример поиска сканеров серии RF627Old в сети 

.. code-block:: Matlab

   clc
   dll_in_matlab = NET.addAssembly('rf62Xsdk.dll');
   dll_in_matlab.Classes

   clc;
   import SDK.SCANNERS.*
   import SDK.SCANNERS.RF62X.*
   import SDK.SCANNERS.RF62X+RF627old.*
   import System.Collections.Generic.*

   % Initialize sdk library
   RF62X.SdkInit();

   % Print return rf62X sdk version
   RF62X.SdkVersion()

   % Search for RF627old devices over network
   list=Search()
   
   % Cleanup resources allocated with SdkInit()
   RF62X.SdkCleanup()



.. _how_to_use_rf62x_sdk_csharp_get_profile:

Получение профиля сканера
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример получения профилей от сканеров серии RF627Old




.. _how_to_use_rf62x_sdk_csharp_get_set_params:

Получение и установка параметров
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Ниже приведен пример получения и изменения имени сканера, установки IP адреса, смены 
состояния лазера (включение или отключение):

