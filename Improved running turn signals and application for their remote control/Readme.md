# Улучшенные бегущие поворотники

Это проект "Улучшенные бегущие поворотники". Здесь Вы найдете код для ардуино и приложение для дистанционного 
управления поворотниками, написанное на языке C#.
Программа для arduino позволяет управлять огнями(поворотниками) с помощью кнопок. Всего 4 кнопки,
одна отвечает за включение левого поворотника, другая - за включение правого, третья - за включение
обоих сразу (аварийный режим), четвертая отвечает за переключение скорости бегущих поворотников.
Скоростей всего 3: медленная, средняя и быстрая.
Приложение для дистанционного управления позволяет управлять поворотниками из программы на том же
компьютере, к которому подключена плата ардуино. Приложение выполняет те же функции, что и кнопки,
но через него поворотниками удобнее управлять.

Чтобы проверить самостоятельно, как работает программа Running turn signals(Бегущие поворотники),
Вам нужно:
1) Скачать и установить Arduino IDE;
2) Соберите цепь как показано на рисунке scheme-of-circuit.png;
3) Подключите плату Arduino к компьютеру через USB-вход с помощью USB 2.0 Cable Type A/B;
4) Запустите Arduino IDE через скетч document.ino из папки document;
5) Выберите на панели Select Board Ваш порт(Arduino Uno COM3);
5) Нажмите кнопку "Upload".

Можно управлять кнопками, установленными на макетной плате либо через приложение.

Инструкция для управления через приложение:
6) Запустить можно через exe-файл, расположенный по пути "Remote control application\OPD\bin\Debug\OPD.exe"
либо через OPD.sln файл, расположенный по пути "Remote control application\OPD.sln".
7) Нажать кнопку Пуск на верхней панели.
8) Одно нажатие левой стрелки, повернутой влево, - одно мигание левого поворотника; аналогично с правой
стрелкой; А - аварийное мигание обоих поворотников; label - скорость бегущих огней.