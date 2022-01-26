int led_G = D0; //LED สีเขียว
int led_R = D1; //LED สีเเดง
int analogPin = A0; //ประกาศตัวแปร ให้ analogPin แทนขา analog ขาที่5
int val = 0;
int map_val = 0 ;
void setup() {
  pinMode(led_G , OUTPUT);  // sets the pin as output
  pinMode(led_R, OUTPUT);  // sets the pin as output
  Serial.begin(9600);
}

void loop() {
  val = analogRead(analogPin);  //อ่านค่าสัญญาณ analog ขา5 ที่ต่อกับ Soil Moisture Sensor Module v1
 
  //ปรับเปลี่ยนค่าจาก 0-1023 เป็น 0-100 เป็นการเเปลงผกผัน
  map_val = map(val, 0, 1023, 100, 0); 
  
  Serial.print("val = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(map_val); // พิมพ์ค่าของตัวแปร val
  
  if (map_val > 50) {//จากค่าที่ทำการแปลง map_val มีค่ามากกว่า 50 เเสดงว่าดินมีความชื้นเกิน 50 เปอร์เซ็น
    digitalWrite(led_G , LOW); // สั่งให้ LED เขียวดับ
    digitalWrite(led_R, HIGH); // สั่งให้ LED สีเเดง ติดสว่าง
  }
  else { 
    digitalWrite(led_G , HIGH); // สั่งให้ LED เขียวติดสว่าง
    digitalWrite(led_R, LOW);// สั่งให้ LED สีเเดง ดับ
  }
  delay(3000);
}
