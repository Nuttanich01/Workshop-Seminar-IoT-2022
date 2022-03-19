#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5 //กำหนดขาที่จะเชื่อมต่อ Sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Set WiFi credentials
#define WIFI_SSID "your wifi"
#define WIFI_PASS "your password"
 
// Set IFTTT Webhooks event name and key
#define IFTTT_Key "your key"
#define IFTTT_Event "your event" 

WiFiClient client;
int analogPin = A0; //ประกาศตัวแปร ให้ analogPin แทนขา analog ขาที่5
int val = 0;
int map_val = 0;
float temp = 0;
float IFTTT_Value1 = 0;
float IFTTT_Value2 = 0;


void setup() {
  Serial.begin(115200); // Serial output only for information, you can also remove all Serial commands
  WiFi.begin(WIFI_SSID, WIFI_PASS); 
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  } 
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  sensors.begin();
}

void loop() {
  Serial.println("Requesting temperatures...");
  sensors.requestTemperatures(); //อ่านข้อมูลจาก library
  temp = sensors.getTempCByIndex(0);
  Serial.print("Temperature is: ");
  Serial.print(temp); // แสดงค่า อูณหภูมิ 
  Serial.println(" *C");
  IFTTT_Value1 = temp;

  val = analogRead(analogPin);  //อ่านค่าสัญญาณ analog ขา5 ที่ต่อกับ Soil Moisture Sensor Module v1
  map_val = map(val, 0, 1023, 100, 0); //ปรับเปลี่ยนค่าจาก 0-1024 เป็น 0-100
  Serial.print("val = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(map_val); // พิมพ์ค่าของตัวแปร val
  IFTTT_Value2 = map_val;
  
  // Send Webook to IFTTT
  send_webhook();
  delay(60000);
}


void send_webhook(){// function Send Webook to IFTTT
  // construct the JSON payload
  String jsonString = "";
  jsonString += "{\"value1\":\"";
  jsonString += IFTTT_Value1;
  jsonString += "\",\"value2\":\"";
  jsonString += IFTTT_Value2;
  jsonString += "\"}";
  int jsonLength = jsonString.length();  
  String lenString = String(jsonLength);
  // connect to the Maker event server
  client.connect("maker.ifttt.com", 80);
  // construct the POST request
  String postString = "";
  postString += "POST /trigger/";
  postString += IFTTT_Event;
  postString += "/with/key/";
  postString += IFTTT_Key;
  postString += " HTTP/1.1\r\n";
  postString += "Host: maker.ifttt.com\r\n";
  postString += "Content-Type: application/json\r\n";
  postString += "Content-Length: ";
  postString += lenString + "\r\n";
  postString += "\r\n";
  postString += jsonString; // combine post request and JSON
  client.print(postString);
  delay(500);
  client.stop();
}
