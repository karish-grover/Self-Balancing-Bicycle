# Auto detect text files and perform LF normalization
* text=auto
//bluetooth connection code
String str;// raw string received from android to arduino
int blueToothVal;// stores the last value sent over via bluetooth

#include <Servo.h>
Servo myservo;
float pos = 156.5;

int ena = 5;
int enb = 6;

int in1 = 8;
int in2 = 9;
int in3 = 11;
int in4 = 10;

void setup()
{

  Serial.begin(9600);// Serial 1 is for Bluetooth communication - DO NOT MODIFY

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  myservo.attach(3);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  analogWrite(ena, 150);
  analogWrite(enb, 150);
  delay(1000);
}

void loop()
{
  bluetooth(); // Run the Bluetooth procedure to see if there is any data being sent via BT
}

void bluetooth()
{
  while (Serial.available())                           // Read bluetooth commands over Serial1 // Warning: If an error with Serial1 occurs, make sure Arduino Mega 2560 is Selected
  {
    {
      str = Serial.readStringUntil('\n');               // str is the temporary variable for storing the last sring sent over bluetooth from Android devic
    }

    blueToothVal = (str.toInt());                        //  convert the string 'str' into an integer and assign it to blueToothVal

    switch (blueToothVal)
    {
      case 1:
        Serial.println("Forward");
        Forward();
        break;

      case 2:
        Serial.println("Reverse");
        Reverse();
        break;

      case 3:
        Serial.println("Left");
        LeftTurn();
        Stop();
        break;

      case 4:
        Serial.println("Right");
        RightTurn();
        Stop();
        break;

      case 5:
        Serial.println("Stop");
        Stop();
        break;

    }                                                              // end of switch case

  }                                                              // end of while loop Serial1 read

  // if no data from Bluetooth
  if (Serial.available() < 0)
  {
    Serial.println("No Bluetooth Data ");
  }

}

void Forward()
{
  myservo.write(pos);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(15);
}

void Reverse()
{
  myservo.write(pos);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(15);
}

void LeftTurn()
{
  for (pos; pos >= 100; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }

}

void RightTurn(){
  for (pos; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
}

void Stop()
{

  myservo.write(156.5);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(100);
  

}
