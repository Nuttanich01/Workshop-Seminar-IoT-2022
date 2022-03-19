#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN D4 //ใช้ประกาศว่าจะใช้ PIN D4 ในการรับข้อมูลจาก DHT22
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  Serial.begin(115200);
  Serial.println();
  dht.begin();
  lcd.begin();//เริ่มการทำงานของ LCD
  lcd.backlight();// เปิดไฟแบล็กไลค์

}
void loop() {
  float t = dht.readTemperature(); //รับค่าอุณหภูมิในอากาศจาก DHT22
  float h = dht.readHumidity(); //รับค่าความชื้นในอากาศจาก DHT22
  if(isnan(t)||isnan(h)){//ใช้ในการเช็คค่าจาก DHT22 ว่ามีค่าส่งมาหรือไม่
    Serial.println("Failed!"); //ถ้าไม่มีค่าส่งมาจะขึ้นว่า failed
  }
  else{
    Serial.print("Temp :"); 
    Serial.print(t); //เเสดงค่าอุณหภูมิในอากาศ
    Serial.println("*C");
    Serial.print("Humid : ");
    Serial.print(h);  //เเสดงค่าความชื้นในอากาศ
    Serial.println("%");
    Serial.println("-------------------------------------");}
  delay(500);
  lcd.setCursor(0, 0);//เลื่อนเคเซอร์ไปบรรทัดที่ 1 ลำดับที่ 0
  lcd.print("hum:     ");
  lcd.setCursor(4, 0);//เลื่อนเคเซอร์ไปบรรทัดที่ 1 ลำดับที่ 4
  lcd.print(h);//เเสดงค่าความชื้นในอากาศ
  lcd.setCursor(9, 0);//เลื่อนเคเซอร์ไปบรรทัดที่ 1 ลำดับที่ 9
  lcd.print("%");
  lcd.setCursor(0, 1);//เลื่อนเคเซอร์ไปบรรทัดที่ 2 ลำดับที่ 0
  lcd.print("Tem:     ");
  lcd.setCursor(4, 1);//เลื่อนเคเซอร์ไปบรรทัดที่ 2 ลำดับที่ 4
  lcd.print(t);//เเสดงค่าอุณหภูมิในอากาศ
  lcd.setCursor(9, 1);//เลื่อนเคเซอร์ไปบรรทัดที่ 2 ลำดับที่ 9
  lcd.print("C");
  delay(500);
}
