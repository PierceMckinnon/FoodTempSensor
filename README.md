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
  
[This](https://github.com/PierceMckinnon/FoodTempSensor/tree/master/Core) is the core code
## Step 1: Setting up the thermistor
The thermistor resistance value changes with temperature and so I used a simple voltage divider circuit to determine the resistance of the unit.
- 3.3-IR1-IR2=0
- V-IR2 =0
- I= V/R2
- 3.3-(V/R2)*R1-V=0
- (-V+3.3)*R2/V=R1
This can then be used together with the Steinhart and Hart equation to determine temperature. I configured the ADC so that I could get digital values to be used in the equation.
To print the temperature onto the LCD I made a custom float to char function.

## Step 2: Configuring the accelerometer
Configuring the accelerometer involved a lot of reading the datasheet to figure out what registers I needed.
    
## Step 3: Design a custom PCB and 3D print a unit to contain the device
To be completed 
  
