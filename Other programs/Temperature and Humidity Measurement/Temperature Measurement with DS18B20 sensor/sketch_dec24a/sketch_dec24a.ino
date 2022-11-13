#include <OneWire.h>
#include <DallasTemperature.h>
 
// Номер пина Arduino с подключенным датчиком
#define PIN_DS18B20 5
 
// Создаем объект OneWire
OneWire oneWire(PIN_DS18B20);
 
// Создаем объект DallasTemperature для работы с сенсорами, передавая ему ссылку на объект для работы с 1-Wire.
DallasTemperature dallasSensors(&oneWire);
 
// Специальный объект для хранения адреса устройства
DeviceAddress sensorAddress;
 
void setup(void){
  Serial.begin(9600);
  Serial.println("Пример работы с датчиком температуры ds18b20 с помощью библиотеки DallasTemperature");
 

  // Выполняем поиск устрйоств на линии
  Serial.print("Ищем устройства...");
  dallasSensors.begin();
  Serial.print("Найдено ");
  Serial.print(dallasSensors.getDeviceCount(), DEC);
  Serial.println(" устройств.");
 

  // Определяем режим питания (по отдельной линии или через паразитное питание по линии данных)
  Serial.print("Режим паразитного питания: ");
  if (dallasSensors.isParasitePowerMode()) Serial.println("ВКЛЮЧЕН");
  else Serial.println("ВЫКЛЮЧЕН");
 
  // Раскомментируйте, если хотите задать адрес устройства вручную
  //sensorAddress = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
 

  // Поиск устройства:
  // Ищем адрес устройства по порядку (индекс задается вторым параметром функции)
  if (!dallasSensors.getAddress(sensorAddress, 0)) Serial.println("Не можем найти первое устройство");
 
  // Второй вариант поиска с помощью библиотеки OnewWire.
  // Перезапускаем поиск
  //oneWire.reset_search();
  // Находим первое устройство и запоминаем его адрес в sensorAddress
  //if (!oneWire.search(sensorAddress)) Serial.println("Unable to find address for sensorAddress");
 

  // Отображаем адрес ds18b20, который мы нашли
  Serial.print("Адрес устройства: ");
  printAddress(sensorAddress);
  Serial.println();
 

  // Устанавливаем разрешение датчика в 12 бит (мы могли бы установить другие значения, точность уменьшится, но скорость получения данных увеличится
  dallasSensors.setResolution(sensorAddress, 12);
 
  Serial.print("Разрешение датчика: ");
  Serial.print(dallasSensors.getResolution(sensorAddress), DEC);
  Serial.println();
}
 
void loop(void){
  // Запрос на измерения датчиком температуры
 
  Serial.print("Измеряем температуру...");
  dallasSensors.requestTemperatures(); // Просим ds18b20 собрать данные
  Serial.println("Выполнено");
 

  //  Запрос на получение сохраненного значения температуры
  printTemperature(sensorAddress);
 

  // Задержка для того, чтобы можно было что-то разобрать на экране
  delay(1000);
}
 

// Вспомогательная функция печати значения температуры для устрйоства
void printTemperature(DeviceAddress deviceAddress){
  float tempC = dallasSensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.println(tempC);
}
 

// Вспомогательная функция для отображения адреса датчика ds18b20
void printAddress(DeviceAddress deviceAddress){
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
