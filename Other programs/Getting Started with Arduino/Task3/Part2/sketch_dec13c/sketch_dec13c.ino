const int LED=9;
const int BUTTON=2;
int i;

void setup() {
  // put your setup code here, to run once:
  int i=0;
pinMode (LED, OUTPUT);
pinMode (BUTTON, INPUT);
}

void loop() {  
if (digitalRead(BUTTON)== LOW)
{
  digitalWrite(LED, LOW);
}
else
{
  for(;i<8;i++)
  {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
  }
}
}
