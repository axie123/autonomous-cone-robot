// This is the main process that the Arduinos would run on. 


#include <Wire.h> // I2C communication library
void Robot(void);
void requestEvent(void);
const byte rxPin = 1;
const byte txPin = 0;

void setup() {
   // put your setup code here, to run once:
   Wire.begin(8); // Join I2C bus with address 8
 
   // Register callback functions
   Wire.onReceive(Robot); // Called when this slave device receives a data transmission from master.
   Wire.onRequest(requestEvent); // Called when master requests data from this slave device.

   pinMode(PD4,OUTPUT); //DC Motors
   pinMode(PD5,OUTPUT); //DC Motors
   pinMode(PD6,OUTPUT); //DC Motors
   pinMode(PD7,OUTPUT); //DC Motors
   pinMode(PD3,OUTPUT); //Servo wire - crack
   pinMode(PD2,OUTPUT); //Servo wire - hole
   pinMode(PB4,INPUT);  //center sensor
   pinMode(PB0,INPUT);  //crack sensor
   pinMode(A0,OUTPUT);
   
   // Open serial port to PC (hardware UART)
   Serial.begin(9600); 
}

int encode = 0;
int fmeters = 2;
int move_spot = 0;
int pos_time = 0;
int distance;
int cones;

volatile bool send_to_pic = false;
volatile uint8_t incomingByte;
void loop() {
     void Robot(void);
}

void Robot(void) {
   static uint8_t buf[3] = {0};
   static uint8_t counter = 0;
   uint8_t x = Wire.read(); // Receive byte which is the signal for the robot to start operating.
   if (x == 'A') {
      while (encode < fmeters) { // This makes the robot go forward for 4 meters. 
      
      // This makes the robot go forward. The values are: forward - 231 , backward - 247.
      digitalWrite(PD7,LOW);
      digitalWrite(PD4,HIGH);
      analogWrite(PD5,0);
      analogWrite(PD6,231); 
      encode += 1;
   }
   // This part makes the robot go all the way towards the end without sensing.
   digitalWrite(PD7,LOW);
   digitalWrite(PD4,LOW);
   analogWrite(PD5,0);
   analogWrite(PD6,0); 
   delayMicroseconds(1000);
   while (encode < fmeters*2) { // This makes the robot go backwards.
        digitalWrite(PD7,HIGH);
        digitalWrite(PD4,LOW);
        analogWrite(PD5,247);
        analogWrite(PD6,0); 
        encode += 1;
        if (digitalRead(PB4) > 0){ // The truth condition of this statement is that the sensors detect a crack or hole.
          digitalWrite(PD7,LOW); // Stops the robot
          digitalWrite(PD4,LOW);
          analogWrite(PD5,0);
          analogWrite(PD6,0); 
          if (digitalRead(PB0) > 0){ // Checking the reading of crack sensors.
            // Moves to position.
            digitalWrite(PD7,HIGH); 
            digitalWrite(PD4,LOW);
            analogWrite(PD5,247);
            analogWrite(PD6,0);
            encode += pos_time; // Added time to move to position.
            delayMicroseconds(move_spot); // Time to move to position
            digitalWrite(PD3,HIGH); // Tells the crack placer to start by sending a high to the other Arduino.
            digitalWrite(PD7,LOW); // Stops the robot
            digitalWrite(PD4,LOW);
            analogWrite(PD5,0);
            analogWrite(PD6,0); 
            delay(3000);
            digitalWrite(PD3,LOW); // Sets the sensor to low 
            delay(4000000); // Gives time for the other Arduino to operate the arm. 
            //Get distance      
          }
          else { // Detects only a hole.
            digitalWrite(PD7,HIGH);
            digitalWrite(PD4,LOW);
            analogWrite(PD5,247);
            analogWrite(PD6,0);
            encode += pos_time;
            delayMicroseconds(move_spot);
            digitalWrite(PD2,HIGH); // Tells the hole placer to start (signal sent to Arduino).
            digitalWrite(PD7,LOW); // Stops the robot
            digitalWrite(PD4,LOW);
            analogWrite(PD5,0);
            analogWrite(PD6,0); 
            delay(3000);
            digitalWrite(PD2,LOW); // Sets the sensor to low.
            delay(2000000); // Gives time to place the cones.
            //Get distance
          }
        }
      }
      digitalWrite(PD7,LOW); // Stops the robot
      digitalWrite(PD4,LOW);
      analogWrite(PD5,0);
      analogWrite(PD6,0); 
      x = 'B';
    }
    x = 'B';
    //Send information back to tell them it's finished.
}

/** @brief Callback for when the master requests data */
void requestEvent(void){
    Wire.write(incomingByte); // Respond with message of 1 byte
    incomingByte = 0; // Clear output buffer
}
