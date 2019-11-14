#include <Servo.h>

Servo RC_servo; //定义模型车舵机
char serial_data;//接收raspberrypi数据
/*舵机定义部分*/
int Servopin = 9;//舵机数字接口
int servo_data = 45;//舵机接受数据
int ANG_L = 115;//小车左转角度
int ANG_mid = 80;//小车正向角度
int ANG_R = 45;//小车右转角度
int angle = 45;//定义转向角度存储器，初始正向

/*电机定义部分*/
int Motorpin = 10;//电机数字接口
char motor_data;//电机接受数据
int pulsewidth;//定义脉宽变量
int MTspeed = '9';//电机速度
int val1;
int myangle1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  RC_servo.attach(Servopin);
  pinMode(Motorpin, OUTPUT); //设定舵机接口为输出接口
  Serial.println("servu=o_seral_simple ready" ) ;
  RC_servo.write(45);

  //电调初始化
  //看电调说明书，设置油门行程时，一开始需要把遥控器打到最高点。i<=110大概是2杪多
  for (int i = 0; i <= 110; i++)
  {
    servopulse(Motorpin, 150); //引用脉冲函数
  }

  //等电机发出B-B两声后（就是两秒后，大概就是这里了）把油门打到最低点
  for (int i = 0; i <= 55; i++)
  {
    servopulse(Motorpin, 20); //引用脉冲函数
  }

  //后面提示后，就可以控制电机转动了
  for (int i = 0; i <= 150; i++)
  {
    servopulse(Motorpin, 150); //引用脉冲函数
  }

  Serial.println("hello world" ) ;
}

void loop() {
  // put your main code here, to run repeatedly:
   //通信模块调用
  input_data();

  //舵机逻辑部分
  if (servo_data > angle) {ANG_L = servo_data;}
  if (servo_data == ANG_mid) {ANG_mid = servo_data;}
  if (servo_data < angle) {ANG_R = servo_data;}

  if (servo_data > angle) {turnL();}
  else {if (servo_data == ANG_mid) {_init();}
  else {if (servo_data < angle) {turnR();}
  }
 }
 Motorspeed();
}

/*串口通信模块*/
void input_data() {
  if (Serial.available() > 0)
  {

    serial_data = Serial.read();
    servo_data = serial_data;

    Serial.print("接收到的角度为：");
    Serial.print(servo_data);
    delay(10);
    Serial.flush();
    Serial.print("\n接收完成！");
    Serial.print("\n");
  }
}



/*--转向控制--*/
/*左转*/
void turnL() {
  for (; angle <= ANG_L; angle++) {
    RC_servo.write(angle);
    delay(5);
  }
}
/*右转*/
void turnR() {
  for (
    ; angle >= ANG_R; angle-- ) {
    RC_servo.write(angle);
    delay(5);
  }
}

/*正向*/
void _init() {
  RC_servo.write(ANG_mid);
  delay(5);
}

/*--加减速控制--*/

//下面是servopulse函数部分(此函数意思:也就是說每次都是0.5ms高電平 1.98ms低電平 然後再0.52ms低電平 17ms延時也是低電平)
void servopulse(int Motorpin, int val1) //定义一个脉冲函数
{
  myangle1 = map(val1, 0, 180, 1476, 1800);
  digitalWrite(Motorpin, HIGH); //将舵机接口电平至高
  delayMicroseconds(myangle1);//延时脉宽值的微秒数
  digitalWrite(Motorpin, LOW); //将舵机接口电平至低
  delay(20 - val1 / 1000);
}
//servopulse函数部分到此结束


//将0到9的数转化为0到180角度，并让LED闪烁相应数的次数
void Motorspeed() {
//  if (Serial.available() > 0)
//  {
//    motor_data = Serial.read();
//    delay(100);
//    MTspeed = motor_data;
//    Serial.flush();
//  }

  Serial.print("start_val to :");
  Serial.print(MTspeed,DEC);
  Serial.print("\n");
  if (MTspeed > '0' && MTspeed <= '9')
  {
    val1 = MTspeed - '0'; //将特征量转化为数值变量
    val1 = map(val1, 0, 9, 0, 180); //将角度转化为500-2480的脉宽值
    Serial.print("moving servo to ");
    Serial.print(val1, DEC);
    Serial.println();
    for (int i = 0; i <= 50; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(Motorpin, val1); //引用脉冲函数
    }

  }
}
