#define analog_pin A0

int ldr_value = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ldr_value = analogRead(analog_pin); //อ่านค่า analog จากตัวแปร analog_pin
  Serial.print("LDR value = ");
  Serial.println(ldr_value); //เเสดงค่า ldr_value
  delay(1000);
}
