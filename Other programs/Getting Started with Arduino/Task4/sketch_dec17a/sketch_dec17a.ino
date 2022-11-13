int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup()
{
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);
}

void loop()
{
  setColor(255, 0, 255); // фазан
delay(3000);
setColor(0, 0, 255); // сидит
delay(3000);
setColor(0, 255, 255); // где
delay(3000);
setColor(0, 255, 0); // знать
delay(3000);
setColor(255, 255, 0); // желает
delay(3000);
setColor(255, 128, 0); // охотник
delay(3000);
setColor(255, 0, 0); // каждый
delay(3000);
setColor(0, 0, 0);
delay(5000);
}

void setColor(int red, int green, int blue)
{
analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
}
