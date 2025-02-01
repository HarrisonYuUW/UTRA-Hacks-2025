//Motor Pins
int IN1 = 9; //control pin for first motor
int IN2 = 8; //control pin for first motor
int IN3 = 7; //control pin for second motor
int IN4 = 6; //control pin for second motor

void setup ( ) {
//Serial.begin (9600); //Starting the serial communication at 9600 baud rate
//Initializing the motor pins as output
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
}

void loop ( ) {

digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);

}