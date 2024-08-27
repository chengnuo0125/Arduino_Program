/*
  Blink
  让一个LED灯不断闪烁
  
  2024.8.27
*/


int delay_time = 1000;


void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(delay_time);
  digitalWrite(13, LOW);
  delay(delay_time);
  // delay_time += 1000;
}
