// Простой эскиз NeoPixel Ring (c) 2013 Shae Erisson
// Выпущено под лицензией GPLv3, чтобы соответствовать остальным
// библиотека Adafruit NeoPixel
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define LEDPIN        13 //пин, которому подключена светодиодная лента

#define NUMPIXELS 120 //количество светящихся пикселей


Adafruit_NeoPixel pixels(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);//библиотека для работы светодиодной ленты


const int leftPin = 2;//левый поворотник
const int rightPin = 3;//правый поворотник
const int alarmPin = 4;//аварийный режим
const int freq = 7;//частота или скорость пробегания огней

bool LeftIsUp;
bool LeftWasUp = false;
bool winkerLeft = false;

bool RightIsUp;
bool RightWasUp = false;
bool winkerRight = false;


bool AlarmIsUp;
bool AlarmWasUp = false;
bool alarm = false;

int freqarr[3] = {15, 30, 45};
int freqi = 1;
int delaytime = freqarr[freqi];


void setup() 
{


  pinMode(LEDPIN, OUTPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(alarmPin, INPUT);
  pinMode(freq, INPUT);
  

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  
  pixels.begin();

  Serial.begin(9600);
}

void loop() 
{


//считать состояние кнопки, отвечающей за включение или выключение левого поворотника
  LeftIsUp = digitalRead(leftPin);
  if (LeftWasUp && !LeftIsUp) 
  {     
    LeftIsUp = digitalRead(leftPin);
    if (!LeftIsUp)
    {
      winkerLeft = !winkerLeft;
    }
  }


//считать состояние кнопки, отвечающей за включение или выключение правого поворотника
  RightIsUp = digitalRead(rightPin);
  if (RightWasUp && !RightIsUp) 
  {     
    RightIsUp = digitalRead(rightPin);
    if (!RightIsUp)
    {
      winkerRight = !winkerRight;
    }
  }


//считать состояние кнопки, отвечающей за включение или выключение обоих поворотников
  AlarmIsUp = digitalRead(alarmPin);
  if (AlarmWasUp && !AlarmIsUp) 
  {     
    AlarmIsUp = digitalRead(alarmPin);
    if (!AlarmIsUp)
    {
      alarm = !alarm;
    }
  }


//считать состояние кнопки, отвечающей переключение скорости бегущих огней (поворотников)
  if (digitalRead(freq) == HIGH)
  {
    if (freqi<2) freqi++;
    else freqi = 0;
    delaytime = freqarr[freqi];
  }


//включить левый поворотник, если нажата кнопка для него
  if (winkerLeft)
  {
    pixels.clear();
    for (int i = 59; i>=-8; i--) 
    {
      for (int j = 0; j<=8; j++) if ((i+j)<=59) pixels.setPixelColor(i+j, pixels.Color(28*(8-j), 20*(8-j), 0));
      pixels.show();
      delay(delaytime);
      pixels.clear();
      if (digitalRead(leftPin)) winkerLeft = false; 
      if (digitalRead(rightPin)) 
      {
        winkerLeft = false; 
        winkerRight = true;
      }
      if (digitalRead(alarmPin))
      {
        winkerLeft = false; 
        alarm = true;
      }

      if (digitalRead(freq) == HIGH)
      {
        if (freqi<2) freqi++;
        else freqi = 0;
        delaytime = freqarr[freqi];
      }
    }
  }


//включить правый поворотник, если нажата кнопка для него
  if (winkerRight)
  {
    pixels.clear();
    for (int i = 60; i<=68; i++)  
    {
      for (int j = 0; j<=8;j++) if ((i-j)>=60) pixels.setPixelColor(i-j, pixels.Color(28*(8-j), 20*(8-j), 0));
      pixels.show();
      delay(delaytime);
      pixels.clear();
      if (digitalRead(rightPin)) winkerRight = false; 
      if (digitalRead(leftPin)) 
      {
        winkerRight = false; 
        winkerLeft = true;
      }
      if (digitalRead(alarmPin))
      {
        winkerRight = false;
        alarm = true;
      }
      if (digitalRead(freq) == HIGH)
      {
        if (freqi<2) freqi++;
        else freqi = 0;
        delaytime = freqarr[freqi];
      }
    }
  }


//включить оба поворотника, если нажата кнопка аварийного режима
  if (alarm)
  {
     pixels.clear();
     for (int i = 0; i<=38; i++)  
      {
        for (int j = 0; j<=8; j++)
        {
          if ((59-i+j)<=59) pixels.setPixelColor(59-i+j, pixels.Color(28*(8-j), 20*(8-j), 0));
          if ((59+i-j)>=59) pixels.setPixelColor(59+i-j, pixels.Color(28*(8-j), 20*(8-j), 0));
        }
        pixels.show();
        delay(delaytime);
        pixels.clear();
        if (digitalRead(alarmPin)) alarm = false;
        if (digitalRead(leftPin)) 
        {
          alarm = false; 
          winkerLeft = true;
        }
          if (digitalRead(leftPin))
        {
          alarm = false; 
          winkerRight = true;
        }

        if (digitalRead(freq) == HIGH)
        {
          if (freqi<2) freqi++;
          else freqi = 0;
          delaytime = freqarr[freqi];
        }
      
      }
      
  }


//отправить в порт полученные выше данные для работы поворотников
  Serial.print(winkerLeft);
  Serial.print(winkerRight);
  Serial.print(alarm);
  Serial.println(freqi);
  
  LeftWasUp = LeftIsUp;
  RightWasUp = RightIsUp;
  AlarmWasUp = AlarmIsUp;
}
