# Передача данных между микроконтроллерами

В данной работе представлен пример передачи данных между микроконтроллерами ардуино.
В первой части работы мы реализуем протокол передачи по I2C (на схеме два красных провода, соединяющихся к аналоговым входам), в результате работы которого загорается левый светодиод.
Свечение нашего светодиода, питающегося от входа 9, с передачей по протоколу пары значений 10 и 1, отображается в мониторе последовательного интерфейса.

Чтобы проверить самостоятельно, как работает программа, Вам нужно:
1) Пройти по ссылке https://www.tinkercad.com/things/kLiiYY8aeIB?sharecode=-jjPTGZtt_hAacjCSG8DlLEGA5VMsY-_anLY89xNP98
2) Нажмите на кнопку Моделировать;
3) Нажмите на кнопку Начать моделирование.

Примечание: В седьмой работе ошибка в tinkercad, не работают светодиоды, хотя в реальной конструкции, 
собранной по такой схеме, всё работает нормально. 