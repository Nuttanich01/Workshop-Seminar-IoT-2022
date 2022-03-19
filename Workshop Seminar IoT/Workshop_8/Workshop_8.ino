#include <DHT.h>
#define DHTPIN D4 //ใช้ประกาศว่าจะใช้ PIN D4 ในการรับข้อมูลจาก DHT22
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  dht.begin();//สั่งให้ DHT22 เริ่มทำงาน
  Serial.begin(115200);
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
    Serial.println("-------------------------------------");
  }
  delay(2000);//delay การทำงาน 2 วินาที
}
