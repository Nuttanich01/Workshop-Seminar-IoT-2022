//กำหนด PIN ต่าง ๆ
int LED1 = D5;
int button = D0;
int buttonState = 0;
void setup(){
  //กำหนด mode ให้แต่ละ PIN
  pinMode(D0, INPUT);
  pinMode(D5, OUTPUT);

  Serial.begin(9600); 
}
void loop() {
   buttonState = digitalRead(button);
   Serial.println(buttonState);//แสดงสถานะของ buttonState
   if(buttonState==1){//ใช้ในการเช็คสถานะของ buttonState ว่ามีค่าเท่ากับ 1 หรือ High หรือไม่ 
    digitalWrite(LED1,HIGH);
   }
   else{
    digitalWrite(LED1, LOW);
   }
}
