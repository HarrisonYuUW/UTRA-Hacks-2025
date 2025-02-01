#include <Servo.h>

Servo myservo;

//Motor Pins
#define IN1 1 //control pin for first motor
#define IN2 2 //control pin for first motor
#define IN3 3 //control pin for second motor
#define IN4 4 //control pin for second motor

// Define color sensor pins
#define S0 5
#define S1 6
#define S2 7
#define S3 8
#define sensorOut 9

// Calibration Values
// *Get these from Calibration Sketch
int redMin = 400; // Red minimum value
int redMax = 2600; // Red maximum value
int greenMin = 400; // Green minimum value
int greenMax = 2725; // Green maximum value
int blueMin = 425; // Blue minimum value
int blueMax = 2600; // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

int pos = 0;    // variable to store the servo position

int count = 0; // For timer

int colour = 0;

int movement = 0; // Determines which way to move

int current = 0;

int previous = 0;

int old = 0;

void setup() {
  Serial.begin (9600);

  // Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);

	// Set Frequency scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

  //Serial.begin (9600); //Starting the serial communication at 9600 baud rate
  //Initializing the motor pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myservo.attach(10);  // attaches the servo on pin 9 to the servo object


}

void loop() {
  // Read Red value
	redPW = getRedPW();
	// Map to value from 0-255
	redValue = map(redPW, redMin,redMax,255,0);
	// Delay to stabilize sensor
	delay(200);

	// Read Green value
	greenPW = getGreenPW();
	// Map to value from 0-255
	greenValue = map(greenPW, greenMin,greenMax,255,0);
	// Delay to stabilize sensor
	delay(200);

	// Read Blue value
	bluePW = getBluePW();
	// Map to value from 0-255
	blueValue = map(bluePW, blueMin,blueMax,255,0);
	// Delay to stabilize sensor
	delay(200);

  if (colour == 0) {
    if ((redValue >= 150) || (blueValue >= 150) || (greenValue >= 150)){
      colour = 1;
    }
  } else if (movement == 0){
    movement = 1;

  } else {
    if ((redValue <= 150) && (blueValue <= 150) && (greenValue <= 150)){
      movement = 2;
    }
  }

  if (movement == 0){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (movement == 1){
    count += 1;
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);  
  } else if (movement == 2){
    if (count != 0){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      count -= 1;
    } else {
      movement = 3;
    }
  } else if (movement == 3){
    if (count != 2000) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      count += 1;
    } else {
      movement = 4;
      count = 0;
    }
  } else if (movement == 4){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    if ((redValue >= blueValue) && (redValue >= greenValue)){
      old = previous
      previous = current
      current = 0
    } else if ((greenValue >= redValue) && (greenValue >= blueValue)){
      old = previous
      previous = current
      current = 1
    } else {
      old = previous
      previous = current
      current = 2
    }

    if ((redValue <= 150) && (blueValue <= 150) && (greenValue <= 150)){
      movement = 5;
    }

    if (current == old){
      movement = 6;
    }
  } else if (movement == 5){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    if ((redValue >= blueValue) && (redValue >= greenValue)){
      old = previous
      previous = current
      current = 0
    } else if ((greenValue >= redValue) && (greenValue >= blueValue)){
      old = previous
      previous = current
      current = 1
    } else {
      old = previous
      previous = current
      current = 2
    }

    if (current == old){
      movement = 7;
  } else if (movement == 6){
    if (count != 200){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      count += 1;
    } else {
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      //delay(20);                       // waits 15ms for the servo to reach the position
      }
    }
  } else {
    if (count != 200){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      count += 1;
    } else {
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      //delay(20);                       // waits 15ms for the servo to reach the position
      }
    }
  }

}


// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}