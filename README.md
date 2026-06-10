# Year 1: Air Quality Detector 
It is recommended to view this readme in either visual studio code's preview mode, or 
on this project's GitHub repository at:     
https://github.com/JackPearsonAtUAL/year1-AirQualityDetector 

## Disclaimer 
AI has not been used in any part of this project's development or design process. 

## Component List at End of Project 
    Arduino Nano 

    MIKROE Air Quality Click 

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

### Should have 
Casing </br> 
A way to turn it on and off 

### Could have 
GPS and internet connectivity to update local air quality records</br> 
Screen instead of LED to display data</br> 
Internal power source 

### Won't have 
Tracking capability</br> 
Communication features 


## Development Process 

### Hardware 

1. **Integrating the Air Quality Click**</br> 
    The first step in making this device was setting up the Air Quality Click sensor. 
    When looking at how to implement this sensor, I used the documentation from MIKROE on which pins went where. 
    You can see what it looked like in `supplementaries\hardware_stage_1.jpg`. 

    Originally, I had it plumed into the 3.3V connection, however later I had to change it to a 5V connection.  

2. **Integrating the Dust Sensor**</br> 
    Moving onto the other core sensor, the PPD42NS Grove Dust Sensor. While it is called
    a dust sensor, it identifies any particulate with a diameter >= 1μm. 
    Now as this is a rental piece, the University had previously kitted it out with a 4 pin JST connector. 
    This made my plans slightly harder, as the pins now need to connect to the JST, making an absurdly long cable connection.  

    You can see how I have set up the sensor in `supplementaries\hardware_stage_2.jpg`. 

3. **The change from Arduino Wifi R4 to and Arduino Nano**</br> 

    It was at this point that I realised the Wifi R4 board was simply too large for the project. 
    Therefore, I looked though the university's parts catalogue and found an Arduino Nano board. 
    The Nano had another feature which really helped with my project; it connects directly into the breadboards.  
    However, there was a slight issue with the Nano board; it has no 3.3VB output.  
    Luckily, the Air Quality Click has a 5V input so, I rearranged the cables to make it work. 
    Another advantage of using the Nano board is that you can get between 2 and 4 pins connected to it in each socket.  
    This made it so much easier to work with, especially considering I had a limited number of cables. 
    With all that in mind, I would say that switching to the Nano Board was the right choice.
    The hardware, post integration of the Nano can be found in `supplementaries\hardware_stage_3.jpg` 

4. **Integrating the Screen instead of LEDs**</br> 

    Firstly, I should explain the change of actuator. 
    While I originally wanted to Use LEDs, I realised that they were not the best for accurate data readings. 
    That is why I chose to switch over to a screen instead. 

    This is the part which gave me the most issues. 
    Originally, I was going to be using a Nokia screen.
    Unfortunately, the university kit labs did not have any in stock therefore, I went for the next best option: a 0.96" OLED. 
    This miniature OLED works quite well for the project. 
    My only complaint is that the one I was damaged, prior to me getting it. 
    That is why there are some noticeable black lines in parts of the output.
    The only major issue I ran into while using the screen is that one of the inputs on the chip is labelled SCK.
    That does not seem like an issue, until you look at the boards build.
    It needs an SCL input, not an SCK, which I learnt the hard way.
    When I initially used the SCK on the Nano, the entire device crashed.

    The circuit containing the screen can be seen in `supplementaries\hardware_stage_4.jpg` 

 

### Programming 

1. **Air Quality Click**</br> 
    To program the Air Quality Click's functionality, I used the `MQ135_XCR`'s test project code as a basis for getting the gas percentile. 
    At first, I was worried the code did not work, or that it had short circuited. 
    When booting up, it runs the calibrate () method, which is quite slow.

2. **Dust Sensor**</br> 
    The Dust Sensor, while an older model, did have some documentation to use.
    Grove specifically made an article on their site, dedicated to this sensor.
    You can view the entire thing here: https://wiki.seeedstudio.com/Grove-Dust_Sensor/ . 
    For the code, it was a case of copying the parts which I need, which was honestly most. 
    It did take some time to understand the difference between the Low Pulse Occupancy, ratio, and concentration, but I got there in the end.
    For the output I am specifically using the concentration, as it is the result of the former two values. 

3. **OLED Screen**</br> 
    The OLED screen was by far the part where I had the most trouble. 
    This was purely because I had no manufacturer or model to research. 
    It did take a bit to find the right make, that being the SSD1306 128x64. 
    Once I had this finding the library for it would be simple. 
    Luckily, the library came with a package specifically for this screen. 
    I extracted parts of the code from the example and added them to my own. 
    This is also where I modified how the outputs are handled by saving the two sensor's outputs as stings, to concatenated together and sent to the screen. 

    An example video of what it looks like can be viewed at `supplementaries\air-quality-sensor-demo.mp4` 

## Development Story 
For this project, I chose to make a product for the uncertain future. From the get-go, I knew exactly what I wanted to do; an air quality sensor. Back during the first few week, we had a group task to design a product using a specific sensor or actuator. My group was given a toxic gas sensor, which we used in our design for an air quality sensor. Originally, the project would've only used toxic gas levels in the air, then emitting a bird chirp, which gets louder the cleaner the air is. However, I chose to change this to an RGB LED, as the bird chirping would be annoying and be muffled by local noise pollution. 

Therefore, this is the project I wanted to make: </br> 
A handheld air quality sensor,  
which considers air particulates and harmful gasses 
whilst being no bigger than a modern phone. </br></br>

The first variation's output used a single RGB LED, going from green (good air quality) to red (bad air quality), scaling based on the data from the Air Quality Click. However, when I was pondering what constituted air quality, I realised that I had forgotten about air particulates.  

After looking at the University's catalogue of parts for a dust sensor, I found the Grove PPD42NS Dust Sensor. Now I could use another LED to output the value of the sensor, however there is an issue with that. As of this project there is no definitive "safe" amount of air particulates. This means that if I want to give the user the quantity of dust particulates in the air, I need a better output system. This is where I decided to switch from the LED to a more detailed screen. This allows the device to output several pieces of data like, the volume of toxic gas; whether that amount of gas is safe; and the concentration of particles in the air per minute. 

Initially for the screen I wanted to use a Nokia 5110 LCD however, there were none in stock at the university and I did not want to have to buy parts for a one-time project. Therefore, I changed the screen type to a 0.96" OLED. Changing the type of screen also meant that the connections would change, which worked in my favour, as the Nokia LCD needed 8 inputs, whereas the OLED only needs 4. It also helps to streamline the hardware, as it is far smaller. 

Moving onto the casing, I initially wanted to 3D print it. However, it was brought to my attention that the university had a laser cuter and that I could use wood or thick card and burn a design onto it instead. I could not get a casing made to display, as the tutorial sessions for the printers, laser cutter and woodworking ended a while age. 

However, inside supplementaries, you can find two variations of my sketch. One has just the design (`supplementaries\2d-sketch`), whilst the other includes the holes for the components' sensors(`supplementaries\2d-sketch-with-cutouts.jpg`). I also designed a PCB to use for the device, seen in `supplementaries\air-quality-sensor-pcb.png` 

Now onto the final part of this writeup, the reflection on user experience and any improvements that could be made. Overall, this device is quite easy to use. The only inputs the user needs to do is give it power and air flow. I briefly mentioned beforehand about an internal battery to power the device. If this project were to be commercially produced, I would certainly use a rechargeable battery, with an on/off switch, rather than having to plug the device into a power source. 

As mentioned in the video, the dust sensor does not detect much when the air is static. For a good dust reading you need to be outside with some air flow. Like in the video, with this iteration there is no inbuilt fan, however in a completed device there would be some sort of fan or piece of hardware to make airflow. 

 
