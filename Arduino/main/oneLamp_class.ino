#define BRGHT_STEP 50
#define BRGHT_MAX 255
#define BRGHT_MIN 5

class Lamp
{
  public:
    Lamp(int pinR_in, int pinG_in, int pinB_in)
    {
      pinR = pinR_in;
      pinG = pinG_in;
      pinB = pinB_in;
    }
    void lampConfigure_OUTPUT()
    {
      pinMode(pinR, OUTPUT);
      pinMode(pinG, OUTPUT);
      pinMode(pinR, OUTPUT);
    }
    int pinR;
    int pinG;
    int pinB;
    int state = 0;
    int brightness_R = 5;
    int brightness_G = 5;
    int brightness_B = 5;
};

Lamp *lamp1;
int color;

void setup()
{
  color = 0;
  lamp1 = new Lamp(11, 10, 9);
  lamp1->lampConfigure_OUTPUT();
  Serial.begin(9600);
}

void loop()
{
  char incomingByte;
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    switch (incomingByte)
    {
      case '1':
        switchLamp(lamp1);
        break;
      case 'q':
        addRed(lamp1);
        break;
      case 'w':
        addGreen(lamp1);
        break;
      case 'e':
        addBlue(lamp1);
        break;
      case 'a':
        removeRed(lamp1);
        break;
      case 's':
        removeGreen(lamp1);
        break;
      case 'd':
        removeBlue(lamp1);
        break;
      case 'r':
        changeColor(color, lamp1);
        break;
    }
  }
  updateLamp(lamp1);
}

void switchLamp(Lamp *lamp) {
  lamp->state = (lamp->state == 1) ? 0 : 1;
}

void addRed(Lamp *lamp) {
  lamp->brightness_G = LOW;
  lamp->brightness_B = LOW;
  if (lamp->brightness_R >= BRGHT_MAX)
    return;
  lamp->brightness_R += BRGHT_STEP;
}

void addGreen(Lamp *lamp) {
  if (lamp->brightness_G >= BRGHT_MAX)
    return;
  lamp->brightness_G += BRGHT_STEP;
}

void addBlue(Lamp *lamp) {
  if (lamp->brightness_B >= BRGHT_MAX)
    return;
  lamp->brightness_B += BRGHT_STEP;
}

void removeRed(Lamp *lamp) {
  if (lamp->brightness_R <= BRGHT_MIN)
    return;
  lamp->brightness_R -= BRGHT_STEP;
}

void removeGreen(Lamp *lamp) {
  if (lamp->brightness_G <= BRGHT_MIN)
    return;
  lamp->brightness_G -= BRGHT_STEP;
}

void removeBlue(Lamp *lamp) {
  if (lamp->brightness_B <= BRGHT_MIN)
    return;
  lamp->brightness_B -= BRGHT_STEP;
}

void updateLamp(Lamp *lamp) {
  if (lamp->state == 1) {
    analogWrite(lamp->pinB, lamp->brightness_B);
    analogWrite(lamp->pinG, lamp->brightness_G);
    analogWrite(lamp->pinR, lamp->brightness_R);
  }
  else {
    analogWrite(lamp->pinB, 0);
    analogWrite(lamp->pinG, 0);
    analogWrite(lamp->pinR, 0);
  }
}

void changeColor(int color, Lamp *lamp)
{
  if (color == 760) {
    color = 0;
  }
  color += 10;
  delay(10);
  int redIntensity;
  int greenIntensity;
  int blueIntensity;
  if (color <= 255)
  {
    redIntensity = 255 - color;
    greenIntensity = color;
    blueIntensity = 0;
  }
  else if (color <= 511)
  {
    redIntensity = 0;
    greenIntensity = 255 - (color - 256);
    blueIntensity = (color - 256);
  }
  else
  {
    redIntensity = (color - 512);
    greenIntensity = 0;
    blueIntensity = 255 - (color - 512);
  }
  lamp->brightness_R = redIntensity;
  lamp->brightness_G = greenIntensity;
  lamp->brightness_B = blueIntensity;
}

