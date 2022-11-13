int pirPin = 2;
int minSecsBetweenEmails = 60; // 1 min
long lastSend = -minSecsBetweenEmails * 1000;

void setup()
{
pinMode(pirPin, INPUT);
Serial.begin(9600);
}

void loop()
{
long now = millis();


//считать состояние датчика
if (digitalRead(pirPin) == HIGH)
{

//если датчик уловил движение, вывести в монитор порта слово Movement, если нет, то фразу Too soon.
if (now > (lastSend + minSecsBetweenEmails * 1000))
{
Serial.println("MOVEMENT"); lastSend = now;
}
else
{
Serial.println("Too soon"); }
}
delay(1000);
}
