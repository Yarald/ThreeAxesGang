const int BLUE_PIN = 4;
const int GREEN_PIN = 5;
const int RED_PIN = 6;

void setup() {
  Serial.begin(9600);
  for(int i = 4; i <= 6; i++)
    pinMode(i, OUTPUT);

}

void loop() {
  if(Serial.available() > 0) 
  {
    int x = Serial.read() - '0';
    digitalWrite(x, HIGH);
    delay(1000);
    digitalWrite(x, LOW);
    delay(1000);   
    Serial.flush(); //we need only 1 character 
  }
  
}
