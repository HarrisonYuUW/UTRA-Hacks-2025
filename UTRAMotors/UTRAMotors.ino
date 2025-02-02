#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

//Motor Pins
int IN1 = 2; //control pin for first motor
int IN2 = 3; //control pin for first motor
int IN3 = 4; //control pin for second motor
int IN4 = 5; //control pin for second motor

void setup ( ) {
//Serial.begin (9600); //Starting the serial communication at 9600 baud rate
//Initializing the motor pins as output
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

int count = 0;

void loop ( ) {
if (count < 250){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
} else if (count < 300){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
} else if (count < 400){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
} else {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(20);                       // waits 15ms for the servo to reach the position
  }
}


}