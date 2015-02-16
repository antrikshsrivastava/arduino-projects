#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define SOUND_PIN  A0 //Sound sensor pin

#define NUMBER_OF_SENSORS  1

// Actuator pin definitions
#define SERVO_PIN_1  9
#define GREEN_LED_PIN 10
#define RED_LED_PIN  8

#define UPDATE_PERIOD  20 //Update period in milliseconds

#define TRIGGER_DISTANCE  30
#define SERVO_LOCKED  255
#define SERVO_UNLOCKED  0
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Servo servo_device_1;

struct sensorData {
  double distance_1;  
  double light_1;
  int sound_1;
};

struct actuatorState {
  double servo_1; 
  boolean led_1;
};

sensorData sensors;
actuatorState actuators;

void setup() {
  Serial.begin(9600);
  //Initialise sensors and actuators
  sensors.distance_1 = -1;
  actuators.servo_1 = 0;
  
  servo_device_1.attach(SERVO_PIN_1);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
}

void updateSensors() {
  updateUltrasonicSensors();
  updateSoundSensors();
}

void applyControlLaws() {
  if (sensors.distance_1 > TRIGGER_DISTANCE) {
    actuators.led_1 = true;  
    actuators.servo_1 = SERVO_UNLOCKED;
  } else {
    actuators.led_1 = false;  
    actuators.servo_1 = SERVO_LOCKED;
  }
}

void updateActuators() {
  servo_device_1.write(actuators.servo_1);
  if (actuators.led_1) {
    digitalWrite(GREEN_LED_PIN, HIGH);
  } else {
    digitalWrite(GREEN_LED_PIN, LOW);  
  }
}

void updateUltrasonicSensors() {
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  sensors.distance_1 = uS / (US_ROUNDTRIP_CM); 
}

void updateSoundSensors() {
  sensors.sound_1 = analogRead(A0);  
  int amp = (sensors.sound_1 >= 512) ? sensors.sound_1 - 512 : 512 - sensors.sound_1;  
  Serial.println(sensors.sound_1);
  if (amp > 100) {
    digitalWrite(RED_LED_PIN, HIGH);  
  } else {
    digitalWrite(RED_LED_PIN, LOW);  
  }
        
}

void loop() {
  updateSensors();
  applyControlLaws();
  updateActuators();
  //Serial.println(sensors.distance_1);
  delay(UPDATE_PERIOD);
}



