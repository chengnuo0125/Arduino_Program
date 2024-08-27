/*
小车沿着设定好的跑到行进，检测到跑道边缘会转弯

2024.8.27
*/


int LSENSOR = A0;
int RSENSOR = A1;
const int PIN_PWM_R1 = 9;
const int PIN_PWM_R2 = 10;
const int PIN_PWM_L1 = 5;
const int PIN_PWM_L2 = 6;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("L:");
  Serial.print(analogRead(LSENSOR));
  Serial.print("   R:");
  Serial.println(analogRead(RSENSOR));

  
  // 直行   
  if(analogRead(RSENSOR)<400&&analogRead(LSENSOR)<400){
    analogWrite(PIN_PWM_R1, 0);  // 右轮前转
    analogWrite(PIN_PWM_R2, 60);
    analogWrite(PIN_PWM_L1, 0);  // 左轮前转
    analogWrite(PIN_PWM_L2, 60);


  // 左转
  }else if(analogRead(RSENSOR)>=400&&analogRead(LSENSOR)<400){
    analogWrite(PIN_PWM_R1, 0);  // 右轮前转
    analogWrite(PIN_PWM_R2, 255);
    analogWrite(PIN_PWM_L1, 255);  // 左轮后转
    analogWrite(PIN_PWM_L2, 0);
    // delay(20);


  // 右转  
  }else if(analogRead(RSENSOR)<400&&analogRead(LSENSOR)>=400){
    analogWrite(PIN_PWM_R1, 255);  // 右轮后转
    analogWrite(PIN_PWM_R2, 0);
    analogWrite(PIN_PWM_L1, 0);  // 左轮前转
    analogWrite(PIN_PWM_L2, 255);
    // delay(20);


  // 停止 
  }else if(analogRead(RSENSOR)>=400&&analogRead(LSENSOR)>=400){
    analogWrite(PIN_PWM_R1, 0);  // 右轮不转
    analogWrite(PIN_PWM_R2, 0);
    analogWrite(PIN_PWM_L1, 0);  // 左轮不转
    analogWrite(PIN_PWM_L2, 0);
 
  };
  // delay(20);
}
