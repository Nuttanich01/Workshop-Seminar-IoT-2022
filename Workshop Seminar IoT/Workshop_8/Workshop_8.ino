#define BLYNK_TEMPLATE_ID "your template id"
#define BLYNK_DEVICE_NAME "your device name"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define LED1 D5
#define LED2 D6
#define LED3 D7

const char ssid[] = "Wifi_name";
const char pass[] = "password";
const char auth[] = "your token";

BlynkTimer timer;
void timerEvent();

void setup()
{
  //ทำการเชื่อมต่อไปที่ Blynk
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid , pass);
  timer.setInterval(1000L, timerEvent);
  
  //กำหนด mode ให้กับ pin
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop()
{
  //เริ่มการทำงานของ Blynk
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V0) { //function การทำงานของ visualpin 0
  if (param.asInt()) { //param.asInt() ใช้ในการเช็คว่ามีการกดปุ่มหรือไม่ ถ้ามีจะ return เป็น true
    
    digitalWrite(LED1, HIGH);
  }
  else {
    digitalWrite(LED1, LOW);
  }
}
BLYNK_WRITE(V1) { //function การทำงานของ visualpin 1
  if (param.asInt()) {
    digitalWrite(LED2, HIGH);
  }
  else {
    digitalWrite(LED2, LOW);
  }
}
BLYNK_WRITE(V2) { //function การทำงานของ visualpin 2
  if (param.asInt()) {
    digitalWrite(LED3, HIGH);
  }
  else {
    digitalWrite(LED3, LOW);
  }
}
void timerEvent() {
}
