/*
Dev note:
This must be run in the arduino IDE, not from. VSCode

Required Libraries:
MQ135_XCR.h

*/
#include <stdio.h>

//LED
const int PIN_RED   = 4;
const int PIN_GREEN = 3;
const int PIN_BLUE  = 2;

// Dust Sensor
int dustPin = 13;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 10000;//sampe 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

// Air click board (Detects toxic gases; ammonia (NH3), nitrogen oxides (NOx) benzene, smoke, CO2, +more)
// Detects between 10 - 1000
// Map the value to a percent by dividing it by 10
#include "MQ135_XCR.h"
MQ135_XCR airSensor(A0);

void setup() {
  Serial.begin(9600);

  airSensor.calibrate();

  // Setup pins
  pinMode(dustPin, INPUT);
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);

  // Get the current time
  starttime = millis();

  Serial.print("This program will output the air quality every ");
  Serial.print(String(sampletime_ms/1000));
  Serial.print(" seconds");
  Serial.println('\n');
}

void loop() {
  if ((millis()-starttime) > sampletime_ms){
    airCheck();
  }

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
    Serial.println('\n');
}

void particleCheck(){
  duration = pulseIn(dustPin, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;

    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    
    Serial.print("Low Pulse Occupancy:");
    Serial.print(lowpulseoccupancy);
    Serial.print(", Ratio:");
    Serial.print(ratio);
    Serial.print(", Dust Concentration:");
    Serial.println(concentration);
    Serial.println('\n');

    lowpulseoccupancy = 0;
    starttime = millis();
}