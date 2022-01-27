//กำหนด PIN ต่าง ๆ
int LED1 = D5;
int LED2 = D6;
int LED3 = D7;
void setup(){
  //กำหนด mode ให้แต่ละ PIN
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT); 
}
void loop() {
  digitalWrite(LED1, HIGH); //สั่งให้ส่งสัญญาณ High ไปที่ LED 1
  delay(500); //delay การทำงาน 0.5 วินาที
  digitalWrite(LED1, LOW); //สั่งให้ส่งสัญญาณ Low ไปที่ LED 1
  delay(500);
  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED2, LOW);
  delay(500);
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED3, LOW);
  delay(500);  
}
