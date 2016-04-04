int datapin = 2;
int clockpin = 3;
int latchpin = 4;
byte data = 0;

void setup()
{
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(latchpin, OUTPUT);
}

void loop()
{
  //myStuff();
  //oneAfterAnother();    // один за другим
  //oneOnAtATime();       // прокрутить строку вниз
  //pingPong();           // прокрутить строку вниз и обратно
  randomLED();          // мигание случайным светодиодом
  //marquee();            // бегущие огни
  //binaryCount();        // двоичный счет от 0 до 255
}

void myStuff()
{
  shiftWrite(0, HIGH);
  delay(1000);
  shiftWrite(0,LOW);
  delay(1000);
  shiftWrite(1, HIGH);
  delay(1000);
  shiftWrite(1,LOW);
  delay(1000);
  shiftWrite(2, HIGH);
  delay(1000);
  shiftWrite(2,LOW);
  delay(1000);
}

void shiftWrite(int desiredPin, boolean desiredState)
{
  bitWrite(data,desiredPin,desiredState);
  shiftOut(datapin, clockpin, MSBFIRST, data);
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}

void oneAfterAnother()
{
  int index;
  int delayTime = 100; 
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);
    delay(delayTime);
  }
  for(index = 7; index >= 0; index--)
  {
    shiftWrite(index, LOW);
    delay(delayTime);
  }
  delay(delayTime);
}

void oneOnAtATime()
{
  int index;
  int delayTime = 100; 
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);
    delay(delayTime);
    shiftWrite(index, LOW);
  }
}

void pingPong()
{
  int index;
  int delayTime = 100;
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH); 
    delay(delayTime); 
    shiftWrite(index, LOW);
  }
  for(index = 7; index >= 0; index--)
  {
    shiftWrite(index, HIGH);
    delay(delayTime);
    shiftWrite(index, LOW);
  }
}

void randomLED()
{
  int index;
  int delayTime = 100;

  index = random(8); 
  
  shiftWrite(index, HIGH);
  delay(delayTime);
  shiftWrite(index, LOW);
}

void marquee()
{
  int index;
  int delayTime = 2000;
  
  for(index = 0; index <= 3; index++)
  {
    shiftWrite(index, HIGH);
    shiftWrite(index+4, HIGH);
    delay(delayTime); 
    shiftWrite(index, LOW);
    shiftWrite(index+4, LOW); 
  }
}

void binaryCount()
{
  int delayTime = 1000;
  shiftOut(datapin, clockpin, MSBFIRST, data);
  
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
  
  data++;
  
  delay(delayTime);
}
