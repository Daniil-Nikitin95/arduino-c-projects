#include <Servo.h>  //подключение библиотеки servo


Servo myservo;  // создание объекта servo для управления мотором
// на большинстве плат Arduino можно создать 12 servo объектов


String inputString = "";         // переменная типа string для сохранения входных данных
boolean stringComplete = false;  // флаг данные получены 


void setup() {
  myservo.attach(5); //выбираем девятый управляющий дискретный выход контроллера для управления моторчиком 


  //инициализация последовательного порта:
  Serial.begin(9600);


  // получить 200 байтов и записать в переменную inputString:
  inputString.reserve(200);


  myservo.write(0); //выставляем изначальное положение серво в 0 градусов
}


void loop() {
  serialEvent(); //вызов нашей коммуникационной функции


  // печатаем ответ в COM-порт и поворачиваем серво на заданный угол:
  if (stringComplete) {
    Serial.println(inputString);


    myservo.write(inputString.toInt()); //задание положения серво-машинке из полученной команды


    // обнуляем строковую переменную:
    inputString = "";
    stringComplete = false;
  }
}


void serialEvent() {
  while (Serial.available()) {
    // получить новый байт данных:
    char inChar = (char)Serial.read();


    // добавить новый байт к строковой переменной inputString:
    inputString += inChar;


    // если входной символ является новой строкой, взвести флаг
    // что бы основной цикл обработал принятую команду:
    if (inChar == '\n') {
      stringComplete = true;
    }


  }
}
