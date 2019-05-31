#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object
const int sensorPin= 0;
const int mins = 1;
const float ipsmsvs=0.0057;
float result = 0;
float preresult = 0;
int cpm = 0;
int val = 0;
unsigned long previousMillis = millis(); 
const long interval = 60000*mins; 

void setup() {
Serial.begin(9600);
digitalWrite(14, HIGH); 
byte numDigits = 4;
byte digitPins[] = {9, 10, 11, 12};
byte segmentPins[] = {2, 3, 13, 5, 6, 7, 8, 4};
bool resistorsOnSegments = false;
bool updateWithDelays = false;
bool leadingZeros = true;
bool disableDecPoint = false;

sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
sevseg.setBrightness(90);
}

void loop() {
  int val = analogRead(sensorPin);
  unsigned long currentMillis = millis();
  if(val < 3989){
  cpm++;
  if (currentMillis - previousMillis >= interval) {
     result = (cpm*ipsmsvs/((currentMillis - previousMillis)/60))*1000;
     char string[15] = "";    
     char dstr[7] = "";
     dtostrf(result, 3, 3, dstr);
     sprintf(string, "result: %s", dstr);
     Serial.println(string);
     preresult = result;
     cpm = 0;
     previousMillis = currentMillis;
  }
  else {
     result = preresult;
  }
  if(cpm % 200 == 0 && cpm != 0){
     preresult = (cpm*ipsmsvs/((currentMillis - previousMillis)/60))*1000;
  }

}

if(result >= 9){
  sevseg.setNumber(result, 1);
}
if(result >= 0.9){
  sevseg.setNumber(result, 2);
}
else{
if(result >= 0.09){
  sevseg.setNumber(result, 3);
}
else{
  sevseg.setNumber(result, 4);
}
}
sevseg.refreshDisplay();  
}
