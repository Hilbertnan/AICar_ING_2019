/*舵机控制模块*/

#include <Servo.h>

Servo myservo;
int Servopin = 9;
int  serial_data = 0;
int ANG_L = 115;
int ANG_mid = 80;
int ANG_R = 45;
int angle = 80;
int data = 0;
void setup()
{
  Serial.begin(9600);
  myservo.attach(Servopin);
}

void loop() {
  //通信模块调用
  input_data();

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

/*串口通信模块*/
void input_data() {
  if (Serial.available() > 0)
  {

    serial_data = Serial.read();


    Serial.print(serial_data - 48);
    delay(100);
    Serial.flush();
    Serial.print("\n接收完成！");
    Serial.print("\n");
    delay(100);
    if ((serial_data - 48) == 9) {
      data = 80;
    } else {
      data = (serial_data - 48 - 1) * 10 + 45;
    }
    Serial.print("接收到的角度为：");
    Serial.print(data);
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
