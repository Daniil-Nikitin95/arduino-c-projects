// Простой эскиз NeoPixel Ring (c) 2013 Shae Erisson
// Выпущено под лицензией GPLv3, чтобы соответствовать остальным
// библиотека Adafruit NeoPixel
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> //Требуется для Adafruit Trinket 16 МГц
#endif
#define LEDPIN 11 //пин, которому подключена светодиодная лента
#define NUMPIXELS 60 //количество светящихся пикселей
int soundPin = 8; //звуковой датчик, не используется(если подключить его к плате, то будет работать)



Adafruit_NeoPixel strip(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800); //библиотека для работы светодиодной ленты


const int leftPin = 2; //левый поворотник
const int rightPin = 3; //правый поворотник
const int alarmPin = 4; //аварийный режим
const int freq = 7; //частота или скорость пробегания огней
int freqarr[3] = {20, 30, 45}; //скорость пробегания огней в секунду
int freqi = 2;
int delaytime = freqarr[freqi]; //задержка между пробегающими огнями
char val; //проверка сообщений с порта
bool work = false, no_sound = false;
const int del = 100; //по умолчанию
int high = 2500; //по умолчанию


void cancel(){  //отключиться от серийного порта
      work = false;
      int high = 2500; 
}


void setup() 
{
  pinMode(LEDPIN, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(freq, INPUT);
  

// Эти строки предназначены специально для поддержки Adafruit Trinket 5V 16 MHz.
   // Любая другая плата, вы можете удалить эту часть (но ничего страшного, если ее оставят):
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // КОНЕЦ кода Trinket.

  strip.begin();// ИНИЦИАЛИЗАЦИЯ объекта полосы NeoPixel (ОБЯЗАТЕЛЬНО)
  Serial.begin(9600);//Устанавливает скорость передачи данных в битах в секунду (бод) для последовательной передачи данных
}

void loop() 
{
  if (Serial.available() > 0) {
    val = Serial.read();

    switch(val)
    {
//дистанционное включение левого поворотника из приложения
      case '1':
  strip.clear();// Отключаем все цвета пикселей

      if (!no_sound)
    {
      tone(soundPin, high);  
      delay(del); 
      noTone(soundPin);
    }
    //work = false;

    for (int i = 29; i>=-8; i--) 
    {
      for (int j = 0; j<=8; j++) if ((i+j)<=29) strip.setPixelColor(i+j, strip.Color(28*(8-j), 20*(8-j), 0));
      strip.show();
      delay(delaytime);
      strip.clear();
      if (digitalRead(freq) == HIGH)
      {
        if (freqi<2) freqi++;
        else freqi = 0;
        delaytime = freqarr[freqi];
      }
    }
    break;
     
//дистанционное включение правого поворотника из приложения   
      case '2':
    strip.clear();    

    if (!no_sound)
    {
      tone(soundPin, high);  
      delay(del); 
      noTone(soundPin);
    }
    //work = false;
    
    for (int i = 30; i<=68; i++)  
    {
      for (int j = 0; j<=8;j++) if ((i-j)>=30) strip.setPixelColor(i-j, strip.Color(28*(8-j), 20*(8-j), 0));
      strip.show();
      delay(delaytime);
      strip.clear();
      if (digitalRead(freq) == HIGH)
      {
        if (freqi<2) freqi++;
        else freqi = 0;
        delaytime = freqarr[freqi];
      }
    }
    break;


//дистанционное включение одновременно обоих поворотников из приложения
      case '3':
     strip.clear();

     if (!no_sound)
    {
      tone(soundPin, high);  
      delay(del); 
      noTone(soundPin);
    }
    // work = false;
     
     for (int i = 0; i<=38; i++)  
      {
        for (int j = 0; j<=8; j++)
        {
          if ((29-i+j)<=29) strip.setPixelColor(29-i+j, strip.Color(28*(8-j), 20*(8-j), 0));
          if ((29+i-j)>=29) strip.setPixelColor(29+i-j, strip.Color(28*(8-j), 20*(8-j), 0));
        }
        strip.show();
        delay(delaytime);
        strip.clear();
        if (digitalRead(freq) == HIGH)
        {
          if (freqi<2) freqi++;
          else freqi = 0;
          delaytime = freqarr[freqi];
        }
      }
      break;


//установить высокую скорость бегущих огней из приложения
      case '4':
        freqi = 2;
        delaytime = freqarr[freqi];
        break;


//установить среднюю скорость бегущих огней из приложения
      case '5':
        freqi = 1;
        delaytime = freqarr[freqi];
        break;


//установить низкую скорость бегущих огней из приложения
      case '6':
        freqi = 0;
        delaytime = freqarr[freqi];
        break;


//включить или выключить звук аварийной сигнализации
      case '7':
        if (no_sound) no_sound = !no_sound;
        else no_sound = true;
        break;


//выключить звук из приложения
      case '0':   //возвращает в первоначальное положение
        cancel();
        break;


//установить частоту звукого сигнала из приложения       
      case 'a':
        high = 1000;
        break;

      case 'b':
        high = 1250;
        break;

      case 'c':
        high = 1500;
        break;

      case 'd':
        high = 1750;
        break;

      case 'e':
        high = 2000;
        break;

      case 'f':
        high = 2250;
        break;

      case 'g':
        high = 2500;
        break;

      case 'h':
        high = 2750;
        break;

      case 'i':
        high = 3000;
        break;

      case 'j':
        high = 3250;
        break;
    }
    
  }


//увеличить частоту бегущих огней с кнопки
if (digitalRead(freq) == HIGH)
{
  if (freqi<2) freqi++;
  else freqi = 0;
  delaytime = freqarr[freqi];
}  


//включить левый поворотник с кнопки
if ((digitalRead (2) == 1)and (digitalRead (3) == 0))   
{
  strip.clear();

      if (!no_sound)
    {
      tone(soundPin, high);  
      delay(del); 
      noTone(soundPin);
    }
    //work = false;
    
    for (int i = 29; i>=-8; i--) 
    {
      for (int j = 0; j<=8; j++) if ((i+j)<=29) strip.setPixelColor(i+j, strip.Color(28*(8-j), 20*(8-j), 0));
      strip.show();
      delay(delaytime);
      strip.clear();
      if (digitalRead(freq) == HIGH)
      {
        if (freqi<2) freqi++;
        else freqi = 0;
        delaytime = freqarr[freqi];
      }
    }
} 


//включить правый поворотник с кнопки
if ((digitalRead (3) == 1) and (digitalRead (2) == 0)) 
{                             
    strip.clear();    

    if (!no_sound)
    {
      tone(soundPin, high);  
      delay(del); 
      noTone(soundPin);
    }
    //work = false;
    
    for (int i = 30; i<=68; i++)  
    {
      for (int j = 0; j<=8;j++) if ((i-j)>=30) strip.setPixelColor(i-j, strip.Color(28*(8-j), 20*(8-j), 0));
      strip.show();
      delay(delaytime);
      strip.clear();
      if (digitalRead(freq) == HIGH)
      {
        if (freqi<2) freqi++;
        else freqi = 0;
        delaytime = freqarr[freqi];
      }
    }
}


//включить оба поворотника с кнопки
if ((digitalRead (3) == 1) and (digitalRead (2) == 1))       
{                              
     strip.clear();

     if (!no_sound)
    {
      tone(soundPin, high);  
      delay(del); 
      noTone(soundPin);
    }
    // work = false;
     
     for (int i = 0; i<=38; i++)  
      {
        for (int j = 0; j<=8; j++)
        {
          if ((29-i+j)<=29) strip.setPixelColor(29-i+j, strip.Color(28*(8-j), 20*(8-j), 0));
          if ((29+i-j)>=29) strip.setPixelColor(29+i-j, strip.Color(28*(8-j), 20*(8-j), 0));
        }
        strip.show();
        delay(delaytime);
        strip.clear();
        if (digitalRead(freq) == HIGH)
        {
          if (freqi<2) freqi++;
          else freqi = 0;
          delaytime = freqarr[freqi];
        }
      }
}
}
