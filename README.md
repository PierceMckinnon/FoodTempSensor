# FoodTempSensor

The intention of this project is to create a digital food thermometer as I am starting to cook more.
I used a thermistor to detect temperature, and this temperature is then displayed on an LCD. 
To learn I2C I incorperated an acceleromter which will be attached to the LCD so the screen adjusts if I flip it around.
Learning outcomes of this project so far:
- How to effectively read datasheets
- How to configure a makefile with make 
- How to configure STM32 peripherals using STM32HAL
- How to setup I2C communication with STM32HAL
- How to set up interrupts over EXTI lines
- How to debug effectively 
- How to use the STM32CubeMX tool
- How to use a logic analyzer to debug communication lines
  
[This](https://github.com/PierceMckinnon/FoodTempSensor/tree/master/Core) is the core code
## Step 1: Setting up the thermistor
The thermistor resistance value changes with temperature and so I used a simple voltage divider circuit to determine the resistance of the unit.
- 3.3-IR1-IR2=0
- V-IR2 =0
- I= V/R2
- 3.3-(V/R2)*R1-V=0
- (-V+3.3)*R2/V=R1
This can then be used together with the Steinhart and Hart equation to determine temperature. I configured the ADC so that I could get digital values to be used in the equation.
To print the temperature onto the LCD I made a custom float to char function. I found the temperature to be accurate to +-1 degree Celcius at room temperature. Unfortunately, the thermistor cannot be used to penetrate meat such as chicken to determine the internal temperature. The meat must be cut open which results in some heat loss but it still provides a reasonable estimate.

![](https://raw.githubusercontent.com/PierceMckinnon/FoodTempSensor/master/Images/Temperature%20Working.PNG)
## Step 2: Configuring the accelerometer
Configuring the accelerometer involved a lot of reading the datasheet to figure out what registers I needed. I chose to include an accelerometer so that the LCD screen would rotate when the user rotates the physical device. When the accelerometers arrived I soldered on some pin headers and got to work.

![](https://raw.githubusercontent.com/PierceMckinnon/FoodTempSensor/master/Images/Accelerometer.PNG)

I wanted the LCD to respond immediately to rotation so I configured the accelerometer with interrupts. On every data ready signal an interrupt occurs and I check the rotation of the accelerometer which would be attached to the LCD. I was having some trouble debugging the I2C bus so I bought a logic analyzer.

![](https://raw.githubusercontent.com/PierceMckinnon/FoodTempSensor/master/Images/Logicanalyzer.png)

Here is the final system. 

![](https://raw.githubusercontent.com/PierceMckinnon/FoodTempSensor/master/Images/System.PNG)
## Step 3: Design a custom PCB and 3D print a unit to contain the device
To be completed 
  
