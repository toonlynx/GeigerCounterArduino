#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object
const int sensorPin= 0;
const float ipsmsvs=0.0057;
float result = 0;
float preresult = 0;
int cpm = 0;
int val = 0;
unsigned long previousMillis = millis(); 
const long interval = 60000; 

void setup() {
//Serial.begin(9600);
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
  if(val < 4020){
  unsigned long currentMillis = millis();
  cpm++;
  if (currentMillis - previousMillis >= interval) {
     result = cpm*(ipsmsvs/((currentMillis - previousMillis)/1000));
     preresult = result;
     cpm = 0;
     previousMillis = currentMillis;
     //Serial.println("currentMillis");
    // Serial.println(currentMillis);

  }
  else {
     result = preresult;
  }
 // if(cpm > 300){
   //  result = cpm*(ipsmsvs/((currentMillis - previousMillis)/1000));
 // }
  
     /*    Serial.println("currentMillis1");
         Serial.println(currentMillis);
         Serial.println("previousMillis");
         Serial.println(previousMillis);
         Serial.println("VAL");
         Serial.println(val);
         Serial.println("RESULT");
         Serial.println(result);
         Serial.println("NUMBER");
         Serial.println(cpm); */

}

if(result >= 0.9){
  sevseg.setNumber(result, 1);
}
if(result >= 0.09){
  sevseg.setNumber(result, 2);
}
else{
if(result >= 0.009){
  sevseg.setNumber(result, 3);
}
else{
  sevseg.setNumber(result, 4);
}
}
sevseg.refreshDisplay(); 
}
