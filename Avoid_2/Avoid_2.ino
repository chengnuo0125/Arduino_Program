bool dst2;
float dst;
int sta=3;
const int   echo=A4;                         //echO接A4脚
const int   trig=A5;                         //echO接A5脚
float ld = 30.0;
const int irout = 3;
const int t=26;
const int v = 331.45+0.61*t;
void fw(int vel){
  analogWrite(5,0);
  analogWrite(6,vel);
  analogWrite(9,0);
  analogWrite(10,vel);  
}

void bw(int vel){
  analogWrite(6,0);
  analogWrite(5,vel);
  analogWrite(10,0);
  analogWrite(9,vel);  
}

void tr(){
  analogWrite(5,128);
  analogWrite(6,0);
  analogWrite(10,128);
}

void tl(){
  analogWrite(9,128);
  analogWrite(10,0);
  analogWrite(6,128);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(echo,INPUT);                       //设置echo为输入脚
  pinMode(trig,OUTPUT);                      //设置trig为输出脚
}

float getd(){
  digitalWrite(trig,HIGH);
  delayMicroseconds(1);
  digitalWrite(trig,LOW); 
  float dis;
  dis  = pulseIn(echo,HIGH);             //计数接收高电平时间
  dis  = dis*v/2/10000; 
  Serial.print("\n传感器信号:"); 
  Serial.print(dis); 
  Serial.print("红外：");
  Serial.print(digitalRead(irout));
  return dis;
}

int search(){
  float rd,ld;
  bw(32);
  delay(300);
  fw(0);
  tr();
  delay(800);
  fw(0);
  rd=getd();
  tl();
  delay(1600);
  fw(0);
  ld=getd(); 
  if (rd<=20&&ld<=20){return 0;}
  if (rd>=ld){return 1;}
  else if(rd<ld){return 2;}
  return 0;   
}

void loop() {
  // put your main code here, to run repeatedly:
  dst  = getd();
  //计算距离 1：声速：340M/S  2：实际距离为1/2声速距离 3：计数时钟为1US//温补公式：c=(331.45+0.61t/℃)m•s-1 (其中331.45是在0度）
  if (dst>=100){fw(255);}
  else if (dst<100&&dst>=50){fw(128);}
  else if (dst>=30&&dst<50){fw(64);}
  else if (dst<=30){
    int s;
    s=search();
    sta=1;
    if(s==1){
      tr();
      delay(1600);
      fw(64);
      delay(200);
    }
    if(s==2){
      fw(64);
      delay(200);
    }
    if (s==0){bw(128);delay(1000);s=search();}
    }
    else{fw(16);}
}
//  fw(128);
//  if(dst<=15){
//    fw(0)