# Year 1: Air Quality Detector
It is reccomended to view this readme in either visual studio code's preview mode, or
on this project's github repository at: 

https://github.com/JackPearsonAtUAL/year1-AirQualityDetector
## Disclaimer
AI has not been used in any part of this project's development or design process.
## Original Component List
    Arduino Wifi R4

    Mikroe Air Quality Click

    Grove Dust Sensor PPD42

    Breadboard

    LCD Screen Nokia 5110 

## Component List at End of Project
    Arduino Nano

    Mikroe Air Quality Click

    Grove Dust Sensor PPD42

    Breadboard

    OLED 0.96" Screen   

## Language
    C++
## Libraries / Packages
    Arduino UNO R4 Boards
    Arduino SAMD Boards (32-bits arm cortex-m0+)
    MQ135_XCR
    Adafruit SSD1306

## Images / Video
    year1-AirQualityDetector/supplementaries
## MoSCoW Method
### Must have
RGB LED to show the air quality</br>
Gas sensor </br>
Particle count sensor
### Should have
Casing <br>
A way to turn it on and off
### Could have
GPS and internet connectivity to update local air quality records</br>
Screen to display data</br>
Internal power source
### Won't have
Tracking capability</br>
Communication features

## Development Process
### Hardware
1. **Integrating the Air Quality Click**</br>
    The first step in making this device was setting up the Air Quality Click sensor.
    When looking at how to implement this sensor, I used the doccumentation from MIKROE on which pins went where. You can see what it looked like in `hardware_stage_1.jpg`. 
2. **Integrating the Dust Sensor**</br>
    Moving onto the other core sonsor, the PPD42 grove dust sensor. While it is called
    a dust sensor, it actually identifies any particulate witha diameter >= 1μm. Now as this is a rntal piece, the University had kitted it out with a 4 pin JST conncetor.
    This made my plans slightly harder, as the pins now need to connect to the JST, making a absurdly long cable connection. You can see how I've set up the sensor in `hardware_stage_2.jpg`
3. **The change from Arduino Wifi R4 to and Arduino Nano**</br>
    It was at this point that I realised the Wifi R4 board was simply too large for 
    the project. Therefore, I looked though the university's parts catalogue and found
4. **Integrating the Screen**</br>

### Programming
1. **Initial sensor: Air Quality Click**</br>
2. **Initial output: LED**</br>
3. **Second sensor: Dust Sensor**</br>
4. **Change of output: LED to text on screen**</br>

## Personal Thoughts
For this porject, I chose to make a product for the uncertain future. From the get go, I knew exactly what I wanted to do; an air quality sensor. 
Back during the first few week, we had a group task to design a product using a specific sensor or actuator. My group was given a toxic gas sensor,
which we used in our design for an air quality sensor. Originally, the project would've only used toxic gas levels in the air, then emmiting a bird 
chip, which gets louder the cleaner the air is. Howevery I chose to change this to a screen, which displays the gas and dust count. 
My reasoning for this is that as time goes on the climate is getting worse. There's more harmful gasses in the air and far more polluting particulates. 

Therefore, this is the project I wanted to make: </br>
A hand heald air quality sensor, 
which takes into account pair particulates and harful gasses
whilst being no bigger than a modern phone.



