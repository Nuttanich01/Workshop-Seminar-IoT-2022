int analogPin = A0; //ประกาศตัวแปร ให้ analogPin แทนขา analog ขาที่5
int val = 0;
int map_val = 0 ;


void setup() {
  Serial.begin(9600);
}
//น้อยกว่า 500 ดินมีความชื้น
void loop() {
  val = analogRead(analogPin);  //อ่านค่าสัญญาณ analog ขา5 ที่ต่อกับ Soil Moisture Sensor Module v1
  //ปรับเปลี่ยนค่าจาก 0-1023 เป็น 0-100 เป็นการเเปลงผกผัน
  map_val = map(val, 0, 1023, 100, 0); 
  Serial.print("val = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(map_val); // พิมพ์ค่าของตัวแปร val
  delay(1000);
}
