#include <AFMotor.h>

//**********5 Channel IR Sensor Connection**********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4
//*************************************************//

//defining motors
#define speed 80
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

void setup() {
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
}

void loop() {
  //Reading Sensor Values
  int s1 = digitalRead(ir1);  //Left Most Sensor
  int s2 = digitalRead(ir2);  //Left Sensor
  int s3 = digitalRead(ir3);  //Middle Sensor
  int s4 = digitalRead(ir4);  //Right Sensor
  int s5 = digitalRead(ir5);  //Right Most Sensor

  //if only middle sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going forward 
    motor1.run(FORWARD);
    motor1.setSpeed(speed);
    motor2.run(FORWARD);
    motor2.setSpeed(speed);
    motor3.run(FORWARD);
    motor3.setSpeed(speed);
    motor4.run(FORWARD);
    motor4.setSpeed(speed);
  }
  
  //if only left sensor detects black line
  else if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //going left 
    motor1.run(BACKWARD);
    motor1.setSpeed(speed);
    motor2.run(BACKWARD);
    motor2.setSpeed(speed);
    motor3.run(FORWARD);
    motor3.setSpeed(speed);
    motor4.run(FORWARD);
    motor4.setSpeed(speed);
    delay(50);
  }
  
  //if only left most sensor detects black line
  else if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //going left
    motor1.run(BACKWARD);
    motor1.setSpeed(speed);
    motor2.run(BACKWARD);
    motor2.setSpeed(speed);
    motor3.run(FORWARD);
    motor3.setSpeed(speed);
    motor4.run(FORWARD);
    motor4.setSpeed(speed);
    delay(200);
  }

  //if only right sensor detects black line
  else if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
  {
    //going right 
    motor1.run(FORWARD);
    motor1.setSpeed(speed);
    motor2.run(FORWARD);
    motor2.setSpeed(speed);
    motor3.run(BACKWARD);
    motor3.setSpeed(speed);
    motor4.run(BACKWARD);
    motor4.setSpeed(speed);
    delay(50);
  }

  //if only right most sensor detects black line
  else if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    //going right 
    motor1.run(FORWARD);
    motor1.setSpeed(speed);
    motor2.run(FORWARD);
    motor2.setSpeed(speed);
    motor3.run(BACKWARD);
    motor3.setSpeed(speed);
    motor4.run(BACKWARD);
    motor4.setSpeed(speed);
    delay(200);
  }

  //if middle and right sensor detects black line
  else if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    //going right 
    motor1.run(FORWARD);
    motor1.setSpeed(speed);
    motor2.run(FORWARD);
    motor2.setSpeed(speed);
    motor3.run(BACKWARD);
    motor3.setSpeed(speed);
    motor4.run(BACKWARD);
    motor4.setSpeed(speed);
    delay(10);
  }

  //if middle and left sensor detects black line
  else if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going left
    motor1.run(BACKWARD);
    motor1.setSpeed(speed);
    motor2.run(BACKWARD);
    motor2.setSpeed(speed);
    motor3.run(FORWARD);
    motor3.setSpeed(speed);
    motor4.run(FORWARD);
    motor4.setSpeed(speed);
    delay(10);
  }

  //if middle, left and left most sensor detects black line
  else if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going left
    motor1.run(BACKWARD);
    motor1.setSpeed(speed);
    motor2.run(BACKWARD);
    motor2.setSpeed(speed);
    motor3.run(FORWARD);
    motor3.setSpeed(speed);
    motor4.run(FORWARD);
    motor4.setSpeed(speed);
    delay(100);
  }

  //if middle, right and right most sensor detects black line
  else if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
     //going right 
    motor1.run(FORWARD);
    motor1.setSpeed(speed);
    motor2.run(FORWARD);
    motor2.setSpeed(speed);
    motor3.run(BACKWARD);
    motor3.setSpeed(speed);
    motor4.run(BACKWARD);
    motor4.setSpeed(speed);
    delay(100);
  }

  //if all sensors are on a black line
  else if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //stop
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);
  }
  else 
  {
   //going forward 
    motor1.run(FORWARD);
    motor1.setSpeed(speed);
    motor2.run(FORWARD);
    motor2.setSpeed(speed);
    motor3.run(FORWARD);
    motor3.setSpeed(speed);
    motor4.run(FORWARD);
    motor4.setSpeed(speed);
  }
}
