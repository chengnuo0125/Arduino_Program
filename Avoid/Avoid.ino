/*
超声波和红外测距
当检测到前方近处有物体时，进行转向

2024.8.27
*/


bool IR_distance;
float ultrasound_distance;
const int   echo=A4;                         //echO接A4脚
const int   trig=A5;                         //echO接A5脚

const int PIN_PWM_R1 = 9;
const int PIN_PWM_R2 = 10;
const int PIN_PWM_L1 = 5;
const int PIN_PWM_L2 = 6;
const int irout = 11;


// r 是奇数时左拐；r 是偶数时右拐 
int r = 0;

// 前进
void ahead(int v){
  // v 是速度
  analogWrite(PIN_PWM_L1, 0);
  analogWrite(PIN_PWM_L2, v);
  analogWrite(PIN_PWM_R1, 0);
  analogWrite(PIN_PWM_R2, v);
}

// 左转
void left(int v){
  analogWrite(PIN_PWM_L1, 0);
  analogWrite(PIN_PWM_L2, v);
  analogWrite(PIN_PWM_R1, v);
  analogWrite(PIN_PWM_R2, 0);
}

// 右转
void right(int v){
  analogWrite(PIN_PWM_L1, v);
  analogWrite(PIN_PWM_L2, 0);
  analogWrite(PIN_PWM_R1, 0);
  analogWrite(PIN_PWM_R2, v);
}

// 后退
void back(int v){
  analogWrite(PIN_PWM_L1, v);
  analogWrite(PIN_PWM_L2, 0);
  analogWrite(PIN_PWM_R1, v);
  analogWrite(PIN_PWM_R2, 0);
}

// 停车
void stop(){
  analogWrite(PIN_PWM_L1, 0);
  analogWrite(PIN_PWM_L2, 0);
  analogWrite(PIN_PWM_R1, 0);
  analogWrite(PIN_PWM_R2, 0);
}







void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(echo,INPUT);                       //设置echo为输入脚
  pinMode(trig,OUTPUT);                      //设置trig为输出脚
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig,HIGH);
  delayMicroseconds(1);
  digitalWrite(trig,LOW); 
  ultrasound_distance  = pulseIn(echo,HIGH);             //计数接收高电平时间
  ultrasound_distance  = ultrasound_distance*340/2/10000;           //计算距离 1：声速：340M/S  2：实际距离为1/2声速距离 3：计数时钟为1US//温补公式：c=(331.45+0.61t/℃)m•s-1 (其中331.45是在0度）
  Serial.print("超声传感器测量距离: ");
  Serial.print(ultrasound_distance);
  Serial.print("CM,红外传感器信号:");
  Serial.println(digitalRead(irout));

  IR_distance = digitalRead(irout);


  // ultrasound_distance = 50;  // 测试红外距离传感器时去掉最前面的"//"
  // IR_distance = 1;  // 测试超声波传感器时去掉最前面的"//"

  if(ultrasound_distance<30||IR_distance==0){
    stop();
  }
  else{
    ahead(100);
  }
  delay(50);                                 

}