// Blue-4 Green-5 Red-6
#define LAMPS_MAX_COUNT 1
typedef struct Lamp_S {
  int pinR;
  int pinG;
  int pinB;
  int brightness;  
  int state;
} Lamp_T;
typedef struct LampList_S {
  Lamp_T list[LAMPS_MAX_COUNT];
};

char incomingByte;
Lamp_T myLamp;
myLamp.pinB = 4;
myLamp.pinG = 5;
myLamp.pinR = 6;
myLamp.brightness = 5;
myLamp.state = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(myLamp.pinB, OUTPUT);
  pinMode(myLamp.pinG, OUTPUT);
  pinMode(myLamp.pinR, OUTPUT);
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
        turnOnLamp();
        break;
      case '+':
        addBrightness();
        break;
      case '-':
        removeBrightness();
        break;
    }
    updateLamp();
  }
}
void turnOnLamp(){
   myLamp.state = (myLamp.state == 1) ? 0 : 1;
}

void addBrightness(){
  if(myLamp.brightness == 255)
    return;
  myLamp.brightness += 50;
}

void removeBrightness() {
  if(myLamp.brightness == 5)
    return;
  myLamp.brightness -= 50;
}

void updateLamp() {
  if(myLamp.state == 1) {
    analogWrite(myLamp.pinB, myLamp.brightness);
    analogWrite(myLamp.pinG, myLamp.brightness);
    analogWrite(myLamp.pinR, myLamp.brightness);
  }
}

