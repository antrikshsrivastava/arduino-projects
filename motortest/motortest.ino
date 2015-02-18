void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);   
  pinMode(13, OUTPUT);    
}

void loop() {
   digitalWrite(13, HIGH);
   analogWrite(3, 80);
   analogWrite(6, 80);
   delay(5000);
   analogWrite(3, 0);
   analogWrite(6, 0);   
   digitalWrite(13, LOW);   
   delay(1000);    
}
