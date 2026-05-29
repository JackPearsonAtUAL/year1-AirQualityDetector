/*
Dev note:
This must be run in the arduino IDE, not from. VSCode

Boards:
arduino wifi r4
arduino samd boards (32-bits arm cortex-m0+)

Required Libraries:
MQ135_XCR
Adafruit SSD1306

*/
#include <stdio.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Dust Sensor
int dustPin = 13;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 5000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

// Air click board (Detects toxic gases; ammonia (NH3), nitrogen oxides (NOx) benzene, smoke, CO2, +more)
// Detects between 10 - 1000
// Map the value to a percent by dividing it by 10
#include "MQ135_XCR.h"
MQ135_XCR airSensor(A0);

// Screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Outputs
String gasPPM = "";
String particleAmount = "";
String _output = "";

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Booting");
  display.display();

  airSensor.calibrate();

  // Setup pins
  pinMode(dustPin, INPUT);

  // Get the current time
  starttime = millis();

  
}

void loop() {
  if ((millis()-starttime) > sampletime_ms){
    airCheck();
  }
}


void airCheck(){
  gasCheck();
  particleCheck();

  _output = gasPPM + '\n' + particleAmount;
    display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println(_output);
  display.display();
  Serial.println(_output);
}

void gasCheck(){
    // put your main code here, to run repeatedly:
    float ppm = airSensor.getPPM();
    String airQuality = airSensor.getAirQuality();

    /*Serial.print("Harmful Gases (ppm): ");
    Serial.print(ppm/10);
    Serial.print("% | Air Quality: ");
    Serial.println(airQuality); 
    Serial.println('\n');*/
    String gas = arduino::String(ppm/10);
    gasPPM = "Toxic gas %: " + gas + '\n' + "Quality: " + airQuality;
}

void particleCheck(){
  duration = pulseIn(dustPin, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;

    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    
    /*Serial.print("Low Pulse Occupancy:");
    Serial.print(lowpulseoccupancy);
    Serial.print(", Ratio:");
    Serial.print(ratio);
    Serial.print(", Dust Concentration:");
    Serial.println(concentration);
    Serial.println('\n');*/
    //String part = arduino::String(concentration);
    particleAmount = "          Particle count: \n" + '\n' + arduino::String(concentration) + '\n';


    lowpulseoccupancy = 0;
    starttime = millis();
}