#define BLYNK_TEMPLATE_ID "your template id"
#define BLYNK_DEVICE_NAME "your device name"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D1 //กำหนดขาที่จะเชื่อมต่อ Sensor
#define LED D5
#define Buzzer D6

const char ssid[] = "Wifi_name";
const char pass[] = "password";
const char auth[] = "your token";

float c = 0;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
BlynkTimer timer;
void timerEvent();

void setup(void) {
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, timerEvent);
  
  sensors.begin();
  pinMode(LED,OUTPUT);
  pinMode(Buzzer,OUTPUT);
} 

void loop(void) {
  Blynk.run();
  timer.run();
}

void timerEvent(){
  sensors.requestTemperatures(); //อ่านข้อมูลจาก library
  c = sensors.getTempCByIndex(0);
  Serial.print("Temperature = ");
  Serial.print(c); // แสดงค่า อูณหภูมิ 
  Serial.println(" °C");
  
  Blynk.virtualWrite(V0,c);//ส่งค่าไปที่ blynk โดยใช้ visualpin 0
  
   if (sensors.getTempCByIndex(0) > 27) { 
    digitalWrite(LED, LOW); // สั่งให้ LED ดับ
    digitalWrite(Buzzer, HIGH); // สั่งให้ Buzzer ส่งเสียง
  }
  else {
    digitalWrite(LED, HIGH); // สั่งให้ LED ติดสว่าง
    digitalWrite(Buzzer, LOW); // สั่งให้ Buzzerดับ
  }
}
