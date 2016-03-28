void setup()

{

//pinMode(9, OUTPUT);

}

void loop(){
  analogWrite(9,350);
  delay(1000);
  analogWrite(9,50);
  delay(1000);
  analogWrite(9,10);
  delay(1000);
  analogWrite(9,0);
  delay(1000);
}

