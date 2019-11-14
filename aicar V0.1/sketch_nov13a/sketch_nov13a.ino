#include <SCoop.h>
#include <Servo.h>

/*通信及数据处理部分*/
String comdata = "";//接收raspberrypi数据
int mark = 0;
char *data_ID[] = {"MOTOR：", "SERIAL：", "S1：", "S2：", "none：", "none："};

/*舵机定义部分*/
Servo RC_servo; //定义模型车舵机
int Servopin = 9;//定义舵机数字接口
int servo_data = 80;//舵机接受数据
int ANG_L = 115;//小车左转角度
int ANG_mid = 80;//小车正向角度
int ANG_R = 45;//小车右转角度
int angle = 80;//转向角度存储器，初始正向

/*电机定义部分*/
int Motorpin = 10;//定义电机数字接口
int motor_data;//电机接受数据
int MTspeed;//电机速度

//初始化
void setup() {
  Serial.begin(115200);//初始化波特率
  RC_servo.attach(Servopin);
  pinMode(Motorpin, OUTPUT); //设定舵机接口为输出接口
  Serial.println("AI_car=o_seral_simple ready" ) ;
  mySCoop.start();
  Serial.println("hello car" );
}

void loop() {
  yield();
  input_data();//调用串口通信模块
}

//多线程快速定义
defineTaskLoop(Servo_)//定义舵机线程
{

  Servo_logic();//调用舵机逻辑
  angle = servo_data;//角度存储器

}
defineTaskLoop(Motor_)//定义电机线程
{

  Motorspeed();//调用调速模块
  
}

/*串口通信模块*/
void input_data() {

  int motor_data_temp = 0;
  int servo_data_temp = 0;

  //不断循环检测串口缓存，一个个读入字符串，
  while (Serial.available() > 0)
  {
    //读入之后将字符串，串接到comdata上面。
    comdata += char(Serial.read());
    //延时一会，让串口缓存准备好下一个数字，不延时会导致数据丢失，
    delay(2);
    //标记串口读过数据，如果没有数据的话，直接不执行这个while了。
    mark = 1;
  }

  if (mark == 1) //如果接收到数据则执行comdata分析操作，否则什么都不做。
  {
    //显示刚才输入的字符串（可选语句）
    Serial.println(comdata);
    //显示刚才输入的字符串长度（可选语句）
    Serial.print("LEN:");
    Serial.println(comdata.length());
    
    /*******************下面是重点*******************/
    for (int i = 0; i < 7 ; i++)
    {
      
      if (i < 4)
      {

        motor_data_temp = motor_data_temp * 10 + (comdata[i] - '0');
      }
      else
      {

        servo_data_temp = servo_data_temp * 10 + (comdata[i] - '0');
      }
    }
   
    comdata = String("");
    if(motor_data_temp >= 800 && motor_data_temp <= 2000){
        motor_data = motor_data_temp;
     }
    if(servo_data_temp >= 45 && servo_data_temp <= 115){
        servo_data = servo_data_temp; 
      }
    
//    Serial.print(data_ID[0]);
//    Serial.println(motor_data);
//    Serial.print(data_ID[1]);
//    Serial.println(servo_data);

    MTspeed = motor_data;
    

    Serial.print(data_ID[0]);
    Serial.print(MTspeed);
    Serial.print("     ");
    Serial.print(data_ID[1]);
    Serial.println(servo_data);
    //输出之后必须将读到数据的mark置0，不置0下次循环就不能使用了。
    mark = 0;

  }
}


void Servo_logic(){
  //舵机逻辑部分
  if (servo_data > angle) {ANG_L = servo_data;}
  if (servo_data == ANG_mid) {ANG_mid = servo_data;}
  if (servo_data < angle) {ANG_R = servo_data;}

  if (servo_data > angle) {turnL();}
  else {if (servo_data == ANG_mid) {_init();}
  else {if (servo_data < angle) {turnR();}
  }
 }
}



/*--转向控制--*/
/*左转*/
void turnL() {
  for (; angle <= ANG_L; angle++) {
    RC_servo.write(angle);
  }
}
/*右转*/
void turnR() {
  for (
    ; angle >= ANG_R; angle-- ) {
    RC_servo.write(angle);
  }
}

/*正向*/
void _init() {
  RC_servo.write(ANG_mid);
}

/*--加减速控制--*/
void servopulse(int Motorpin, int MTspeed) //定义一个脉冲函数
{
  digitalWrite(Motorpin, HIGH); //将舵机接口电平至高
  delayMicroseconds(MTspeed);//延时脉宽值的微秒数
  digitalWrite(Motorpin, LOW); //将舵机接口电平至低
  delay(20);
}


void Motorspeed() {
//    Serial.print("moving_to :");
//    Serial.print(MTspeed);
//    Serial.print("    ");
//    Serial.print("servo_to :");
//    Serial.println(angle);
  servopulse(Motorpin, MTspeed); //引用脉冲函数
}
