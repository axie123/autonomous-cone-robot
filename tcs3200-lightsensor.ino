// This code is to test out the effectiveness of the TCS3200 light sensors by their difference in frequency readings between the 
// white floor and the black hockey tape. At the end, we decided to only allow cracks since there was little time left.

#define S0 4
#define S1 2
#define S2 12
#define S3 7

#define sensorOut 5  // Difference Boundary - 50 (HockeyTape), Right Most
#define sensorOut2 6 //  Difference Boundary - 50 (HockeyTape), 
#define sensorOut3 9 //  Difference Boundary - 25 (HockeyTape), Center 
#define sensorOut4 3 //  Difference Boundary - 40 (HockeyTape), 
#define sensorOut5 11 // Difference Boundary - 50 (HockeyTape), Left Most

int frequency = 0;
int frequency_l = 0;
int frequency_r = 0;

void setup() {
  pinMode(S0, OUTPUT); // Setting 4 pinout puts to power the sensors.
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT); // 5 pin inputs on the Arduino to get the readings for detecting cracks and holes.
  pinMode(sensorOut2, INPUT);
  pinMode(sensorOut3, INPUT);
  pinMode(sensorOut4, INPUT);
  pinMode(sensorOut5, INPUT); 
  pinMode(13,OUTPUT); // This one is used to send a message to an Arduino letting them know it was a hole.
  
  // Setting frequency-scaling to 20%.
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Reading on the serial monitor.
  Serial.begin(9600);
}
void loop() {
  // Setting red filtered photodiodes with S0 to S3.
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Getting the light frequecy read by the middle sensor.
  frequency = pulseIn(sensorOut3, LOW);
  delayMicroseconds(50);
  Serial.println(frequency);
  
  // Gets port 13 to send a signal for the hole for the arm to start operating.
  if (frequency > 8){
    frequency = pulseIn(sensorOut3, LOW);
    delayMicroseconds(50);
    Serial.println(frequency);
     if (frequency > 8){
        digitalWrite(13,HIGH); // Send Signal for Hole.
        delay(2000);
        digitalWrite(13,LOW);
     } 
  }
}
