//串口通信模块
int  serial_data = 0;
int data = 0;
void setup() {
  // put your setup code here, to run once:
  

  //pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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
