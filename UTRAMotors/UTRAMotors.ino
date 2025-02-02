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
}

void loop ( ) {

digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);

}