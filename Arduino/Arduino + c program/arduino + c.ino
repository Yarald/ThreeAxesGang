const int RED_PIN = 6;
const int GREEN_PIN = 5;
const int BLUE_PIN = 4;
char incomingByte;
 
void setup()
{
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);  
}
 
void loop()
{
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    switch(incomingByte)
    {
      case 'r':
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        break;
      case 'b':
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        break;
      case 'g':
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
        break;
    }
  }
}

void showSpectrum()
{
  int x;
  for (x = 0; x < 768; x++)
  {
    showRGB(x); 
    delay(10); 
  }
}
 
void showRGB(int color)
{
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
  else // color >= 512      
  {
    redIntensity = (color - 512);      
    greenIntensity = 0;                  
    blueIntensity = 255 - (color - 512); 
  }
  analogWrite(RED_PIN, redIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
  
}
