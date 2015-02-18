int motor = 9;

void setup(){
  pinMode(9,OUTPUT);
 
  Serial.begin(9600);
}

void loop(){

  int motor_speed = 50;
                    //PWM can only ouput 255 different values
 
  analogWrite(motor,motor_speed);
 
  //Serial.println(motor_speed);//for testing purposes
}
