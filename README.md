# BusRepeater_NXP_Arduino
I2C bus-repeater device evaluation board sample code for [Arduino](https://www.arduino.cc) 

> **Note**
This library works with [`I2C_device`](https://github.com/teddokano/I2C_device_Arduino) and [MUX_SW_NXP_Arduino](https://github.com/teddokano/MUX_SW_NXP_Arduino) libraries together. Please be sure both libraries are imported in your environment before trying to build. 

![Boards](https://github.com/teddokano/additional_files/blob/main/BusRepeater_NXP_Arduino/board.jpg)  
_PCA9617ADP-ARD : Arduino® Shield Evaluation Board for I²C bus repeater_  
_Oscilloscope probes are on J18 (A-side of DUT, voltage is controled by LDO1) and J15 (B-side, LDO2) jumper pins to monitor I²C signal voltage_

## What is this?
An Arduino demo code for I2C bus-repeater device evaluation board.  
This demo code shows PCA9617A operation with changing two I²C signal voltages.  
The two voltages are supplied from LDOs on the board. This sample code controls those LDOs via GPIO pins.  
An EEPROM:M24C02 is on the board. The sample code communicats with the EEPROM to show its waveform.  
Use an oscilloscope to find voltage/waveform on the board. 

## Supported board
Type#|Features|Interface|Evaluation board
---|---|---|---
[PCA9617A](https://www.nxp.com/products/interfaces/ic-spi-i3c-interface-devices/ic-bus-repeaters-hubs-extenders/level-translating-fm-plus-ic-bus-repeater:PCA9617A)	|Level Translating Fm+ I²C-Bus Repeater	|I²C Fast-mode Plus (1MHz)			|[PCA9617ADP-ARD Arduino Shield Level Translating Fm+ I2C-Bus Repeater Evaluation Board](https://www.nxp.com/design/design-center/development-boards/analog-toolbox/arduino-shields-solutions/pca9617adp-ard-arduino-shield-level-translating-fm-plus-ic-bus-repeater-evaluation-board:PCA9617ADP-ARD)

# Getting started

Use Library manager in Arduino IDE for easy install

# What's inside?

## No class library
Since the PCA9617A is an I²C bus repeater, no sofware control is needed.  
So, this repository is **NOT** containing `PCA9617A` class library but just a sample demo code.  

## Examples
Examples are provided as scketch files.

### How to use?

After library install, Choose menu on Arduino-IDE: `File`→`Examples`→`BusRepeater_NXP_Arduino`→ PCA9617ADP-ARD_demo

### The demo code

On **Arduino Uno R3** ...
When the program is started, **messages** are appeared on terminal screen at **begining only**.  
**While the demo running, no screen update will be done** because LDO2 control line is shared with `Serial.print()` feature on Arduino SDK. 
<U>To perform output all voltage variation on LDO2, the screen message needed to be disabled.</U>  
While the demo, prove on the signal lines and monitor the waveform on an oscilloscope.  

On **Arduino Uno R4**, such restriction does not exist.  
The messages will be shown on the screen.  

LDO1 and LDO2 can output several voltages. LDO1 voltage becomes the signal voltage on A-side of DUT and LDO2 voltage becomes B-side one.  
- LDO1 (A-side, I²C signals on J18) output can be set 0.8V, 1.8V, 2.5V, 3.3V and 4.96V.  
- LDO2 (B-side, I²C signals on J15) output can be set 2.5V, 3.0V, 3.3V and 4.96V.   

The demo performs I²C comunication with all convination of two LDO output except condition of "LDO1=4.96 and LDO2=2.5V". This is not allowed convination (see datasheet Table 5, note \[2\]), this is prevented on board hardware mechanism (see `INTER_LOCK` signal on schematic diagram).  

User can set to show messages while the demo by disabling `ENABLE_FULL_LDO2_VOLTAGE_VARIATION` option (comment-out the line of this word definition). It will show some information on the screen but the voltage on LDO2 will be repeated in "3.3V, 4.96V, 3.3V, 4.96V" pattern.  

Followings are waveform. Both are SCL line voltage, ch1 (yellow) is A-side and ch2 (blue) is B-side.  
All LDO2 output tried at one LDO1 output level. 
Negative spikes are I²C communication which is done after 1 second from each voltage setting completed.  
![Waveforms](https://github.com/teddokano/additional_files/blob/main/BusRepeater_NXP_Arduino/waveform0.png)  

Next picture is same as above but `#define ENABLE_FULL_LDO2_VOLTAGE_VARIATION` was commented-out.  
![Waveforms](https://github.com/teddokano/additional_files/blob/main/BusRepeater_NXP_Arduino/waveform1.png)  

## Related libraries
Library|Feature|Target devices|Required library
---|---|---|---
[GPIO_NXP_Arduino](https://github.com/teddokano/GPIO_NXP_Arduino)				|GPIO libraries						|PCAL6408A, PCAL6416A, PCAL6524, PCAL6534, PCA9555, PCA9554	|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[LCDDriver_NXP_Arduino](https://github.com/teddokano/LCDDriver_NXP_Arduino)		|LCD driver libraries				|PCA8561						|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[LEDDriver_NXP_Arduino](https://github.com/teddokano/LEDDriver_NXP_Arduino)		|LED driver libraries				|PCA9955B, PCA9956B, PCA9957	|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[MUX_SW_NXP_Arduino](https://github.com/teddokano/MUX_SW_NXP_Arduino)			|I²C mux/switch libraries			|PCA9846						|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[RTC_NXP_Arduino](https://github.com/teddokano/RTC_NXP_Arduino)					|RTC libraries						|PCF2131, PCF85063A				|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[TempSensor_NXP_Arduino](https://github.com/teddokano/TempSensor_NXP_Arduino)	|Temperature sensor libraries		|LM75B, PCT2075, P3T1085		|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)			|Base library for I²C operations	|none (can be applied as base class for all I²C targets)|---
