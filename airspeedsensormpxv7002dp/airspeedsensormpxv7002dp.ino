void setup ()
{
  Serial.begin(9600);
}


void loop()
{
  float vfss = 3.5;
  int pValue = analogRead(0);
  //Serial.println(pValue);
  float vOut = map(pValue,0,1023,0,5);
  //float pressure = (vOut+0.0625*vfss)-0.5 ;
  float pressure = ((pValue/(float)1023)-0.5)*5;
  float velocity = sqrt((2*pressure*1000)/(1.225));
  Serial.print(pressure); Serial.print(", velocity = ");
  Serial.print((int)(velocity-8.5)); Serial.println("m/s");
  //Serial.println(vOut);
  //Serial.println(pressure);
  delay(100); 
}
