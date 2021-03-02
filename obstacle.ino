# Auto detect text files and perform LF normalization
* text=auto

#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

//our L298N control pins
const int in3 = 11;
const int in4 = 10;
int enb = 6;

//sensor pins
#define trig_pin 1 //analog input 1
#define echo_pin 0 //analog input 2
#define maximum_distance 200

boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo motor on which ultrasonic sensro is mounted
Servo servo_motor_front;//our servo on which controls the right and left motion
float servo_motor_pos = 60;
float servo_motor_front_pos = 156.5;


void setup() {
  Serial.begin(9600);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);


  servo_motor.attach(3); //our servo pin
  servo_motor_front.attach(4);//fromt wheel servo motor pin
  servo_motor_front.write(servo_motor_pos);
  servo_motor.write(servo_motor_pos);//recheck the angle

  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  analogWrite(enb, 200);
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  Serial.println(distance);
  if (distance <= 20) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft) {
      turnRight();
      moveStop();
    }
    else {
      turnLeft();
      moveStop();
    }
  }
  else {
    moveForward();
  }
  distance = readPing();
}

int lookRight() {
  servo_motor.write(180);
  servo_motor_front.write(servo_motor_pos);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(servo_motor_pos);
  return distance;
}

int lookLeft() {
  servo_motor.write(80);
  servo_motor_front.write(servo_motor_pos);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(servo_motor_pos);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  servo_motor.write(servo_motor_pos);
  servo_motor_front.write(servo_motor_front_pos);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void moveForward() {
  servo_motor.write(servo_motor_pos);
  if (!goesForward) {
    goesForward = true;
    servo_motor_front.write(servo_motor_front_pos);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

void moveBackward() {
  servo_motor.write(servo_motor_pos);
  goesForward = false;
  servo_motor_front.write(servo_motor_front_pos);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  servo_motor.write(servo_motor_pos);
  servo_motor_front.write(180);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000);
  servo_motor_front.write(servo_motor_front_pos);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000);

}

void turnLeft() {
  servo_motor.write(servo_motor_pos);
  servo_motor_front.write(90);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000);
  servo_motor_front.write(servo_motor_front_pos);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000);

}
