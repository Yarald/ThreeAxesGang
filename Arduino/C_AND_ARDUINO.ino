struct LAMP
{
  int state;
  int pinR;
  int pinG;
  int pinB;
  int brightnessR;
  int brightnessG;
  int brightnessB;
};

LAMP LAMP1 = {0,9,10,11,5,5,5};
char incomingByte;

void setup()
{
  Serial.begin(9600);
  pinMode(LAMP1.pinB, OUTPUT);
  pinMode(LAMP1.pinG, OUTPUT);
  pinMode(LAMP1.pinR, OUTPUT);
}
 
void loop()
{
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    switch(incomingByte)
    {
      case '1':
        turnOnOffLamp();
        break;
      case '+':
        addBrightness();
        break;
      case '-':
        removeBrightness();
        break;
      case 'q':
      case 'w':
      case 'e':
        changeColor(incomingByte);
        break;
    }
    updateLamp();
  }
}
void turnOnOffLamp(){
   LAMP1.state = (LAMP1.state == 1) ? 0 : 1;
}

void addBrightness(){
  if(LAMP1.brightnessR > 205 || LAMP1.brightnessG > 205 || LAMP1.brightnessB > 205)
    return;
  LAMP1.brightnessR += 50;
  LAMP1.brightnessG += 50;
  LAMP1.brightnessB += 50;
}

void changeColor(char ch

void removeBrightness() {
  if(LAMP1.brightnessR < 55 || LAMP1.brightnessG < 55 || LAMP1.brightnessB < 55)
    return;
  LAMP1.brightnessR -= 50;
  LAMP1.brightnessG -= 50;
  LAMP1.brightnessB -= 50;
}

void updateLamp() {
  if(LAMP1.state == 1) {
    analogWrite(LAMP1.pinB, LAMP1.brightness);
    analogWrite(LAMP1.pinG, LAMP1.brightness);
    analogWrite(LAMP1.pinR, LAMP1.brightness);
  }
  else {
    analogWrite(LAMP1.pinB, LOW);
    analogWrite(LAMP1.pinG, LOW);
    analogWrite(LAMP1.pinR, LOW);
  }
}

