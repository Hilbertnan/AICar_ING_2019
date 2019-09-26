int sp1=9;//定义舵机接口数字接口7
int pulsewidth;//定义脉宽变量
int val;
int val1;
int speed1=0;
int myangle1;



void setup()
{
  pinMode(sp1,OUTPUT);//设定舵机接口为输出接口
  //设置两组串口波特率
  Serial.begin(9600);
  
  Serial.println("servu=o_seral_simple ready" ) ;
    
    Serial.println("hello world" ) ;

}

void loop()
{
      String inchars="";
  while(Serial.available()>0)
  {
    char inchar=Serial.read();
    if(isDigit(inchar))
    {
      inchars+=inchar;
    }
      speed1=inchars.toInt();
  }


Serial.println(speed1);


    
  
delay(100);
}
