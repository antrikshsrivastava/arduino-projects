

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Serial.println("A");
  //int rssiDur = pulseIn(9, LOW, 200);
  //Serial.println(rssiDur);
  int duration= pulseIn(9,HIGH,200);
  Serial.println(duration);
             
  //delay(100);
}
