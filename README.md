# FoodTempSensor

Welcome to my Arduino Door Lock Project!
The intention of this project is to create a digital food thermometer as I am starting to cook more.
I use a thermistor to detect temperature, and this temperature is displayed on an LCD. 
To learn I2C I incorperated an acceleromter which will be attached to the LCD so the screen adjusts if I flip it around.
  
[This](https://github.com/PierceMckinnon/FoodTempSensor/tree/master/Core) is the core code
## Step 1: Setting up the thermistor
To detect when the door was closed I used the HC-SR04 ultrasonic sensor. I placed it a few centimeters from the closed door. When the door is closed the ultrasonic sensor read a distance of about 2.3cm. Thus, I set a threshold of 3cm for the detection of the door. When the sensor goes below this threshold, the lock closed. Below is a picture of the ultrasonic sensor.  
  
![]()   
## Step 2: Configuring the accelerometer
I needed a method to open the lock from inside my room. Using what I had available, I created two different mechanisms. The first is a push button and the second is an IR receiver. Once the IR receiver reads a specific hex value the lock opens. This hex value corresponds with the power button on the IR remote. Below is a picture of the main breadboard.  
    
## Step 3: Design a custom PCB and 3D print a unit to contain the device
To be completed 
  
