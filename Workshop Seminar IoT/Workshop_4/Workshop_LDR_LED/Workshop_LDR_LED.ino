#define analog_pin A0
#define LED D7

int ldr_value = 0;
String led_state = "LOW";

void setup() {
  //กำหนด mode ให้กับ pin
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);//ส่งสัญญาณ LOW ไปที่ LED
  Serial.begin(9600);
}
void loop() {
  ldr_value = analogRead(analog_pin);
  if(ldr_value > 700){//เช็คค่าของ ldr_value ว่ามีค่ามากกว่า 700 หรือไม่
    digitalWrite(LED, LOW);//ส่งสัญญาณ LOW ไปที่ LED
    led_state = "LOW";
  }
  else{
    digitalWrite(LED, HIGH);//ส่งสัญญาณ HIGH ไปที่ LED
    led_state = "HIGH";
  }  
  Serial.print("LDR value: ");
  Serial.print(ldr_value); // เเสดงค่าของ ldr_value 
  Serial.print("\t");
  Serial.print("LED state: ");
  Serial.println(led_state); // เเสดงสถานะของ led_state 
  delay(1000);
}
