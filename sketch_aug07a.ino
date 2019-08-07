int leftWhisker = 5;
int rightWhisker = 7;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //use the serial port
  
  pinMode(leftWhisker, INPUT);
  pinMode(rightWhisker, INPUT);
  
  Serial.println("setup completed!");
  
}

void loop() {
  int leftWhiskerValue = digitalRead(leftWhisker);
  int rightWhiskerValue = digitalRead(leftWhisker);

  Serial.print("Left :");
  Serial.println(leftWhiskerValue);
  Serial.print("Right :");
  Serial.println(leftWhiskerValue);

  
  // put your main code here, to run repeatedly:
  Serial.print("We are ");
  Serial.println("looping now!");

  delay(100); // delay to avoid overloading the serial port buffer
}
