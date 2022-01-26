const int trigPin = D1;
const int echoPin = D2;

//กำหนดความเร็วของเสียงให้อยู่ในหน่วย cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float distanceInch;

void setup() {
  //ตั้งค่า mode ให้ pin
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  digitalWrite(trigPin, LOW);
}

void loop() {
  // ตั้งค่า trigPin ให้เป็น High เป็นเวลา 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // อ่านค่าจาก echoPin ซึ่งจะคืนค่าเป็นเวลา sound wave travel (หน่วยเวลาเป็น micro seconds)
  duration = pulseIn(echoPin, HIGH);
  
  // คำนวณระยะทาง
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // เเสดงระยะทาง
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  delay(1000);
}
