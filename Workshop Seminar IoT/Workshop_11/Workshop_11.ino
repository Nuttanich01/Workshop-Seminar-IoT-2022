#define BLYNK_TEMPLATE_ID "your template id"
#define BLYNK_DEVICE_NAME "your device name"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//กำหนดความเร็วของเสียงให้อยู่ในหน่วย cm/uS
#define SOUND_VELOCITY 0.034
#define TRIG_PIN D1
#define ECHO_PIN D2

const char ssid[] = "Wifi_name";
const char pass[] = "password";
const char auth[] = "your token";

long duration;
float distanceCm;

BlynkTimer timer;
void timerEvent();
void pushDistance();

void setup() {
  Serial.begin(115200); // Starts the serial communication

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, timerEvent);

  pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input
  digitalWrite(TRIG_PIN, LOW); // Clears the trigPin
}

void loop() {
  // ตั้งค่า trigPin ให้เป็น High เป็นเวลา 10 micro seconds
  Blynk.run();
  timer.run();
}

void timerEvent() {
  // เเสดงระยะทาง
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  //อ่านค่าจาก echoPin ซึ่งจะคืนค่าเป็นเวลา sound wave travel (หน่วยเวลาเป็น micro seconds)
  duration = pulseIn(ECHO_PIN, HIGH);

  // คำนวณระยะทาง
  distanceCm = duration * SOUND_VELOCITY / 2;
  if (distanceCm >= 200 || distanceCm <= 0) {
    Serial.println("Out of range");
  }
  else {
    Blynk.virtualWrite(V0, distanceCm); //ส่งค่าไปที่ Blynk โดยใช้ visualpin v0
    Serial.print("Distance (cm): ");
    Serial.print(distanceCm);
    Serial.println(" cm");
  }
}
