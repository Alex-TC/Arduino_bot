#include <Servo.h>                           // Include servo library

Servo servoRight;
Servo servoLeft;

byte wLeftOld;                               // Previous loop whisker values
byte wRightOld;                              
byte counter;                                // For counting alternate corners

void forwards(int time){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(time);
}

void backwards(int time){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  delay(time);
}

void turn_left(int time){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(time);
}

void turn_right(int time){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(time);
}

void circle(){
  forwards(250);
  turn_right(75);
}

void pause(int time){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(time);
}

int leftWhisker = 5;
int rightWhisker = 7;
int piezo = A5;
int sensorReading = 0;
int threshold = 10;
int irLedPin = 2;
int irReceiverPin= 9;
//int irDetect(int irLedPin, int irReceiverPin, long frequency);

  
void moveKitty() {
  forwards(300);
  backwards(300);

  // Your Code Here

}



void stopKitty() {
  pause(500);
}

void setup() {
 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  pinMode(irLedPin, OUTPUT);  pinMode(irReceiverPin, INPUT);   // Left IR LED & Receiver

  Serial.begin(9600);

  pinMode (piezo, INPUT);
  Serial.begin(9600); //use the serial port
  
  pinMode(leftWhisker, INPUT);
  pinMode(rightWhisker, INPUT);
  
  Serial.println("setup completed!");
  servoLeft.attach(13);
  servoRight.attach(12);
  wLeftOld = 0;                              // Init. previous whisker states
  wRightOld = 1;  
  counter = 0;                               // Initialize counter to 0
}

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}  

void loop() {

  int irLeft = irDetect(irLedPin, irReceiverPin, 38000);       // Check for object
  Serial.println(irLeft);                    // Display 1/0 no detect/detect
  delay(1000);                                // 0.1 second delay
  
  int leftWhiskerValue = digitalRead(leftWhisker);
  int rightWhiskerValue = digitalRead(rightWhisker);
  // Corner Escape

  if(leftWhiskerValue != rightWhiskerValue)                        // One whisker pressed?
  {                                          // Alternate from last time?
    if ((leftWhiskerValue != wLeftOld) && (rightWhiskerValue != wRightOld))  
    {                                       
      counter++;                             // Increase count by one
      wLeftOld = leftWhiskerValue;                      // Record current for next rep
      wRightOld = rightWhiskerValue;
      if(counter == 2)                       // Stuck in a corner?
      {
        leftWhiskerValue = 0;                           // Set up for U-turn
        rightWhiskerValue = 0;
        counter = 0;                         // Clear alternate corner count
      }
    }  
    else                                     // Not alternate from last time
    {
      counter = 0;                           // Clear alternate corner count
    }
  }  
 
  
  if ( leftWhiskerValue == 0 && rightWhiskerValue == 0) {
    Serial.println("Left and Right whiskers pressed!");
    backwards(1000);
    turn_left(800);
  }
  else if (leftWhiskerValue == 0) {
    Serial.println("Left whisker pressed!");
    backwards(1000);
    turn_right(400);
  }
  else if (rightWhiskerValue == 0) {
    Serial.println("Right whisker pressed!");
    backwards(1000);
    turn_left(400);
  }
  else {
    Serial.println("Nothing pressed!");
    forwards(20);
  }
//  delay(1000); // delay to avoid overloading the serial port buffer
//
//
//   sensorReading = analogRead(piezo);
//  Serial.println(sensorReading);
//
//  if ( sensorReading >= threshold) {
//    backwards(500);
//    delay(1000);}


  //Your Code Here

}
