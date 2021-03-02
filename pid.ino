# Auto detect text files and perform LF normalization
* text=auto
#include <MPU6050_tockn.h>
#include <Wire.h>// MPU6050  and Wire  libraries
#include <PID_v1.h>//PID Library

MPU6050 mpu6050(Wire);

double Setpoint;
double Input, Output, Input1;
double Kp = 4.0, Ki = 0.0, Kd = 2.0; //assigning random values

//motor controllling pins
int ena = 5;
int in1 = 8;
int in2 = 9;

PID myPID(&Input1, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  //turn the MPU6050 sensor on
  mpu6050.begin();

  //Calculating offset values
  mpu6050.calcGyroOffsets(true);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  Setpoint = 0.56;
  myPID.SetControllerDirection(REVERSE);
  //motor module control
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  mpu6050.update();
  Input = mpu6050.getAngleY();
  if (Input < Setpoint) {
    Input1 = abs(Input);
  }
  else {
    Input1 = Input;
  }
//  Input1=abs(Input);
    if (abs(Input - Setpoint) <= 3) {
      Ki = 1.0;
      myPID.SetTunings(Kp , Ki, Kd );
    }
    else {
      Ki = 0.0;
      myPID.SetTunings(Kp , Ki, Kd );
    }

  myPID.Compute();
  Serial.println(Output);//check the outputvalues of the PID Code
  //scale the output before writing it
  if (abs(Input - Setpoint) <= 3) {
    if  (Output>10){
      Output=10;
    }
  }

  analogWrite(ena, Output+50); //writing the output of the PID Code to  the motor module
  
  if (Input >= Setpoint) {
    digitalWrite(in1,  HIGH);
    digitalWrite(in2, LOW);
    delay(10);
  }
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(10);
  }
  analogWrite(ena, 0);
}
