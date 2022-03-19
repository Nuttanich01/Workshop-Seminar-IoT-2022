#define BLYNK_TEMPLATE_ID "your template id"
#define BLYNK_DEVICE_NAME "your device name"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN D4 //ใช้ประกาศว่าจะใช้ PIN D4 ในการรับข้อมูลจาก DHT22
#define DHTTYPE DHT22

const char ssid[] = "Wifi_name";
const char pass[] = "password";
const char auth[] = "your token";

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void timerEvent();

void setup() {
  dht.begin();//สั่งให้ DHT22 เริ่มทำงาน
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, timerEvent);
  Serial.begin(115200);
}
void loop() {
  Blynk.run();
  timer.run();
}
void timerEvent(){
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
    
    Blynk.virtualWrite(V0,t);//ส่งค่าอุณหภูมิไปที่ blynk โดยใช้ visualpin 0
    Blynk.virtualWrite(V1,h);//ส่งค่าความชื้นไปที่ blynk โดยใช้ visualpin 1
  }
}
