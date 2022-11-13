/*Ультразвуковой датчик расстояния и Arduino – полный гайд

Распиновка ультразвукового датчика расстояния:

VCC: +5V

Trig : Триггер (INPUT) – 11 пин

Echo: Эхо (OUTPUT) – 12 пин

GND: GND

*/

int trigPin = 11;    //Триггер – зеленый проводник

int echoPin = 12;    //Эхо – желтый проводник

long duration, cm;

void setup() {

//Serial Port begin

Serial.begin (9600);

//Инициализирум входы и выходы

pinMode(trigPin, OUTPUT);

pinMode(echoPin, INPUT);

}

void loop()

{

// Датчик срабатывает и генерирует импульсы шириной 10 мкс или больше

// Генерируем короткий LOW импульс, чтобы обеспечить «чистый» импульс HIGH:

digitalWrite(trigPin, LOW);

delayMicroseconds(5);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);

// Считываем данные с ультразвукового датчика: значение HIGH, которое

// зависит от длительности (в микросекундах) между отправкой

// акустической волны и ее обратном приеме на эхолокаторе.

pinMode(echoPin, INPUT);

duration = pulseIn(echoPin, HIGH);

// преобразование времени в расстояние

cm = (duration/2) / 29.1;

Serial.print(cm);

Serial.print("cm");

Serial.println();

delay(1000);

}
