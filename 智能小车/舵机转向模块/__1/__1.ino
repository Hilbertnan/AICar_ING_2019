/*舵机转向模块*/

#include <Servo.h>

Servo myservo;
int Servopin = 9;
int ANG_L = 115;
int ANG_mid = 80;
int ANG_R = 45;
int angle = 60;
int data = 0;
void setup()
{
  myservo.attach(Servopin);
}

void loop() {
  //舵机逻辑部分
  if (data > angle) {
    ANG_L = data;
  }
  if (data == ANG_mid) {
    ANG_mid = data;
  }
  if (data < angle) {
    ANG_R = data;
  }

  if (data > angle) {
    turnL();
  }
  else {
    if (data == ANG_mid) {
      _init();
    }
    else {
      if (data < angle) {
        turnR();
      }
    }
  }
}

/*左转*/
void turnL() {
  for (; angle <= ANG_L; angle++) {
    myservo.write(angle);
    delay(5);
  }
}
/*右转*/
void turnR() {
  for (
    ; angle >= ANG_R; angle-- ) {
    myservo.write(angle);
    delay(5);
  }
}

/*正向*/
void _init() {
  myservo.write(data);
  delay(5);
}
