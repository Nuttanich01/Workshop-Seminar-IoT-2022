#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
#define LED 13

const char* ssid = ""; ;                        //***change
const char* password = "";                      //***change
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "";                   //***change
const char* mqtt_Token = "";                    //***change
const char* mqtt_Secret = "";                   //***change

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempProbe(&oneWire);
WiFiClient espClient;
PubSubClient client(espClient);

char msg[100];
float temp = 0.0;
bool isReady = false;

void reconnect();
void onoff(int );                               //sent LED status to netpie
void callback(char* , byte* , unsigned int );   //get data from netpie
float readTemp();
void displayTemp();
void displayLED();

void setup() {
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library");
  tempProbe.begin();
  pinMode(LED, OUTPUT);

  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);             // access wifi
  while (WiFi.status() != WL_CONNECTED)   //check disconnect
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  isReady = true;
}

void loop() {
  if (!client.connected())
    reconnect();
    
  client.loop();
  
  if (millis() % 1000 == 0 && isReady) {
    temp = readTemp();
    String data = "{\"data\": {\"temperature\":" + String(temp) + "}}";
    data.toCharArray(msg, data.length() + 1);
    client.publish("@shadow/data/update", msg); // sent data to shadow netpie
    displayTemp();
    displayLED();
  }
}

void reconnect()
{
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_Client, mqtt_Token, mqtt_Secret)) {
      Serial.println("connected");
      client.subscribe("@msg/ledState");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.print("Try again in 5 sec");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) //get data from netpie
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  String msg;
  for (int i = 0; i < length; i++) {
    msg = msg + (char)payload[i];
  }
  Serial.println(msg);
  if ( String(topic) == "@msg/ledState")
    if (msg == "on") {
      onoff(true);
      client.publish("@shadow/data/update", "{\"data\" : {\"ledState\" : \"on\"}}");
    }
    else if (msg == "off") {
      onoff(false);
      client.publish("@shadow/data/update", "{\"data\" : {\"ledState\" : \"off\"}}");
    }
}

void onoff(bool led) //sent LED status to netpie
{
  if (led)
  {
    Serial.println("Turn on LED");
    digitalWrite(LED, HIGH);
  }
  else if (!led)
  {
    Serial.println("Turn off LED");
    digitalWrite(LED, LOW);
  }
}

float readTemp() {
  tempProbe.requestTemperatures();
  return tempProbe.getTempCByIndex(0);
}

void displayTemp() {
  Serial.print("temp = ");
  Serial.print(temp);
  Serial.println(" °C");
}

void displayLED(){
  Serial.print("LED Status : ");
  Serial.println(digitalRead(LED));
  Serial.println();
}
