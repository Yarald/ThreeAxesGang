#define step 10
#define max 235
#define min 25
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
      case 'a':
      case 'w':
      case 's':
      case 'e':
      case 'd':
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
  if(LAMP1.brightnessR > max || LAMP1.brightnessG > max || LAMP1.brightnessB > max)
    return;
  LAMP1.brightnessR += step;
  LAMP1.brightnessG += step;
  LAMP1.brightnessB += step;
}

//q - red
//w - green
//e - blue
void changeColor(char incomingByte)
{
  if(incomingByte == 'q' || incomingByte == 'a')
  {
    if(incomingByte == 'q') {
      if(LAMP1.brightnessR < min) {
        return;
      }
      LAMP1.brightnessR -= step;
    }
    else if (incomingByte == 'a') {
      if(LAMP1.brightnessR > max) {
        return;
      }
      LAMP1.brightnessR += step;
    }
  }
  if(incomingByte == 'w' || incomingByte == 's')
  {
    if(incomingByte == 'w') {
      if(LAMP1.brightnessG < min) {
        return;
      }
      LAMP1.brightnessG -= step;
    }
    else if (incomingByte == 's') {
      if(LAMP1.brightnessG > max) {
        return;
      }
      LAMP1.brightnessG += step;
    }
  }
  if(incomingByte == 'e' || incomingByte == 'd')
  {
    if(incomingByte == 'e') {
      if(LAMP1.brightnessB < min) {
        return;
      }
      LAMP1.brightnessB -= step;
    }
    else if (incomingByte == 'd') {
      if(LAMP1.brightnessB > max) {
        return;
      }
      LAMP1.brightnessB += step;
    }
  }
}

void removeBrightness() {
  if(LAMP1.brightnessR < min || LAMP1.brightnessG < min || LAMP1.brightnessB < min)
    return;
  LAMP1.brightnessR -= step;
  LAMP1.brightnessG -= step;
  LAMP1.brightnessB -= step;
}

void updateLamp() {
  if(LAMP1.state == 1) {
    analogWrite(LAMP1.pinB, LAMP1.brightnessB);
    analogWrite(LAMP1.pinG, LAMP1.brightnessG);
    analogWrite(LAMP1.pinR, LAMP1.brightnessR);
  }
  else {
    analogWrite(LAMP1.pinB, LOW);
    analogWrite(LAMP1.pinG, LOW);
    analogWrite(LAMP1.pinR, LOW);
  }
}

