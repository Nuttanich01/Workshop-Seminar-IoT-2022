#define BLYNK_TEMPLATE_ID "your template id"
#define BLYNK_DEVICE_NAME "your device name"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define Relay D2
#define LED_G D5
#define LED_R D6
#define SOIL_MOIST A0

const char ssid[] = "Wifi_name";
const char pass[] = "password";
const char auth[] = "your token";

int raw_data = 0;
int moisture = 0 ;

BlynkTimer timer;
void timerEvent();

void setup()
{
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, timerEvent);
  
  pinMode(LED_G, OUTPUT);  // sets the pin as output
  pinMode(LED_R, OUTPUT);  // sets the pin as output
}

void loop()
{
  Blynk.run();
  timer.run();
}

void timerEvent(){
  raw_data = analogRead(SOIL_MOIST);  //อ่านค่าสัญญาณ analog จาก PIN A0 ที่ต่อกับ Soil Moisture Sensor Module v1
  moisture = map(raw_data, 0, 1023, 100, 0); //ปรับเปลี่ยนค่าจาก 0-1023 เป็น 0-100
  Serial.print("Moisture = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(moisture); // พิมพ์ค่าของตัวแปร val
  
  Blynk.virtualWrite(V0, moisture);//ส่งค่าไปที่ blynk โดยใช้ visualpin 0
 
  if (moisture > 50) {//จากค่าที่ทำการแปลง map_val มีค่ามากกว่า 50 เเสดงว่าดินมีความชื้นเกิน 50 เปอร์เซ็น
    digitalWrite(LED_G, LOW); // สั่งให้ LED เขียวดับ
    digitalWrite(LED_R, HIGH); // สั่งให้ LED สีเเดง ติดสว่าง
  }
  else { 
    digitalWrite(LED_G, HIGH); // สั่งให้ LED เขียวติดสว่าง
    digitalWrite(LED_R, LOW);// สั่งให้ LED สีเเดง ดับ
  }
}
