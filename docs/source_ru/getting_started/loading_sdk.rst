.. _clone_rf62x_sdk:

*******************************************************************************
Загрузка проекта
*******************************************************************************

Git-клиент
===============================================================================

Для разработчиков, которые хотят загрузить библиотеку из исходников с помощью 
Git-клиента, следует выполнить следующие инструкции:

*  | **Установите git-клиент на свой локальный компьютер (если ещё не установлен)**
   | - В Linux используйте команду терминала: ``sudo apt install git``
   | - На MacOS используйте команду терминала: ``brew install git``
   | - Для других платформ смотрите `документация по установке git <https://git-scm.com/downloads>`__.

*  | **Откройте командную строку/терминал на вашем компьютере**
   | - В Linux щелкните панель запуска и найдите «терминал» - `terminal`
   | - В OS X нажмите command-space и найдите «терминал» - `terminal`
   | - В Windows нажмите меню «Пуск» и найдите «командную строку» - `cmd`.

*  **Клонируйте репозиторий с помощью следующих команд:**

   .. code-block:: bash

      git clone https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git
      cd RF62X-SDK
      git submodule update --init --recursive

Git в Qt Creator
===============================================================================

Для разработчиков, которые хотят загрузить и собрать библиотеку из исходников с 
помощью Git, встроенного в IDE Qt Creator, следует выполнить следующие инструкции:

1. Нажмите **File->New File or Project**


2. Выберите опцию **Import Project->Git Clone**, как показано ниже.

.. figure:: ../_static/clone-qt-code.png
    :alt: chouse repo
    :width: 100%
    :align: center


3. Введите url-адрес SDK ``https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git``, 
   выберите опцию **«Recursive»**, а затем нажмите **Next**.

.. figure:: ../_static/clone-qt-code-repo.png
    :alt: chouse repo
    :width: 100%
    :align: center

4. После загрузки откройте файл CMakeLists.txt необходимого вам проекта  
   через **File > Open File or Project**, выберите компилятор (MinGW, MSVC2017, Clang)
   и нажмите **Configure Project**

5. Запустите сборку проекта


Git в Visual Studio
===============================================================================

Для разработчиков, которые хотят загрузить и собрать библиотеку из исходников с 
помощью Git, встроенного в IDE Visual Studio, следует выполнить следующие инструкции:

1. Откройте Visual Studio 2019.

2. В стартовом окне выберите **Клонирование или извлечение кода**.

.. figure:: ../_static/clone-checkout-code-dark.png
    :alt: clone code
    :width: 100%
    :align: center

3. Введите url-адрес SDK ``https://gitlab.com/riftek_llc/software/sdk/scanners/RF62X-SDK.git``,
   выберите или введите местоположение хранилища, а затем нажмите **Клонировать**.

.. figure:: ../_static/clone-checkout-code-git-repo-dark.png
    :alt: chouse repo
    :width: 100%
    :align: center

4. После чего Visual Studio загрузит проект из удаленного репозитория и откроет его.

5. Выберите один из необходимых вам проектов и запустите его сборку.

.. figure:: ../_static/run-csharp-code-git-repo-dark.png
    :alt: chouse repo
    :width: 100%
    :align: center

.. note:: Для сборки библиотек **на языке С++**, а также компиляции приложений с примерами их использования в Visual Studio 
   должен быть установлен `C++ CMake tools для Windows <https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019>`__.




