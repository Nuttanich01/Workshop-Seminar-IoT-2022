#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5 //กำหนดขาที่จะเชื่อมต่อ Sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int ledPin = D5;
int Buzzer = D6;

void setup(void) {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  // sets the pin as output
  pinMode(Buzzer, OUTPUT);
  Serial.println("Dallas Temperature IC Control Library");
  sensors.begin();
}
 
void loop(void) {
  Serial.println("Requesting temperatures...");
  sensors.requestTemperatures(); //อ่านข้อมูลจาก library
  Serial.print("Temperature is: ");
  Serial.print(sensors.getTempCByIndex(0)); // แสดงค่า อูณหภูมิ 
  Serial.println(" *C");
  if (sensors.getTempCByIndex(0) > 32) { 
    digitalWrite(ledPin, HIGH); // สั่งให้ LED สว่าง
    digitalWrite(Buzzer, HIGH); // สั่งให้ Buzzer ส่งเสียง
  }
  else {
    digitalWrite(ledPin, LOW); // สั่งให้ LED ดับ 
    digitalWrite(Buzzer, LOW); // สั่งให้ Buzzerดับ
  }
delay(1000);
}
