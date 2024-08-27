/*
显示左侧和右侧反射传感器的数据

2024.8.27
*/


int LSENSOR = A0;
int RSENSOR = A1;


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

 
  delay(20);
    

}
