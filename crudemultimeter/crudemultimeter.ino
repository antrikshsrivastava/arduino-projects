int val = 0;

void setup() {
  Serial.begin(9600);  
  pinMode(2, OUTPUT); 
  pinMode(13, OUTPUT); 
  digitalWrite(2, HIGH);
}

void loop() {
  val = analogRead(5);
  if (val > 900) digitalWrite(13, HIGH);
  if (val < 900) digitalWrite(13, LOW);
  Serial.println(val);
//  delay(200);
}
