#include <Servo.h>                           // Include servo library

Servo servoRight;
Servo servoLeft;

void forwards(int delayy){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(delayy);
}

void backwards(int delayy){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  delay(delayy);
}

void spin_left(int delayy){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(delayy);
}

void spin_right(int delayy){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(delayy);
}

void circle(){
  forwards(500);
  spin_right(250);
}

void pause(int delayy){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(delayy);
}

int leftWhisker = 5;
int rightWhisker = 7;
int piezo = A5;
int sensorReading = 0;
int threshold = 10;

void moveKitty() {
  forwards(300);
  backwards(300);

  // Your Code Here

}



void stopKitty() {
  pause(500);
}

void setup() {

  pinMode (piezo, INPUT);
  Serial.begin(9600); //use the serial port
  
  pinMode(leftWhisker, INPUT);
  pinMode(rightWhisker, INPUT);
  
  Serial.println("setup completed!");
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop() {
  
  int leftWhiskerValue = digitalRead(leftWhisker);
  int rightWhiskerValue = digitalRead(rightWhisker);

  if ( leftWhiskerValue == 0 && rightWhiskerValue == 0) {
    Serial.println("Left and Right whiskers pressed!");
    backwards(1500);
    circle();
//    spin_right(250);
  }
  else if (leftWhiskerValue == 0) {
    Serial.println("Left whiser pressed!");
    pause(250);
    backwards(1500);
    spin_right(75);
  }
  else if (rightWhiskerValue == 0) {
    Serial.println("Right whisker pressed!");
    pause(250);
    backwards(1500);
    spin_left(75);
  }
  else {
    Serial.println("Nothing is pressed!");
    forwards(500);
  }


  delay(1000); // delay to avoid overloading the serial port buffer


   sensorReading = analogRead(piezo);
  Serial.println(sensorReading);

  if ( sensorReading >= threshold) {
    backwards(500);
    delay(1000);

  }

  //Your Code Here

}
