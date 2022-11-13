// Пример тестового скетча для различных датчиков влажности/температуры DHT
// Автор: ladyada, общественное достояние

#include "DHT.h"
#include "dht11.h"

#define DHTPIN 2     // цифровой пин, к которому мы подключены

// Раскомментируйте любой тип, который вы используете!
#define DHTTYPE DHT11   // DHT 11
//define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Подключаем контакт 1 (левый) датчика к +5В
// ПРИМЕЧАНИЕ. При использовании платы с логикой 3,3 В, такой как Arduino Due, подключите контакт 1
// до 3,3В вместо 5В!
// Подключите контакт 2 датчика к вашему DHTPIN
// Подключите контакт 4 (справа) датчика к ЗАЗЕМЛЕНИЮ
// Подключите резистор 10K от контакта 2 (данные) к контакту 1 (питание) датчика

// Инициализировать датчик DHT.
// Обратите внимание, что более ранние версии этой библиотеки принимали необязательный третий параметр для
// настроить тайминги для более быстрых процессоров. Этот параметр больше не нужен
// поскольку текущий алгоритм чтения DHT настраивается для работы с более быстрыми процессами.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
// Подождите несколько секунд между измерениями.
  delay(2000);


// Чтение температуры или влажности занимает около 250 миллисекунд!
   // Показания датчика также могут быть «старыми» до 2 секунд (это очень медленный датчик)
  float h = dht.readHumidity();


// Чтение температуры в градусах Цельсия (по умолчанию)
  float t = dht.readTemperature();


// Чтение температуры в градусах Фаренгейта (isFahrenheit = true)
  float f = dht.readTemperature(true);


// Проверяем, не завершились ли какие-либо операции чтения, и выходим досрочно (чтобы повторить попытку).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


// Расчет теплового индекса в Фаренгейтах (по умолчанию)
  float hif = dht.computeHeatIndex(f, h);


// Расчет теплового индекса в градусах Цельсия (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);


  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
