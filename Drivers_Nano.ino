// This file was used to test the functions of the Arduino Nano v3.0 on the DC motors used for driving the robot. We tried it with PWM 
// and digital pins.

void setup() {
  pinMode(PD7,OUTPUT); //Digital
  pinMode(PD4,OUTPUT);
  pinMode(PD5,OUTPUT); //Analog (PWM)
  pinMode(PD6,OUTPUT);
}

void loop() {
  digitalWrite(PD7,LOW);
  digitalWrite(PD4,HIGH);
  analogWrite(PD5,0); // 0 is off for PWM
  analogWrite(PD6,255); // 255 is the max for PWM.
}
