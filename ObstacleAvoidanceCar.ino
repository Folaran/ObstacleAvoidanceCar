
#include <AFMotor.h> //import your motor shield library
#define trigPin 12 // define the pins of your sensor
#define echoPin 13 
AF_DCMotor motor1(1,MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor2(2, MOTOR12_8KHZ);
 
void setup() {
  Serial.begin(9600); // Serial communication  
  Serial.println("Motor test!");
  pinMode(trigPin, OUTPUT);// set the trigPin to output (Send sound waves)
  pinMode(echoPin, INPUT);// set the echoPin to input (recieve sound waves)
  motor1.setSpeed(105); //set the speed of the motors, ideally between 0-255
  motor2.setSpeed (105);  
}
 
void loop() {

  long duration, distance; // scanning the distance between the sensor(car) and a potential obstacle
  digitalWrite(trigPin, LOW); //assigning low to trigPin sensor
  delayMicroseconds(2); // delay for succesful sensor operation.
  digitalWrite(trigPin, HIGH); //assigning high to trigPin sensor

  delayMicroseconds(10); //delay
  digitalWrite(trigPin, LOW); //assigning lowt to trigPin
  duration = pulseIn(echoPin, HIGH); // assigning high to echoPin
  distance = (duration/2) / 29.1;// convert the distance to centimeters.
  if (distance < 25)/*if there's an obstacle 25 centimers, ahead, do the following: */ {   
    Serial.println ("Close Obstacle detected!" );
    Serial.println ("Obstacle Details:");
    Serial.print ("Car is :" );
    Serial.print ( distance);
    Serial.print ( " CM away from obstacle");// prints out the distance between the sensors and obstacle.
    Serial.println (" Obstacle is close enough to cause collision.");
    Serial.println (" Turning !");
    motor1.run(FORWARD);  // Turn wheels left or right as long as there's an obstacle ahead.
    motor2.run (BACKWARD); // stop back wheels and reverse while there's an obstacle ahead

}
  else {
   Serial.println ("No obstacle detected. going forward");
   delay (15);
   motor1.run(FORWARD); // front wheels dont turn if there's no obstacle ahead, Go Forward! 
   motor2.run(FORWARD); // back wheels move forward as long as there's no obstacle ahead
  }   
}
