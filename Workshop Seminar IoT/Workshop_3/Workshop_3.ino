int relay1 = D1;
void setup() {
  pinMode(relay1, OUTPUT);   
}

void loop() {
 digitalWrite(relay1, HIGH);  // สั่งเปิดรีเลย์ 
 delay(1000); 
 digitalWrite(relay1, LOW);   // สั่งปิดรีเลย์
 delay(1000); 
}
