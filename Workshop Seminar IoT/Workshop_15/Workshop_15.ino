#define BLYNK_TEMPLATE_ID "your template id"
#define BLYNK_DEVICE_NAME "your device name"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//ประกาศตัวแปร
#define SOUND_VELOCITY 0.034

#define TRIG          D0
#define ONE_WIRE_BUS  D1
#define ECHO          D2
#define RELAY         D3
#define LED_R         D5
#define LED_G         D6
#define LED_Y         D7

#define SOIL_MOIST    A0

const char ssid[] = "Wifi_name";
const char pass[] = "password";
const char auth[] = "your token";

int raw_data = 0;
int moisture = 0;

long duration;
float distanceCm;

float c = 0;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
BlynkTimer timer;

void timerEvent();
void pinConfig();
void pushDistance();
void pushMoisture();
void pushTemp();

void setup(void) {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, timerEvent);
  pinConfig();
} 
void loop(void) {
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V3) { //function visualpin6 ใช้ในการกดปุ่มบน blynk
  if(param.asInt()){
    digitalWrite(RELAY, LOW); }
  else{
    digitalWrite(RELAY, HIGH); }
}

void pinConfig(){
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT); 
  digitalWrite(TRIG, LOW);
  
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  
  sensors.begin();

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  
  digitalWrite(LED_R, HIGH); 
  digitalWrite(LED_G, HIGH); 
  digitalWrite(LED_Y, HIGH); 
}

void timerEvent(){
  pushTemp();
  pushDistance();
  pushMoisture();
}

void pushTemp(){
  //อ่านค่าอุหณภูมิจาก DS18B20 temperature sensor
  sensors.requestTemperatures();
  c = sensors.getTempCByIndex(0);
  Blynk.virtualWrite(V0,c);
  Serial.print("Temperature is: ");
  Serial.print(c); 
  Serial.println(" °C");
  //เช็คอุณหภูมิ
  if(c > 27){
      digitalWrite(LED_R, HIGH); 
  }
  else{
      digitalWrite(LED_R, LOW);
  }
}

void pushMoisture(){
  //อ่านค่าความชื้นในดินจาก soil moisture sensor
  raw_data = analogRead(SOIL_MOIST);  
  moisture = map(raw_data, 0, 1023, 100, 0);
  Blynk.virtualWrite(V1, moisture);
  Serial.print("Moisture = ");
  Serial.println(moisture);

  if (moisture > 50) { 
    digitalWrite(LED_Y, LOW); 
    digitalWrite(LED_G, HIGH); 
  }
  else{
    digitalWrite(LED_Y, HIGH); 
    digitalWrite(LED_G, LOW); 
  }
}

void pushDistance(){
  //อ่านค่าระยะทางจาก ultrasonic sensor
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, HIGH);
  distanceCm = duration * SOUND_VELOCITY/2;

  if (distanceCm >= 200 || distanceCm <= 0) {
    Serial.println("Out of range");
  }
  else { 
    Blynk.virtualWrite(V2, distanceCm); //ส่งค่าไปที่ Blynk โดยใช้ visualpin v3
    Serial.print("Distance (cm): ");
    Serial.print(distanceCm);
    Serial.println(" cm");
  }
}
