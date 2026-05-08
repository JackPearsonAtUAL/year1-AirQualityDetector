/*
Required Libraries:
MQ135_XCR.h

*/
#include <stdio.h>

//LED
const int PIN_RED   = 4;
const int PIN_GREEN = 3;
const int PIN_BLUE  = 2;

// Air click board (Detects toxic gases; ammonia (NH3), nitrogen oxides (NOx) benzene, smoke, CO2, +more)
// Detects between 10 - 1000
// Map the value to a percent by dividing it by 10
#include "MQ135_XCR.h"
MQ135_XCR airSensor(A0);

void setup() {
  Serial.begin(9600);
  airSensor.calibrate();
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  
}

void loop() {
  airCheck();
  colorChange(52, 168);

  delay(2000);
}

void checkColour(String s){
  if (s == "")
}

// B is always 0
void colorChange(int R, int G){
  analogWrite(PIN_RED,   R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE,  0);
}

void airCheck(){
  gasCheck();
  particleCheck();
}

void gasCheck(){
    // put your main code here, to run repeatedly:
    float ppm = airSensor.getPPM();
    String airQuality = airSensor.getAirQuality();

    Serial.print("Harmful Gases (ppm): ");
    Serial.print(ppm/10);
    Serial.print("% | Air Quality: ");
    Serial.println(airQuality); 
}

void particleCheck(){
  return;
}